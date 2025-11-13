/**
 * @file test_joystick.cpp
 * @brief Unit tests for Joystick mapping functions.
 * @ingroup Control
 * @author Team03
 * @date 2025-10-31
 * @version 1.0
 * @details These tests exercise the pure-math portions of the joystick
 * mapping utilities and do not require hardware.
 */

#include <gtest/gtest.h>
#include "../include/Joystick.hpp"
#include <cmath>

class JoystickTest : public ::testing::Test {
protected:
    // No hardware needed for these tests - they're pure math
};

TEST_F(JoystickTest, AxisMappingCenter) {
    EXPECT_FLOAT_EQ(Joystick::map_axis(0), 0.0f);
}

TEST_F(JoystickTest, AxisMappingExtremes) {
    EXPECT_FLOAT_EQ(Joystick::map_axis(32767), 1.0f);
    EXPECT_FLOAT_EQ(Joystick::map_axis(-32767), -1.0f);
}

TEST_F(JoystickTest, AxisMappingIntermediate) {
    EXPECT_NEAR(Joystick::map_axis(16383), 0.5f, 0.01f);
    EXPECT_NEAR(Joystick::map_axis(-16383), -0.5f, 0.01f);
}

TEST_F(JoystickTest, DeadzoneFiltersSmall) {
    EXPECT_FLOAT_EQ(Joystick::apply_deadzone(0.0f, 0.15f), 0.0f);
    EXPECT_FLOAT_EQ(Joystick::apply_deadzone(0.1f, 0.15f), 0.0f);
    EXPECT_FLOAT_EQ(Joystick::apply_deadzone(-0.1f, 0.15f), 0.0f);
    EXPECT_FLOAT_EQ(Joystick::apply_deadzone(0.14f, 0.15f), 0.0f);
}

TEST_F(JoystickTest, DeadzonePassesLarge) {
    float result = Joystick::apply_deadzone(0.5f, 0.15f);
    EXPECT_GT(result, 0.0f);
    EXPECT_LT(result, 0.5f);
    
    result = Joystick::apply_deadzone(-0.5f, 0.15f);
    EXPECT_LT(result, 0.0f);
}

TEST_F(JoystickTest, DeadzoneBoundary) {
    EXPECT_FLOAT_EQ(Joystick::apply_deadzone(0.15f, 0.15f), 0.0f);
    
    float result = Joystick::apply_deadzone(0.16f, 0.15f);
    EXPECT_GT(result, 0.0f);
    EXPECT_LT(result, 0.1f);
}

TEST_F(JoystickTest, DeadzonePreservesSign) {
    float pos = Joystick::apply_deadzone(0.8f, 0.15f);
    float neg = Joystick::apply_deadzone(-0.8f, 0.15f);
    
    EXPECT_GT(pos, 0.0f);
    EXPECT_LT(neg, 0.0f);
    EXPECT_NEAR(fabs(pos), fabs(neg), 0.01f);
}

TEST_F(JoystickTest, AngleMappingCenter) {
    EXPECT_FLOAT_EQ(Joystick::map_axis_to_angle(0), 90.0f);
}

TEST_F(JoystickTest, AngleMappingExtremes) {
    EXPECT_FLOAT_EQ(Joystick::map_axis_to_angle(-32767), 0.0f);
    EXPECT_FLOAT_EQ(Joystick::map_axis_to_angle(32767), 180.0f);
}

TEST_F(JoystickTest, AngleMappingIntermediate) {
    EXPECT_NEAR(Joystick::map_axis_to_angle(16383), 135.0f, 1.0f);
    EXPECT_NEAR(Joystick::map_axis_to_angle(-16383), 45.0f, 1.0f);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}