#include "MotionController.h"

MotionController::MotionController() : leftWheel(LEFT, WHEEL_TRAVEL_PER_TICK), rightWheel(RIGHT, WHEEL_TRAVEL_PER_TICK) {
}

void MotionController::begin(Adafruit_MotorShield* AFMS) {
  this->leftWheel.begin(AFMS);
  this->rightWheel.begin(AFMS);
  this->leftWheelController.begin(&this->leftWheel);
  this->rightWheelController.begin(&this->rightWheel);
}

void MotionController::cruise(const unsigned int speed) {
  this->leftWheel.setSpeed(speed);
  this->rightWheel.setSpeed(speed);
  this->leftWheel.run(F);
  this->rightWheel.run(F);
}

void MotionController::move(const unsigned int speed, const unsigned int distance, Direction dir) {
  MotorMovement leftMovement(speed, distance, dir, DEFINITE);
  MotorMovement rightMovement(speed, distance, dir, DEFINITE);
  this->commitMotorMovements(leftMovement, rightMovement);
}

void MotionController::turn(const unsigned int speed, const int radius, const int degree, const Side side) {
  if(speed==0 || degree==0) {
    return;
  }

}

void MotionController::rotate(const unsigned int speed, const int degree) {
  if(degree==0) {
    return;
  }

  float dist = WHEEL_TRAVEL_PER_DEGREE * abs(degree) / 2;
  Direction leftDir, rightDir;
  if (degree > 0) {
    leftDir = B;
    rightDir = F;
  }
  else {
    leftDir = F;
    rightDir = B;
  }
  MotorMovement leftMovement(speed,  dist, leftDir, DEFINITE);
  MotorMovement rightMovement(speed, dist, rightDir, DEFINITE);
  this->commitMotorMovements(leftMovement, rightMovement);
}

void MotionController::rotateNow(const unsigned int speed, const int degree) {
  MotorMovement leftMovement, rightMovement;
  this->createRotationMovements(speed, degree, leftMovement, rightMovement);
  this->executeMotorMovements(leftMovement, rightMovement);
}

void MotionController::createRotationMovements(const unsigned int speed, const int degree, MotorMovement& leftMovement, MotorMovement& rightMovement) {
  float dist = WHEEL_TRAVEL_PER_DEGREE * abs(degree) / 2;
  Direction leftDir, rightDir;
  if (degree > 0) {
    leftDir = B;
    rightDir = F;
  }
  else {
    leftDir = F;
    rightDir = B;
  }
  leftMovement.setSpeed(speed);
  leftMovement.setDistance(dist);
  leftMovement.setDirection(leftDir);    
  rightMovement.setSpeed(speed);
  rightMovement.setDistance(dist);
  rightMovement.setDirection(rightDir);    
}

void MotionController::commitMotorMovements(const MotorMovement& left, const MotorMovement& right) {
  this->motorMovementQueue.offer(left, right);
}

void MotionController::executeMotorMovements(const MotorMovement& left, const MotorMovement& right) {
  this->leftWheelController.setMotorMovement(left);
  this->rightWheelController.setMotorMovement(right);
  this->leftWheelController.run();
  this->rightWheelController.run();
}

void MotionController::reset() {
  this->leftWheel.stop();
  this->rightWheel.stop();
  this->leftWheel.resetCounter();
  this->rightWheel.resetCounter();
  this->motorMovementQueue.clear();
}

void MotionController::getWheelDistanceTravelled(unsigned int& leftDistance, unsigned int& rightDistance) {
  leftDistance = abs(this->leftWheel.getDistanceTravelled());
  rightDistance = abs(this->rightWheel.getDistanceTravelled());
}

bool MotionController::isMoving() {
  bool leftMoving = this->leftWheelController.isMoving();
  bool rightMoving = this->rightWheelController.isMoving();
  return leftMoving || rightMoving;
}

bool MotionController::isInMotion() {
  bool leftInMotion = this->leftWheelController.hasMovement();
  bool rightInMotion = this->rightWheelController.hasMovement();
  Serial.print(F("MotionController.isInMotion: leftInMotion = "));
  Serial.print(leftInMotion);
  Serial.print(F(", rightInMotion = "));
  Serial.println(rightInMotion);
  return leftInMotion || rightInMotion;
}

void MotionController::step() {
  bool isLeftInMotion = this->leftWheelController.step();
  bool isRightInMotion = this->rightWheelController.step();

  if ((!isLeftInMotion) && (!isRightInMotion)) {
    if (this->motorMovementQueue.getSize() == 0) {
      Serial.println(F("MotionController.step(): queue is empty, return"));
      return;
    }
    MotorMovement leftMovement, rightMovement;
    this->motorMovementQueue.take(leftMovement, rightMovement);
    Serial.println(F("MotionController.step: fetched left and right movements"));
    Serial.print(F("MotionController.step: "));
    Serial.print(F("left movement: "));
    leftMovement.print();
    Serial.print(F(", right movement: "));
    rightMovement.print();
    Serial.println();
    this->executeMotorMovements(leftMovement, rightMovement);
  }
}