/*
 * MotorMovement.cpp
 *
 *  Created on: Dec 19, 2014
 *      Author: myang
 */

#include "MotorMovement.h"

MotorMovement::MotorMovement(const unsigned int speed, const unsigned int distance, const Direction dir, const MovementDuration duration) {
	this->speed = speed;
	this->distance = distance;
	this->dir = dir;
	this->duration = duration;
}

MotorMovement::MotorMovement() {
	this->speed = 0;
	this->distance = 0;
	this->dir = F;
	this->duration = DEFINITE;
}

void MotorMovement::setSpeed(const unsigned int speed) {
	this->speed = speed;
}

void MotorMovement::setDistance(const unsigned int distance) {
	this->distance = distance;
}

void MotorMovement::setDirection(const Direction dir) {
	this->dir = dir;
}

void MotorMovement::setDuration(const MovementDuration duration) {
	this->duration = duration;
}

unsigned int MotorMovement::getSpeed() {
	return this->speed;
}

unsigned int MotorMovement::getDistance() {
	return this->distance;
}

Direction MotorMovement::getDirection() {
	return this->dir;
}

MovementDuration MotorMovement::getDuration() {
	return this->duration;
}

void MotorMovement::print() {
	Serial.print(F("speed = "));
	Serial.print(this->speed);
	Serial.print(F(", dist = "));
	Serial.print(this->distance);
	Serial.print(F(", dir = "));
	Serial.print(this->dir == F ? F("F") : this->dir == B ? F("B") : F("H"));
	Serial.print(F(", dur = "));
	Serial.print(this->duration == INDEFINITE ? F("INDEF") : F("DEF"));
}