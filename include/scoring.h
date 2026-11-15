#pragma once

// Scoring setup
void scoringSetup();

// Manual claw controls
void scoringMechUp();
void scoringMechDown();
void scoringMechStop();

// Scoring wheels
void scoringWheels();
void scoringWheelsAccept();
void scoringWheelsReject();
void scoringWheelsStop();
void changeScoringDirection();

// Automatic claw controls
void checkScoringAutoTrigger();
bool updateScoringAuto();
void cancelScoringAuto();
void syncScoringAuto();
bool isScoringAutoMovingUp();
bool isScoringAutoRunning();

// Scoring information
double getScoringMechPosition();
double getScoringTemperature();
void resetScoringMechPosition();

// Claw positions for autonomous
void scoringTo90(int timeout = 2000);
void scoringFold(int timeout = 2000);
void scoringToPin(int timeout = 2000);
void scoringToPickup(int timeout = 2000);

// Timed scoring wheels
void scoringRejectFor(int milliseconds);