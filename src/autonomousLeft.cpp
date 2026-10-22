#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"

//Competition Auton
void AutonCompLeft() {
chassis.setPose(0, 62.75, 0);
chassis.moveToPoint(0, 65, 2000, {.maxSpeed = 127, .forwards = true});
chassis.turnToHeading(0, 1000);
chassis.moveToPoint(0, 61.75, 2000, {.maxSpeed = 127, .forwards = false});
chassis.turnToHeading(0, 1000);
chassis.moveToPoint(0, 65, 2000, {.maxSpeed = 127, .forwards = true});
chassis.turnToHeading(0, 1000);
chassis.moveToPoint(0, 61.75, 2000, {.maxSpeed = 127, .forwards = false});
chassis.turnToHeading(0, 1000);
chassis.moveToPoint(1, 57.75, 2000, {.maxSpeed = 127, .forwards = false});
chassis.turnToHeading(315, 1000);
chassis.waitUntilDone();
chassis.moveToPoint(12.25, 47, 2500, {.maxSpeed = 127, .forwards = false});
chassis.turnToHeading(270, 1000);
liftToPosition(1650);
chassis.waitUntilDone();
scoringTo90();

chassis.moveToPoint(17.25, 46.75, 1000, {.maxSpeed = 127, .forwards = false});
chassis.turnToHeading(270, 1000);
chassis.waitUntilDone();
chassis.moveToPoint(8.75, 52.25, 2000, {.maxSpeed = 127, .forwards = true});
chassis.turnToHeading(305, 1000);
liftToPosition(1400);
chassis.waitUntilDone();
scoringWheelsReject();

pros::delay(1000);

scoringWheelsStop();

chassis.moveToPoint(4.25, 58.5, 2000, {.maxSpeed = 127, .forwards = true});
chassis.turnToHeading(90, 1000);
liftToPosition(getNormalLiftPosition());
scoringFold();
chassis.waitUntilDone();
}