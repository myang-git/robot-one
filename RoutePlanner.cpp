#include "RoutePlanner.h"

RoutePlanner::RoutePlanner() {
  this->lastDistance = -1;
}

void RoutePlanner::begin(RangeFinder* frontRangeFinder, RangeFinder* backRangeFinder) {
  this->frontRangeFinder = frontRangeFinder;
  this->backRangeFinder = backRangeFinder;
}

void RoutePlanner::findExit(MotionController* motionController) {
  MotorMovement leftMovement, rightMovement;
  this->radarSweep(motionController, CRUISE_SPEED, 360, leftMovement, rightMovement);
  motionController->commitMotorMovements(leftMovement, rightMovement);
}

void RoutePlanner::backOut(MotionController* motionController) {
  MotorMovement leftMovement, rightMovement;

  leftMovement.setSpeed(MAX_SPEED);
  leftMovement.setDirection(B);
  leftMovement.setDistance(50);
  leftMovement.setDuration(DEFINITE);
  rightMovement.setSpeed(MAX_SPEED);
  rightMovement.setDirection(B);
  rightMovement.setDistance(50);
  rightMovement.setDuration(DEFINITE);
  motionController->commitMotorMovements(leftMovement, rightMovement);

  motionController->createRotationMovements(MAX_SPEED, 180, leftMovement, rightMovement);
  motionController->commitMotorMovements(leftMovement, rightMovement);

  leftMovement.setSpeed(MAX_SPEED);
  leftMovement.setDirection(F);
  leftMovement.setDistance(300);
  leftMovement.setDuration(DEFINITE);
  rightMovement.setSpeed(MAX_SPEED);
  rightMovement.setDirection(F);
  rightMovement.setDistance(300);
  rightMovement.setDuration(DEFINITE);
  motionController->commitMotorMovements(leftMovement, rightMovement);

  motionController->createRotationMovements(MAX_SPEED, 180, leftMovement, rightMovement);
  motionController->commitMotorMovements(leftMovement, rightMovement);

}

void RoutePlanner::radarSweep(MotionController* motionController, const unsigned int speed, const int degree, MotorMovement& leftMovement, MotorMovement& rightMovement) {
  motionController->createRotationMovements(speed, degree, leftMovement, rightMovement);
  motionController->executeMotorMovements(leftMovement, rightMovement);
  int minDistance = 999999;
  unsigned int leftDist = 0, rightDist = 0;
  while (motionController->isInMotion()) {
    int dist = this->frontRangeFinder->getDistance();
    if (dist < minDistance) {
      minDistance = dist;
      motionController->getWheelDistanceTravelled(leftDist, rightDist);
      Serial.print("RoutePlanner.radarSweep(): found min dist: ");
      Serial.print(dist);
      Serial.print(", left dist: ");
      Serial.print(leftDist);
      Serial.print(", right dist: ");
      Serial.println(rightDist);
    }
  }
  leftMovement.setDistance(leftDist);
  rightMovement.setDistance(rightDist);
}

void RoutePlanner::updateTimer(MotionController* motionController) {
  if (this->lastSampleTime > 0) {
    unsigned long dt = millis() - this->lastSampleTime;
    if (motionController->isMoving()) {
      this->movingTime+=dt;
      this->idleTime = 0;
    }
    else {
      this->movingTime = 0;
      this->idleTime+=dt;
    }
  }  
  this->lastSampleTime = millis();
  Serial.print("RoutePlanner.updateTimer(): moving time: ");
  Serial.print(this->movingTime);
  Serial.print(", idle time: ");
  Serial.println(this->idleTime);
}

void RoutePlanner::stop(MotionController* motionController) {
  MotorMovement stop(0, 0, F, INDEFINITE);
  motionController->commitMotorMovements(stop, stop);
}

void RoutePlanner::cruise(MotionController* motionController) {
  MotorMovement leftCruiseMovement, rightCruiseMovement;
  leftCruiseMovement.setSpeed(CRUISE_SPEED);
  leftCruiseMovement.setDistance(0);
  leftCruiseMovement.setDuration(INDEFINITE);
  rightCruiseMovement.setSpeed(CRUISE_SPEED);
  rightCruiseMovement.setDistance(0);
  rightCruiseMovement.setDuration(INDEFINITE);
  motionController->commitMotorMovements(leftCruiseMovement, rightCruiseMovement);  
}

bool RoutePlanner::nextMove(MotionController* motionController) {
  this->updateTimer(motionController);
	if (motionController->isInMotion()) {
    Serial.println("RoutePlanner.nextMove: in motion. returned");
		return false;
	}

	int dist = this->frontRangeFinder->getDistance();
  int backDist = this->backRangeFinder->getDistance();
  int distDiff = this->lastDistance >= 0 ? dist - this->lastDistance : 0;
  this->lastDistance = dist;

  Serial.print("RoutePlanner.nextMove: dist = ");
  Serial.print(dist);
  Serial.print(", back dist: ");
  Serial.print(backDist);
  Serial.print(", dist diff = ");
  Serial.println(distDiff);

  if (backDist < kRoutePlannerAlertDistance) {
    Serial.println(F("RoutePlanner.nextMove: speed up"));
    MotorMovement speedUp(MAX_SPEED, ROBOT_BODY_RADIUS * 4, F, DEFINITE);
    motionController->commitMotorMovements(speedUp, speedUp);
    Serial.println(F("RoutePlanner.nextMove: done"));
    return true;
  }

  if (dist < kRoutePlannerAlertDistance && distDiff < -300) {
    Serial.println(F("RoutePlanner.nextMove: back out"));
    this->backOut(motionController);
    Serial.println(F("RoutePlanner.nextMove: done"));
    return true;
  }

	if (dist < kRoutePlannerMinDistance) {
    Serial.println(F("RoutePlanner.nextMove: find exit"));
		this->findExit(motionController);
    Serial.println(F("find exit - done"));
    return true;
	}

  // if (dist < kRoutePlannerAlertDistance) {
  //   Serial.println("RoutePlanner.nextMove: slow down");
  //   MotorMovement slowDown(SLOW_SPEED, 0, HOLD, INDEFINITE);
  //   motionController->commitMotorMovements(slowDown, slowDown);
  //   Serial.println("RoutePlanner.nextMove: slow down - done");
  //   return true;
  // }

  long dt = random(5);
  if (this->movingTime > 5 + dt) {
    this->stop(motionController);
    return true;
  }

  if (this->idleTime > 5 + dt) {
    this->cruise(motionController);
    return true;
  }

  this->cruise(motionController);
  Serial.println(F("RoutePlanner.nextMove: enqueued cruising movements"));
	return true;
}
