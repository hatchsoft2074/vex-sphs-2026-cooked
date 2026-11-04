
#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"
#include <cmath>

// Drives a distance using the robot's current heading
void driveDistance(double inches, bool forwards) {
    auto pose = chassis.getPose();

    double radians = pose.theta * 3.141592653589793 / 180.0;
    double distance = forwards ? inches : -inches;

    double targetX = pose.x + distance * std::sin(radians);
    double targetY = pose.y + distance * std::cos(radians);

    chassis.moveToPoint(
        targetX,
        targetY,
        4000,
        {.forwards = forwards, .maxSpeed = 90},
        false
    );
}

void AutonCompRight() {

    chassis.setPose(61.5, 6, 90);

    chassis.moveToPoint(64, 5.75, 4000,
        {.forwards = true, .minSpeed = 127});

    chassis.turnToHeading(90, 2000,
        {.maxSpeed = 127}, false);

    chassis.moveToPoint(61.5, 6, 4000,
        {.forwards = false, .minSpeed = 127});

    chassis.turnToHeading(90, 2000,
        {.maxSpeed = 127}, false);

    chassis.moveToPoint(64, 5.75, 4000,
        {.forwards = true, .minSpeed = 127});

    chassis.turnToHeading(90, 2000,
        {.maxSpeed = 127}, false);

    chassis.moveToPoint(61.5, 6, 4000,
        {.forwards = false, .minSpeed = 127});

    chassis.turnToHeading(90, 2000,
        {.maxSpeed = 127}, false);

    liftToPosition(1650);

    chassis.waitUntilDone();

    scoringTo90();

    scoringWheelsAccept();
    pros::delay(250);
    scoringWheelsStop();

    // Converted VEXcode turn
    chassis.turnToHeading(126.714, 2000,
        {.maxSpeed = 127}, false);

    chassis.turnToHeading(180, 2000,
        {.maxSpeed = 127}, false);

    liftToPosition(100);

    scoringWheelsReject();
    pros::delay(500);
    scoringWheelsStop();

    chassis.waitUntilDone();

    chassis.moveToPoint(46.5, 9, 4000,
        {.forwards = true, .maxSpeed = 90}, false);

    liftToPosition(1750);

    chassis.turnToHeading(135, 2000,
        {.maxSpeed = 127}, false);

    chassis.moveToPose(28.25, 18.5, 135, 4000,
        {.forwards = false, .lead = 0.6, .maxSpeed = 127}, false);

    liftToPosition(100);

    scoringWheelsAccept();
    pros::delay(500);
    scoringWheelsStop();

    chassis.waitUntilDone();

    liftToPosition(2800);

    // Reverse 13.139 inches
    driveDistance(13.139, false);

    liftToPosition(2000);

    chassis.waitUntilDone();

    scoringWheelsReject();
    pros::delay(500);
    scoringWheelsStop();

    chassis.waitUntilDone();

    liftToPosition(2500);

    // Forward 11.294 inches
    driveDistance(11.294, true);

    chassis.turnToHeading(225, 2000,
        {.maxSpeed = 127}, false);

    chassis.turnToHeading(225, 2000,
        {.maxSpeed = 127}, false);

    chassis.moveToPoint(41.75, 41.75, 4000,
        {.forwards = false, .maxSpeed = 127}, false);

    liftToPosition(100);

    scoringWheelsAccept();
    pros::delay(500);
    scoringWheelsStop();

    chassis.waitUntilDone();

    liftToPosition(3800);

    // Reverse 12.311 inches
    driveDistance(12.311, false);

    chassis.turnToHeading(0, 2000,
        {.maxSpeed = 127}, false);

    liftToPosition(3000);

    chassis.waitUntilDone();

    scoringWheelsReject();
    pros::delay(500);
    scoringWheelsStop();

    chassis.waitUntilDone();

    // Forward 13.768 inches
    driveDistance(13.768, true);

    chassis.turnToHeading(90, 2000,
        {.maxSpeed = 127}, false);

    scoringFold();

    liftToPosition(getNormalLiftPosition());
}
