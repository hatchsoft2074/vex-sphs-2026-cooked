
#include "scoring.h"
#include "main.h"
#include <algorithm>
#include "lift.h"

// Scoring motors
pros::Motor scoringMech(8);
pros::Motor scoringWheelMotor(9);

int scoringMechSpeed = 70;
int scoringWheelsSpeed = 127;

// Automatic scoring settings
double scoringAutoUpHeight = 1850;
double scoringAutoDownHeight = 1400;
double scoring90Position = 850;
double scoringFoldedPosition = 0;
double scoringPinPosition = 600;
double scoringPickupPosition = 1150;
double scoringAutoTolerance = 25;

double previousLiftPosition = 0;
bool scoringAutoMovingUp = false;
bool scoringAutoMovingDown = false;
bool scoringDirection = true;

void scoringSetup() {
    scoringMech.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    scoringMech.tare_position();
    previousLiftPosition = getLiftPosition();
}

void scoringMechUp() {
    scoringMech.move(scoringMechSpeed);
}

void scoringMechDown() {
    scoringMech.move(-scoringMechSpeed);
}

void scoringMechStop() {
    scoringMech.move(0);
}

void scoringWheels() {
    scoringWheelMotor.move(
        scoringDirection ? -scoringWheelsSpeed : scoringWheelsSpeed
    );
}

void scoringWheelsAccept() {
    scoringWheelMotor.move(-scoringWheelsSpeed);
}

void scoringWheelsReject() {
    scoringWheelMotor.move(scoringWheelsSpeed);
}

void scoringWheelsStop() {
    scoringWheelMotor.move(0);
}

void changeScoringDirection() {
    scoringDirection = !scoringDirection;
}

void checkScoringAutoTrigger() {
    double currentLiftPosition = getLiftPosition();

    if (previousLiftPosition < scoringAutoUpHeight &&
        currentLiftPosition >= scoringAutoUpHeight) {
        scoringAutoMovingUp = true;
        scoringAutoMovingDown = false;
    }

    if (previousLiftPosition > scoringAutoDownHeight &&
        currentLiftPosition <= scoringAutoDownHeight) {
        scoringAutoMovingUp = false;
        scoringAutoMovingDown = true;
    }

    previousLiftPosition = currentLiftPosition;
}

bool updateScoringAuto() {
    checkScoringAutoTrigger();

    if (scoringAutoMovingUp) {
        if (getScoringMechPosition() <
            scoring90Position - scoringAutoTolerance) {
            scoringMechUp();
            return true;
        }

        scoringMechStop();
        scoringAutoMovingUp = false;
        return false;
    }

    if (scoringAutoMovingDown) {
        if (getScoringMechPosition() >
            scoringFoldedPosition + scoringAutoTolerance) {
            scoringMechDown();
            return true;
        }

        scoringMechStop();
        scoringAutoMovingDown = false;
        return false;
    }

    return false;
}

void cancelScoringAuto() {
    scoringAutoMovingUp = false;
    scoringAutoMovingDown = false;
}

void syncScoringAuto() {
    previousLiftPosition = getLiftPosition();
    scoringAutoMovingUp = false;
    scoringAutoMovingDown = false;
}

bool isScoringAutoMovingUp() {
    return scoringAutoMovingUp;
}

bool isScoringAutoRunning() {
    return scoringAutoMovingUp || scoringAutoMovingDown;
}

double getScoringMechPosition() {
    return scoringMech.get_position();
}

double getScoringTemperature() {
    return std::max(
        scoringMech.get_temperature(),
        scoringWheelMotor.get_temperature()
    );
}

void resetScoringMechPosition() {
    scoringMech.tare_position();
}

// Move claw to the 90 degree position
void scoringTo90() {
    cancelScoringAuto();

    unsigned int start = pros::millis();

    while (pros::millis() - start < 2000) {
        if (getScoringMechPosition() >=
            scoring90Position - scoringAutoTolerance) {
            break;
        }

        scoringMechUp();
        pros::delay(20);
    }

    scoringMechStop();
}

// Fold claw back to its starting position
void scoringFold() {
    cancelScoringAuto();

    unsigned int start = pros::millis();

    while (pros::millis() - start < 2000) {
        if (getScoringMechPosition() <=
            scoringFoldedPosition + scoringAutoTolerance) {
            break;
        }

        scoringMechDown();
        pros::delay(20);
    }

    scoringMechStop();
}

// Move claw to position 600 for picking up pins
void scoringToPin() {
    cancelScoringAuto();

    unsigned int start = pros::millis();

    while (pros::millis() - start < 2000) {
        double currentPosition = getScoringMechPosition();

        if (currentPosition < scoringPinPosition - scoringAutoTolerance) {
            scoringMechUp();
        } else if (currentPosition > scoringPinPosition + scoringAutoTolerance) {
            scoringMechDown();
        } else {
            break;
        }

        pros::delay(20);
    }

    scoringMechStop();
}

// Move claw to the pickup position
void scoringToPickup() {
    cancelScoringAuto();

    unsigned int start = pros::millis();

    while (pros::millis() - start < 2000) {
        double currentPosition = getScoringMechPosition();

        if (currentPosition < scoringPickupPosition - scoringAutoTolerance) {
            scoringMechUp();
        } else if (currentPosition > scoringPickupPosition + scoringAutoTolerance) {
            scoringMechDown();
        } else {
            break;
        }

        pros::delay(20);
    }

    scoringMechStop();
}

// Run scoring wheels in reject direction for a set time
void scoringRejectFor(int milliseconds) {
    scoringWheelsReject();
    pros::delay(milliseconds);
    scoringWheelsStop();
}
