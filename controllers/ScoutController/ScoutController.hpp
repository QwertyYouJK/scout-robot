#pragma once

#include "../BaseRobot/BaseRobot.hpp"

class ScoutRobot : public BaseRobot {
public:
	ScoutRobot();
	~ScoutRobot();

	void run() override;
	void move(double speed) override;
	void rotate(double speed) override;

	void speak() override;
	bool readColour();
	// Add more member functions
private:
	// Add private members
};