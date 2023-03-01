#include <SPI.h>
#include <HighPowerStepperDriver.h>

const uint8_t CSPin = 10;
const uint8_t upSwitchPin = 1;
const uint8_t downSwitchPin = 2;
//const uint8_t limitUpSwitchPin = 15;
//const uint8_t limitDwnSwitchPin = 16;
int upSwState = 0;
int dwnSwState = 0;
int dirSetUp = 0;
int dirSetDwn = 0;
int limitUp = 0;
int limitDwn = 0;
int loopnum = 0;
int driverStatus = 0;

const uint16_t StepPeriodUs = 15;
const uint16_t SensePeriodMs = 500;

HighPowerStepperDriver sd;

elapsedMicros sinceStep;
elapsedMillis sinceSense;


void setupMotorDriver()
{
  // Give the driver some time to power up.
  delay(1);
  
  // Reset the driver to its default settings and clear latched status
  // conditions.
  sd.resetSettings();
  sd.clearStatus();

  // Select auto mixed decay.  TI's DRV8711 documentation recommends this mode
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
