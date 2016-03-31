#ifndef __SONARRANGEFINDER_H__
#define __SONARRANGEFINDER_H__
#include <Arduino.h>

#include "Common.h"
#include "RangeFinder.h"

static const unsigned int kUltrasoundMinDist = 25.4 * 6;
static const unsigned int kUltrasoundMaxDist = 25.4 * 254;

class SonarRangeFinder : public RangeFinder {

private:
	unsigned int pin;
	double mmPerVolt;
	double minDist;
	double maxDist;

public:
  SonarRangeFinder();
  void begin(const unsigned int dataPin);
  int getDistance();

};

#endif