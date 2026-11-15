#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"


//Competition Auton
void AutonCompRight() {
chassis.setPose(61.75, 5.5, 90);
chassis.moveToPoint(63.5, 5.5, 450, {.forwards = true, .maxSpeed = 127, .minSpeed = 100}, false);
chassis.moveToPoint(62.25, 5.5, 450, {.forwards = false, .maxSpeed = 127, .minSpeed = 100}, false);
chassis.moveToPoint(63.5, 5.5, 450, {.forwards = true, .maxSpeed = 127, .minSpeed = 100}, false);
chassis.moveToPoint(58, 5.5, 1000, {.forwards = false, .maxSpeed = 127, .minSpeed = 100}, false);
liftToPositionAsync(1650);

scoringTo90();

chassis.moveToPose(46, 22.5, 180, 1800, {.forwards = false, .lead = 0.131, .maxSpeed = 127, .minSpeed = 0}, false);
liftToPosition(100);
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

scoringToPickup(); 
chassis.moveToPoint(47.5, 6.75, 1700, {.forwards = true, .maxSpeed = 127, .minSpeed = 1}, false);
chassis.moveToPose(25.5, 21, 120, 1600, {.forwards = false, .lead = 0.346, .maxSpeed = 127, .minSpeed = 50}, false);
scoringWheelsAccept();
scoringToPin();
pros::delay(250);

scoringWheelsStop();

scoringTo90();

liftToPosition(2800);
chassis.moveToPose(46.5, 24.25, 270, 1800, {.forwards = false, .lead = 0, .maxSpeed = 127, .minSpeed = 80}, false);
liftToPosition(2000);
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

liftToPosition(2800);
chassis.moveToPose(26.75, 28.5, 225, 1200, {.forwards = true, .lead = 0, .maxSpeed = 127, .minSpeed = 1}, false);
chassis.turnToHeading(225, 2000, {.maxSpeed = 127, .minSpeed = 1}, false);
liftToPositionAsync(75);

scoringToPickup(); 
chassis.moveToPose(44.5, 45, 225, 1700, {.forwards = false, .lead = 0.6, .maxSpeed = 127, .minSpeed = 50}, false);
chassis.turnToHeading(225, 2000, {.maxSpeed = 127, .minSpeed = 50}, false);
scoringWheelsAccept();
scoringToPin();
pros::delay(250);

scoringWheelsStop();

scoringTo90();

liftToPositionAsync(3800);

chassis.moveToPose(45.5, 19.5, 0, 2000, {.forwards = false, .lead = 0.558, .maxSpeed = 60, .minSpeed = 40}, false);
liftToPosition(3000);
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

liftToPosition(3800);
chassis.moveToPoint(45.25, 37.75, 2000, {.forwards = true, .maxSpeed = 127, .minSpeed = 40}, false);
chassis.turnToHeading(90, 2000, {.maxSpeed = 60, .minSpeed = 0}, false);
liftToPosition(getNormalLiftPosition());
scoringFold();
}