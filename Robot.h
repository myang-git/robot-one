/*
 * Robot.h
 *
 *  Created on: Dec 18, 2014
 *      Author: myang0402
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include "Common.h"
#include "Wheel.h"
#include "MotorMovement.h"
#include "MotionController.h"
#include "RangeFinder.h"
#include "IRRangeFinder.h"
#include "SonarRangeFinder.h"
#include "RoutePlanner.h"

class Robot {
private:
	Adafruit_MotorShield* AFMS;
	MotionController motionController;
	SonarRangeFinder frontRangeFinder;
	IRRangeFinder backRangeFinder;
	RoutePlanner routePlanner;
	MotorMovement nextLeftMovement;
	MotorMovement nextRightMovement;

public:
	Robot();

	void begin(Adafruit_MotorShield* AFMS);
	void test();
	void testRangeFinder();
	void poll();
	void printStatus();


};

#endif /* ROBOT_H_ */
