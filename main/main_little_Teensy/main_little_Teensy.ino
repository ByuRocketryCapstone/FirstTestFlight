#include "motorSetup.h"
#include "motorFcns.h"
#include <SPI.h>
#include <HighPowerStepperDriver.h>
//const uint8_t CSPin = 10;
//const uint8_t upSwitchPin = 1;
//const uint8_t downSwitchPin = 2;
//const uint8_t limitUpSwitchPin = 15;
//const uint8_t limitDwnSwitchPin = 16;
//int upSwState = 0;
//int dwnSwState = 0;
//int dirSetUp = 0;
//int dirSetDwn = 0;
//int limitUp = 0;
//int limitDwn = 0;
//int loopnum = 0;
//int driverStatus = 0;
//const uint16_t StepPeriodUs = 15;
//const uint16_t SensePeriodMs = 500;
//HighPowerStepperDriver sd;
//elapsedMicros sinceStep;
//elapsedMillis sinceSense;
int motor_enable;
int motor_direction;
int limit_switch;
int upSwitch;
int downSwitch;

 
void setup() {
  // put your setup code here, to run once:
  HighPowerStepperDriver sd;
  elapsedMicros sinceStep;
  elapsedMillis sinceSense;
  const uint16_t StepPeriodUs = 15;
  const uint16_t SensePeriodMs = 500;
  int loopnum = 0;
  int driverStatus = 0;
  SPI.begin();
  pinMode(2,INPUT); // manual switch pins up and down switch
  pinMode(3,INPUT); 
  pinMode(20,INPUT); //limit switch which is on pin 20
  pinMode(0,INPUT); //this corresponds to pin 0 which is our motor enable pin
  pinMode(1,INPUT); //this is pin 1 which is our direction high is ccw (open) low is cw (close)
  int motor_enable = digitalRead(0);
  int motor_direction = digitalRead(1);
  int limit_switch = digitalRead(20);
  int upSwitch = digitalRead(3);
  int downSwitch = digitalRead(2);
  delay(1);
  sd.setChipSelectPin(10);
  sd.resetSettings();
  sd.clearStatus();
  // Select auto mixed decay.  TI's DRV8711 documentation recommends this mod
  // for most applications, and we find that it usually works well.
  sd.setDecayMode(HPSDDecayMode::AutoMixed);
  // Set the current limit. You should change the number here to an appropriate
  // value for your particular system.
  sd.setCurrentMilliamps36v4(3000);
  // Set the number of microsteps that correspond to one full step. 32
  sd.setStepMode(HPSDStepMode::MicroStep32);
  // Enable the motor outputs.
  sd.enableDriver();
  

}

void loop() {
  // put your main code here, to run repeatedly:
  int limit_switch = 0;
  if (motor_enable == 1){
      if(motor_direction == 0 && limit_switch == 1){
        //do nothing
      }
      if(limit_switch == 0){
       StepMotor(motor_direction);
      }

      if(limit_switch == 1 && motor_direction == 1){
       StepMotor(motor_direction);
      }
}
else if (motor_enable == 0){

  //do nothing or you die
    
  }

if (upSwitch == 1){
      if(motor_direction == 0 && limit_switch == 1){
        //do nothing
      }
      if(limit_switch == 0){
       StepMotor(motor_direction);
      }
}
else if (downSwitch == 0){

  //do nothing or you die
    
  }

  

}
