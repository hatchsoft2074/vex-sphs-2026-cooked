
#include "main.h"
#include "opcontrol.h"
#include "robotConfigs.h"
#include "lift.h"
#include "scoring.h"
#include <algorithm>

// Driver curve settings
lemlib::ExpoDriveCurve throttle_curve(3, 10, 1.019);
lemlib::ExpoDriveCurve steer_curve(3, 10, 1.019);

// Ansh settings
double anshSteerExpo = 1.019;
double anshThrottleExpo = 1.019;

// Eva settings
double evaSteerExpo = 1.019;
double evaThrottleExpo = 1.019;

pros::Controller controller(pros::E_CONTROLLER_MASTER);

DriverMode driverMode = PRACTICE;
bool practiceSkills = false;

// Change driving sensitivity
void updateDriverCurves(double &steerExpo, double &throttleExpo) {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
            steerExpo -= 0.001;
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
            steerExpo += 0.001;
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            throttleExpo -= 0.001;
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
            throttleExpo += 0.001;
        }
    }

    steerExpo = std::max(1.000, steerExpo);
    throttleExpo = std::max(1.000, throttleExpo);

    controller.print(2, 0, "S:%.3f T:%.3f", steerExpo, throttleExpo);
}

// Drive the robot
void drive(double steerExpo, double throttleExpo) {
    int leftY = controller.get_analog(
        pros::E_CONTROLLER_ANALOG_LEFT_Y
    );

    int rightX = controller.get_analog(
        pros::E_CONTROLLER_ANALOG_RIGHT_X
    );

    lemlib::ExpoDriveCurve throttleCurve(3, 10, throttleExpo);
    lemlib::ExpoDriveCurve steerCurve(3, 10, steerExpo);

    // Negative steering fixes reversed turning
    chassis.arcade(
        -throttleCurve.curve(leftY),
        -steerCurve.curve(rightX),
        true
    );
}

// Ansh competition controls
void competitionDriver() {
    updateDriverCurves(anshSteerExpo, anshThrottleExpo);
    drive(anshSteerExpo, anshThrottleExpo);

    // Cascade controls
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        toggleMatchLoad();
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        liftUp();
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        liftDown();
    }
    else if (!isMatchLoadMoving()) {
        liftStop();
    }

    updateMatchLoad();

    // Ratchet claw controls
    // R2 closes the claw
    // L2 opens the claw
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        scoringClose();
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        scoringOpen();
    }
    else {
        scoringStop();
    }

    pros::delay(25);
}

// Eva skills controls
void skillsDriver() {
    updateDriverCurves(evaSteerExpo, evaThrottleExpo);
    drive(evaSteerExpo, evaThrottleExpo);

    // Cascade controls
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        toggleMatchLoad();
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        liftUp();
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        liftDown();
    }
    else if (!isMatchLoadMoving()) {
        liftStop();
    }

    updateMatchLoad();

    // Ratchet claw controls
    // R1 closes the claw
    // R2 opens the claw
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        scoringClose();
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        scoringOpen();
    }
    else {
        scoringStop();
    }

    pros::delay(25);
}

// Practice mode
void practiceDriver() {
    // X + A selects Ansh controls
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) &&
        controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {

        practiceSkills = false;
        controller.rumble(".-");
        pros::delay(500);
    }

    // X + B selects Eva controls
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) &&
        controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {

        practiceSkills = true;
        controller.rumble("-...");
        pros::delay(500);
    }

    if (practiceSkills) {
        skillsDriver();
    }
    else {
        competitionDriver();
    }
}
