// File:          LeaderController.cpp
// Date:
// Description:
// Author:
// Modifications:

#include "ScoutController.hpp"

ScoutRobot::ScoutRobot() {};
ScoutRobot::~ScoutRobot() {}

void ScoutRobot::run() {
	// Main runner for leader robot controller
	while (step(TIME_STEP) != -1) {
		// Main loop
		updateCurrentPosition();
		speak();
	}
}
void ScoutRobot::move(double speed) {}
void ScoutRobot::rotate(double speed) {}

void ScoutRobot::speak() {
	std::cout << "xPos is " << currentPositionX << '\n';
	std::cout << "yPos is " << currentPositionY << '\n';
	std::cout << "yaw is " << currentYaw << '\n';
}

//bool ScoutRobot::readColour() {
//	return true;
//}

int main() {
	ScoutRobot myController;
	myController.run();
	return 0;
}