#include "autonomous.hpp"
#include "lift.h"
#include "scoring.h"

void AutonCompRight(){


chassis.moveToPoint(0, 10, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(90, 1000);
chassis.moveToPoint(10, 10, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(180, 1000);
chassis.moveToPoint(10, 0, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(270, 1000);
chassis.moveToPoint(0, 0, 4000, {.forwards = true, .maxSpeed = 127});
chassis.turnToHeading(0, 1000);
}