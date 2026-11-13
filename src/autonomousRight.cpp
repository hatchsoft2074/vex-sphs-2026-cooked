#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"

void AutonCompRight(){


chassis.setPose(61.75, 5.5, 90);
chassis.moveToPoint(63.5, 5.5, 500, {.forwards = true, .maxSpeed = 127, .minSpeed = 100}, false);
chassis.moveToPoint(61.75, 5.5, 500, {.forwards = false, .maxSpeed = 127, .minSpeed = 100}, false);
chassis.moveToPoint(63.5, 5.5, 500, {.forwards = true, .maxSpeed = 127, .minSpeed = 100}, false);
chassis.moveToPoint(58, 5.5, 500, {.forwards = false, .maxSpeed = 127, .minSpeed = 100}, false);
liftToPosition(1650);
scoringTo90();

chassis.moveToPose(47, 23.5, 180, 1500, {.forwards = false, .lead = 0, .maxSpeed = 127, .minSpeed = 1}, false);
liftToPosition(100);
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

scoringToPickup(); 
chassis.waitUntilDone();
chassis.moveToPoint(47.5, 6.5, 1500, {.forwards = true, .maxSpeed = 127, .minSpeed = 1}, false);
chassis.moveToPose(28.5, 20, 120, 1500, {.forwards = false, .lead = 0.6, .maxSpeed = 127, .minSpeed = 0}, false);
scoringToPin();
scoringWheelsAccept();
pros::delay(250);

scoringWheelsStop();

scoringTo90();

liftToPosition(2800);
chassis.moveToPose(47.5, 23.5, 270, 1500, {.forwards = false, .lead = 0.729, .maxSpeed = 127, .minSpeed = 0}, false);
liftToPosition(2000);
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

liftToPosition(2800);
chassis.waitUntilDone();
chassis.moveToPoint(33.5, 25.5, 1500, {.forwards = true, .maxSpeed = 127, .minSpeed = 1}, false);
chassis.turnToHeading(180, 500, {.maxSpeed = 127, .minSpeed = 1}, false);
liftToPosition(75);
scoringToPickup(); 
chassis.moveToPose(42.5, 42.5, 225, 2000, {.forwards = false, .lead = 0.521, .maxSpeed = 127, .minSpeed = 0}, false);
chassis.turnToHeading(225, 500, {.maxSpeed = 127, .minSpeed = 0}, false);
scoringToPin();
scoringWheelsAccept();
pros::delay(250);

scoringWheelsStop();

scoringTo90();

chassis.waitUntilDone();
liftToPosition(3800);
chassis.moveToPose(47.5, 22.5, 0, 2000, {.forwards = false, .lead = 0.503, .maxSpeed = 127, .minSpeed = 0}, false);
liftToPosition(3000);
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

liftToPosition(3800);
chassis.waitUntilDone();
chassis.moveToPoint(47, 35.5, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}, false);
chassis.turnToHeading(90, 500, {.maxSpeed = 127, .minSpeed = 0}, false);
liftToPosition(getNormalLiftPosition());
scoringFold();
}