/**
 * @file RobotController.hpp
 * @brief High level robot control logic connecting joystick input to actuators.
 * @ingroup Control
 * @author Team03
 * @date 2025-10-31
 * @version 1.0
 */

#ifndef ROBOTCONTROLLER_HPP
#define ROBOTCONTROLLER_HPP

#include "DualPCA9685.hpp"
#include "Joystick.hpp"

/**
 * @class RobotController
 * @brief Handles joystick input and translates it into motor and servo commands.
 *
 * The controller reads joystick events and maps axes/buttons to throttle and
 * steering commands. It also provides an emergency stop routine to immediately
 * disable actuators.
 */
class RobotController {
private:
    DualPCA9685 robot;
    Joystick joystick;
    
    float throttle;
    float steering_angle;
    float throttle_gain;
    float deadzone;

public:
    /**
     * @brief Construct a RobotController and initialize defaults.
     * @details Initializes joystick and motor/servo trims, prints usage help.
     */
    RobotController();
    
    /**
     * @brief Start the main control loop and process joystick events.
     * @details Blocks until the process is terminated. Reads events from the
     * Joystick and dispatches to axis/button handlers.
     */
    void run();  

    /**
     * @brief Process joystick axis events.
     * @param axis Axis index (e.g., 0 for steering, 1 for throttle).
     * @param value Raw axis value from joystick.
     * @details Maps the raw axis value to normalized input, applies deadzone
     * and throttle gains, and sends commands to the robot actuator driver.
     */
    void process_axis_event(uint8_t axis, int16_t value);

    /**
     * @brief Handle joystick button events.
     * @param button Button index.
     * @param pressed True when the button is pressed.
     * @details Currently the X button (0) triggers emergency stop when pressed.
     */
    void process_button_event(uint8_t button, bool pressed);

    /**
     * @brief Immediately stop motors and center steering.
     * @details Resets throttle and steering to safe values and disables PWM.
     */
    void emergency_stop();
};

#endif