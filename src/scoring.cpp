
#include "scoring.h"
#include "main.h"

// Ratchet claw motor on port 14
pros::Motor scoringMotor(14);

int scoringSpeed = 127;

void scoringSetup() {
    scoringMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    scoringMotor.move(0);
}

// Close the ratchet claw
void scoringClose() {
    scoringMotor.move(scoringSpeed);
}

// Open the ratchet claw
void scoringOpen() {
    scoringMotor.move(-scoringSpeed);
}

// Stop the ratchet claw
void scoringStop() {
    scoringMotor.move(0);
}

// Get the claw motor temperature
double getScoringTemperature() {
    return scoringMotor.get_temperature();
}
