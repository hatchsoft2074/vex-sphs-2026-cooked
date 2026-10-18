#include "autonomous.hpp"

// Move scoring mechanism
void autonScoringPosition(double target) {
    unsigned int start = pros::millis();

    while (pros::millis() - start < 2000) {
        double current = getScoringMechPosition();

        if (current < target - 20) {
            scoringMechUp();
        } else if (current > target + 20) {
            scoringMechDown();
        } else {
            break;
        }

        pros::delay(20);
    }

    scoringMechStop();
}

// Competition
void AutonComp() {

    // Toggling
    left_motor_group.move(80);
    right_motor_group.move(80);
    left_motor_group.move(-80);
    right_motor_group.move(-80);
    pros::delay(250);
    left_motor_group.move(80);
    right_motor_group.move(80);
    left_motor_group.move(-80);
    right_motor_group.move(-80);

    // First Pin
    chassis.moveToPoint(50.388, 19.788, 4000, {.forwards = false, .maxSpeed = 127});
    chassis.turnToHeading(139.39, 1000);
    chassis.moveToPoint(54.982, 18.388, 4000, {.forwards = true, .maxSpeed = 127});
    chassis.turnToHeading(348.665, 1000);
    liftUp();
    autonScoringPosition(890);
    liftStop();
    liftDown();
    liftStop();
    scoringWheelsAccept();
    scoringWheelsStop();

    // Second Pin
    chassis.moveToPoint(46.732, 43.019, 4000, {.forwards = true, .maxSpeed = 127});
    chassis.turnToHeading(176.73, 1000);
    liftDown();
    liftStop();
    chassis.moveToPoint(46.913, 27.623, 4000, {.forwards = true, .maxSpeed = 127});
    chassis.turnToHeading(0, 1000);
    liftUp();
    liftStop();
    scoringWheelsReject();
    liftDown();
    liftStop();
    chassis.moveToPoint(58.506, 58.053, 4000, {.forwards = true, .maxSpeed = 127});
    chassis.turnToHeading(90.053, 1000);
    liftUp();
    liftStop();
    liftDown();
    liftStop();
    scoringWheelsAccept();
    scoringWheelsStop();

    // To Match Loader
    chassis.moveToPoint(65.414, 58.047, 4000, {.forwards = true, .maxSpeed = 127});
    chassis.turnToHeading(90, 1000);
}