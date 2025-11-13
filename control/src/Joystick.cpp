/**
 * @file Joystick.cpp
 * @brief Implementation of the Joystick wrapper used by RobotController.
 * @ingroup Control
 * @author Team03
 * @date 2025-10-31
 * @version 1.0
 */

#include "../include/Joystick.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <cstring>
#include <stdexcept>
#include <cstdio>
#include <cmath>

/**
 * @brief Open the joystick device in non-blocking mode and print the name.
 * @param device Path to the joystick device node.
 * @throws runtime_error if the device cannot be opened.
 */
Joystick::Joystick(const char* device) {
    fd = open(device, O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        throw std::runtime_error("Failed to open joystick. Make sure controller is connected!");
    }
    
    char name[128];
    if (ioctl(fd, JSIOCGNAME(sizeof(name)), name) < 0) {
        strcpy(name, "Unknown");
    }
    // Informational: which joystick was opened
    printf("Joystick connected: %s\n", name);
}

Joystick::~Joystick() {
    if (fd >= 0) close(fd);
}

/**
 * @brief Attempt to read one js_event from the device.
 * @param event Pointer to js_event to populate.
 * @return true if a full event was read, false otherwise.
 */
bool Joystick::read_event(struct js_event* event) {
    int bytes = read(fd, event, sizeof(*event));
    if (bytes == sizeof(*event)) {
        return true;
    }
    return false;
}

/**
 * @brief Normalize raw axis value to floating range [-1, 1].
 */
float Joystick::map_axis(int16_t value) {
    return value / 32767.0f;
}

/**
 * @brief Map raw axis value to servo angle in degrees.
 */
float Joystick::map_axis_to_angle(int16_t value) {
    return 90.0f + (value / 32767.0f) * 90.0f;
}

/**
 * @brief Apply a deadzone to an axis value and re-scale the remaining range.
 * @param value Input in [-1,1].
 * @param deadzone Threshold to zero out small inputs.
 * @return Scaled value where range immediately outside deadzone maps to
 *         [0,1].
 */
float Joystick::apply_deadzone(float value, float deadzone) {
    if (fabs(value) < deadzone) return 0.0f;
    
    float sign = (value > 0) ? 1.0f : -1.0f;
    return sign * (fabs(value) - deadzone) / (1.0f - deadzone);
}