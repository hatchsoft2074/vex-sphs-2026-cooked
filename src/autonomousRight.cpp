#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"

void AutonCompRight(){


chassis.setPose(61.5, 5.75, 90);
chassis.moveToPoint(65, 5.75, 4000, {.forwards = true, .minSpeed = 127});
chassis.turnToHeading(90, 1000);
chassis.moveToPoint(61.5, 5.75, 4000, {.forwards = false, .minSpeed = 127});
chassis.turnToHeading(90, 1000);
chassis.moveToPoint(65, 5.75, 4000, {.forwards = true, .minSpeed = 127});
chassis.turnToHeading(90, 1000);
chassis.moveToPoint(61.5, 5.75, 4000, {.forwards = false, .minSpeed = 127});
chassis.turnToHeading(90, 1000);
chassis.moveToPoint(46.75, 12.5, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(180, 1000);
liftToPosition(1650);
chassis.waitUntilDone();
scoringTo90();

scoringWheelsAccept();
pros::delay(250);

scoringWheelsStop();

chassis.turnToPoint(46.75, 17.5, 4000, {.forwards = false, .maxSpeed = 127});
chassis.moveToPoint(46.75, 17.5, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(180, 1000);
liftToPosition(100);
scoringWheelsReject();

pros::delay(500);

scoringWheelsStop();

chassis.waitUntilDone();
chassis.moveToPoint(46.75, 11, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(180, 1000);
chassis.moveToPoint(40.75, 14.25, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(120, 1000);
liftToPosition(1750);
chassis.moveToPoint(29.5, 19.75, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(120, 1000);
liftToPosition(100);
scoringWheelsAccept();
pros::delay(500);

scoringWheelsStop();

chassis.waitUntilDone();
liftToPosition(1700);
chassis.moveToPoint(35.5, 23.25, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(270, 1000);
chassis.moveToPoint(41, 23.25, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(270, 1000);
liftToPosition(1000);
chassis.waitUntilDone();
scoringWheelsReject();

pros::delay(500);

scoringWheelsStop();

chassis.waitUntilDone();
liftToPosition(1800);
chassis.moveToPoint(35.5, 23.25, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(270, 1000);
chassis.moveToPoint(38.25, 38.5, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(225, 1000);
chassis.moveToPoint(41.5, 41.5, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(225, 1000);
liftToPosition(100);
scoringWheelsAccept();
pros::delay(500);

scoringWheelsStop();

chassis.waitUntilDone();
liftToPosition(2800);
chassis.moveToPoint(46.5, 35.25, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);
chassis.moveToPoint(46.5, 29, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);
liftToPosition(2000);
chassis.waitUntilDone();
scoringWheelsReject();

pros::delay(500);

scoringWheelsStop();

chassis.waitUntilDone();
liftToPosition(getNormalLiftPosition());
chassis.moveToPoint(46.5, 35.25, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);
scoringFold();
chassis.moveToPoint(55.5, 35.25, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
}