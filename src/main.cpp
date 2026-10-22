
#include "main.h"
#include "robotConfigs.h"
#include "opControl.h"
#include "lift.h"
#include "intake.h"
#include "scoring.h"
#include "scoringMacro.h"
#include "autonomous.hpp"

#include <atomic>

//Selectors 
rd::Selector selector({
    {"Left Auton", AutonCompLeft},
    {"Right Auton", AutonCompRight},
    {"Competition", competitionDriver},
    {"Skills", skillsDriver},
    {"Practice", practiceDriver}
});

// Tracks the practice autonomous
std::atomic<bool> practiceAutonRunning(false);
pros::Task* practiceAutonTask = nullptr;

bool practiceCancelHeld = false;

// Stops the robot's motors
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

// Starts autonomous for practice
void startPracticeAuton() {
    if (practiceAutonRunning.load()) {
        return;
    }

    if (practiceAutonTask != nullptr) {
        practiceAutonTask->remove();
        delete practiceAutonTask;
        practiceAutonTask = nullptr;
    }

    stopPracticeAutonMotors();

    practiceAutonRunning.store(true);

    practiceAutonTask = new pros::Task([]() {
        autonomous();

        stopPracticeAutonMotors();
        practiceAutonRunning.store(false);
    });

    controller.rumble(".");
}

// Cancels practice autonomous
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
    controller.rumble("..");
}

// Displays the robot's position
void updateScreenTask() {
    while (true) {
        pros::lcd::print(0, "X: %f", chassis.getPose().x);
        pros::lcd::print(1, "Y: %f", chassis.getPose().y);
        pros::lcd::print(2, "Theta: %f", chassis.getPose().theta);
        pros::delay(50);
    }
}

// Lets the driver select a mode
void selectDriverMode() {
    pros::screen::erase();
    pros::screen::print(pros::E_TEXT_MEDIUM, 20, 30, "DRIVER MODE");

    // Competition button
    pros::screen::fill_rect(40, 50, 440, 100);
    pros::screen::print(pros::E_TEXT_MEDIUM, 150, 65, "COMPETITION");

    // Skills button
    pros::screen::fill_rect(40, 115, 440, 165);
    pros::screen::print(pros::E_TEXT_MEDIUM, 190, 130, "SKILLS");

    // Practice button
    pros::screen::fill_rect(40, 180, 440, 230);
    pros::screen::print(pros::E_TEXT_MEDIUM, 185, 195, "PRACTICE");

    while (true) {
        auto status = pros::screen::touch_status();

        if (status.touch_status == pros::E_TOUCH_PRESSED) {
            if (status.x >= 40 && status.x <= 440 &&
                status.y >= 50 && status.y <= 100) {
                driverMode = COMPETITION;
                break;
            }

            if (status.x >= 40 && status.x <= 440 &&
                status.y >= 115 && status.y <= 165) {
                driverMode = SKILLS;
                break;
            }

            if (status.x >= 40 && status.x <= 440 &&
                status.y >= 180 && status.y <= 230) {
                driverMode = PRACTICE;
                break;
            }
        }

        pros::delay(20);
    }

    pros::screen::erase();

    if (driverMode == COMPETITION) {
        pros::screen::print(
            pros::E_TEXT_MEDIUM, 20, 30,
            "COMPETITION SELECTED"
        );
    } else if (driverMode == SKILLS) {
        pros::screen::print(
            pros::E_TEXT_MEDIUM, 20, 30,
            "SKILLS SELECTED"
        );
    } else {
        pros::screen::print(
            pros::E_TEXT_MEDIUM, 20, 30,
            "PRACTICE SELECTED"
        );
    }

    pros::delay(1000);
}

// Sets up the robot when the program starts
void initialize() {
    pros::lcd::initialize();

    chassis.calibrate();

    // The lift starts at zero
    // The scoring mechanism starts fully folded
    liftSetup();
    intakeSetup();
    scoringSetup();

    selectDriverMode();

    pros::Task screen_task(updateScreenTask);
}

// Runs when the robot is disabled
void disabled() {
    if (practiceAutonRunning.load()) {
        cancelPracticeAuton();
    }
}

// Runs before competition autonomous
void competition_initialize() {

}

// Runs the competition autonomous
void autonomous() {
    if (/* left auton */) {
        chassis.setPose(0, 62.75, 0);
        AutonCompLeft();
    }
    else (/* right auton */) {
        chassis.setPose(62.824, 0.043, 90);
        AutonCompRight();
    }
}

// Runs driver controls
void opcontrol() {
    while (true) {

        // Practice mode autonomous controls
        if (driverMode == PRACTICE) {
            bool yPressed = controller.get_digital_new_press(
                pros::E_CONTROLLER_DIGITAL_Y
            );

            bool xHeld = controller.get_digital(
                pros::E_CONTROLLER_DIGITAL_X
            );

            bool upHeld = controller.get_digital(
                pros::E_CONTROLLER_DIGITAL_UP
            );

            bool cancelPressed = xHeld && upHeld;

            // X and Up cancels autonomous
            if (cancelPressed && !practiceCancelHeld) {
                cancelPracticeAuton();
            }

            // Y starts autonomous with one press
            if (yPressed &&
                !cancelPressed &&
                !practiceAutonRunning.load()) {
                startPracticeAuton();
            }

            practiceCancelHeld = cancelPressed;

            // Stop normal driver controls while autonomous runs
            if (practiceAutonRunning.load()) {
                pros::delay(10);
                continue;
            }
        }

        // Run the selected driver controls
        if (driverMode == COMPETITION) {
            competitionDriver();
        }
        else if (driverMode == SKILLS) {
            skillsDriver();
        }
        else {
            practiceDriver();
        }

        pros::delay(10);
    }
}
