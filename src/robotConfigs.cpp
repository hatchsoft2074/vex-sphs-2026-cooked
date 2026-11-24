
#include "main.h"
#include "robotConfigs.h"

// The claw is at the front of the robot.
// Left front 20, left back 19.
// Right front 21, right back 10.
// Check motor directions before driving.

pros::MotorGroup left_motor_group({20, 19}, pros::MotorGears::blue);
pros::MotorGroup right_motor_group({-21, -10}, pros::MotorGears::blue);

// Drivetrain settings
lemlib::Drivetrain drivetrain(
    &left_motor_group,
    &right_motor_group,
    10.75,
    lemlib::Omniwheel::NEW_275,
    454.5,
    2
);

// IMU
pros::Imu imu(14);

// Port 18 is now used by the cascade.
// Horizontal tracking is disabled for now.

// Vertical tracking sensor on port 13
pros::Rotation vertical_encoder(-13);

lemlib::TrackingWheel vertical_tracking_wheel(
    &vertical_encoder,
    lemlib::Omniwheel::NEW_2,
    0
);

// Odometry settings
lemlib::OdomSensors sensors(
    &vertical_tracking_wheel,
    nullptr,
    nullptr,
    nullptr,
    &imu
);

// Lateral PID
lemlib::ControllerSettings lateral_controller(
    10, 0, 3, 3, 1, 100, 3, 500, 0
);

// Angular PID
lemlib::ControllerSettings angular_controller(
    4, 0, 3, 0, 1, 100, 3, 500, 0
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
