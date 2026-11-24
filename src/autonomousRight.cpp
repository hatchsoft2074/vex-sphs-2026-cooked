
#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"

// Right autonomous
// Disabled until the new robot autonomous is programmed
void AutonCompRight() {
    chassis.cancelAllMotions();
    scoringStop();
    liftStop();
}
