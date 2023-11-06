#pragma once

#include "../BaseRobot/BaseRobot.hpp"

class LeaderRobot : public BaseRobot {
public:
	LeaderRobot();
	~LeaderRobot();
  
	void run() override;
	void move(double speed) override;
	void rotate(double speed) override;
  
	void speak() override;
	// Add more member functions
private:
	// Add private members
};