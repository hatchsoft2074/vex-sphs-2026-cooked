
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
void scoringTo90();
void scoringFold();
void scoringToPin();
void scoringToPickup();

// Timed scoring wheels
void scoringRejectFor(int milliseconds);
