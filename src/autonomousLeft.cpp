#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"


//Competition Auton
void AutonCompLeft() {
chassis.setPose(62, -5.5, 90);
chassis.moveToPoint(63.5, -5.5, 450, {.forwards = true, .maxSpeed = 127, .minSpeed = 100}, false);
chassis.moveToPoint(62, -5.5, 450, {.forwards = false, .maxSpeed = 127, .minSpeed = 100}, false);
chassis.moveToPoint(64.5, -5.5, 450, {.forwards = true, .maxSpeed = 127, .minSpeed = 100}, false);
chassis.moveToPoint(58, -5.5, 1000, {.forwards = false, .maxSpeed = 127, .minSpeed = 100}, false);
liftToPositionAsync(1650);

scoringTo90();

chassis.moveToPose(46, -23.5, 0, 3000, {.forwards = false, .lead = 0.131, .maxSpeed = 127, .minSpeed = 0}, false);
liftToPosition(100);
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

scoringToPickup(); 
chassis.moveToPoint(46, -12.5, 1700, {.forwards = true, .maxSpeed = 127, .minSpeed = 1}, false);
}