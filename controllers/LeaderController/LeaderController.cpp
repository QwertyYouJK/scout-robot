// File:          LeaderController.cpp
// Date:
// Description:
// Author:
// Modifications:

#include "LeaderController.hpp"

LeaderRobot::LeaderRobot()
	: frontLeftMotor{ getMotor("front left wheel motor") }
	, frontRightMotor{ getMotor("front right wheel motor") }
	, rearLeftMotor{ getMotor("rear left wheel motor") }
	, rearRightMotor{ getMotor("rear right wheel motor") }
	, lidar{ getLidar("lidar") } {
	lidar->enable(TIME_STEP);
};

LeaderRobot::~LeaderRobot() {}
  
void LeaderRobot::run() {
	// Main runner for leader robot controller
	while (step(TIME_STEP) != -1) {
		// Main loop
		move(10);
		wait(1000);
	}
}
void LeaderRobot::move(double speed) {
	std::cout << "Moving with speed of " << speed << "!\n";
}

void LeaderRobot::rotate(double speed) {}


int main() {
	LeaderRobot myController;
	myController.run();
	return 0;
}