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
	frontLeftMotor->setPosition(INFINITY);
	frontRightMotor->setPosition(INFINITY);
	rearLeftMotor->setPosition(INFINITY);
	rearRightMotor->setPosition(INFINITY);
	lidar->enable(TIME_STEP);
};

LeaderRobot::~LeaderRobot() {}
  
void LeaderRobot::run() {
	// Main runner for leader robot controller
	while (step(TIME_STEP) != -1) {
		// Main loop
		move(5);
		wait(1000);
		rotate(5);
		wait(1000);
	}
}
void LeaderRobot::move(double speed) {
	frontLeftMotor->setVelocity(speed);
	frontRightMotor->setVelocity(speed);
	rearLeftMotor->setVelocity(speed);
	rearRightMotor->setVelocity(speed);
	std::cout << "Moving\n";
}

void LeaderRobot::rotate(double speed) {
	frontLeftMotor->setVelocity(speed);
	rearLeftMotor->setVelocity(speed);
	frontRightMotor->setVelocity(-1 * speed);
	rearRightMotor->setVelocity(-1 * speed);
	std::cout << "Rotating\n";
}


int main() {
	LeaderRobot myController;
	myController.run();
	return 0;
}