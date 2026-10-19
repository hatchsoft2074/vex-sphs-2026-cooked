
#include "autonomous.hpp"
#include <cmath>

// Cascade positions
const double PIN1_SCORE_HEIGHT = 2500;

const double PINCONE1_PICKUP_HEIGHT = 1360;
const double PINCONE1_SCORE_HEIGHT = 2500;

const double PINCONE2_PICKUP_HEIGHT = 1360;
const double PINCONE2_SCORE_HEIGHT = 2500;

const double FINAL_CASCADE_HEIGHT = 1360;

// Scoring mechanism positions
const double PIN1_CLAW_ANGLE = 890;
const double PINCONE1_CLAW_ANGLE = 890;
const double PINCONE2_CLAW_ANGLE = 890;

const double FINAL_CLAW_ANGLE = 0;

// Toggle timings
const int TOGGLE_FORWARD_TIME = 500;
const int TOGGLE_BACKWARD_TIME = 500;

// Scoring wheel timings
const int PIN1_SCORE_TIME = 500;

const int PINCONE1_PICKUP_TIME = 750;
const int PINCONE1_SCORE_TIME = 500;

const int PINCONE2_PICKUP_TIME = 750;
const int PINCONE2_SCORE_TIME = 500;

// Mechanism settings
const int LIFT_TIMEOUT = 3000;
const int CLAW_TIMEOUT = 2000;

const double LIFT_TOLERANCE = 30;
const double CLAW_TOLERANCE = 20;

// Drive to a point using LemLib
void autonMove(double x, double y, bool forwards) {
    chassis.moveToPoint(
        x, y, 4000,
        {.forwards = forwards, .maxSpeed = 127}
    );

    chassis.waitUntilDone();
}

// Turn to a heading using LemLib
void autonTurn(double heading) {
    chassis.turnToHeading(heading, 1000);
    chassis.waitUntilDone();
}

// Move the lift to an encoder position
bool autonLiftTo(double target) {
    // Normal autonomous movements stay above intake height.
    // The lift can still start at zero.
    if (target < getNormalLiftPosition()) {
        target = getNormalLiftPosition();
    }

    if (target > getMaxLiftPosition()) {
        target = getMaxLiftPosition();
    }

    cancelMatchLoad();

    unsigned int start = pros::millis();

    while (pros::millis() - start < LIFT_TIMEOUT) {
        // This must run repeatedly to update motor speed.
        if (moveLiftToPosition(target)) {
            liftStop();
            return true;
        }

        pros::delay(20);
    }

    liftStop();
    return false;
}

// Move the scoring mechanism to an encoder position
bool autonClawTo(double target) {
    if (target < 0) {
        target = 0;
    }

    if (target > 920) {
        target = 920;
    }

    cancelScoringAuto();

    unsigned int start = pros::millis();

    while (pros::millis() - start < CLAW_TIMEOUT) {
        double error = target - getScoringMechPosition();

        if (std::abs(error) <= CLAW_TOLERANCE) {
            scoringMechStop();
            return true;
        }

        if (error > 0) {
            scoringMechUp();
        } else {
            scoringMechDown();
        }

        pros::delay(20);
    }

    scoringMechStop();
    return false;
}

// Move forward and backward to flip the toggle
void autonToggle() {
    left_motor_group.move(80);
    right_motor_group.move(80);

    pros::delay(TOGGLE_FORWARD_TIME);

    left_motor_group.move(-80);
    right_motor_group.move(-80);

    pros::delay(TOGGLE_BACKWARD_TIME);

    left_motor_group.move(0);
    right_motor_group.move(0);
}

// Score a pin or pin and cone
bool autonScore(double height, double angle, int time) {
    if (!autonLiftTo(height)) {
        return false;
    }

    if (!autonClawTo(angle)) {
        return false;
    }

    // Your original scoring code used negative motor power.
    scoringWheelsAccept();
    pros::delay(time);
    scoringWheelsStop();

    return true;
}

// Pick up a pin and cone
bool autonPickup(double height, int time) {
    if (!autonLiftTo(height)) {
        return false;
    }

    // Your original pickup code used positive motor power.
    scoringWheelsReject();
    pros::delay(time);
    scoringWheelsStop();

    return true;
}

// Competition autonomous
void AutonCompV1() {

    // Flip the toggle twice
    autonToggle();
    autonToggle();

    // Score the first pin already inside the robot
    autonMove(51.433, 18.406, false);
    autonTurn(139.979);

    autonMove(51.607, 12.993, true);
    autonTurn(113.532);

    if (!autonScore(
        PIN1_SCORE_HEIGHT,
        PIN1_CLAW_ANGLE,
        PIN1_SCORE_TIME
    )) {
        goto autonEnd;
    }

    // Pick up the first pin and cone
    autonMove(28.825, 23.483, false);
    autonTurn(90.331);

    autonMove(39.975, 23.245, true);
    autonTurn(270);

    if (!autonPickup(
        PINCONE1_PICKUP_HEIGHT,
        PINCONE1_PICKUP_TIME
    )) {
        goto autonEnd;
    }

    // Score the first pin and cone
    autonMove(35.858, 27.811, true);
    autonTurn(325.008);

    if (!autonScore(
        PINCONE1_SCORE_HEIGHT,
        PINCONE1_CLAW_ANGLE,
        PINCONE1_SCORE_TIME
    )) {
        goto autonEnd;
    }

    // Pick up the second pin and cone
    autonMove(46.979, 40.954, true);
    autonTurn(178.668);

    autonMove(46.6, 30.338, true);
    autonTurn(0);

    if (!autonPickup(
        PINCONE2_PICKUP_HEIGHT,
        PINCONE2_PICKUP_TIME
    )) {
        goto autonEnd;
    }

    // Score the second pin and cone
    autonMove(57.56, 57.747, true);
    autonTurn(91.284);

    if (!autonScore(
        PINCONE2_SCORE_HEIGHT,
        PINCONE2_CLAW_ANGLE,
        PINCONE2_SCORE_TIME
    )) {
        goto autonEnd;
    }

    // Move to the final position
    autonMove(62.082, 57.879, true);
    autonTurn(90);

autonEnd:
    scoringWheelsStop();
    intakeStop();

    // Fold the scoring mechanism
    autonClawTo(FINAL_CLAW_ANGLE);

    // Return the lift to intake position
    autonLiftTo(FINAL_CASCADE_HEIGHT);

    scoringMechStop();
    liftStop();
}
