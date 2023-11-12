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
	leftMotor->setPosition(0);
	rightMotor->setPosition(0);
	leftMotor->setVelocity(0);
	rightMotor->setVelocity(0);
	camera->enable(TIME_STEP);
	distance->enable(TIME_STEP);
};
ScoutRobot::~ScoutRobot() {}

void ScoutRobot::run() {
	// Main runner for leader robot controller
	while (step(TIME_STEP) != -1) {
		// Main loop
		std::pair <std::string, std::string> message{ receiveMessage() };
		if (message.first != "") {
			setTargetPosition(std::stod(message.first), std::stod(message.second));
			hasTarget = true;
			updateCurrentPosition();
			moveToTarget(0);
		}
		if (hasTarget) {
			rotateToOOI();
			updateCurrentPosition();
			moveToTarget(0.5);

			moveToOOI();
			updateCurrentPosition();
			moveToTarget(0.5);

			if (readColour()) {
				std::cout << "This is robot " << ID << " and in front of me is green!\n";
				sendMessage("0", ID, "green");
			}
			else {
				std::cout << "This is robot " << ID << " and in front of me is red!\n";
				sendMessage("0", ID, "red");
			}
			hasTarget = false;
		}
	}
}
void ScoutRobot::move(double speed) {
	leftMotor->setVelocity(speed);
	rightMotor->setVelocity(speed);
	std::cout << "Moving\n";
}

void ScoutRobot::rotate(double speed) {
	leftMotor->setVelocity(-speed);
	rightMotor->setVelocity(speed);
	std::cout << "Rotating\n";
}


void ScoutRobot::rotateToOOI() {
	leftMotor->setPosition(INFINITY);
	rightMotor->setPosition(INFINITY);
	double rotateSpeed{ 2.177 }; // around pi/2 rad per second
	rotate(rotateSpeed);
	double timeWait{ angleDiff / (PI / 2) * 1000 };
	wait(timeWait);
}

void ScoutRobot::moveToOOI() {
	leftMotor->setPosition(INFINITY);
	rightMotor->setPosition(INFINITY);
	double moveSpeed{ 4.88 }; // around 0.1 m per second
	move(moveSpeed);
	double timeWait{ distanceDiff / 0.1 * 1000 };
	wait(timeWait);
}

bool ScoutRobot::readColour() {
	std::cout << "Reading Colour\n";
	camera->recognitionEnable(TIME_STEP);
	int num{ camera->getRecognitionNumberOfObjects() };
	if (num) {
		return true;
	}
	return false;
}

void ScoutRobot::stop() {
	leftMotor->setVelocity(0);
	rightMotor->setVelocity(0);
	std::cout << "Stop!\n";
}

int main() {
	ScoutRobot myController;
	myController.run();
	return 0;
}