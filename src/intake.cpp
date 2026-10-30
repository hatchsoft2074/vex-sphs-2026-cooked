# include "lift.h"
# include "main.h"
# include "opcontrol.h"
# include "robotConfigs.h"
# include "intake.h"
# include <algorithm>

pros::MotorGroup intake_motors({20, -17}, pros::MotorGears::green);

// speed of the intake
int intakeSpeed = 127;

//intake initializer
void intakeSetup() {
    intake_motors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void intakeAccept() {
    intake_motors.move(intakeSpeed);
}

void intakeReject() {
    intake_motors.move(-intakeSpeed);
}

void intakeStop() {
    intake_motors.move(0);
}

double getIntakeTemperature() {
    double hottest = 0;
    for (double t : intake_motors.get_temperature_all()) {
        hottest = std::max(hottest, t);
    }
    return hottest;
}