// File:          BaseRobot.cpp
// Date:          XX/XX/XXXX
// Description:   Implementation of BaseRobot to be inherited by the Leader and Scout robots classes.
// Author:        XXX XXX
// zID:           z5401349
// Modifications:

#include "BaseRobot.hpp"

BaseRobot::BaseRobot()
	: ID{ getName() }
	, receiver{ getReceiver("receiver") }
	, emitter{ getEmitter("emitter") }
	, gps{ getGPS("gps") }
	, compass{ getCompass("compass") }
	, keyboard{ getKeyboard() } {
	receiver->enable(TIME_STEP);
	gps->enable(TIME_STEP);
	compass->enable(TIME_STEP);
	keyboard->enable(TIME_STEP);
};

BaseRobot::~BaseRobot() = default;

void BaseRobot::keyboardControl() {
	std::ifstream file("keyboardConfig.txt");
	std::string config;
	std::getline(file, config);
	if (config.compare("keyboardControl=true") == 0) {
		keyboardEnabled = true;
		char const key = static_cast<char>(keyboard->getKey());
		setPosInf();
		if (key == 'W' || key == 'w') {
			move(6.28);
		} else if (key == 'A' || key == 'a') {
			rotate(6.28);
		} else if (key == 'S' || key == 's') {
			move(-6.28);
		} else if (key == 'D' || key == 'd') {
			rotate(-6.28);
		} else {
			stop();
		}
	} else {
		keyboardEnabled = false;
	}
}

void BaseRobot::updateCurrentPosition() {
	// retrieve gps data
	auto gpsValues{ gps->getValues() };
	currentPositionX = gpsValues[0];
	currentPositionY = gpsValues[1];
	// retrieve compass data
	auto compassValues{ compass->getValues() };
	double rad{ atan2(compassValues[1], compassValues[0]) };
	rad -= PI / 2;
	rad *= -1;
	if (rad < 0) {
		rad += 2 * PI;
	}
	currentYaw = rad;
}

void BaseRobot::setTargetPosition(double x, double y) {
	targetPositionX = x;
	targetPositionY = y;
}

bool BaseRobot::moveToTarget(double stopDistance) {
	// calculate distance
	double dist{ sqrt(pow((currentPositionX - targetPositionX), 2) + pow((currentPositionY - targetPositionY), 2)) };
	if (dist <= stopDistance) return true;
	distanceDiff = dist - stopDistance;
	// calcalate angle difference
	double rad{ atan2(targetPositionY - currentPositionY, targetPositionX - currentPositionX) };
	if (rad < 0) {
		rad += 2 * PI;
	}
	if (rad > currentYaw) {
		angleDiff = rad - currentYaw;
	}
	else {
		angleDiff = 2 * PI - (currentYaw - rad);
	}
	return false;
}

void BaseRobot::sendMessage(const std::string& ID, const std::string& data0, const std::string& data1) {
    std::cout << "Sending message to " << ID << std::endl;
    std::string message{};
    message.append(ID);
    message.append("|");
    message.append(data0);
    message.append("|");
    message.append(data1);
    emitter->send(message.c_str(), (int)strlen(message.c_str()) + 1);
}


std::pair<std::string, std::string> BaseRobot::receiveMessage() {
    if (receiver->getQueueLength() > 0) {
        std::string message{ static_cast<const char*>(receiver->getData()) };
        receiver->nextPacket();

        std::istringstream iss{ message };
        std::string incomingId{};
        std::getline(iss, incomingId, '|');

        if (ID.compare(incomingId) == 0) {
            // ID matches, now extract data0 and data1
            std::string data0{};
            std::string data1{};
            if (std::getline(iss, data0, '|') && std::getline(iss, data1, '|')) {
                std::cout << "Received message with matching ID: " << message << std::endl;
                return std::make_pair(data0, data1);
            }
        }
    }
    // If the ID doesn't match or the format is incorrect, return an empty pair
    return std::make_pair("", "");
}

void BaseRobot::wait(double waitPeriod) {
	const double start{ getTime() };
	while (getTime() - start < waitPeriod * 0.001) {
		step(TIME_STEP);
	}
}