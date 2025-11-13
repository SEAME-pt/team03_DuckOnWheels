/**
 * @file RobotController.cpp
 * @brief Implementation of the RobotController that maps joystick events.
 * @ingroup Control
 * @author Team03
 * @date 2025-10-31
 * @version 1.0
 */

#include "../include/RobotController.hpp"
#include <cstdio>
#include <unistd.h>

/**
 * @brief Construct a RobotController with default parameters.
 * @details Sets default throttle, steering center angle, throttle gain and
 * deadzone. Prints a short usage/help message to stdout and initializes the
 * motor state to stopped.
 */
RobotController::RobotController() 
        : throttle(0.0f), 
            steering_angle(90.0f),
            throttle_gain(0.8f),
            deadzone(0.15f) {
    
        printf("\n=== JetRacer PS3 Controller ===\n");
        printf("Axis 0 (Left stick X): Steering (left/right)\n");
        printf("Axis 1 (Left stick Y): Throttle (forward/backward)\n");
        printf("X button (Button 0): Emergency stop\n");
        printf("Press Ctrl+C to quit\n\n");
    
        // Ensure motors are in a stopped state on startup
        robot.set_motor(throttle);
}

/**
 * @brief Handle joystick axis updates.
 * @param axis Index of the axis event.
 * @param value Raw axis value from the hardware driver.
 * @details Axis 0 is mapped to steering: the mapped value is converted to an
 * angle in the 0–180° range and sent to the servo. Axis 1 controls throttle;
 * the input is inverted (push forward = positive throttle), deadzone-applied,
 * scaled by throttle_gain and passed to motor driver.
 */
void RobotController::process_axis_event(uint8_t axis, int16_t value) {
    if (axis == 0) {
        float raw = Joystick::map_axis(value);
        float steering_input = Joystick::apply_deadzone(raw, deadzone);
        steering_angle = 90.0f + steering_input * 90.0f;
        robot.set_servo_angle(steering_angle);
        printf("Steering: %.1f°", steering_angle);
    } 
    else if (axis == 1) {
        // Invert Y axis so pushing forward yields positive throttle
        float raw = -Joystick::map_axis(value);
        throttle = Joystick::apply_deadzone(raw, deadzone) * throttle_gain;
        robot.set_motor(-1 * throttle);
        printf("Throttle: %+.2f", throttle);
    }
}

/**
 * @brief Handle button press/release events from the joystick.
 * @param button Button index from the event.
 * @param pressed True if the button was pressed, false if released.
 * @details The controller currently uses button 0 (X) as an emergency stop
 * trigger. Additional buttons can be mapped to other features here.
 */
void RobotController::process_button_event(uint8_t button, bool pressed) {
    if (button == 0 && pressed) {
        printf(">>> EMERGENCY STOP! <<<\n");
        emergency_stop();
    }
}

/**
 * @brief Immediately disable motors and center the steering servo.
 * @details Resets internal state and delegates to the DualPCA9685 driver to
 * stop PWM outputs. This is safe to call from signal handlers or event
 * callbacks.
 */
void RobotController::emergency_stop() {
    throttle = 0.0f;
    steering_angle = 90.0f;
    robot.stop_all();
}

/**
 * @brief Main event loop for processing joystick input.
 * @details Continuously polls the `Joystick` device for events and dispatches
 * them to the appropriate handlers. The loop sleeps briefly to avoid busy
 * waiting.
 */
void RobotController::run() {
    struct js_event event;
    
    while (true) {
        if (joystick.read_event(&event)) {
            if (event.type & JS_EVENT_INIT) continue;
            
            if (event.type == JS_EVENT_AXIS) {
                printf("Axis %d: %6d | ", event.number, event.value);
                process_axis_event(event.number, event.value);
                printf("\n");
            }
            else if (event.type == JS_EVENT_BUTTON) {
                printf("Button %d: %s\n", event.number, event.value ? "PRESSED" : "released");
                process_button_event(event.number, event.value);
            }
        }
        
        // Sleep 10ms between polls to reduce CPU usage while maintaining
        // responsive control loop timing.
        usleep(10000);
    }
}