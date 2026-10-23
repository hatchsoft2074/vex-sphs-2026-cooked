
#include "lift.h"
#include "main.h"

pros::Motor liftMotor1(10);
pros::Motor liftMotor2(-16);

int liftSpeed = 127;

double matchLoadPosition = 0;
double normalLiftPosition = 1400;
double maxLiftPosition = 4130;

double liftPositionTolerance = 20;
double liftSlowdownStart = 600;
double liftMediumDistance = 300;
double liftFinalDistance = 100;

int liftMediumSpeed = 65;
int liftSlowSpeed = 30;
int liftFinalSpeed = 35;

bool matchLoadMoving = false;
double matchLoadTarget = 0;

void liftStop() {
    liftMotor1.move(0);
    liftMotor2.move(0);
}

void liftSetup() {
    liftMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    liftMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    liftMotor1.tare_position();
    liftMotor2.tare_position();

    matchLoadMoving = false;
    liftStop();
}

double getLiftPosition() {
    return liftMotor1.get_position() + normalLiftPosition;
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

int getLiftDownSpeed(double distance) {
    if (distance <= liftFinalDistance) {
        return liftFinalSpeed;
    }

    if (distance <= liftMediumDistance) {
        return liftSlowSpeed;
    }

    if (distance <= liftSlowdownStart) {
        return liftMediumSpeed;
    }

    return liftSpeed;
}

void liftUp() {
    cancelMatchLoad();

    liftMotor1.move(liftSpeed);
    liftMotor2.move(liftSpeed);
}

void liftDown() {
    cancelMatchLoad();

    double distance = getLiftPosition() - normalLiftPosition;

    if (distance <= 0) {
        liftStop();
        return;
    }

    int speed = getLiftDownSpeed(distance);

    liftMotor1.move(-speed);
    liftMotor2.move(-speed);
}

bool moveLiftToPosition(double targetPosition) {
    double error = targetPosition - getLiftPosition();

    if (error > liftPositionTolerance) {
        int speed = liftSpeed;

        if (error <= liftFinalDistance) {
            speed = liftFinalSpeed;
        } else if (error <= liftMediumDistance) {
            speed = liftSlowSpeed;
        } else if (error <= liftSlowdownStart) {
            speed = liftMediumSpeed;
        }

        liftMotor1.move(speed);
        liftMotor2.move(speed);

        return false;
    }

    if (error < -liftPositionTolerance) {
        int speed = getLiftDownSpeed(-error);

        liftMotor1.move(-speed);
        liftMotor2.move(-speed);

        return false;
    }

    liftStop();
    return true;
}

// Move lift to a position and wait until finished
void liftToPosition(double targetPosition) {
    unsigned int start = pros::millis();

    while (pros::millis() - start < 3000) {
        if (moveLiftToPosition(targetPosition)) {
            break;
        }

        pros::delay(20);
    }

    liftStop();
}

void toggleMatchLoad() {
    double currentPosition = getLiftPosition();

    if (currentPosition >= normalLiftPosition - liftPositionTolerance) {
        matchLoadTarget = matchLoadPosition;
    } else {
        matchLoadTarget = normalLiftPosition;
    }

    matchLoadMoving = true;
}

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
