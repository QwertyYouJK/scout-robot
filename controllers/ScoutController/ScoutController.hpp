#pragma once

#include "../BaseRobot/BaseRobot.hpp"

class ScoutRobot : public BaseRobot {
public:
	ScoutRobot();
	~ScoutRobot();

	void run() override;
	void move(double speed) override;
	void rotate(double speed) override;
	void stop() override;
	void setPosInf() override;

	void rotateToOOI();
	void moveToOOI();
	bool readColour();

private:
	std::unique_ptr<webots::Motor> leftMotor{};
	std::unique_ptr<webots::Motor> rightMotor{};
	std::unique_ptr<webots::Camera> camera{};
	std::unique_ptr<webots::DistanceSensor> distance{};
};