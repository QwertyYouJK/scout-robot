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

#include <webots/Receiver.hpp>
#include <webots/Emitter.hpp>
#include <webots/Robot.hpp>
#include <webots/Keyboard.hpp>
#include <webots/GPS.hpp>
#include <webots/Compass.hpp>

constexpr int TIME_STEP{ 64 };
constexpr double PI{ 3.14159265358979323846 };

class BaseRobot : public webots::Robot {
public:
	BaseRobot();
	~BaseRobot();
  
	virtual void run() = 0;
	virtual void move(double speed) = 0;
	virtual void rotate(double speed) = 0;
	virtual void speak() = 0;

	void keyboardControl();
	void updateCurrentPosition();
	void setTargetPosition(double x, double y);
	bool moveToTarget(double stopDistance);
	   
	void sendMessage(const std::string& ID, const std::string& data0, const std::string& data1);
	std::pair<std::string, std::string> receiveMessage();

	//void wait(BaseRobot& robot, double waitPeriod);

protected:
	std::string ID{};
	double currentPositionX{};
	double currentPositionY{};
	double currentYaw{};
	double targetPositionX{};
	double targetPositionY{};

	double distance{};
	double angleDiff{};
	// add additional members as needed
  
private:
	std::unique_ptr<webots::Receiver> receiver{};
	std::unique_ptr<webots::Emitter> emitter{};
	std::unique_ptr<webots::GPS> gps{};
	std::unique_ptr<webots::Compass> compass{};
	// add additional members as needed
};
