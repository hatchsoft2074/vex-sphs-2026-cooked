#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"

void AutonCompRight(){


chassis.setPose(61.5, 5.75, 90);
chassis.moveToPoint(65, 5.75, 4000, {.forwards = true, .minSpeed = 127});
//chassis.turnToHeading(90, 1000);
chassis.moveToPoint(61.5, 5.75, 4000, {.forwards = false, .minSpeed = 127});
//chassis.turnToHeading(90, 1000);
chassis.moveToPoint(65, 5.75, 4000, {.forwards = true, .minSpeed = 127});
//chassis.turnToHeading(90, 1000);
chassis.moveToPoint(61.5, 5.75, 4000, {.forwards = false, .minSpeed = 127});
//chassis.turnToHeading(90, 1000);
chassis.turnToPoint(46.75, 12.5, 4000, {.forwards = false, .minSpeed = 127});
chassis.turnToPoint(46.75, 17.5, 4000, {.forwards = false, .minSpeed = 127});
liftToPosition(1650);
chassis.waitUntilDone();
scoringTo90();

scoringWheelsAccept();
pros::delay(250);

scoringWheelsStop();

chassis.moveToPoint(46.75, 11, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(180, 1000);
liftToPosition(100);
chassis.waitUntilDone();
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

liftToPosition(1700);
chassis.turnToPoint(40.75, 14.25, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToPoint(28.25, 21, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToPoint(36.25, 23.25, 4000, {.forwards = true, .maxSpeed = 127});
chassis.waitUntilDone();
liftToPosition(100);
chassis.waitUntilDone();
scoringWheelsAccept();
pros::delay(250);

scoringWheelsStop();

chassis.waitUntilDone();
liftToPosition(1750);
chassis.turnToPoint(41, 23.25, 4000, {.forwards = false, .maxSpeed = 127});
chassis.moveToPoint(36.25, 23.25, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(270, 1000);
chassis.waitUntilDone();
liftToPosition(1000);
chassis.waitUntilDone();
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

chassis.waitUntilDone();
liftToPosition(1800);
chassis.turnToPoint(38.25, 38.5, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToPoint(42.25, 42.25, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToPoint(46.5, 35.25, 4000, {.forwards = true, .maxSpeed = 127});
chassis.waitUntilDone();
liftToPosition(100);
chassis.waitUntilDone();
scoringWheelsAccept();
pros::delay(250);

scoringWheelsStop();

liftToPosition(2800);
chassis.turnToPoint(46.5, 29, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToPoint(46.5, 35.25, 4000, {.forwards = true, .minSpeed  = 127});
chassis.waitUntilDone();
liftToPosition(2000);
chassis.waitUntilDone();
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

chassis.waitUntilDone();
chassis.moveToPoint(55.5, 35.25, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
}