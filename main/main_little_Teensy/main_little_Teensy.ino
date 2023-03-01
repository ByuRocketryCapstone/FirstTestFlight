#include "motorSetup.h"
#include "motorFcns.h"

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_D0,INPUT); //this corresponds to pin 0 which is our motor enable pin
  pinMode(pin_D1,INPUT); //this is pin 1 which is our direction high is ccw (open) low is cw (close)
  setupMotorDriver();

}

void loop() {
  // put your main code here, to run repeatedly:
  if (pin

}
