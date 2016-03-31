#ifndef __IRRANGEFINDER_H__
#define __IRRANGEFINDER_H__

#include <Arduino.h>
#include "RangeFinder.h"

static const unsigned int kIRMinDist = 100;
static const unsigned int kIRMaxDist = 800;
static const double kIRMMPerVolt = (kIRMaxDist - kIRMinDist) / (0.4 - 3.0);


class IRRangeFinder : public RangeFinder {

private:
	double minDist;
	double maxDist;
	unsigned int pin;

public:
	IRRangeFinder();
	void begin(const unsigned int dataPin);
	int getDistance();

};


#endif
