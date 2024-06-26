// File:          BaseRobot.hpp
// Date:          XX/XX/XXXX
// Description:   Header file of BaseRobot to be inherited by the Leader and Scout robots classes.
// Author:        XXX XXX
// zID:           z5401349
// Modifications:

#pragma once

// add additional includes as needed
#include <iostream>
#include <memory>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <fstream>

#include <webots/Receiver.hpp>
#include <webots/Emitter.hpp>
#include <webots/Robot.hpp>
#include <webots/Keyboard.hpp>
#include <webots/GPS.hpp>
#include <webots/Compass.hpp>
#include <webots/Motor.hpp>
#include <webots/Lidar.hpp>
#include <webots/Camera.hpp>
#include <webots/DistanceSensor.hpp>

constexpr int TIME_STEP{ 64 };
constexpr double PI{ 3.14159265358979323846 };
constexpr double LEADER_WHEEL_RADIUS{ 0.043 };
constexpr double SCOUT_WHEEL_RADIUS{ 0.02 };
constexpr double SCOUT_WHEEL_DISTANCE{ 0.026 };

class BaseRobot : public webots::Robot {
public:
	BaseRobot();
	virtual ~BaseRobot();
  
	virtual void run() = 0;
	virtual void move(double speed) = 0;
	virtual void rotate(double speed) = 0;
	virtual void stop() = 0;
	virtual void setPosInf() = 0;

	void keyboardControl();
	void updateCurrentPosition();
	void setTargetPosition(double x, double y);
	bool moveToTarget(double stopDistance);
	   
	void sendMessage(const std::string& ID, const std::string& data0, const std::string& data1);
	std::pair<std::string, std::string> receiveMessage();

	void wait(double waitPeriod);

protected:
	std::string ID{};
	double currentPositionX{};
	double currentPositionY{};
	double currentYaw{};
	double targetPositionX{};
	double targetPositionY{};

	double distanceDiff{};
	double angleDiff{};
	bool hasTarget{ false };
	bool keyboardEnabled{ false };
	// add additional members as needed
  
private:
	std::unique_ptr<webots::Receiver> receiver{};
	std::unique_ptr<webots::Emitter> emitter{};
	std::unique_ptr<webots::GPS> gps{};
	std::unique_ptr<webots::Compass> compass{};
	std::unique_ptr<webots::Keyboard> keyboard{};
	// add additional members as needed
};
