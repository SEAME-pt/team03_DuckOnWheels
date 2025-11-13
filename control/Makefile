CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude
LDFLAGS = -lgtest -lgtest_main -pthread

# Source files
SRC_DIR = src
SOURCES = $(SRC_DIR)/DualPCA9685.cpp $(SRC_DIR)/Joystick.cpp $(SRC_DIR)/RobotController.cpp

# Test files
TEST_DIR = test
TESTS = test_motor test_servo test_joystick

# Main program
MAIN = robot_control

all: $(MAIN) $(TESTS)

$(MAIN): main.cpp $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lpthread

test_motor: $(TEST_DIR)/test_motor.cpp $(SRC_DIR)/DualPCA9685.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

test_servo: $(TEST_DIR)/test_servo.cpp $(SRC_DIR)/DualPCA9685.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

test_joystick: $(TEST_DIR)/test_joystick.cpp $(SRC_DIR)/Joystick.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

test: $(TESTS)
	@echo "Running motor tests..."
	sudo ./test_motor
	@echo "\nRunning servo tests..."
	sudo ./test_servo
	@echo "\nRunning joystick tests..."
	./test_joystick

clean:
	rm -f $(MAIN) $(TESTS)

.PHONY: all test clean