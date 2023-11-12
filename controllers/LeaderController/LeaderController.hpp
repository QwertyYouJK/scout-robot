#pragma once

#include "../BaseRobot/BaseRobot.hpp"

class LeaderRobot : public BaseRobot {
public:
	struct OOI {
		double x;
		double y;
		int scoutNum;
	};
	
	LeaderRobot();
	~LeaderRobot();
  
	void run() override;
	void move(double speed) override;
	void rotate(double speed) override;
	
	void stop();
	void rotateToOOI();
	void moveToOOI();
	void scanLidarData();
	void fileOutput(const std::string& output) const;

private:
	std::unique_ptr<webots::Motor> frontLeftMotor{};
	std::unique_ptr<webots::Motor> frontRightMotor{};
	std::unique_ptr<webots::Motor> rearLeftMotor{};
	std::unique_ptr<webots::Motor> rearRightMotor{};
	std::unique_ptr<webots::Lidar> lidar{};
	std::vector<LeaderRobot::OOI> mOOIs{};
};