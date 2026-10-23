#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"

void AutonCompRight(){


chassis.setPose(58, 0, 90);
chassis.moveToPoint(65, 0, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
chassis.moveToPoint(58, 0, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
chassis.moveToPoint(65.001, 0, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
chassis.moveToPoint(58, 0.164, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
chassis.moveToPoint(58, 0, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(135, 1000);
chassis.moveToPoint(47, 12.25, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(180, 1000);
liftToPosition(1650);
chassis.waitUntilDone();
scoringTo90();

scoringWheelsAccept();
pros::delay(500);

scoringWheelsStop();

chassis.moveToPoint(47, 18, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(180, 1000);
liftToPosition(100);
scoringWheelsReject();

pros::delay(1000);

scoringWheelsStop();

chassis.waitUntilDone();
chassis.moveToPoint(52.207, 8.876, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(145, 1000);
chassis.moveToPoint(58.552, 4.465, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);
liftToPosition(getNormalLiftPosition());
scoringFold();
chassis.waitUntilDone();
}