#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"

void AutonSkills(){


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
chassis.moveToPoint(46.75, 17.5, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(180, 1000);
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
chassis.moveToPoint(40.75, 14.25, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(120, 1000);
chassis.moveToPoint(29.5, 19.75, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(120, 1000);
chassis.moveToPoint(35.5, 23.25, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(270, 1000);
chassis.waitUntilDone();
liftToPosition(100);
chassis.waitUntilDone();
scoringWheelsAccept();
pros::delay(250);

scoringWheelsStop();

chassis.waitUntilDone();
liftToPosition(1750);
chassis.moveToPoint(41, 23.25, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(270, 1000);
chassis.moveToPoint(35.5, 23.25, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(270, 1000);
chassis.waitUntilDone();
liftToPosition(1000);
chassis.waitUntilDone();
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

chassis.waitUntilDone();
liftToPosition(1800);
chassis.moveToPoint(38.25, 38.5, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(225, 1000);
chassis.moveToPoint(41.5, 41.5, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(225, 1000);
chassis.moveToPoint(46.5, 35.25, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);
chassis.waitUntilDone();
liftToPosition(100);
chassis.waitUntilDone();
scoringWheelsAccept();
pros::delay(250);

scoringWheelsStop();

liftToPosition(2800);
chassis.moveToPoint(46.5, 29, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);
chassis.moveToPoint(46.5, 35.25, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);
chassis.waitUntilDone();
liftToPosition(2000);
chassis.waitUntilDone();
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

chassis.waitUntilDone();
liftToPosition(2500);
chassis.moveToPoint(58.25, 58.25, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
liftToPosition(getNormalLiftPosition());
scoringFold();
chassis.moveToPoint(61.75, 58.25, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
chassis.moveToPoint(46.5, 29, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);
intakeReject();
scoringWheelsAccept();
pros::delay(1000);

pros::delay(500);

intakeStop();
scoringWheelsStop();

chassis.waitUntilDone();
scoringTo90();

liftToPosition(3500);
chassis.moveToPoint(58.25, 58.25, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
chassis.waitUntilDone();
liftToPosition(3000);
chassis.waitUntilDone();
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

liftToPosition(3500);
chassis.waitUntilDone();
chassis.moveToPoint(61.75, 58.25, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
liftToPosition(getNormalLiftPosition());
scoringFold();
chassis.moveToPoint(46.5, 29, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);
intakeReject();
scoringWheelsAccept();
pros::delay(1000);

pros::delay(500);

intakeStop();
scoringWheelsStop();

chassis.waitUntilDone();
scoringTo90();

liftToPosition(4000);
chassis.moveToPoint(26.75, 55.75, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(320, 1000);
chassis.waitUntilDone();
liftToPosition(3500);
chassis.waitUntilDone();
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

liftToPosition(4000);
chassis.waitUntilDone();
chassis.moveToPoint(5.5, 60.5, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);
liftToPosition(getNormalLiftPosition());
scoringFold();
chassis.moveToPoint(5.5, 65, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);
chassis.moveToPoint(5.5, 61.5, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);
chassis.moveToPoint(5.5, 65, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);
chassis.moveToPoint(5.5, 59.25, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);
chassis.moveToPoint(61.75, 58.25, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
chassis.moveToPoint(29, 46.75, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
intakeReject();
scoringWheelsAccept();
pros::delay(1000);

pros::delay(500);

intakeStop();
scoringWheelsStop();

chassis.waitUntilDone();
scoringTo90();

liftToPosition(1600);
chassis.moveToPoint(61.75, 58.25, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
liftToPosition(100);
chassis.waitUntilDone();
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

liftToPosition(getNormalLiftPosition());
chassis.moveToPoint(29, 46.75, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
scoringFold();
chassis.waitUntilDone();
intakeReject();
scoringWheelsAccept();
pros::delay(1000);

pros::delay(500);

intakeStop();
scoringWheelsStop();

chassis.waitUntilDone();
scoringTo90();

liftToPosition(1800);
chassis.moveToPoint(61.75, 58.25, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
liftToPosition(1000);
chassis.waitUntilDone();
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

liftToPosition(1500);
chassis.waitUntilDone();
chassis.moveToPoint(29, 46.75, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
liftToPosition(getNormalLiftPosition());
scoringFold();
chassis.waitUntilDone();
intakeReject();
scoringWheelsAccept();
pros::delay(1000);

pros::delay(500);

intakeStop();
scoringWheelsStop();

chassis.waitUntilDone();
scoringTo90();

liftToPosition(2800);
chassis.moveToPoint(61.75, 58.25, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
liftToPosition(2000);
chassis.waitUntilDone();
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

liftToPosition(2500);
chassis.waitUntilDone();
chassis.moveToPoint(29, 46.75, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
liftToPosition(getNormalLiftPosition());
scoringFold();
chassis.waitUntilDone();
intakeReject();
scoringWheelsAccept();
pros::delay(1000);

pros::delay(500);

intakeStop();
scoringWheelsStop();

chassis.waitUntilDone();
scoringTo90();

liftToPosition(3800);
chassis.moveToPoint(61.75, 58.25, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
liftToPosition(3000);
chassis.waitUntilDone();
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

liftToPosition(3500);
chassis.waitUntilDone();
chassis.moveToPoint(29, 46.75, 4000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
liftToPosition(getNormalLiftPosition());
scoringFold();
chassis.waitUntilDone();
intakeReject();
scoringWheelsAccept();
pros::delay(1000);

intakeStop();
scoringWheelsStop();

chassis.waitUntilDone();
scoringTo90();

liftToPosition(4000);
chassis.moveToPoint(35.5, 46.75, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(135, 1000);
liftToPosition(3500);
chassis.waitUntilDone();
scoringWheelsReject();

pros::delay(250);

scoringWheelsStop();

liftToPosition(4000);
chassis.waitUntilDone();
chassis.moveToPoint(29, 37, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(230, 1000);
liftToPosition(getNormalLiftPosition());
scoringFold();
chassis.moveToPoint(0.75, 12.5, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(225, 1000);
}