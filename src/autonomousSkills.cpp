
#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"

// Skills autonomous
// Disabled until the new robot autonomous is programmed
void AutonSkills() {
    chassis.cancelAllMotions();
    scoringStop();
    liftStop();
}
