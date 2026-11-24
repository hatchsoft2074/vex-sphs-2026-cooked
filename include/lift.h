
#pragma once

void liftSetup();

void liftUp();
void liftDown();
void liftStop();

double getLiftPosition();
double getLiftTemperature();

double getNormalLiftPosition();
double getMatchLoadPosition();
double getMaxLiftPosition();

bool moveLiftToPosition(double targetPosition);

void liftToPosition(double targetPosition, int timeout = 3000);
void liftToPositionAsync(double targetPosition, int timeout = 3000);

bool isLiftAsyncMoving();
void cancelLiftAsync();

void toggleMatchLoad();
void updateMatchLoad();
void cancelMatchLoad();
bool isMatchLoadMoving();
