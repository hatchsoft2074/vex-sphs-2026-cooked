#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"


//Competition Auton
void AutonSkills() {
chassis.setPose(61.75, 5.5, 90);
chassis.moveToPoint(63.5, 5.5, 450, {.forwards = true, .maxSpeed = 127, .minSpeed = 120}, false);
chassis.moveToPoint(62.25, 5.5, 450, {.forwards = false, .maxSpeed = 127, .minSpeed = 120}, false);
chassis.moveToPoint(63.5, 5.5, 450, {.forwards = true, .maxSpeed = 127, .minSpeed = 120}, false);
chassis.moveToPoint(58, 5.5, 1000, {.forwards = false, .maxSpeed = 127, .minSpeed = 120}, false);
liftToPositionAsync(1650, 1100);
scoringTo90(500);
chassis.moveToPose(46.75, 25, 180, 1350, {.forwards = false, .lead = 0.493, .maxSpeed = 110, .minSpeed = 95}, false);
liftToPosition(100, 700);
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

scoringToPickup(500);
chassis.moveToPoint(47.5, 6.75, 1700, {.forwards = true, .maxSpeed = 127, .minSpeed = 100}, false);
chassis.moveToPose(22.5, 22.5, 120, 1600, {.forwards = false, .lead = 0.367, .maxSpeed = 127, .minSpeed = 50}, false);
scoringWheelsAccept();
scoringToPin(500);
pros::delay(250);

scoringWheelsStop();

scoringTo90(500);
liftToPositionAsync(2800, 1100);
chassis.moveToPose(43, 23.25, 270, 1600, {.forwards = false, .lead = 0, .maxSpeed = 110, .minSpeed = 85}, false);
liftToPosition(2000);
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

liftToPosition(2800, 600);
chassis.moveToPose(27, 28.5, 225, 1200, {.forwards = true, .lead = 0, .maxSpeed = 127, .minSpeed = 100}, false);
chassis.turnToHeading(225, 1100, {.maxSpeed = 127, .minSpeed = 1}, false);
liftToPositionAsync(75, 1400);
scoringToPickup(500);
chassis.moveToPose(44.5, 45, 225, 1700, {.forwards = false, .lead = 0.6, .maxSpeed = 127, .minSpeed = 55}, false);
chassis.turnToHeading(225, 1500, {.maxSpeed = 127, .minSpeed = 50}, false);
scoringWheelsAccept();
scoringToPin(500);
pros::delay(250);

scoringTo90(500);
scoringWheelsStop();

liftToPositionAsync(3750, 1450);
chassis.moveToPose(46.5, 19.25, 0, 1850, {.forwards = false, .lead = 0.079, .maxSpeed = 70, .minSpeed = 60}, false);
scoringWheelsReject();

liftToPosition(3000, 1500);
pros::delay(250);

scoringWheelsStop();

liftToPosition(3950, 1100);
chassis.moveToPoint(46, 37.5, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 40}, false);
chassis.turnToHeading(80, 1500, {.maxSpeed = 60, .minSpeed = 0}, false);
liftToPosition(getNormalLiftPosition());
scoringFold(500);
}