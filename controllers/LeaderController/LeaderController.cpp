// File:          LeaderController.cpp
// Date:
// Description:
// Author:
// Modifications:

#include "LeaderController.hpp"

LeaderController::LeaderController() {}
LeaderController::~LeaderController() {}
  
void LeaderController::run() {
  // Main runner for leader robot controller
  while (step(TIME_STEP) != -1) {
    // Main loop
    speak();
  }
}
void LeaderController::move(double speed) {}
void LeaderController::rotate(double speed) {}

void LeaderController::speak() {
  std::cout << "I am the leader\n";
}


int main() {
  LeaderController myController;
  myController.run();
  return 0;
}