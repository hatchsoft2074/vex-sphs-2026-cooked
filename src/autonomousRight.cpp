#include "main.h"
#include "autonomous.hpp"
#include "robotConfigs.h"
#include "lift.h"
#include "scoring.h"
#include "toggles.h"
#include "scoringMacro.h"

void AutonCompRight() {
chassis.setPose(65.155, 4.858, 90.899);
chassis.moveToPoint(49.144, 6.53, 4000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0}, false);
chassis.turnToHeading(177.435, 2000, {.maxSpeed = 127, .minSpeed = 0}, false);
liftToPositionAsync(600, 4000);

chassis.moveToPose(46.839, 18.805, 180.855, 4000, {.forwards = false, .lead = 0.6, .maxSpeed = 127, .minSpeed = 0}, false);
chassis.turnToHeading(180.855, 2000, {.maxSpeed = 127, .minSpeed = 0}, false);
liftToPosition(100, 4000);
scoringOpen();
chassis.moveToPoint(46.659, 5.606, 4000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}, false);
chassis.turnToHeading(178.909, 2000, {.maxSpeed = 127, .minSpeed = 0}, false);
scoringStop();
liftToPositionAsync(getNormalLiftPosition());
chassis.moveToPose(29.682, 14.901, 140.681, 4000, {.forwards = false, .lead = 0.831, .maxSpeed = 127, .minSpeed = 0}, false);
chassis.turnToHeading(140.681, 2000, {.maxSpeed = 127, .minSpeed = 0}, false);
scoringClose();
chassis.moveToPose(26.63, 19.482, 141.582, 4000, {.forwards = false, .lead = 0.6, .maxSpeed = 127, .minSpeed = 0}, false);
chassis.turnToHeading(141.582, 2000, {.maxSpeed = 127, .minSpeed = 0}, false);
liftToPositionAsync(1300, 4000);

chassis.moveToPose(32.668, 26.945, 271.302, 4000, {.forwards = false, .lead = 0.6, .maxSpeed = 127, .minSpeed = 0}, false);
chassis.turnToHeading(271.302, 2000, {.maxSpeed = 127, .minSpeed = 0}, false);
scoringStop();
chassis.moveToPose(42.349, 23.826, 269.199, 4000, {.forwards = false, .lead = 0.6, .maxSpeed = 127, .minSpeed = 0}, false);
chassis.turnToHeading(269.199, 2000, {.maxSpeed = 127, .minSpeed = 0}, false);
liftToPosition(900, 4000);
scoringOpen();
chassis.moveToPoint(31.675, 31.634, 4000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0}, false);
chassis.turnToHeading(227.291, 2000, {.maxSpeed = 127, .minSpeed = 0}, false);
scoringStop();
chassis.moveToPoint(38.881, 37.41, 4000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0}, false);
chassis.turnToHeading(216.498, 2000, {.maxSpeed = 127, .minSpeed = 0}, false);
scoringClose();
chassis.moveToPose(43.603, 43.324, 222.709, 4000, {.forwards = false, .lead = 0.6, .maxSpeed = 127, .minSpeed = 0}, false);
chassis.turnToHeading(222.709, 2000, {.maxSpeed = 127, .minSpeed = 0}, false);
liftToPositionAsync(1700, 4000);

chassis.moveToPose(48.733, 38.433, 2.49, 4000, {.forwards = true, .lead = 0.6, .maxSpeed = 127, .minSpeed = 0}, false);
chassis.turnToHeading(2.49, 2000, {.maxSpeed = 127, .minSpeed = 0}, false);
scoringStop();
chassis.moveToPose(46.943, 27.817, 0, 4000, {.forwards = false, .lead = 0.6, .maxSpeed = 127, .minSpeed = 0}, false);
chassis.turnToHeading(0, 2000, {.maxSpeed = 127, .minSpeed = 0}, false);
liftToPosition(1300, 4000);
}