/**
 * @file Joystick.hpp
 * @brief Lightweight wrapper around the Linux joystick API for reading events.
 * @ingroup Control
 * @author Team03
 * @date 2025-10-31
 * @version 1.0
 */

#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

#include <linux/joystick.h>

/**
 * @class Joystick
 * @brief Opens a joystick device and provides helpers for event reading and
 * axis mapping.
 */
class Joystick {
private:
    int fd; ///< File descriptor for the joystick device

public:
    /**
     * @brief Open a joystick device node.
     * @param device Path to joystick device (default: /dev/input/js0).
     * @details Throws runtime_error if the device cannot be opened.
     */
    Joystick(const char* device = "/dev/input/js0");

    /**
     * @brief Close the joystick device if open.
     */
    ~Joystick();
    
    /**
     * @brief Read a single joystick event if available.
     * @param event Pointer to an allocated js_event structure to fill.
     * @return true if an event was read, false otherwise.
     */
    bool read_event(struct js_event* event);
    
    /**
     * @brief Convert raw 16-bit axis value to normalized float [-1.0, 1.0].
     */
    static float map_axis(int16_t value);

    /**
     * @brief Map a raw axis value to a servo angle [0,180].
     */
    static float map_axis_to_angle(int16_t value);

    /**
     * @brief Apply a deadzone to an input value and re-scale outside region.
     * @param value Input value in [-1.0, 1.0].
     * @param deadzone Threshold to consider as zero.
     */
    static float apply_deadzone(float value, float deadzone = 0.15f);
};

#endif