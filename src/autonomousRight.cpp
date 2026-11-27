#include "main.h"
#include "autonomous.hpp"
#include "robotConfigs.h"
#include "lift.h"
#include "scoring.h"
#include "toggles.h"
#include "scoringMacro.h"

void AutonCompRight() {
 // set position to x:0, y:0, heading:0
    chassis.setPose(0, 0, 0);
    // turn to face heading 90 with a very long timeout
    chassis.moveToPoint(0, 10, 0, 10000);
}