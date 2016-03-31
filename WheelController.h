#ifndef __WHEELCONTROLLER_H__
#define __WHEELCONTROLLER_H__

#include "Wheel.h"
#include "MotorMovement.h"

class WheelController {

private:
	Wheel* wheel;
	MotorMovement motorMovement;

public:
	WheelController();
	void begin(Wheel* wheel);
	void setMotorMovement(const MotorMovement& movement);
	void run();
	bool hasMovement();
	bool isMoving();
	bool step();

};

#endif