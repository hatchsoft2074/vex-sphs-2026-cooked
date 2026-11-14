#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"


//Competition Auton
void AutonCompRight() {
chassis.setPose(61.75, 5.5, 90);
chassis.moveToPoint(63.5, 5.5, 500, {.forwards = true, .maxSpeed = 127, .minSpeed = 100}, false);
chassis.moveToPoint(62.25, 5.5, 500, {.forwards = false, .maxSpeed = 127, .minSpeed = 100}, false);
chassis.moveToPoint(63.5, 5.5, 500, {.forwards = true, .maxSpeed = 127, .minSpeed = 100}, false);
chassis.moveToPoint(58, 5.5, 500, {.forwards = false, .maxSpeed = 127, .minSpeed = 100}, false);
liftToPosition(1650);
scoringTo90();

chassis.moveToPose(45.75, 21.25, 180, 4000, {.forwards = false, .lead = 0, .maxSpeed = 127, .minSpeed = 1}, false);
liftToPosition(100);
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

scoringToPickup(); 
chassis.waitUntilDone();
chassis.moveToPoint(47.5, 6.5, 4000, {.forwards = true, .maxSpeed = 127, .minSpeed = 1}, false);
chassis.moveToPose(27, 20.25, 120, 4000, {.forwards = false, .lead = 0.346, .maxSpeed = 127, .minSpeed = 0}, false);
scoringToPin();
scoringWheelsAccept();
pros::delay(250);

scoringWheelsStop();

scoringTo90();

liftToPosition(2800);
chassis.moveToPose(45.25, 23.25, 270, 4000, {.forwards = false, .lead = 0.729, .maxSpeed = 127, .minSpeed = 0}, false);
liftToPosition(2000);
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

liftToPosition(2800);
chassis.waitUntilDone();
chassis.moveToPose(26.75, 28.5, 225, 4000, {.forwards = true, .lead = 0, .maxSpeed = 127, .minSpeed = 1}, false);
chassis.turnToHeading(225, 2000, {.maxSpeed = 127, .minSpeed = 1}, false);
liftToPosition(75);
scoringToPickup(); 
chassis.moveToPose(42.25, 44, 225, 4000, {.forwards = false, .lead = 0.6, .maxSpeed = 127, .minSpeed = 0}, false);
chassis.turnToHeading(225, 2000, {.maxSpeed = 127, .minSpeed = 0}, false);
scoringToPin();
scoringWheelsAccept();
pros::delay(250);

scoringWheelsStop();

scoringTo90();

chassis.waitUntilDone();
liftToPosition(3800);
chassis.moveToPose(46, 23.75, 0, 4000, {.forwards = false, .lead = 0.558, .maxSpeed = 127, .minSpeed = 0}, false);
liftToPosition(3000);
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

liftToPosition(3800);
chassis.waitUntilDone();
chassis.moveToPoint(46.25, 36, 4000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}, false);
chassis.turnToHeading(90, 2000, {.maxSpeed = 127, .minSpeed = 0}, false);
liftToPosition(getNormalLiftPosition());
scoringFold();
}