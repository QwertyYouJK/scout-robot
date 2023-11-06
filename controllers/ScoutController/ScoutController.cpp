// File:          LeaderController.cpp
// Date:
// Description:
// Author:
// Modifications:

#include "ScoutController.hpp"

ScoutRobot::ScoutRobot() {}
ScoutRobot::~ScoutRobot() {}

void ScoutRobot::run() {
	// Main runner for leader robot controller
	while (step(TIME_STEP) != -1) {
		// Main loop
		speak();
	}
}
void ScoutRobot::move(double speed) {}
void ScoutRobot::rotate(double speed) {}

void ScoutRobot::speak() {
	std::cout << "I am the scout\n";
}

bool readColour() {}

int main() {
	ScoutRobot myController;
	myController.run();
	return 0;
}