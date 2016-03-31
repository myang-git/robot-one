#ifndef __MOTIONCONTROLLER_H__
#define __MOTIONCONTROLLER_H__

#include <Adafruit_MotorShield.h>
#include "Common.h"
#include "Wheel.h"
#include "WheelController.h"
#include "MotorMovement.h"
#include "MotorMovementQueue.h"

const float WHEEL_TRAVEL_PER_DEGREE = PI_180 * ROBOT_BODY_RADIUS;
const int WHEEL_TRAVEL_PER_TICK = 3;

class MotionController {

private:
  Wheel leftWheel;
  Wheel rightWheel;
  WheelController leftWheelController;
  WheelController rightWheelController;
  MotorMovementQueue motorMovementQueue;

public:
  MotionController();
  void begin(Adafruit_MotorShield* AFMS);
  void commitMotorMovements(const MotorMovement& left, const MotorMovement& right);
  void executeMotorMovements(const MotorMovement& left, const MotorMovement& right);
  void cruise(const unsigned int speed);
  void move(const unsigned int speed, const unsigned int distance, const Direction dir);
  void turn(const unsigned int speed, const int radius, const int degree, const Side side);
  void rotate(const unsigned int speed, const int degree);
  void rotateNow(const unsigned int speed, const int degree);
  void createRotationMovements(const unsigned int speed, const int degree, MotorMovement& leftMovement, MotorMovement& rightMovement);
  void getWheelDistanceTravelled(unsigned int& leftDistance, unsigned int& rightDistance);
  bool isInMotion();
  bool isMoving();
  void reset();
  void step();

};

#endif
