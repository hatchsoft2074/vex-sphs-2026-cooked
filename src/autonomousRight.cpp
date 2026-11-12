#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"

void AutonCompRight(){


chassis.setPose(61, 4, 90);
chassis.moveToPoint(64, 4, 4000, {.forwards = true, .minSpeed = 127}, false);
chassis.moveToPoint(61, 4, 4000, {.forwards = false, .minSpeed = 127}, false);
chassis.moveToPoint(64, 4, 4000, {.forwards = true, .minSpeed = 127}, false);
chassis.moveToPoint(47, 4, 4000, {.forwards = false, .minSpeed = 80}, false);
liftToPosition(1650);
scoringTo90();

chassis.moveToPoint(47, 15.5, 4000, {.forwards = true, .maxSpeed = 127}, false);
liftToPosition(100);
scoringWheelsReject();

pros::delay(500);

scoringWheelsStop();

chassis.moveToPoint(47, 6.5, 4000, {.forwards = true, .maxSpeed = 127}, false);
chassis.moveToPoint(47, 4, 4000, {.forwards = true, .maxSpeed = 127}, false);
scoringToPickup();
chassis.moveToPoint(28, 18.5, 4000, {.forwards = false, .maxSpeed = 127}, false);
scoringToPin();
scoringWheelsAccept();
pros::delay(500);

scoringWheelsStop();

scoringTo90();

chassis.moveToPoint(31.5, 23.5, 4000, {.forwards = false, .maxSpeed = 100}, false);
liftToPosition(2800);
chassis.moveToPoint(39, 23.5, 4000, {.forwards = false, .maxSpeed = 127}, false);
liftToPosition(2000);
scoringWheelsReject();

pros::delay(500);

scoringWheelsStop();

liftToPosition(2800);
chassis.moveToPoint(31.5, 24, 4000, {.forwards = true, .maxSpeed = 127}, false);
chassis.moveToPoint(25, 25, 4000, {.forwards = true, .maxSpeed = 127}, false);
liftToPosition(50);
scoringToPickup();
chassis.moveToPoint(41, 41, 4000, {.forwards = false, .maxSpeed = 127}, false);
scoringToPin();
scoringWheelsAccept();
pros::delay(500);

scoringWheelsStop();

scoringTo90();

chassis.moveToPoint(46.5, 41.5, 4000, {.forwards = false, .maxSpeed = 100}, false);
liftToPosition(3800);
chassis.moveToPoint(46.5, 30.5, 4000, {.forwards = false, .maxSpeed = 127}, false);
liftToPosition(3000);
scoringWheelsReject();

pros::delay(500);

scoringWheelsStop();

liftToPosition(3800);
chassis.moveToPoint(46.5, 39.5, 4000, {.forwards = true, .maxSpeed = 127}, false);
liftToPosition(getNormalLiftPosition());
scoringFold();
}