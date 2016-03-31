/*
 * Robot.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: myang0402
 */

#include "Robot.h"

Robot::Robot() {
}

void Robot::begin(Adafruit_MotorShield* AFMS) {
	this->AFMS = AFMS;
	this->motionController.begin(this->AFMS);
	this->frontRangeFinder.begin(kFrontRangeFinderDataPin);
	this->backRangeFinder.begin(kBackRangeFinderDataPin);
	this->routePlanner.begin(&this->frontRangeFinder, &this->backRangeFinder);
}

void Robot::test() {
	this->motionController.rotate(CRUISE_SPEED, 360);
	this->motionController.step();
}

void Robot::testRangeFinder() {
	int frontDist = this->frontRangeFinder.getDistance();
	int backDist = this->frontRangeFinder.getDistance();
	Serial.print("front dist: ");
	Serial.print(frontDist);
	Serial.print(", back dist: ");
	Serial.println(backDist);
}

void Robot::poll() {
	this->motionController.step();
	this->routePlanner.nextMove(&this->motionController);
}

void Robot::printStatus() {
}
