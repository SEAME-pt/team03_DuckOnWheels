/**
 * @file DualPCA9685.cpp
 * @brief Implementation of the DualPCA9685 I2C PWM driver.
 * @ingroup Control
 * @author Team03
 * @date 2025-10-31
 * @version 1.0
 */

#include "../include/DualPCA9685.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <stdexcept>
#include <cmath>
#include <cstdio>

void DualPCA9685::write_byte(int fd, uint8_t reg, uint8_t val) {
    uint8_t buffer[2] = {reg, val};
    if (write(fd, buffer, 2) != 2) {
        throw std::runtime_error("Failed to write I2C byte");
    }
}

void DualPCA9685::set_pwm(int fd, uint8_t channel, uint16_t on, uint16_t off) {
    uint8_t reg_base = 0x06 + 4 * channel;
    write_byte(fd, reg_base, on & 0xFF);
    write_byte(fd, reg_base + 1, on >> 8);
    write_byte(fd, reg_base + 2, off & 0xFF);
    write_byte(fd, reg_base + 3, off >> 8);
}

void DualPCA9685::init_pca(int fd, uint8_t prescaler) {
    // Bring device to a known reset state, set prescaler, and restart
    write_byte(fd, 0x00, 0x00);
    usleep(5000);
    write_byte(fd, 0x01, 0x04);
    usleep(5000);
    write_byte(fd, 0x00, 0x10);
    usleep(5000);
    write_byte(fd, 0xFE, prescaler);
    usleep(5000);
    write_byte(fd, 0x00, 0x80);
    usleep(5000);
}

/**
 * @brief Open I2C buses and initialize both PCA9685 devices.
 * @details Throws runtime_error when device nodes or ioctls fail. The
 * constructor chooses addresses 0x60 for motor controller and 0x40 for the
 * servo controller per platform wiring.
 */
DualPCA9685::DualPCA9685() {
    if ((fd_motor = open("/dev/i2c-1", O_RDWR)) < 0) {
        throw std::runtime_error("Failed to open I2C for motor");
    }
    if (ioctl(fd_motor, I2C_SLAVE, 0x60) < 0) {
        throw std::runtime_error("Failed to set motor I2C address");
    }
    
    if ((fd_servo = open("/dev/i2c-1", O_RDWR)) < 0) {
        throw std::runtime_error("Failed to open I2C for servo");
    }
    if (ioctl(fd_servo, I2C_SLAVE, 0x40) < 0) {
        throw std::runtime_error("Failed to set servo I2C address");
    }
    
    init_pca(fd_motor, 121);
    init_pca(fd_servo, 121);
}

DualPCA9685::~DualPCA9685() {
    stop_all();
    close(fd_motor);
    close(fd_servo);
}

void DualPCA9685::set_pwm_duty(uint8_t channel, float duty_fraction) {
    if (duty_fraction <= 0.0f) {
        set_pwm(fd_motor, channel, 0, 0);
    } else if (duty_fraction >= 1.0f) {
        set_pwm(fd_motor, channel, 0, 4095);
    } else {
        uint16_t duty = static_cast<uint16_t>(duty_fraction * 4095);
        set_pwm(fd_motor, channel, 0, duty);
    }
}

void DualPCA9685::set_motor(float throttle) {
    float duty = fabs(throttle);
    
    // Map positive throttle to forward motor channel configuration,
    // negative throttle to reverse configuration.
    if (throttle > 0.0f) {
        set_pwm_duty(0, duty);
        set_pwm_duty(1, 1.0f);
        set_pwm_duty(2, 0.0f);
        set_pwm_duty(3, 0.0f);
        set_pwm_duty(4, duty);
        set_pwm_duty(5, 0.0f);
        set_pwm_duty(6, 1.0f);
        set_pwm_duty(7, duty);
    } else if (throttle < 0.0f) {
        set_pwm_duty(0, duty);
        set_pwm_duty(1, 0.0f);
        set_pwm_duty(2, 1.0f);
        set_pwm_duty(3, 0.0f);
        set_pwm_duty(4, duty);
        set_pwm_duty(5, 1.0f);
        set_pwm_duty(6, 0.0f);
        set_pwm_duty(7, duty);
    } else {
        stop_motors();
    }
}

void DualPCA9685::stop_motors() {
    for (uint8_t ch = 0; ch < 8; ++ch) {
        set_pwm_duty(ch, 0);
    }
}

uint16_t DualPCA9685::angle_to_pwm(float angle) {
    const float SERVO_MIN_MS = 0.5f;
    const float SERVO_MAX_MS = 2.5f;
    const float SERVO_FREQ = 50.0f;
    
    if (angle < 0.0f) angle = 0.0f;
    if (angle > 180.0f) angle = 180.0f;
    
    float pulse_ms = SERVO_MIN_MS + (angle / 180.0f) * (SERVO_MAX_MS - SERVO_MIN_MS);
    float pulse_length_us = 1000000.0f / SERVO_FREQ / 4096.0f;
    return static_cast<uint16_t>(pulse_ms * 1000.0f / pulse_length_us);
}

void DualPCA9685::set_servo_angle(float angle) {
    uint16_t pwm = angle_to_pwm(angle);
    set_pwm(fd_servo, 0, 0, pwm);
}

void DualPCA9685::stop_all() {
    stop_motors();
    set_pwm(fd_servo, 0, 0, 0);
}