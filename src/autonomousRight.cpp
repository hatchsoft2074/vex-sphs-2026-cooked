#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"

void AutonCompRight(){


chassis.setPose(61.5, 6, 90);
chassis.moveToPoint(64, 5.75, 4000, {.forwards = true, .minSpeed = 127});
chassis.turnToHeading(90, 2000, {.maxSpeed = 127}, false);
chassis.moveToPoint(61.5, 6, 4000, {.forwards = false, .minSpeed = 127});
chassis.turnToHeading(90, 2000, {.maxSpeed = 127}, false);
chassis.moveToPoint(64, 5.75, 4000, {.forwards = true, .minSpeed = 127});
chassis.turnToHeading(90, 2000, {.maxSpeed = 127}, false);
chassis.moveToPoint(61.5, 6, 4000, {.forwards = false, .minSpeed = 127});
chassis.turnToHeading(90, 2000, {.maxSpeed = 127}, false);
liftToPosition(1650);
chassis.waitUntilDone();
scoringTo90();

scoringWheelsAccept();
pros::delay(250);

scoringWheelsStop();

drivetrain.turn_to_heading(126.714, DEGREES)
chassis.turnToHeading(180, 2000, {.maxSpeed = 127}, false);
liftToPosition(100);
scoringWheelsReject();

pros::delay(500);

scoringWheelsStop();

chassis.waitUntilDone();
chassis.moveToPoint(46.5, 9, 4000, {.forwards = true, .maxSpeed = 90}, false);
liftToPosition(1750);
chassis.turnToHeading(135, 2000, {.maxSpeed = 127}, false);
chassis.moveToPose(28.25, 18.5, 135, 4000, {.forwards = false, .lead = 0.6, .maxSpeed = 127}, false);
liftToPosition(100);
scoringWheelsAccept();
pros::delay(500);

scoringWheelsStop();

chassis.waitUntilDone();
liftToPosition(2800);
drivetrain.drive_for(FORWARD if false else REVERSE, 13.139, INCHES)
liftToPosition(2000);
chassis.waitUntilDone();
scoringWheelsReject();

pros::delay(500);

scoringWheelsStop();

chassis.waitUntilDone();
liftToPosition(2500);
drivetrain.drive_for(FORWARD if true else REVERSE, 11.294, INCHES)
chassis.turnToHeading(225, 2000, {.maxSpeed = 127}, false);
chassis.turnToHeading(225, 2000, {.maxSpeed = 127}, false);
chassis.moveToPoint(41.75, 41.75, 4000, {.forwards = false, .maxSpeed = 127}, false);
liftToPosition(100);
scoringWheelsAccept();
pros::delay(500);

scoringWheelsStop();

chassis.waitUntilDone();
liftToPosition(3800);
drivetrain.drive_for(FORWARD if false else REVERSE, 12.311, INCHES)
chassis.turnToHeading(0, 2000, {.maxSpeed = 127}, false);
liftToPosition(3000);
chassis.waitUntilDone();
scoringWheelsReject();

pros::delay(500);

scoringWheelsStop();

chassis.waitUntilDone();
drivetrain.drive_for(FORWARD if true else REVERSE, 13.768, INCHES)
chassis.turnToHeading(90, 2000, {.maxSpeed = 127}, false);
scoringFold();
liftToPosition(getNormalLiftPosition());
}