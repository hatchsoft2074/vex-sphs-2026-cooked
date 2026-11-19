#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"


//Competition Auton
void AutonCompLeft() {
chassis.setPose(61.5, 5.5, 90);
chassis.moveToPoint(60, 5.5, 300, {.forwards = true, .maxSpeed = 127, .minSpeed = 120}, false);
chassis.moveToPoint(63.5, 5.5, 450, {.forwards = true, .maxSpeed = 127, .minSpeed = 120}, false);
chassis.moveToPoint(62.25, 5.5, 450, {.forwards = false, .maxSpeed = 127, .minSpeed = 120}, false);
chassis.moveToPoint(63.5, 5.5, 450, {.forwards = true, .maxSpeed = 127, .minSpeed = 120}, false);
chassis.moveToPoint(58, 5.5, 450, {.forwards = false, .maxSpeed = 127, .minSpeed = 120}, false);
liftToPositionAsync(1650, 1100);
scoringTo90(500);
chassis.moveToPose(46.75, 25, 180, 1350, {.forwards = false, .lead = 0.493, .maxSpeed = 110, .minSpeed = 95}, false);
liftToPosition(100, 700);
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

scoringToPickup(500);
chassis.moveToPoint(47.5, 6.75, 1700, {.forwards = true, .maxSpeed = 127, .minSpeed = 50}, false);
liftToPosition(getNormalLiftPosition());
scoringFold();
}