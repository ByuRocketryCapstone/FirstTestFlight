//#include "motorSetup.h"
//#include "motorFcns.h"
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
int motor_enable = 0;
int motor_direction = 0;
int limit_switch = 0;
int upSwitch = 0;
int downSwitch = 0;
HighPowerStepperDriver sd;
elapsedMicros sinceStep;
elapsedMillis sinceSense;
const uint16_t StepPeriodUs = 15;
const uint16_t SensePeriodMs = 500;

//function to step motor when it's supposed to
//uint16_t StepMotor(bool motor_direction) {
//
//  if (motor_direction) {
//    sd.step();
//    //Serial.print('1'); //move it up
//    sinceStep = 0;
//    return 1;//return 1 for up
//  }
//
////1 encoder pulse is 360/400 of a revolution about .9 degrees
//
//  else if (!motor_direction) {
//    sd.step();
//    //Serial.print('2');
//    sinceStep = 0;
//    return 2;//return 2 for down
//  }
//
//  else {
//    return 0;//return 0 for no move
//  }
//}

void setup() {
 
  // put your setup code here, to run once:
  int loopnum = 0;
  int driverStatus = 0;
  SPI.begin();
  pinMode(2,INPUT); // manual switch pins up and down switch
  pinMode(3,INPUT); 
  pinMode(20,INPUT); //limit switch which is on pin 20
  pinMode(0,INPUT); //this corresponds to pin 0 which is our motor enable pin
  pinMode(22,INPUT); //this is pin 1 which is our direction high is ccw (open) low is cw (close)
  pinMode(7, OUTPUT);
//  int motor_enable = digitalRead(0);
//  bool motor_direction = digitalRead(22);
//  int limit_switch = digitalRead(20);
//  int upSwitch = digitalRead(3);
//  int downSwitch = digitalRead(2);
  sd.setChipSelectPin(10);
  delay(1);
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
  digitalWrite(7, HIGH);
  sd.setDirection(1);
  //Serial.begin(9600);

}

void loop() {
  int motor_enable = digitalRead(0);
  int motor_direction = digitalRead(22);
  int limit_switch = digitalRead(20);
  int upSwitch = digitalRead(3);
  int downSwitch = digitalRead(2);
  // put your main code here, to run repeatedly:
  limit_switch = 0;
  if ((motor_enable == 1 || upSwitch == 1 || downSwitch == 1) && sinceStep >= StepPeriodUs){
      //Serial.print("I made it here");
      if((motor_direction == 0 || downSwitch == 1) && limit_switch == 1){
        //Serial.print("Whoops I am here now");
      }
      else if(limit_switch == 0){
        if(downSwitch) {
          motor_direction = 0;
        }
        else if(upSwitch) {
          motor_direction = 1;
        }
        //Serial.print("I am just before a step");
        sd.setDirection(motor_direction);
        //Serial.print("DIRECTION SET");
        sd.step();
        //Serial.print("STEP TAKEN");
        delayMicroseconds(StepPeriodUs);
        //StepMotor(motor_direction);
        //sinceStep = 0;
        return 1;
      }

      else if(limit_switch == 1 && (motor_direction == 1 || upSwitch)){
        if(upSwitch) {
          motor_direction = 1;
        }
       sd.setDirection(motor_direction);
       sd.step();
       delayMicroseconds(StepPeriodUs);
       return 2;
      }
}
else if (motor_enable == 0){

  return 0;
    
  }  

}
