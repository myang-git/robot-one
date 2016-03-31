//robot1.ino

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "Robot.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Robot robot;

void setup() {
  randomSeed(analogRead(3));
  Serial.begin(9600);
  AFMS.begin();
  Serial.println(F("motor shield ready"));
  PololuWheelEncoders::init(2, 3, 4, 5);
  Serial.println(F("wheel encoders ready"));
  robot.begin(&AFMS);
  Serial.println(F("robot initialized"));
  Serial.println(F("wait 1 second"));
  delay(2000);
  Serial.println(F("robot ready"));
}

void loop() {
  //robot.poll();
  robot.testRangeFinder();
  delay(500);
}
