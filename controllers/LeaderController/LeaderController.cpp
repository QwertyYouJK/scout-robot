// File:          LeaderController.cpp
// Date:
// Description:
// Author:
// Modifications:

#include "LeaderController.hpp"

LeaderRobot::LeaderRobot() {}
LeaderRobot::~LeaderRobot() {}
  
void LeaderRobot::run() {
	// Main runner for leader robot controller
	while (step(TIME_STEP) != -1) {
		// Main loop
		speak();
	}
}
void LeaderRobot::move(double speed) {}
void LeaderRobot::rotate(double speed) {}

void LeaderRobot::speak() {
	std::cout << "I am the leader\n";
}


int main() {
	LeaderRobot myController;
	myController.run();
	return 0;
}