
#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"

// Left autonomous
// Disabled until the new robot autonomous is programmed
void AutonCompLeft() {
    chassis.cancelAllMotions();
    scoringStop();
    liftStop();
}
