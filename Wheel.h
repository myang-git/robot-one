
/*
 * Wheel.h
 *
 *  Created on: Dec 19, 2014
 *      Author: myang
 */

#ifndef WHEEL_H_
#define WHEEL_H_

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <PololuWheelEncoders.h>

#include "Common.h"


class Wheel {
public:
	Wheel(const Side side, const int mmPerTick);
	void begin(Adafruit_MotorShield* AFMS);
	int getDistanceTravelled();
	void resetCounter();
	void setSpeed(const int speed);
	void run(const Direction dir);
	void stop();
	void brake();

private:
	Side side;
	Adafruit_DCMotor* motor;
	int mmPerTick;
	int currentMotorDir;
	int currentSpeed;

	int getCounts();
};

#endif /* WHEEL_H_ */
