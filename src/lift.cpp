#include "lift.h"
#include "main.h"
#include <algorithm>
#include <atomic>

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

int liftMediumSpeed = 50;
int liftSlowSpeed = 25;
int liftFinalSpeed = 18;

bool matchLoadMoving = false;
double matchLoadTarget = 0;

// Async lift settings
std::atomic<bool> liftAsyncMoving(false);
std::atomic<double> liftAsyncTarget(0);
std::atomic<unsigned int> liftAsyncStart(0);
std::atomic<unsigned int> liftAsyncTimeout(3000);

void liftStop() {
liftMotor1.move(0);
liftMotor2.move(0);
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

liftMotor1.tare_position();
liftMotor2.tare_position();

matchLoadMoving = false;
liftAsyncMoving = false;
liftStop();

// Run the async lift controller in the background
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

double getLiftPosition() {
return liftMotor1.get_position() + normalLiftPosition;
}

double getLiftTemperature() {
return std::max(
liftMotor1.get_temperature(),
liftMotor2.get_temperature()
);
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

// Manual lift up at full speed
void liftUp() {
liftAsyncMoving = false;
cancelMatchLoad();

liftMotor1.move(liftSpeed);
liftMotor2.move(liftSpeed);
}

// Manual lift down with slowdown near normal height
void liftDown() {
liftAsyncMoving = false;
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

// Move lift and wait until it finishes
void liftToPosition(double targetPosition, int timeout) {
cancelLiftAsync();
cancelMatchLoad();

unsigned int start = pros::millis();

while (pros::millis() - start < static_cast<unsigned int>(std::max(0, timeout))) {
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
liftAsyncTarget = targetPosition;
liftAsyncTimeout = static_cast<unsigned int>(std::max(0, timeout));
liftAsyncStart = pros::millis();
liftAsyncMoving = true;
}

void toggleMatchLoad() {
cancelLiftAsync();

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