/**
 * @file DualPCA9685.hpp
 * @brief Low-level driver for two PCA9685 devices (motor + servo) over I2C.
 * @ingroup Control
 * @author Team03
 * @date 2025-10-31
 * @version 1.0
 */

#ifndef DUALPCA9685_HPP
#define DUALPCA9685_HPP

#include <cstdint>

/**
 * @class DualPCA9685
 * @brief Manages two PCA9685 PWM controllers: one for motor outputs and one
 * for servo control.
 *
 * Provides simple APIs to set motor throttle and servo angle as well as
 * utilities to stop outputs safely.
 */
class DualPCA9685 {
private:
    int fd_motor;
    int fd_servo;
    
    /**
     * @brief Write a single register byte to the given I2C file descriptor.
     * @param fd Open file descriptor for the I2C device.
     * @param reg Register address to write.
     * @param val Value to write.
     * @details Throws runtime_error on fail.
     */
    void write_byte(int fd, uint8_t reg, uint8_t val);

    /**
     * @brief Set the raw PWM on/off counts for a channel on a device.
     */
    void set_pwm(int fd, uint8_t channel, uint16_t on, uint16_t off);

    /**
     * @brief Initialize PCA9685 registers with a prescaler value.
     */
    void init_pca(int fd, uint8_t prescaler);

    /**
     * @brief Convert duty fraction (0.0-1.0) to PWM registers and send.
     */
    void set_pwm_duty(uint8_t channel, float duty_fraction);

    /**
     * @brief Convert an angle (degrees) to PCA9685 PWM off count.
     * @param angle Angle in degrees (0-180).
     * @return PWM off count corresponding to the requested angle.
     */
    uint16_t angle_to_pwm(float angle);

public:
    /**
     * @brief Open I2C devices and configure PCA9685 controllers.
     * @details Throws on any I2C or ioctl failure. The constructor will
     * initialize controllers with sane prescalers for standard servos.
     */
    DualPCA9685();

    /**
     * @brief Close I2C devices and stop outputs.
     */
    ~DualPCA9685();

    /**
     * @brief Set motor throttle.
     * @param throttle Range -1.0 (full reverse) to +1.0 (full forward). Values
     * outside this range are handled gracefully by saturating to the valid
     * range in the implementation.
     * @details Splits throttle across multiple motor channels according to the
     * platform wiring.
     */
    void set_motor(float throttle);

    /**
     * @brief Set the steering servo angle.
     * @param angle Desired servo angle in degrees (0-180).
     */
    void set_servo_angle(float angle);

    /**
     * @brief Stop all motor channels immediately.
     */
    void stop_motors();

    /**
     * @brief Stop motors and servo outputs.
     */
    void stop_all();
};

#endif