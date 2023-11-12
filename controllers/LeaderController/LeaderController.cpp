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
	lidar->enablePointCloud();
};

LeaderRobot::~LeaderRobot() {}
  
void LeaderRobot::run() {
	// Main runner for leader robot controller
	bool scanned{ false };
	while (step(TIME_STEP) != -1) {
		// Main loop
		// scan environment once
		if (!scanned) {
			scanLidarData();
			scanned = true;
			setTargetPosition(2, 2);
			updateCurrentPosition();
			moveToTarget(0);
		}

		// checking for messages
		std::pair <std::string, std::string> message{ receiveMessage() };
		if (message.first != "") {
			std::ostringstream ss;
			ss << "Robot " << message.first << " has identified a " << message.second << " OOI\n";
			std::string output{ ss.str() };
			fileOutput(output);
			std::cout << output;

			// set green OOI as target
			int size{ static_cast<int>(mOOIs.size()) };
			for (int i{ 0 }; i < size; i++) {
				if (message.second == "green" && mOOIs[i].scoutNum == std::stoi(message.first)) {
					ss << "Green OOI has been found, moving to x: " << mOOIs[i].x << " y: " << mOOIs[i].y << '\n';
					std::string output{ ss.str() };
					fileOutput(output);
					std::cout << output;
					setTargetPosition(mOOIs[i].x, mOOIs[i].y);
					updateCurrentPosition();
					moveToTarget(0);
					hasTarget = true;
				}
			}
		}

		if (hasTarget) {
			rotateToOOI();
			updateCurrentPosition();
			moveToTarget(0.5);

			moveToOOI();
			updateCurrentPosition();
			moveToTarget(0.5);

			stop();

			fileOutput("Successfully arrived at the green OOI\n");
			std::cout << "Successfully arrived at the green OOI\n";

			hasTarget = false;
		}
		


	}
}
void LeaderRobot::move(double speed) {
	frontLeftMotor->setVelocity(speed);
	frontRightMotor->setVelocity(speed);
	rearLeftMotor->setVelocity(speed);
	rearRightMotor->setVelocity(speed);
	//std::cout << "Moving\n";
}

void LeaderRobot::rotate(double speed) {
	frontLeftMotor->setVelocity(-speed);
	rearLeftMotor->setVelocity(-speed);
	frontRightMotor->setVelocity(speed);
	rearRightMotor->setVelocity(speed);
	//std::cout << "Rotating\n";
}

void LeaderRobot::stop() {
	frontLeftMotor->setVelocity(0);
	rearLeftMotor->setVelocity(0);
	frontRightMotor->setVelocity(0);
	rearRightMotor->setVelocity(0);
	//std::cout << "Stop!\n";
}

void LeaderRobot::rotateToOOI() {
	frontLeftMotor->setPosition(INFINITY);
	rearLeftMotor->setPosition(INFINITY);
	frontRightMotor->setPosition(INFINITY);
	rearRightMotor->setPosition(INFINITY);
	double rotateSpeed{ 4.8704 }; // around pi/2 rad per second
	rotate(rotateSpeed);
	double timeWait{ angleDiff / (PI / 2) * 1000};
	wait(timeWait);
}

void LeaderRobot::moveToOOI() {
	frontLeftMotor->setPosition(INFINITY);
	rearLeftMotor->setPosition(INFINITY);
	frontRightMotor->setPosition(INFINITY);
	rearRightMotor->setPosition(INFINITY);
	double moveSpeed{ 5.68 }; // around 0.25 m per second
	move(moveSpeed);
	double timeWait{ distanceDiff / 0.25 * 1000 };
	wait(timeWait);
}

void LeaderRobot::scanLidarData() {
	auto data{ lidar->getPointCloud() };
	int numPoints{ lidar->getNumberOfPoints() };
	int scoutNum{ 1 };
	for (int i{ 0 }; i < numPoints; i++) {
		auto lidarPoint{ data[i] };
		if (lidarPoint.z == 0) {
			double x{ 0 };
			double y{ 0 };
			int numPointsOOI{ 0 };
			while (lidarPoint.z == 0) {
				x += lidarPoint.x;
				y += lidarPoint.y;
				numPointsOOI++;
				i++;
				lidarPoint = data[i];
			}
			mOOIs.push_back({ x / numPointsOOI, y / numPointsOOI, scoutNum });
			scoutNum++;
		}
	}

	// append output.txt
	int size{ static_cast<int>(mOOIs.size()) };
	for (int i{ 0 }; i < size; i++) {
		std::ostringstream ss;
		ss << "OOI discovered at x:" << mOOIs[i].x << " y: " << mOOIs[i].y << '\n';
		std::string output{ ss.str() };
		fileOutput(output);
		std::cout << output;
	}

	// send message to scout robots
	for (int i{ 0 }; i < size; i++) {
		std::string ID{ std::to_string(mOOIs[i].scoutNum) };
		std::string data1{ std::to_string(mOOIs[i].x) };
		std::string data2{ std::to_string(mOOIs[i].y) };
		sendMessage(ID, data1, data2);
		std::ostringstream ss;
		ss << "Target pose x:" << mOOIs[i].x << " y: " << mOOIs[i].y << " sent to robot " << mOOIs[i].scoutNum << '\n';
		std::string output{ ss.str() };
		fileOutput(output);
		std::cout << output;
	}
}

void LeaderRobot::fileOutput(const std::string& output) const {
	std::ofstream outputFile;
	outputFile.open("output.txt", std::ofstream::app);
	outputFile << output;
}

int main() {
	LeaderRobot myController;
	myController.run();
	return 0;
}