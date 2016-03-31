#ifndef __ROUTEPLANNER_H__
#define __ROUTEPLANNER_H__

#include "Common.h"
#include "Utils.h"
#include "MotionController.h"
#include "MotorMovement.h"
#include "RangeFinder.h"

static const unsigned int kRoutePlannerAlertDistance = 500;
static const unsigned int kRoutePlannerMinDistance = 5 * ROBOT_BODY_RADIUS;

class RoutePlanner {

private:
  RangeFinder* frontRangeFinder;
  RangeFinder* backRangeFinder;
  unsigned long lastSampleTime;
  unsigned long movingTime;
  unsigned long idleTime;
  unsigned int lastDistance;
	void radarSweep(MotionController* motionController, const unsigned int speed, const int degree, MotorMovement& leftMovementOut, MotorMovement& rightMovementOut);
  void findExit(MotionController* motionController);
  void backOut(MotionController* motionController);
  void updateTimer(MotionController* motionController);
  void cruise(MotionController* motionController);
  void stop(MotionController* motionController);

public:
  RoutePlanner();
  void begin(RangeFinder* frontRangeFinder, RangeFinder* backRangeFinder);
  bool nextMove(MotionController* motionController);
};

#endif