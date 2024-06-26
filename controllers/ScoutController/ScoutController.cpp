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
			moveToTarget(0.3);

			moveToOOI();
			updateCurrentPosition();
			moveToTarget(0.3);

			stop();

			if (readColour()) {
				sendMessage("0", ID, "green");
			}
			else {
				sendMessage("0", ID, "red");
			}
			hasTarget = false;
		}
	}
}
void ScoutRobot::move(double speed) {
	leftMotor->setVelocity(speed);
	rightMotor->setVelocity(speed);
}

void ScoutRobot::rotate(double speed) {
	leftMotor->setVelocity(-speed);
	rightMotor->setVelocity(speed);
}


void ScoutRobot::rotateToOOI() {
	setPosInf();
	double rotateSpeed{ 3 };
	rotate(rotateSpeed);
	double timeWait{ angleDiff / 2.16405 * 1000 };
	wait(timeWait);
}

void ScoutRobot::moveToOOI() {
	setPosInf();
	double moveSpeed{ 6.28 };
	move(moveSpeed);
	double timeWait{ distanceDiff / 0.128614 * 1000 };
	wait(timeWait);
}

bool ScoutRobot::readColour() {
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
}

void ScoutRobot::setPosInf() {
	leftMotor->setPosition(INFINITY);
	rightMotor->setPosition(INFINITY);
}

int main() {
	ScoutRobot myController;
	myController.run();
	return 0;
}