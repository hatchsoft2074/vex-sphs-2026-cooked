#include "main.h"
#include "autonomous.hpp"
#include "robotConfigs.h"
#include "lift.h"
#include "scoring.h"
#include "toggles.h"
#include "scoringMacro.h"

void AutonCompRight() {
chassis.setPose(0, 0, 0);
chassis.moveToPoint(0, 10, 4000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}, false);
}