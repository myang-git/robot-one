/*
 * MotorMovement.h
 *
 *  Created on: Dec 19, 2014
 *      Author: myang
 */

#ifndef MOTORMOVEMENT_H_
#define MOTORMOVEMENT_H_

#include "Arduino.h"
#include "Wheel.h"
#include "Common.h"

class MotorMovement {
public:
	MotorMovement(const unsigned int speed, const unsigned int distance, const Direction dir, const MovementDuration duration);
	MotorMovement();
	void setDirection(const Direction dir);
	void setSpeed(const unsigned int speed);
	void setDistance(const unsigned int distance);
	void setDuration(const MovementDuration duration);
	unsigned int getSpeed();
	unsigned int getDistance();
	Direction getDirection();
	MovementDuration getDuration();

	void print();

private:
	Direction dir;
	unsigned int speed;
	unsigned int distance;
	MovementDuration duration;
};

#endif /* MOTORMOVEMENT_H_ */
