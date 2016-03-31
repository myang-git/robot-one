#ifndef __RANGEFINDER_H__
#define __RANGEFINDER_H__

static const unsigned int kRangeFinderSampleCount = 20;
static const unsigned int kFrontRangeFinderDataPin = 0;
static const unsigned int kBackRangeFinderDataPin = 1;
static const double kVoltConst = 0.0048828125;

class RangeFinder {

public:
	virtual int getDistance();

};

#endif