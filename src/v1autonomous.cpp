#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"

//Competition Auton (CompAutonV67)
void AutonCompV1() {


//Toggle
chassis.setPose(62.824, 0.043, 90);
chassis.moveToPoint(65.021, 0.091, 2000, {.maxSpeed = 127, .forwards = true});
chassis.turnToHeading(90, 1000);
chassis.moveToPoint(61.685, 0.139, 2000, {.maxSpeed = 127, .forwards = false});
chassis.turnToHeading(90, 1000);
chassis.moveToPoint(65.001, 0.105, 2000, {.maxSpeed = 127, .forwards = true});
chassis.turnToHeading(90, 1000);
chassis.moveToPoint(61.65, 0.164, 2000, {.maxSpeed = 127, .forwards = false});
chassis.turnToHeading(90, 1000);
chassis.moveToPoint(57.705, 1.101, 2000, {.maxSpeed = 127, .forwards = false});
chassis.turnToHeading(135, 1000);
chassis.waitUntilDone();


//Prepare Pin 
chassis.moveToPoint(47, 12.25, 2500, {.maxSpeed = 127, .forwards = false});
chassis.turnToHeading(180, 1000);
liftToPosition(1650);
chassis.waitUntilDone();
scoringTo90();

chassis.moveToPoint(46.75, 17.25, 1000, {.maxSpeed = 127, .forwards = false});
chassis.turnToHeading(180, 1000);
chassis.waitUntilDone();
chassis.moveToPoint(52.207, 8.876, 2000, {.maxSpeed = 127, .forwards = true});
chassis.turnToHeading(145, 1000);


//Score Pin
liftToPosition(1400);
chassis.waitUntilDone();
scoringWheelsReject();

pros::delay(1000);

scoringWheelsStop();

chassis.moveToPoint(58.552, 4.465, 2000, {.maxSpeed = 127, .forwards = true});
chassis.turnToHeading(0, 1000);


//End & Reset
liftToPosition(getNormalLiftPosition());
scoringFold();
chassis.waitUntilDone();
}