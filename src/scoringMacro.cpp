
#include "scoringMacro.h"
#include "main.h"
#include "lift.h"

// Cascade lowering macro
bool scoringMacroEnabled = false;

void startScoringMacro() {
    // Stop previous automatic movement
    cancelLiftAsync();
    cancelMatchLoad();

    // Start lowering to position 0
    scoringMacroEnabled = true;
    liftToPositionAsync(0, 5000);
}

void updateScoringMacro() {
    // Stop tracking when movement finishes
    if (scoringMacroEnabled && !isLiftAsyncMoving()) {
        scoringMacroEnabled = false;
    }
}

bool isScoringMacroRunning() {
    return scoringMacroEnabled && isLiftAsyncMoving();
}

bool isScoringPositionActive() {
    return false;
}
