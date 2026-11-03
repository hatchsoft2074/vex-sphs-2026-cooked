#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"

void AutonCompRight(){

//Toggles
chassis.setPose(61.5, 5.75, 90);
chassis.moveToPoint(65, 5.75, 1000, {.forwards = true, .minSpeed = 127});
chassis.moveToPoint(61.5, 5.75, 1000, {.forwards = false, .minSpeed = 127});
chassis.moveToPoint(65, 5.75, 1000, {.forwards = true, .minSpeed = 127});
chassis.moveToPoint(61.5, 5.75, 1000, {.forwards = false, .minSpeed = 127});

//In front of goal preparing to score Pin 1
chassis.moveToPoint(46.75, 12.5, 1000, {.forwards = false, .maxSpeed = 127});

liftToPosition(1650);
chassis.waitUntilDone();
scoringTo90();
scoringWheelsAccept();
pros::delay(250);
scoringWheelsStop();

//Scoring Pin 1
chassis.moveToPoint(46.75, 17.5, 1000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(180, 1000);

liftToPosition(100);
scoringWheelsReject();
pros::delay(500);
scoringWheelsStop();
chassis.waitUntilDone();

//Going to Pin set 2
chassis.moveToPoint(46.75, 12.5, 750, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(180, 1000);
chassis.moveToPoint(46.75, 11.75, 800, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(180, 1000);

liftToPosition(1750);
chassis.moveToPoint(29.5, 19.75, 500, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(120, 1000);

//Picking up Pin set 2
liftToPosition(100);
scoringWheelsAccept();
pros::delay(500);
scoringWheelsStop();
chassis.waitUntilDone();

//Going to score Pin set 2
liftToPosition(2800);
chassis.moveToPoint(35.5, 23.25, 1500, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(270, 1000);
chassis.moveToPoint(41, 23.25, 600, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(270, 1000);

//Scoring Pin set 2
liftToPosition(2000);
chassis.waitUntilDone();
scoringWheelsReject();
pros::delay(500);
scoringWheelsStop();
chassis.waitUntilDone();

//Going to Pin set 3
liftToPosition(2500);

chassis.moveToPoint(35.5, 23.25, 600, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(270, 1000);
chassis.moveToPoint(35.5, 23.25, 600, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(270, 1000);
chassis.moveToPoint(34.25, 23.25, 100, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(270, 1000);
chassis.moveToPoint(38.25, 38.5, 500, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(225, 1000);
chassis.moveToPoint(41.5, 41.5, 1600, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(225, 1000);

//Picking up Pin set 3
liftToPosition(100);
scoringWheelsAccept();
pros::delay(500);
scoringWheelsStop();
chassis.waitUntilDone();
liftToPosition(3800);

//Going to score Pin set 3
chassis.moveToPoint(46.5, 35.25, 600, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);
chassis.moveToPoint(46.5, 29, 1000, {.forwards = false, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);

liftToPosition(3000);
chassis.waitUntilDone();
scoringWheelsReject();
pros::delay(500);
scoringWheelsStop();
chassis.waitUntilDone();

//Final Positions
liftToPosition(getNormalLiftPosition());

chassis.moveToPoint(46.5, 35.25, 700, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);

scoringFold();

chassis.moveToPoint(46.5, 35.25, 700, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);
chassis.moveToPoint(55.5, 35.25, 100, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);

}