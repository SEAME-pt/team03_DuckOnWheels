/**
 * @file test_motor.cpp
 * @brief Integration-style tests for DualPCA9685 motor outputs.
 * @ingroup Control
 * @author Team03
 * @date 2025-10-31
 * @version 1.0
 * @details These tests will be skipped when hardware is not present. They
 * perform basic calls to the motor API to ensure no exceptions are thrown and
 * that stop functions behave as expected.
 */

#include <gtest/gtest.h>
#include "../include/DualPCA9685.hpp"
#include <stdexcept>

class MotorTest : public ::testing::Test {
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
            robot->stop_all();
            delete robot;
        }
    }
};

TEST_F(MotorTest, AcceptsValidThrottle) {
    EXPECT_NO_THROW(robot->set_motor(0.0f));
    EXPECT_NO_THROW(robot->set_motor(0.5f));
    EXPECT_NO_THROW(robot->set_motor(1.0f));
    EXPECT_NO_THROW(robot->set_motor(-0.5f));
    EXPECT_NO_THROW(robot->set_motor(-1.0f));
}

TEST_F(MotorTest, HandlesExtremeValues) {
    EXPECT_NO_THROW(robot->set_motor(2.0f));
    EXPECT_NO_THROW(robot->set_motor(-2.0f));
    EXPECT_NO_THROW(robot->set_motor(0.001f));
}

TEST_F(MotorTest, StopMotorsWorks) {
    robot->set_motor(0.5f);
    EXPECT_NO_THROW(robot->stop_motors());
    EXPECT_NO_THROW(robot->set_motor(0.0f));
}

TEST_F(MotorTest, ForwardDirection) {
    EXPECT_NO_THROW({
        robot->set_motor(0.3f);
        usleep(100000);
        robot->stop_motors();
    });
}

TEST_F(MotorTest, ReverseDirection) {
    EXPECT_NO_THROW({
        robot->set_motor(-0.3f);
        usleep(100000);
        robot->stop_motors();
    });
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}