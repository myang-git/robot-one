/*
 * Common.h
 *
 *  Created on: Dec 19, 2014
 *      Author: myang0402
 */

#ifndef COMMON_H_
#define COMMON_H_

const float Pi = 3.1415926;
const float PI_180 = 0.01745329251;
const int INF_DISTANCE = 999999;
const int MAX_SPEED = 170;
const int CRUISE_SPEED = 100;
const int SLOW_SPEED = 65;
const int ROBOT_BODY_RADIUS = 44;
const int INCH_TO_MM = 25.4;

typedef enum {LEFT, RIGHT} Side;

typedef enum {F, B, HOLD} Direction;

typedef enum {INDEFINITE, DEFINITE} MovementDuration;


#endif /* COMMON_H_ */
