#include "WheelController.h"

WheelController::WheelController() {

}

void WheelController::begin(Wheel* wheel) {
	this->wheel = wheel;
	this->motorMovement.setDuration(INDEFINITE);
}

void WheelController::setMotorMovement(const MotorMovement& movement) {
	this->motorMovement = movement;
	this->wheel->setSpeed(this->motorMovement.getSpeed());
}

void WheelController::run() {
	this->wheel->resetCounter();
	if (this->motorMovement.getDirection() != HOLD) {
		this->wheel->run(this->motorMovement.getDirection());
	}
}

bool WheelController::isMoving() {
	(this->motorMovement.getSpeed() > 0 && this->motorMovement.getDuration() == INDEFINITE) || this->hasMovement();
}

bool WheelController::hasMovement() {
	if (this->motorMovement.getDuration() == INDEFINITE) {
		return false;
	}
	unsigned int targetDist = this->motorMovement.getDistance();
	unsigned int distTravelled = abs(this->wheel->getDistanceTravelled());
	return distTravelled < targetDist;
}

bool WheelController::step() {
	if (this->motorMovement.getDuration() == INDEFINITE) {
		return false;
	}

	bool hasPendingMovement = true;
	unsigned int targetDist = this->motorMovement.getDistance();
	unsigned int distTravelled = abs(this->wheel->getDistanceTravelled());
	if (distTravelled >= targetDist)  {
		this->wheel->stop();
		hasPendingMovement = false;
	}
	Serial.print(F("WheelController.step: target dist = "));
	Serial.print(targetDist);
	Serial.print(F(", dist travelled = "));
	Serial.print(distTravelled);
	Serial.print(F(", dur = "));
	Serial.print(this->motorMovement.getDuration() == INDEFINITE ? "INDEF" : "DEF");
	Serial.println();
	return hasPendingMovement;
}