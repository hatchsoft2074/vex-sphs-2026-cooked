
#include "autonomous.hpp"

// Pin 1 & 2 Score Heights and Pickup Heights

const double PIN1_SCORE_HEIGHT = 2500;

const double PINCONE1_PICKUP_HEIGHT = 1360;
const double PINCONE1_SCORE_HEIGHT = 2500;

const double PINCONE2_PICKUP_HEIGHT = 1360;
const double PINCONE2_SCORE_HEIGHT = 2500;

const double FINAL_CASCADE_HEIGHT = 1360;

// Claw Angle

const double PIN1_CLAW_ANGLE = 890;
const double PINCONE1_CLAW_ANGLE = 890;
const double PINCONE2_CLAW_ANGLE = 890;

const double FINAL_CLAW_ANGLE = 0;

// Timings 

const int TOGGLE_FORWARD_TIME = 500;
const int TOGGLE_BACKWARD_TIME = 500;

const int PIN1_SCORE_TIME = 500;

const int PINCONE1_PICKUP_TIME = 750;
const int PINCONE1_SCORE_TIME = 500;

const int PINCONE2_PICKUP_TIME = 750;
const int PINCONE2_SCORE_TIME = 500;

// Non-Explode Code

const int LIFT_TIMEOUT = 3000;
const int CLAW_TIMEOUT = 1500;

const double LIFT_TOLERANCE = 30;
const double CLAW_TOLERANCE = 20;

// Super Move

void autonMove(double x, double y, bool forwards) {
    chassis.moveToPoint(
        x, y, 4000,
        {.forwards = forwards, .maxSpeed = 127}
    );

    chassis.waitUntilDone();
}

void autonTurn(double heading) {
    chassis.turnToHeading(heading, 1000);
    chassis.waitUntilDone();
}

// Cascade Twerker 

bool autonLiftTo(double target) {

    // Do not lower below normal intake position
    if (target < 1360) {
        target = 1360;
    }

    unsigned int start = pros::millis();

    moveLiftToPosition(target);

    while (pros::millis() - start < LIFT_TIMEOUT) {

        double error = target - getLiftPosition();

        if (error >= -LIFT_TOLERANCE &&
            error <= LIFT_TOLERANCE) {
            liftStop();
            return true;
        }

        pros::delay(20);
    }

    liftStop();
    return false;
}

// Scoring Twerker

bool autonClawTo(double target) {

    unsigned int start = pros::millis();

    while (pros::millis() - start < CLAW_TIMEOUT) {

        double error = target - getScoringMechPosition();

        if (error >= -CLAW_TOLERANCE &&
            error <= CLAW_TOLERANCE) {
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

// Toggle Stuff

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

// Scoring 1

bool autonScore(
    double cascadeHeight,
    double clawAngle,
    int scoreTime
) {

    if (!autonLiftTo(cascadeHeight)) {
        return false;
    }

    if (!autonClawTo(clawAngle)) {
        return false;
    }

    scoringWheelMotor(-45);
    pros::delay(scoreTime);
    scoringWheelMotor(0);

    return true;
}

// Pickup 1

bool autonPickup(
    double cascadeHeight,
    int pickupTime
) {

    if (!autonLiftTo(cascadeHeight)) {
        return false;
    }

    scoringWheelMotor(45);
    pros::delay(pickupTime);
    scoringWheelMotor(0);

    return true;
}

// Tuff Auton V1

void AutonCompV1() {

    // Auton Toggling 

    autonToggle();
    autonToggle();

    // SCORE PIN 1
    // Pin starts inside the robot
   

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

    // Picking Up Set 1

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

    // Scoring Set 1

    autonMove(35.858, 27.811, true);
    autonTurn(325.008);

    if (!autonScore(
        PINCONE1_SCORE_HEIGHT,
        PINCONE1_CLAW_ANGLE,
        PINCONE1_SCORE_TIME
    )) {
        goto autonEnd;
    }

    // Picking up Set 2

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

    // Scoring Set 2

    autonMove(57.56, 57.747, true);
    autonTurn(91.284);

    if (!autonScore(
        PINCONE2_SCORE_HEIGHT,
        PINCONE2_CLAW_ANGLE,
        PINCONE2_SCORE_TIME
    )) {
        goto autonEnd;
    }

    // Final 

    autonMove(62.082, 57.879, true);
    autonTurn(90);

autonEnd:

    scoringWheelMotor(0);
    intakeStop();

    // Fold scoring mechanism
    autonClawTo(FINAL_CLAW_ANGLE);

    // Lower cascade to intake height
    autonLiftTo(FINAL_CASCADE_HEIGHT);

    scoringMechStop();
    liftStop();
}
