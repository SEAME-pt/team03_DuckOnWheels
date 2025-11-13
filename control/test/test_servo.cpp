/**
 * @file test_servo.cpp
 * @brief Integration-style tests for servo outputs via DualPCA9685.
 * @ingroup Control
 * @author Team03
 * @date 2025-10-31
 * @version 1.0
 * @details These tests may be skipped when hardware is not present. They
 * exercise angle clamping and basic movement sequences.
 */

#include <gtest/gtest.h>
#include "../include/DualPCA9685.hpp"
#include <stdexcept>
#include <unistd.h>

class ServoTest : public ::testing::Test {
protected:
    DualPCA9685* robot;
    
    void SetUp() override {
        try {
            robot = new DualPCA9685();
        } catch (const std::exception& e) {
            GTEST_SKIP() << "Hardware not available: " << e.what();
        }
    }
    
    void TearDown() override {
        if (robot) {
            robot->set_servo_angle(90.0f);
            delete robot;
        }
    }
};

TEST_F(ServoTest, AcceptsValidAngles) {
    EXPECT_NO_THROW(robot->set_servo_angle(0.0f));
    EXPECT_NO_THROW(robot->set_servo_angle(45.0f));
    EXPECT_NO_THROW(robot->set_servo_angle(90.0f));
    EXPECT_NO_THROW(robot->set_servo_angle(135.0f));
    EXPECT_NO_THROW(robot->set_servo_angle(180.0f));
}

TEST_F(ServoTest, HandlesOutOfRangeAngles) {
    EXPECT_NO_THROW(robot->set_servo_angle(-10.0f));
    EXPECT_NO_THROW(robot->set_servo_angle(200.0f));
    EXPECT_NO_THROW(robot->set_servo_angle(360.0f));
}

TEST_F(ServoTest, SweepMotion) {
    EXPECT_NO_THROW({
        for (float angle = 0.0f; angle <= 180.0f; angle += 45.0f) {
            robot->set_servo_angle(angle);
            usleep(200000);
        }
        robot->set_servo_angle(90.0f);
    });
}

TEST_F(ServoTest, CenterPosition) {
    EXPECT_NO_THROW({
        robot->set_servo_angle(90.0f);
        usleep(500000);
    });
}

TEST_F(ServoTest, RapidAngleChanges) {
    EXPECT_NO_THROW({
        robot->set_servo_angle(0.0f);
        usleep(10000);
        robot->set_servo_angle(180.0f);
        usleep(10000);
        robot->set_servo_angle(90.0f);
    });
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}