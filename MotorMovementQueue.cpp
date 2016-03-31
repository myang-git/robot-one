#include "MotorMovementQueue.h"

MotorMovementQueue::MotorMovementQueue() {
	this->head = 0;
	this->tail = 0;
	this->size = 0;
}

bool MotorMovementQueue::offer(const MotorMovement& leftMovement, const MotorMovement& rightMovement) {
	if (this->size == kMotorMovementQueueSize) {
		return false;
	}
	this->leftMovements[this->tail] = leftMovement;
	this->rightMovements[this->tail] = rightMovement;
	this->tail = (this->tail + 1) % kMotorMovementQueueSize;
	this->size++;
}

bool MotorMovementQueue::take(MotorMovement& leftMovement, MotorMovement& rightMovement) {
	if (this->size==0) {
		return false;
	}
	leftMovement = this->leftMovements[this->head];
	rightMovement = this->rightMovements[this->head];
	this->size--;
	if (this->size > 0) {
		this->head = (this->head + 1) % kMotorMovementQueueSize;
	}
	else {
		this->tail = this->head;
	}
}

int MotorMovementQueue::getSize() {
	return this->size;
}

void MotorMovementQueue::clear() {
	this->size = 0;
	this->head = 0;
	this->tail = this->head;
}