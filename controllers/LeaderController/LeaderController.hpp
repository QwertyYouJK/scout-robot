#pragma once

#include "../BaseRobot/BaseRobot.hpp"

class LeaderController : public BaseRobot {
public:
  LeaderController();
  ~LeaderController();
  
  void run() override;
  void move(double speed) override;
  void rotate(double speed) override;
  
  void speak() override;
  // Add more member functions
private:
  // Add private members
};