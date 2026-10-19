#inlcude "autonomous.h"

//Competition Auton
void AutonComp() {

    //Toggling
left_motor_group(80);
right_motor_group(80);
left_motor_group(-80);
right_motor_group(-80);
pros::delay(250);
left_motor_group(80);
right_motor_group(80);
left_motor_group(-80);
right_motor_group(-80);

    //First Pin
chassis.moveToPoint(50.388, 19.788, 4000, {.maxSpeed = 127, .forwards = false});
chassis.turnToHeading(139.39, 1000);
chassis.moveToPoint(54.982, 18.388, 4000, {.maxSpeed = 127, .forwards = true});
chassis.turnToHeading(348.665, 1000);
liftUp();
scoring90Position(890);
liftStop();
liftDown();
liftStop();
scoringWheelMotor(-20);
scoringWheelMotor(0);

    //Second Pin
chassis.moveToPoint(46.732, 43.019, 4000, {.maxSpeed = 127, .forwards = true});
chassis.turnToHeading(176.73, 1000);
liftDown();
liftStop();
chassis.moveToPoint(46.913, 27.623, 4000, {.maxSpeed = 127, .forwards = true});
chassis.turnToHeading(0, 1000);
liftUp();
liftStop();
scoringWheelMotor(45);
liftDown();
liftStop();
chassis.moveToPoint(58.506, 58.053, 4000, {.maxSpeed = 127, .forwards = true});
chassis.turnToHeading(90.053, 1000);
liftUp();
liftStop();
liftDown();
liftStop();
scoringWheelMotor(-20);
scoringWheelMotor(0);

    //To Match Loader
chassis.moveToPoint(65.414, 58.047, 4000, {.maxSpeed = 127, .forwards = true});
chassis.turnToHeading(90, 1000);
}