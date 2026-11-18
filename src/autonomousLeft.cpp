#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"


//Competition Auton
void AutonCompLeft() {
chassis.setPose(-5.5, -61.75, 180);
chassis.moveToPoint(-5.5, -63.5, 450, {.forwards = true, .maxSpeed = 127, .minSpeed = 120}, false);
chassis.moveToPoint(-5.5, -62.25, 450, {.forwards = false, .maxSpeed = 127, .minSpeed = 120}, false);
chassis.moveToPoint(-5.5, -63.5, 450, {.forwards = true, .maxSpeed = 127, .minSpeed = 120}, false);
chassis.moveToPoint(-5.5, -58, 1000, {.forwards = false, .maxSpeed = 127, .minSpeed = 120}, false);
liftToPositionAsync(1650, 1100);
scoringTo90(500);
chassis.moveToPose(-25, -46.75, 90, 1350, {.forwards = false, .lead = 0.493, .maxSpeed = 110, .minSpeed = 95}, false);
liftToPosition(100, 700);
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

scoringToPickup(500);
chassis.moveToPoint(-6.75, -47.5, 1700, {.forwards = true, .maxSpeed = 127, .minSpeed = 100}, false);
chassis.moveToPose(-22.5, -22.5, 150, 1600, {.forwards = false, .lead = 0.367, .maxSpeed = 127, .minSpeed = 50}, false);
scoringWheelsAccept();
scoringToPin(500);
pros::delay(250);

scoringWheelsStop();

scoringTo90(500);
liftToPositionAsync(2800, 1100);
chassis.moveToPose(-23.25, -43, 0, 1600, {.forwards = false, .lead = 0, .maxSpeed = 110, .minSpeed = 85}, false);
liftToPosition(2000);
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

liftToPosition(2800, 600);
chassis.moveToPose(-28.5, -27, 45, 1200, {.forwards = true, .lead = 0, .maxSpeed = 127, .minSpeed = 100}, false);
chassis.turnToHeading(45, 1100, {.maxSpeed = 127, .minSpeed = 1}, false);
liftToPositionAsync(75, 1400);
scoringToPickup(500);
chassis.moveToPose(-44.5, -43.75, 45, 1700, {.forwards = false, .lead = 0.6, .maxSpeed = 127, .minSpeed = 55}, false);
chassis.turnToHeading(45, 1500, {.maxSpeed = 127, .minSpeed = 50}, false);
scoringWheelsAccept();
scoringToPin(500);
pros::delay(250);

scoringTo90(500);
scoringWheelsStop();

liftToPositionAsync(3750, 1450);
chassis.moveToPose(-19.25, -46.5, 270, 1850, {.forwards = false, .lead = 0.079, .maxSpeed = 70, .minSpeed = 60}, false);
scoringWheelsReject();

liftToPosition(3000, 1500);
pros::delay(250);

scoringWheelsStop();

liftToPosition(3950, 1100);
chassis.moveToPoint(-37.5, -46, 1000, {.forwards = true, .maxSpeed = 127, .minSpeed = 40}, false);
chassis.turnToHeading(190, 1500, {.maxSpeed = 60, .minSpeed = 0}, false);
liftToPosition(getNormalLiftPosition());
scoringFold(500);
}