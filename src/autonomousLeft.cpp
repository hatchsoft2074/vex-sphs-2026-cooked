
#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"

void AutonCompLeft() {
    
chassis.setPose(0, 58, 0);
chassis.moveToPoint(0, 65, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);
chassis.moveToPoint(0, 58, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);
chassis.moveToPoint(0, 65.001, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);
chassis.moveToPoint(0.164, 58, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);
chassis.moveToPoint(0, 58, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(315, 1000);
chassis.moveToPoint(12.25, 47, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(270, 1000);
liftToPosition(1650);
chassis.waitUntilDone();
scoringTo90();

scoringWheelsAccept();
pros::delay(500);

scoringWheelsStop();

chassis.moveToPoint(18.778, 47, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(270, 1000);
liftToPosition(100);
scoringWheelsReject();

pros::delay(1000);

scoringWheelsStop();

chassis.waitUntilDone();
chassis.moveToPoint(8.876, 52.207, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(305, 1000);
chassis.moveToPoint(4.465, 58.552, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
liftToPosition(getNormalLiftPosition());
scoringFold();
chassis.waitUntilDone();
}
