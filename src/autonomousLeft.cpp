#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"

void AutonCompLeft(){


chassis.setPose(0, -61, 270);
chassis.moveToPoint(0, -65, 4000, {.forwards = true, .minSpeed = 127});
//chassis.turnToHeading(270, 1000);
chassis.moveToPoint(0, -61, 4000, {.forwards = false, .minSpeed = 127});
//chassis.turnToHeading(270, 1000);
chassis.moveToPoint(0, -65, 4000, {.forwards = true, .minSpeed = 127});
//chassis.turnToHeading(270, 1000);
chassis.moveToPoint(0, -61, 4000, {.forwards = false, .minSpeed = 127});
//chassis.turnToHeading(270, 1000);
//chassis.moveToPoint(0, -61, 4000, {.forwards = true, .maxSpeed = 127});
//chassis.turnToHeading(135, 1000);
chassis.turnToPoint(-12.25, -47, 4000, {.forwards = false, .maxSpeed = 127});

chassis.moveToPoint(-12.25, -47, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
liftToPosition(1650);
chassis.waitUntilDone();
scoringTo90();

scoringWheelsAccept();
pros::delay(500);

scoringWheelsStop();

chassis.moveToPoint(-18.778, -47, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
liftToPosition(100);
scoringWheelsReject();

pros::delay(1000);

scoringWheelsStop();

chassis.waitUntilDone();
chassis.moveToPoint(-8.876, -52.207, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(125, 1000);
chassis.moveToPoint(-4.465, -58.552, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(270, 1000);
liftToPosition(getNormalLiftPosition());
scoringFold();
chassis.waitUntilDone();
}