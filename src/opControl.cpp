
#include "main.h"
#include "opcontrol.h"
#include "robotConfigs.h"
#include "lift.h"
#include "scoring.h"
#include "scoringMacro.h"
#include "toggles.h"
#include <algorithm>

lemlib::ExpoDriveCurve throttle_curve(3, 10, 1.019);
lemlib::ExpoDriveCurve steer_curve(3, 10, 1.019);

double anshSteerExpo = 1.019;
double anshThrottleExpo = 1.019;
double evaSteerExpo = 1.019;
double evaThrottleExpo = 1.019;

pros::Controller controller(pros::E_CONTROLLER_MASTER);

DriverMode driverMode = PRACTICE;
bool practiceSkills = false;

void updateDriverCurves(double &steerExpo, double &throttleExpo) {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))
            steerExpo -= 0.001;

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT))
            steerExpo += 0.001;

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
            throttleExpo -= 0.001;

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))
            throttleExpo += 0.001;
    }

    steerExpo = std::max(1.000, steerExpo);
    throttleExpo = std::max(1.000, throttleExpo);

    controller.print(2, 0, "S:%.3f T:%.3f", steerExpo, throttleExpo);
}

void drive(double steerExpo, double throttleExpo) {
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    lemlib::ExpoDriveCurve throttleCurve(3, 10, throttleExpo);
    lemlib::ExpoDriveCurve steerCurve(3, 10, steerExpo);

    // Reverse forward and steering
    chassis.arcade(
        throttleCurve.curve(leftY),
        -steerCurve.curve(rightX),
        true
    );
}

// DOWN starts the cascade lowering macro
void updateCascadeMacroButton() {
    if (!controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
        controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        startScoringMacro();
    }

    updateScoringMacro();
}

// Hold B to spin the toggles
void updateToggles() {
    static bool waitForRelease = false;

    bool bHeld = controller.get_digital(
        pros::E_CONTROLLER_DIGITAL_B
    );

    bool xHeld = controller.get_digital(
        pros::E_CONTROLLER_DIGITAL_X
    );

    // Prevent movement when switching practice drivers
    if (driverMode == PRACTICE && xHeld && bHeld) {
        waitForRelease = true;
    }

    if (!bHeld) {
        waitForRelease = false;
    }

    if (bHeld && !waitForRelease) {
        togglesSpin();
    } else {
        togglesStop();
    }
}

// Ansh competition controls
void competitionDriver() {
    updateDriverCurves(anshSteerExpo, anshThrottleExpo);
    drive(anshSteerExpo, anshThrottleExpo);

    updateCascadeMacroButton();
    updateToggles();

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        liftUp();
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        liftDown();
    } else if (!isScoringMacroRunning() &&
               !isLiftAsyncMoving() &&
               !isMatchLoadMoving()) {
        liftStop();
    }

    updateMatchLoad();

    // Ratchet claw
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        scoringClose();
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        scoringOpen();
    } else {
        scoringStop();
    }

    pros::delay(25);
}

// Eva skills controls
void skillsDriver() {
    updateDriverCurves(evaSteerExpo, evaThrottleExpo);
    drive(evaSteerExpo, evaThrottleExpo);

    updateCascadeMacroButton();
    updateToggles();

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        liftUp();
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        liftDown();
    } else if (!isScoringMacroRunning() &&
               !isLiftAsyncMoving() &&
               !isMatchLoadMoving()) {
        liftStop();
    }

    updateMatchLoad();

    // Ratchet claw
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        scoringClose();
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        scoringOpen();
    } else {
        scoringStop();
    }

    pros::delay(25);
}

// Practice mode switches between drivers
void practiceDriver() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) &&
        controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        togglesStop();
        practiceSkills = false;
        controller.rumble(".-");
        pros::delay(500);
    }

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) &&
        controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        updateToggles();
        togglesStop();
        practiceSkills = true;
        controller.rumble("-...");
        pros::delay(500);
    }

    if (practiceSkills) {
        skillsDriver();
    } else {
        competitionDriver();
    }
}
