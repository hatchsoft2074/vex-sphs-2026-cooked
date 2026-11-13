#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"

void AutonCompRight(){


chassis.setPose(61, 4, 90);
chassis.moveToPoint(64, 4, 4000, {.forwards = true, .minSpeed = 100}, false);
chassis.moveToPoint(61, 4, 4000, {.forwards = false, .minSpeed = 100}, false);
chassis.moveToPoint(64, 4, 4000, {.forwards = true, .minSpeed = 100}, false);
chassis.moveToPoint(61, 4, 4000, {.forwards = false, .minSpeed = 100}, false);
chassis.moveToPoint(47, 6.5, 4000, {.forwards = false, .maxSpeed = 127}, false);
liftToPosition(1650);
scoringTo90();

chassis.moveToPoint(47, 16, 4000, {.forwards = false, .maxSpeed = 127}, false);
liftToPosition(100);
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

chassis.moveToPoint(47, 3.5, 4000, {.forwards = true, .maxSpeed = 127}, false);
scoringToPickup();
chassis.moveToPoint(29, 17.5, 4000, {.forwards = false, .maxSpeed = 127}, false);
scoringToPin();
scoringWheelsAccept();
pros::delay(250);

scoringWheelsStop();

scoringTo90();

chassis.moveToPoint(28.5, 23.5, 4000, {.forwards = false, .maxSpeed = 127}, false);
liftToPosition(2800);
chassis.moveToPoint(39, 23, 4000, {.forwards = false, .maxSpeed = 127}, false);
liftToPosition(2000);
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

liftToPosition(2800);
chassis.moveToPoint(28.5, 28, 4000, {.forwards = true, .maxSpeed = 127}, false);
liftToPosition(50);
scoringToPickup();
chassis.moveToPoint(40.5, 41, 4000, {.forwards = false, .maxSpeed = 127}, false);
scoringToPin();
scoringWheelsAccept();
pros::delay(250);

scoringWheelsStop();

scoringTo90();

chassis.waitUntilDone();
chassis.moveToPoint(47, 37, 4000, {.forwards = false, .maxSpeed = 127}, false);
liftToPosition(3800);
chassis.moveToPoint(46.5, 30, 4000, {.forwards = false, .maxSpeed = 127}, false);
liftToPosition(3000);
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

liftToPosition(3800);
chassis.moveToPoint(47, 37, 4000, {.forwards = true, .maxSpeed = 127}, false);
liftToPosition(getNormalLiftPosition());
scoringFold();
}