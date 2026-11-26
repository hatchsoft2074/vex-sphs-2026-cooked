
#include "main.h"
#include "toggles.h"

// Active toggle motor
pros::Motor togglesMotor(13);

// Toggle motor speed
int togglesSpeed = 127;

void togglesSetup() {
    togglesMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    togglesStop();
}

void togglesSpin() {
    togglesMotor.move(togglesSpeed);
}

void togglesStop() {
    togglesMotor.brake();
}

double getTogglesTemperature() {
    return togglesMotor.get_temperature();
}
