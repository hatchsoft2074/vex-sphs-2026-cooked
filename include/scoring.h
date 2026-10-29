#pragma once

void scoringSetup();

void scoringMechUp();
void scoringMechDown();
void scoringMechStop();

void scoringWheels();
void scoringWheelsAccept();
void scoringWheelsReject();
void scoringWheelsStop();

void changeScoringDirection();

void checkScoringAutoTrigger();
bool updateScoringAuto();

void cancelScoringAuto();
void syncScoringAuto();

bool isScoringAutoMovingUp();
bool isScoringAutoRunning();

double getScoringMechPosition();
double getScoringTemperature();

void resetScoringMechPosition();

// Autonomous scoring functions
void scoringTo90();
void scoringFold();
void scoringRejectFor(int milliseconds);