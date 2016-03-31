/*
 * Wheel.cpp
 *
 *  Created on: Dec 19, 2014
 *      Author: myang
 */

#include "Wheel.h"

Wheel::Wheel(const Side side, const int mmPerTick) {
	this->side = side;
	this->mmPerTick = mmPerTick;
	this->currentSpeed = 0;
	this->currentMotorDir = RELEASE;

}

void Wheel::begin(Adafruit_MotorShield* AFMS) {
	if (this->side == LEFT) {
		this->motor = AFMS->getMotor(1);
		Serial.println(F("getMotor(1)"));
	}
	else if (this->side == RIGHT) {
		this->motor = AFMS->getMotor(2);
		Serial.println(F("getMotor(2)"));
	}
	this->motor->setSpeed(0);
	this->motor->run(FORWARD);
	this->motor->run(RELEASE);
	this->currentSpeed = 0;
	this->currentMotorDir = RELEASE;
}

void Wheel::setSpeed(const int speed) {
	this->motor->setSpeed(speed);
	this->currentSpeed = speed;
}

void Wheel::run(const Direction dir) {
	int motorDirection = 0;
	if(dir==F) {
		this->currentMotorDir = FORWARD;
		Serial.println(F("Wheel.run(): motor->run(F)"));
	}
	else if(dir==B) {
		this->currentMotorDir = BACKWARD;
		Serial.println(F("Wheel.run(): motor->run(B)"));
	}
	else if(dir==HOLD) {
		Serial.println(F("Wheel.run(): hold"));
	}
	this->motor->setSpeed(this->currentSpeed);
	this->motor->run(this->currentMotorDir);
}

void Wheel::stop() {
	this->motor->run(RELEASE);
	this->motor->setSpeed(0);
	this->currentSpeed = 0;
	this->currentMotorDir = RELEASE;
}

void Wheel::brake() {
	this->motor->run(BRAKE);
	this->motor->setSpeed(0);
	this->currentSpeed = 0;
	this->currentMotorDir = BRAKE;
}

int Wheel::getCounts() {
	int counts = 0;
	if(this->side==LEFT) {
		counts = PololuWheelEncoders::getCountsM1();
	}
	else {
		counts = PololuWheelEncoders::getCountsM2();
	}
	return counts;
}

int Wheel::getDistanceTravelled() {
	int counts = this->getCounts();
	return counts * this->mmPerTick;
}

void Wheel::resetCounter() {
	if(this->side==LEFT) {
		PololuWheelEncoders::getCountsAndResetM1();
	}
	else {
		PololuWheelEncoders::getCountsAndResetM2();
	}
}
