#include "SonarRangeFinder.h"

SonarRangeFinder::SonarRangeFinder() {

}

void SonarRangeFinder::begin(const unsigned int dataPin) {
	this->pin = dataPin;
	this->mmPerVolt = 5.0 / 512 * 25.4;
	this->minDist = 25.4 * 6;
	this->maxDist = 25.4 * 254;
}

int SonarRangeFinder::getDistance() {
  int dist = 0;
  for (int i=0; i<kRangeFinderSampleCount; i++) {
  	double d = analogRead(this->pin) / 2 * 25.4;
  	if (d < this->minDist) {
  		d = this->minDist;
  	}
  	if (d > this->maxDist) {
  		d = this->maxDist;
  	}
    dist = dist + d;
  }
  return dist / kRangeFinderSampleCount;
}