#include "IRRangeFinder.h"

IRRangeFinder::IRRangeFinder() {
	this->minDist = 100;
	this->maxDist = 800;
}

void IRRangeFinder::begin(const unsigned int dataPin) {
	this->pin = dataPin;
}

int IRRangeFinder::getDistance() {
  int dist = 0;
  for (int i=0; i<kRangeFinderSampleCount; i++) {
		int reading = analogRead(this->pin);
		double d = 277.28 * pow(map(reading, 0, 1023, 0, 5000)/1000.0, -1.2045);
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