#ifndef __MOTORMOVEMENTQUEUE_H__
#define __MOTORMOVEMENTQUEUE_H__

#include "MotorMovement.h"

const static unsigned int kMotorMovementQueueSize = 5;

class MotorMovementQueue {

private:
	uint8_t size;
	uint8_t head;
	uint8_t tail;
	MotorMovement leftMovements[kMotorMovementQueueSize];
	MotorMovement rightMovements[kMotorMovementQueueSize];

public:
	MotorMovementQueue();
	bool offer(const MotorMovement& leftMovement, const MotorMovement& rightMovement);
	bool take(MotorMovement& leftMovement, MotorMovement& rightMovement);
	int getSize();
	void clear();

};

#endif