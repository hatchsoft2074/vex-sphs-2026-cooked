
#include "main.h"
#include "robotConfigs.h"
#include "opControl.h"
#include "lift.h"
#include "intake.h"
#include "scoring.h"
#include "scoringMacro.h"
#include "autonomous.hpp"
#include "mvlib/Optional/lemlib.hpp"
#define MVLIB_USE_SIMPLES
#include "mvlib/api.hpp"
#include <atomic>
#include <cstdio>
#include <string>

// RoboDash selects autonomous routines for Competition and Practice.
rd::Selector selector({
    {"Left Auton", AutonCompLeft},
    {"Right Auton", AutonCompRight},
    {"Skills Auton", AutonSkills}
});

// Use RoboDash for the odometry screen too.
rd::Console odomScreen("Odometry");

std::atomic<bool> practiceAutonRunning(false);
pros::Task* practiceAutonTask = nullptr;
bool practiceCancelHeld = false;
bool autonConfirmed = false;
std::string selectedAutonName = "Left Auton";

// Stops motion and motors used by the autonomous routines.
void stopPracticeAutonMotors() {
    chassis.cancelAllMotions();
    left_motor_group.move(0);
    right_motor_group.move(0);

    cancelMatchLoad();
    cancelScoringAuto();

    liftStop();
    scoringMechStop();
    scoringWheelsStop();
    intakeStop();
}

// Clean up an old practice task after it finishes.
void clearFinishedPracticeTask() {
    if (practiceAutonTask != nullptr && !practiceAutonRunning.load()) {
        practiceAutonTask->remove();
        delete practiceAutonTask;
        practiceAutonTask = nullptr;
    }
}

void startPracticeAuton() {
    if (practiceAutonRunning.load() || !autonConfirmed) return;

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
    if (!practiceAutonRunning.load()) return;

    // Remove the running task before stopping the motors.
    if (practiceAutonTask != nullptr) {
        practiceAutonTask->remove();
        delete practiceAutonTask;
        practiceAutonTask = nullptr;
    }

    stopPracticeAutonMotors();
    practiceAutonRunning.store(false);
    controller.rumble("..");
}

// The odometry screen stays visible after selection.
void updateScreenTask() {
    while (true) {
        if (autonConfirmed || driverMode == SKILLS) {
            auto pose = chassis.getPose();
            char line[96];
            odomScreen.clear();
            std::snprintf(line, sizeof(line), "X: %.2f", pose.x);
            odomScreen.println(line);
            std::snprintf(line, sizeof(line), "Y: %.2f", pose.y);
            odomScreen.println(line);
            std::snprintf(line, sizeof(line), "Theta: %.2f", pose.theta);
            odomScreen.println(line);
            odomScreen.println(driverMode == COMPETITION ? "Mode: Competition" :
                               driverMode == SKILLS ? "Mode: Skills" : "Mode: Practice");
            if (driverMode != SKILLS) {
                odomScreen.println("Auton: " + selectedAutonName);
            }
            pros::delay(250);
        } else {
            pros::delay(50);
        }
    }
}

// Wait for a fresh screen touch, not the previous button press.
void waitForTouchRelease() {
    while (true) {
        auto touch = pros::screen::touch_status();
        if (touch.touch_status != pros::E_TOUCH_PRESSED &&
            touch.touch_status != pros::E_TOUCH_HELD) break;
        pros::delay(20);
    }
}

void selectDriverMode() {
    pros::screen::erase();
    pros::screen::print(pros::E_TEXT_MEDIUM, 20, 20, "DRIVER MODE");

    pros::screen::fill_rect(40, 50, 440, 100);
    pros::screen::print(pros::E_TEXT_MEDIUM, 150, 65, "COMPETITION");

    pros::screen::fill_rect(40, 115, 440, 165);
    pros::screen::print(pros::E_TEXT_MEDIUM, 190, 130, "SKILLS");

    pros::screen::fill_rect(40, 180, 440, 230);
    pros::screen::print(pros::E_TEXT_MEDIUM, 185, 195, "PRACTICE");

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

// RoboDash handles the selection. A on the controller confirms it.
void selectAutonomous() {
    selector.focus();

    // Do not accept an A press held from before selection.
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

// Skills has no selector, so A on the controller confirms the setup.
void confirmSkills() {
    odomScreen.focus();
    odomScreen.println("Skills ready - press A");

    // Ignore an A press held from before this point.
    while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        pros::delay(20);
    }

    while (!controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        pros::delay(20);
    }

    autonConfirmed = true;
    controller.rumble(".");
}

void initialize() {
    // Do not initialize pros::lcd because RoboDash owns the display.
    auto& logger = mvlib::Logger::getInstance();
    logger.setRobot({
        .leftDrivetrain = &left_motor_group,
        .rightDrivetrain = &right_motor_group
    });
    chassis.calibrate();
    mvlib::setOdom(&chassis);
    logger.start();

    liftSetup();
    intakeSetup();
    scoringSetup();

    selectDriverMode();

    if (driverMode == COMPETITION || driverMode == PRACTICE) {
        selectAutonomous();
    } else if (driverMode == SKILLS) {
        confirmSkills();
    }

    odomScreen.focus();
    pros::Task screen_task(updateScreenTask);
}

void disabled() {
    if (practiceAutonRunning.load()) cancelPracticeAuton();
}

void competition_initialize() {
    // Autonomous is already selected before the match.
}

void autonomous() {
    if (driverMode == SKILLS) {
        AutonSkills();            // Skills profile: comp switch runs skills
    } else {
        selector.run_auton();     // Competition and Practice: whatever was picked
    }
}

void opcontrol() {
    while (true) {
        if (driverMode == PRACTICE) {
            bool yPressed = controller.get_digital_new_press(
                pros::E_CONTROLLER_DIGITAL_Y);
            bool rightHeld = controller.get_digital(
                pros::E_CONTROLLER_DIGITAL_RIGHT);

            // Right arrow cancels a running practice autonomous.
            if (rightHeld && !practiceCancelHeld &&
                practiceAutonRunning.load()) {
                cancelPracticeAuton();
            }
            practiceCancelHeld = rightHeld;

            if (practiceAutonRunning.load()) {
                pros::delay(10);
                continue;
            }

            clearFinishedPracticeTask();

            // Y starts the selected autonomous once.
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