// File:          LeaderController.cpp
// Date:
// Description:
// Author:
// Modifications:

#include "ScoutController.hpp"

ScoutRobot::ScoutRobot()
	: leftMotor{ getMotor("left wheel motor") }
	, rightMotor{ getMotor("right wheel motor") }
	, camera{ getCamera("camera") }
	, distance{ getDistanceSensor("distance") } {
	camera->enable(TIME_STEP);
	distance->enable(TIME_STEP);
};
ScoutRobot::~ScoutRobot() {}

void ScoutRobot::run() {
	// Main runner for leader robot controller
	while (step(TIME_STEP) != -1) {
		// Main loop
		wait(1000);
		updateCurrentPosition();
		// Receive messages
		auto message{ receiveMessage() };
		if (message.first != "") {
			setTargetPosition(std::stod(message.first), std::stod(message.second));
			moveToTarget(0);
			std::cout << "I'm robot " << ID << " and my target position is " << targetPositionX << ", " << targetPositionY
				<< " while my position right now is " << currentPositionX << ", " << currentPositionY << '\n';
			std::cout << "The angle diff between my current yaw (" << currentYaw << ") and target is " << angleDiff << '\n';
			std::cout << "The distance between me and target is " << distanceDiff << '\n';
		}
		// Move to OOI
		// Rotate until facing OOI
		
		// Identify OOI colour
		// Report to leader
		// stop

	}
}
void ScoutRobot::move(double speed) {
	leftMotor->setPosition(distanceDiff);
	leftMotor->setVelocity(speed);
	rightMotor->setPosition(distanceDiff);
	rightMotor->setVelocity(speed);
	std::cout << "Moving\n";
}
void ScoutRobot::rotate(double speed) {
	leftMotor->setPosition(angleDiff );
	leftMotor->setVelocity(speed);
	rightMotor->setVelocity(-1 * speed);
	std::cout << "Rotating\n";
}

//bool ScoutRobot::readColour() {
//	return true;
//}

int main() {
	ScoutRobot myController;
	myController.run();
	return 0;
}