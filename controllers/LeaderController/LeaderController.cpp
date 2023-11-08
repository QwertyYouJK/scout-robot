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
	frontLeftMotor->setVelocity(0);
	frontRightMotor->setPosition(INFINITY);
	frontRightMotor->setVelocity(0);
	rearLeftMotor->setPosition(INFINITY);
	rearLeftMotor->setVelocity(0);
	rearRightMotor->setPosition(INFINITY);
	rearRightMotor->setVelocity(0);
	lidar->enable(TIME_STEP);
	lidar->enablePointCloud();
};

LeaderRobot::~LeaderRobot() {}
  
void LeaderRobot::run() {
	// Main runner for leader robot controller
	while (step(TIME_STEP) != -1) {
		// Main loop
		scanLidarData();
		wait(30000);
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