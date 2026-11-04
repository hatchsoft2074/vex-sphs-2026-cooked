
#include "scoringMacro.h"
#include "main.h"
#include "robotConfigs.h"
#include "lift.h"
#include "scoring.h"

bool scoringMacroEnabled = true;

// Macro settings
double macroLiftTolerance = 20;
double macroScoringFoldTolerance = 50;
int macroSafetyTimeout = 10000;
int macroScoringTimeout = 2000;

enum ScoringMacroState {
    MACRO_IDLE,
    MACRO_RETURNING_LIFT,
    MACRO_RETURNING_SCORING
};

ScoringMacroState scoringMacroState = MACRO_IDLE;

uint32_t scoringMacroStartTime = 0;
uint32_t macroScoringStartTime = 0;

void finishScoringMacro() {
    liftStop();
    scoringMechStop();

    scoringMacroState = MACRO_IDLE;
    syncScoringAuto();
}

void startScoringMacro() {
    if (!scoringMacroEnabled || scoringMacroState != MACRO_IDLE) {
        return;
    }

    cancelMatchLoad();
    cancelScoringAuto();

    liftStop();
    scoringMechStop();

    scoringMacroStartTime = pros::millis();
    scoringMacroState = MACRO_RETURNING_LIFT;
}

void updateScoringMacro() {
    if (scoringMacroState == MACRO_IDLE) {
        return;
    }

    // Stop the macro if it takes too long
    if (pros::millis() - scoringMacroStartTime >=
        static_cast<uint32_t>(macroSafetyTimeout)) {
        finishScoringMacro();
        return;
    }

    // Lower the cascade to intake height first
    if (scoringMacroState == MACRO_RETURNING_LIFT) {
        scoringMechStop();

        if (moveLiftToPosition(getNormalLiftPosition())) {
            liftStop();
            macroScoringStartTime = pros::millis();
            scoringMacroState = MACRO_RETURNING_SCORING;
        }

        return;
    }

    // Fold the claw after the cascade reaches intake
    if (scoringMacroState == MACRO_RETURNING_SCORING) {
        liftStop();

        double scoringPosition = getScoringMechPosition();

        if (scoringPosition > macroScoringFoldTolerance) {
            scoringMechDown();
        }
        else if (scoringPosition < -macroScoringFoldTolerance) {
            scoringMechUp();
        }
        else {
            finishScoringMacro();
            return;
        }

        // Stop if the claw cannot reach the target
        if (pros::millis() - macroScoringStartTime >=
            static_cast<uint32_t>(macroScoringTimeout)) {
            finishScoringMacro();
        }

        return;
    }
}

bool isScoringMacroRunning() {
    return scoringMacroState != MACRO_IDLE;
}

bool isScoringPositionActive() {
    return false;
}
