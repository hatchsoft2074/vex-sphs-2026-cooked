
#include "main.h"
#include "robotConfigs.h"
#include "opcontrol.h"
#include "lift.h"
#include "scoring.h"
#include "toggles.h"
#include "autonomous.hpp"
#include "mvlib/Optional/lemlib.hpp"
#include "robodash/core.h"
#include "liblvgl/lvgl.h"
#include "image.h"
#include <algorithm>
#include <atomic>
#include <cstdio>
#include <string>

// Old autonomous routines must be updated for the new robot.
rd::Selector selector({
    {"Left Auton", AutonCompLeft},
    {"Right Auton", AutonCompRight},
    {"Skills Auton", AutonSkills}
});

class OdomScreen {
private:
    rd_view_t* view;
    lv_obj_t* label;
    lv_obj_t* image;
    lv_obj_t* warnBar;
    std::string text;

public:
    explicit OdomScreen(const char* name) {
        view = rd_view_create(name);
        lv_obj_t* root = rd_view_obj(view);

        label = lv_label_create(root);
        lv_obj_set_style_text_font(label, &lv_font_montserrat_16, 0);
        lv_obj_set_style_text_color(label, lv_color_white(), 0);
        lv_obj_align(label, LV_ALIGN_TOP_LEFT, 10, 8);
        lv_label_set_text(label, "");

        image = lv_img_create(root);
        lv_img_set_src(image, &image_dsc);
        lv_obj_align(image, LV_ALIGN_BOTTOM_RIGHT, -10, -10);

        warnBar = lv_obj_create(root);
        lv_obj_set_size(warnBar, lv_pct(100), 30);
        lv_obj_align(warnBar, LV_ALIGN_TOP_MID, 0, 0);
        lv_obj_set_style_bg_color(warnBar, lv_color_hex(0xE01010), 0);
        lv_obj_set_style_bg_opa(warnBar, LV_OPA_COVER, 0);
        lv_obj_set_style_border_width(warnBar, 0, 0);
        lv_obj_set_style_radius(warnBar, 0, 0);
        lv_obj_set_style_pad_all(warnBar, 0, 0);
        lv_obj_clear_flag(warnBar, LV_OBJ_FLAG_SCROLLABLE);

        lv_obj_t* warnText = lv_label_create(warnBar);
        lv_obj_set_style_text_font(warnText, &lv_font_montserrat_20, 0);
        lv_obj_set_style_text_color(warnText, lv_color_white(), 0);
        lv_label_set_text(warnText, "Warning: Burnout!");
        lv_obj_center(warnText);

        lv_obj_add_flag(warnBar, LV_OBJ_FLAG_HIDDEN);
    }

    void showWarning(bool on) {
        if (on) {
            lv_obj_clear_flag(warnBar, LV_OBJ_FLAG_HIDDEN);
            lv_obj_move_foreground(warnBar);
            lv_obj_align(label, LV_ALIGN_TOP_LEFT, 10, 36);
        } else {
            lv_obj_add_flag(warnBar, LV_OBJ_FLAG_HIDDEN);
            lv_obj_align(label, LV_ALIGN_TOP_LEFT, 10, 8);
        }
    }

    void clear() {
        text.clear();
    }

    void println(const std::string& line) {
        text += line;
        text += '\n';
    }

    void render() {
        lv_label_set_text(label, text.c_str());
    }

    void focus() {
        rd_view_focus(view);
    }
};

OdomScreen odomScreen("Odometry");

std::atomic<bool> practiceAutonRunning(false);
std::atomic<bool> keepScreenFocus{false};

pros::Task* practiceAutonTask = nullptr;
bool practiceCancelHeld = false;
bool autonConfirmed = false;
std::string selectedAutonName = "Left Auton";

// Stop the drivetrain, cascade, claw, and toggles
void stopPracticeAutonMotors() {
    chassis.cancelAllMotions();
    left_motor_group.move(0);
    right_motor_group.move(0);

    cancelMatchLoad();
    cancelLiftAsync();
    liftStop();
    scoringStop();
    togglesStop();
}

// Clean up a finished practice task
void clearFinishedPracticeTask() {
    if (practiceAutonTask != nullptr && !practiceAutonRunning.load()) {
        practiceAutonTask->remove();
        delete practiceAutonTask;
        practiceAutonTask = nullptr;
    }
}

void startPracticeAuton() {
    if (practiceAutonRunning.load() || !autonConfirmed) {
        return;
    }

    clearFinishedPracticeTask();
    stopPracticeAutonMotors();

    practiceAutonRunning.store(true);

    practiceAutonTask = new pros::Task([]() {
        autonomous();
        stopPracticeAutonMotors();
        practiceAutonRunning.store(false);
    });

    controller.rumble(".");
}

void cancelPracticeAuton() {
    if (!practiceAutonRunning.load()) {
        return;
    }

    if (practiceAutonTask != nullptr) {
        practiceAutonTask->remove();
        delete practiceAutonTask;
        practiceAutonTask = nullptr;
    }

    stopPracticeAutonMotors();
    practiceAutonRunning.store(false);
    keepScreenFocus.store(false);
    controller.rumble("..");
}

// Find the hottest motor in a group
double hottestInGroup(pros::MotorGroup& group) {
    double hottest = 0;

    for (double t : group.get_temperature_all()) {
        if (t > hottest) {
            hottest = t;
        }
    }

    return hottest;
}

constexpr double TEMP_BURNOUT = 55.0;

// Update the brain screen
void updateScreenTask() {
    while (true) {
        if (autonConfirmed) {
            auto pose = chassis.getPose();
            char line[96];

            if (keepScreenFocus.load()) {
                odomScreen.focus();
            }

            odomScreen.clear();

            double dtTemp = std::max(
                hottestInGroup(left_motor_group),
                hottestInGroup(right_motor_group)
            );

            double liftTemp = getLiftTemperature();
            double clawTemp = getScoringTemperature();
            double togglesTemp = getTogglesTemperature();

            odomScreen.showWarning(
                std::max({
                    dtTemp,
                    liftTemp,
                    clawTemp,
                    togglesTemp
                }) >= TEMP_BURNOUT
            );

            std::snprintf(
                line, sizeof(line),
                "X: %.2f Y: %.2f",
                pose.x, pose.y
            );
            odomScreen.println(line);

            std::snprintf(
                line, sizeof(line),
                "Theta: %.2f",
                pose.theta
            );
            odomScreen.println(line);

            std::snprintf(
                line, sizeof(line),
                "Casc Height: %.0f",
                getLiftPosition()
            );
            odomScreen.println(line);

            // Show all four temperatures together
            std::snprintf(
                line, sizeof(line),
                "Temp - DT: %.0f Lift: %.0f Claw: %.0f Tog: %.0f",
                dtTemp, liftTemp, clawTemp, togglesTemp
            );
            odomScreen.println(line);

            odomScreen.println(
                driverMode == COMPETITION ? "Mode: Competition" :
                driverMode == SKILLS ? "Mode: Skills" :
                "Mode: Practice"
            );

            if (driverMode != SKILLS) {
                odomScreen.println("Auton: " + selectedAutonName);
            }

            odomScreen.render();
            pros::delay(250);
        } else {
            pros::delay(50);
        }
    }
}

// Wait for a new screen touch
void waitForTouchRelease() {
    while (true) {
        auto touch = pros::screen::touch_status();

        if (touch.touch_status != pros::E_TOUCH_PRESSED &&
            touch.touch_status != pros::E_TOUCH_HELD) {
            break;
        }

        pros::delay(20);
    }
}

// Select Competition, Skills, or Practice
void selectDriverMode() {
    pros::screen::erase();
    pros::screen::print(
        pros::E_TEXT_MEDIUM, 20, 20, "DRIVER MODE"
    );

    pros::screen::fill_rect(40, 50, 440, 100);
    pros::screen::print(
        pros::E_TEXT_MEDIUM, 150, 65, "COMPETITION"
    );

    pros::screen::fill_rect(40, 115, 440, 165);
    pros::screen::print(
        pros::E_TEXT_MEDIUM, 190, 130, "SKILLS"
    );

    pros::screen::fill_rect(40, 180, 440, 230);
    pros::screen::print(
        pros::E_TEXT_MEDIUM, 185, 195, "PRACTICE"
    );

    waitForTouchRelease();

    while (true) {
        auto touch = pros::screen::touch_status();

        if (touch.touch_status == pros::E_TOUCH_PRESSED &&
            touch.x >= 40 && touch.x <= 440) {

            if (touch.y >= 50 && touch.y <= 100) {
                driverMode = COMPETITION;
                break;
            }

            if (touch.y >= 115 && touch.y <= 165) {
                driverMode = SKILLS;
                break;
            }

            if (touch.y >= 180 && touch.y <= 230) {
                driverMode = PRACTICE;
                break;
            }
        }

        pros::delay(20);
    }
}

// Select an autonomous routine
void selectAutonomous() {
    selector.focus();

    while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        pros::delay(20);
    }

    while (true) {
        auto chosen = selector.get_auton();

        if (chosen.has_value() &&
            controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {

            selectedAutonName = chosen->name;
            autonConfirmed = true;
            controller.rumble(".");
            break;
        }

        pros::delay(20);
    }
}

// Confirm Skills mode
void confirmSkills() {
    odomScreen.focus();
    odomScreen.clear();
    odomScreen.println("Skills ready - press A");
    odomScreen.render();

    while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        pros::delay(20);
    }

    while (!controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        pros::delay(20);
    }

    autonConfirmed = true;
    controller.rumble(".");
}

// Set up MVLib logging
void setupWatches(mvlib::Logger& logger) {
    logger.watch(
        "Cascade Height",
        LogLevel::INFO,
        WatchMode::onInterval,
        150_mvMs,
        []() { return getLiftPosition(); }
    );

    logger.watch(
        "Cascade Temp",
        LogLevel::INFO,
        WatchMode::onInterval,
        2_mvS,
        []() { return getLiftTemperature(); },
        mvlib::LevelOverride<double>{
            .elevatedLevel = LogLevel::WARN,
            .predicate = mvlib::asPredicate<double>(
                [](const double& t) {
                    return t > 50.0;
                }
            ),
            .label = "Cascade Temp HOT"
        }
    );

    logger.watch(
        "Claw Temp",
        LogLevel::INFO,
        WatchMode::onInterval,
        2_mvS,
        []() { return getScoringTemperature(); },
        mvlib::LevelOverride<double>{
            .elevatedLevel = LogLevel::WARN,
            .predicate = mvlib::asPredicate<double>(
                [](const double& t) {
                    return t > 50.0;
                }
            ),
            .label = "Claw Temp HOT"
        }
    );

    logger.watch(
        "Toggles Temp",
        LogLevel::INFO,
        WatchMode::onInterval,
        2_mvS,
        []() { return getTogglesTemperature(); },
        mvlib::LevelOverride<double>{
            .elevatedLevel = LogLevel::WARN,
            .predicate = mvlib::asPredicate<double>(
                [](const double& t) {
                    return t > 50.0;
                }
            ),
            .label = "Toggles Temp HOT"
        }
    );

    logger.watch(
        "Match Load Moving",
        LogLevel::INFO,
        WatchMode::onChange,
        100_mvMs,
        []() { return isMatchLoadMoving(); }
    );

    logger.watch(
        "Practice Auton Run",
        LogLevel::INFO,
        WatchMode::onChange,
        100_mvMs,
        []() { return practiceAutonRunning.load(); }
    );

    logger.watch(
        "Driver Mode",
        LogLevel::INFO,
        WatchMode::onChange,
        250_mvMs,
        []() {
            return static_cast<int>(driverMode);
        }
    );
}

void initialize() {
    auto& logger = mvlib::Logger::getInstance();

    logger.setRobot({
        .leftDrivetrain = &left_motor_group,
        .rightDrivetrain = &right_motor_group
    });

    chassis.calibrate();
    mvlib::setOdom(&chassis);

    setupWatches(logger);
    logger.start();

    liftSetup();
    scoringSetup();
    togglesSetup();

    selectDriverMode();

    if (driverMode == COMPETITION ||
        driverMode == PRACTICE) {
        selectAutonomous();
    } else {
        confirmSkills();
    }

    odomScreen.focus();
    pros::Task screen_task(updateScreenTask);
}

void disabled() {
    if (practiceAutonRunning.load()) {
        cancelPracticeAuton();
    }

    scoringStop();
    togglesStop();
}

void competition_initialize() {
}

// Run the selected autonomous
void autonomous() {
if (selectedAutonName == "Left Auton") {
AutonCompLeft();
} else if (selectedAutonName == "Right Auton") {
AutonCompRight();
} else if (selectedAutonName == "Skills Auton") {
AutonSkills();
}

// Stop all motors when autonomous finishes
stopPracticeAutonMotors();
}

void opcontrol() {
    keepScreenFocus.store(false);
    odomScreen.focus();

    while (true) {
        if (driverMode == PRACTICE) {
            bool yPressed = controller.get_digital_new_press(
                pros::E_CONTROLLER_DIGITAL_Y
            );

            bool rightHeld = controller.get_digital(
                pros::E_CONTROLLER_DIGITAL_RIGHT
            );

            if (rightHeld &&
                !practiceCancelHeld &&
                practiceAutonRunning.load()) {
                cancelPracticeAuton();
            }

            practiceCancelHeld = rightHeld;

            if (practiceAutonRunning.load()) {
                pros::delay(10);
                continue;
            }

            clearFinishedPracticeTask();

            if (yPressed && !rightHeld) {
                startPracticeAuton();
                pros::delay(10);
                continue;
            }
        }

        if (driverMode == COMPETITION) {
            competitionDriver();
        } else if (driverMode == SKILLS) {
            skillsDriver();
        } else {
            practiceDriver();
        }

        pros::delay(10);
    }
}
