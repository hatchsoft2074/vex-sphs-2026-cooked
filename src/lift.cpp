
#include "lift.h"
#include "main.h"
#include <algorithm>
#include <atomic>

// Cascade winch motors
// Left: 21
// Top right: 15
// Bottom right: 19

pros::Motor liftMotor1(21);
pros::Motor liftMotor2(-15);
pros::Motor liftMotor3(-19);

int liftSpeed = 127;

// Cascade positions
double matchLoadPosition = 0;
double normalLiftPosition = 0;
double maxLiftPosition = 2400;

double liftPositionTolerance = 20;

bool matchLoadMoving = false;
double matchLoadTarget = 0;

// Async lift settings
std::atomic<bool> liftAsyncMoving(false);
std::atomic<double> liftAsyncTarget(0);
std::atomic<unsigned int> liftAsyncStart(0);
std::atomic<unsigned int> liftAsyncTimeout(3000);

// Move all three winch motors together
static void moveAllLiftMotors(int speed) {
    liftMotor1.move(speed);
    liftMotor2.move(speed);
    liftMotor3.move(speed);
}

void liftStop() {
    moveAllLiftMotors(0);
}

void cancelLiftAsync() {
    liftAsyncMoving = false;
    liftStop();
}

bool isLiftAsyncMoving() {
    return liftAsyncMoving.load();
}

void liftSetup() {
    liftMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    liftMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    liftMotor3.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    // Start with the cascade fully lowered
    liftMotor1.tare_position();
    liftMotor2.tare_position();
    liftMotor3.tare_position();

    matchLoadMoving = false;
    liftAsyncMoving = false;
    liftStop();

    // Background lift controller
    static pros::Task liftTask([] {
        while (true) {
            if (liftAsyncMoving.load()) {
                double target = liftAsyncTarget.load();
                unsigned int start = liftAsyncStart.load();
                unsigned int timeout = liftAsyncTimeout.load();

                if (moveLiftToPosition(target) ||
                    pros::millis() - start >= timeout) {
                    liftAsyncMoving = false;
                    liftStop();
                }
            }

            pros::delay(20);
        }
    });
}

// Position 0 is fully lowered
double getLiftPosition() {
    return liftMotor1.get_position();
}

// Return the hottest winch motor temperature
double getLiftTemperature() {
    return std::max({
        liftMotor1.get_temperature(),
        liftMotor2.get_temperature(),
        liftMotor3.get_temperature()
    });
}

double getNormalLiftPosition() {
    return normalLiftPosition;
}

double getMatchLoadPosition() {
    return matchLoadPosition;
}

double getMaxLiftPosition() {
    return maxLiftPosition;
}

// Manual lift up at full speed
void liftUp() {
    liftAsyncMoving = false;
    cancelMatchLoad();

    if (getLiftPosition() >= maxLiftPosition) {
        liftStop();
        return;
    }

    moveAllLiftMotors(liftSpeed);
}

// Manual lift down at full speed
void liftDown() {
    liftAsyncMoving = false;
    cancelMatchLoad();

    if (getLiftPosition() <= 0) {
        liftStop();
        return;
    }

    moveAllLiftMotors(-liftSpeed);
}

// Move toward a target at full speed
bool moveLiftToPosition(double targetPosition) {
    targetPosition = std::clamp(
        targetPosition,
        0.0,
        maxLiftPosition
    );

    double error = targetPosition - getLiftPosition();

    if (error > liftPositionTolerance) {
        moveAllLiftMotors(liftSpeed);
        return false;
    }

    if (error < -liftPositionTolerance) {
        moveAllLiftMotors(-liftSpeed);
        return false;
    }

    liftStop();
    return true;
}

// Move lift and wait until it finishes
void liftToPosition(double targetPosition, int timeout) {
    cancelLiftAsync();
    cancelMatchLoad();

    unsigned int start = pros::millis();

    while (
        pros::millis() - start <
        static_cast<unsigned int>(std::max(0, timeout))
    ) {
        if (moveLiftToPosition(targetPosition)) {
            break;
        }

        pros::delay(20);
    }

    liftStop();
}

// Start moving lift without waiting
void liftToPositionAsync(double targetPosition, int timeout) {
    cancelMatchLoad();

    liftAsyncMoving = false;
    liftAsyncTarget = std::clamp(
        targetPosition,
        0.0,
        maxLiftPosition
    );
    liftAsyncTimeout =
        static_cast<unsigned int>(std::max(0, timeout));
    liftAsyncStart = pros::millis();
    liftAsyncMoving = true;
}

// Match-load button lowers the cascade to 0
void toggleMatchLoad() {
    cancelLiftAsync();

    matchLoadTarget = 0;
    matchLoadMoving = true;
}

// Update the lowering macro
void updateMatchLoad() {
    if (!matchLoadMoving) {
        return;
    }

    if (moveLiftToPosition(matchLoadTarget)) {
        matchLoadMoving = false;
    }
}

void cancelMatchLoad() {
    matchLoadMoving = false;
}

bool isMatchLoadMoving() {
    return matchLoadMoving;
}
