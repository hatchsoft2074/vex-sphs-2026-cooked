
#include "main.h"
#include "robotConfigs.h"

// Motor positions are relative to the brain.
// Left front 20, left back 18.
// Right front 9, right back 2.
// Check motor directions before driving.

pros::MotorGroup left_motor_group({20, 18}, pros::MotorGears::blue);
pros::MotorGroup right_motor_group({-9, -2}, pros::MotorGears::blue);

// Drivetrain settings
lemlib::Drivetrain drivetrain(
    &left_motor_group,
    &right_motor_group,
    10.75,
    lemlib::Omniwheel::NEW_275,
    454.5,
    2
);

// IMU on port 1
pros::Imu imu(1);

// Horizontal tracking sensor on port 10
pros::Rotation horizontal_encoder(10);

// Vertical tracking sensor on port 16
pros::Rotation vertical_encoder(-16);

// Horizontal tracking wheel
lemlib::TrackingWheel horizontal_tracking_wheel(
    &horizontal_encoder,
    lemlib::Omniwheel::NEW_2,
    -1.5
);

// Vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(
    &vertical_encoder,
    lemlib::Omniwheel::NEW_2,
    -1
);

// Odometry settings
lemlib::OdomSensors sensors(
    &vertical_tracking_wheel,
    nullptr,
    &horizontal_tracking_wheel,
    nullptr,
    &imu
);

// Lateral (forward/backward) PID controller
lemlib::ControllerSettings lateral_controller(
    10,  // proportional gain (kP)
    0,   // integral gain (kI)
    3,   // derivative gain (kD)
    3,   // anti windup
    1,   // small error range, in inches
    100, // small error range timeout, in milliseconds
    3,   // large error range, in inches
    500, // large error range timeout, in milliseconds
    0    // maximum acceleration (slew)
);

// Angular (turning) PID controller
lemlib::ControllerSettings angular_controller(
    4,   // proportional gain (kP)
    0,   // integral gain (kI)
    3,   // derivative gain (kD)
    0,   // anti windup
    1,   // small error range, in degrees
    100, // small error range timeout, in milliseconds
    3,   // large error range, in degrees
    500, // large error range timeout, in milliseconds
    0    // maximum acceleration (slew)
);


// Chassis
lemlib::Chassis chassis(
    drivetrain,
    lateral_controller,
    angular_controller,
    sensors,
    &throttle_curve,
    &steer_curve
);
