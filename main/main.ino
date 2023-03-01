// import custom header files
#include "motorSetup.h"
#include "sensorSetup.h"
#include "mainSM.h"
#include "Logger.h"
#include "SensorData.h"
#include "motorFcns.h"
#include "sensorFcns.h"

#include <SD.h>

SensorData* sensorDataList[16];

Adafruit_LSM6DS33 lsm6ds;
Adafruit_LIS3MDL lis3mdl;
Adafruit_DPS310 dps;
Adafruit_Sensor *dps_temp = dps.getTemperatureSensor();
Adafruit_Sensor *dps_pressure = dps.getPressureSensor();

char logBuffer[10240];    //buffer to store log messages between log ticks
File logFile, indexFile, refFile;
const int chipSelect = BUILTIN_SDCARD;
double cutoffTime;
extern double encoder_value;
bool motorRun = false;
bool motorRetract = false;


void setup()
{
  Serial1.begin(115200);//600000);//4608000);//921600);//600000);//115200);
  //while (!Serial1)
  //delay(10); // will pause Zero, Leonardo, etc until serial console opens
  SPI.begin();
  sd.setChipSelectPin(CSPin);
  pinMode(upSwitchPin, INPUT);
  pinMode(downSwitchPin, INPUT);
  pinMode(pin_A5,OUTPUT); //this corresponds to pin 33 which is our motor enable pin
  pinMode(pin_A6,OUTPUT); //this is pin 34 which is our direction high is ccw (open) low is cw (close)
  digitalWrite(pin_A5,LOW); // make sure that some how the motor driver is not enabled before it should


  setupMotorDriver();
  setupSensors();

  main_Init();

  for (int i = 0; i < 16; i++)
  {
    sensorDataList[i] = new SensorData(0,0,0,0,0);
  }

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect.
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

 File dataFile = SD.open("data.txt", FILE_WRITE);

   if (!dataFile) {
    Serial.println("Error opening file.");
    return;
  }
  else {
    Serial.println("The File Exists and We are ready to go")
    }

  }


//if (SD.exists("example.txt")) {
//    Serial.println("example.txt exists.");
//  }
//  else {
//    Serial.println("example.txt doesn't exist.");
//  }
//
//  // open a new file and immediately close it:
//  Serial.println("Creating example.txt...");
//  myFile = SD.open("example.txt", FILE_WRITE);
//  myFile.close();
//
//  // Check to see if the file exists: 
//  if (SD.exists("example.txt")) {
//    Serial.println("example.txt exists.");
//  }
//  else {
//    Serial.println("example.txt doesn't exist.");  
//  }
//
//  // delete the file:
//  Serial.println("Removing example.txt...");
//  SD.remove("example.txt");
//
//  if (SD.exists("example.txt")){ 
//    Serial.println("example.txt exists.");
//  }
//  else {
//    Serial.println("example.txt doesn't exist.");  
//  }
//}



void loop()
{
  static double mainSMTickRate = 1000/10;                      //main state machine tick rate converted from Hz to ms
  static double hardwareTickRate = 1000/20;
  static double sensorTickRate = 1000/20;
  static double logTickRate = 1000/20;

  static double lastMainTick = 0;
  static double lastHardwareTick = 0;
  static double lastSensorTick = 0;
  static double lastLogTick = 0;
  

  // Manage state machine ticks
  if (millis() - lastMainTick > mainSMTickRate)
  {
    main_Tick();
  }
  if (millis() - lastHardwareTick > hardwareTickRate)
  {
    motor_tick();
  }
  if (millis() - lastSensorTick > sensorTickRate)
  {
    sensor_tick();
  }
  if (millis() - lastLogTick > logTickRate)
  {
    //log_tick();
  }

  if (motorRun == true) {


    //probably something here to read what the encoder value is 
    for ( encodervalue < 23) {
    digitalWrite(pin_A5, HIGH); //motor is enabled
    digitalWrite(pin_A6, HIGH); // direction is ccw
    }

    for ( encodervalue >= 23) {
    digitalWrite(pin_A5,LOW);
    }


    if (millis() - cutoffTime >= 20){
 
    for (encodervalue < 67) {
    digitalWrite(pin_A5, HIGH); //motor is enabled
    digitalWrite(pin_A6, HIGH); // direction is ccw
    }

    for ( encodervalue >= 67) {
    digitalWrite(pin_A5,LOW)
    }
    
    }
     
}

if (motorRetract == true){

    for (encodervalue >= 0){
      digitalWrite(pin_A5,HIGH);
      digitalWrite(pin_A6,LOW);
      }
    digitalWrite(pin_A5, LOW);  
  }
  
}
//void getData()
//{
//  sensors_event_t accel, gyro, mag, temp;
//  sensors_event_t temp_event, pressure_event;
//
//  // read the state of the switch
//  upSwState = digitalRead(upSwitchPin);
//  dwnSwState = digitalRead(downSwitchPin);
//  //limitUp = digitalRead(limitUpSwitchPin);
//  //limitDwn = digitalRead(limitDwnSwitchPin);
//
//  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
//  if (upSwState == HIGH && dwnSwState == HIGH) {
//  } else if(upSwState == HIGH && !dirSetUp){ //set dir up
//    sd.setDirection(0);
//    dirSetUp = 1;
//    sd.enableDriver();
//  } else if (upSwState == HIGH && dirSetUp && !limitUp) {//just step up if not at limit
//    //sd.step();
//    //delayMicroseconds(StepPeriodUs);
//    StepMotor(StepPeriodUs);
//  }
//  else if(dwnSwState == HIGH && !dirSetDwn) {//set dir down
//    sd.setDirection(1);
//    dirSetDwn = 1;
//    sd.enableDriver();
//  } else if (dwnSwState == HIGH && dirSetDwn && !limitDwn) {//just step down if not at limit
//    //sd.step();
//    //delayMicroseconds(StepPeriodUs);
//    StepMotor(StepPeriodUs);
//  } 
//  else {//don't move
//    dirSetUp = 0;
//    dirSetDwn = 0;
//    sd.disableDriver();
//    //sd.setDirection(1);
//    //sd.enableDriver();
//    //sd.step();
//    //delayMicroseconds(StepPeriodUs);
//  }
//  //Serial.println(sd.readStatus());
// 
//  //int fault = sd.readFaults();
//  //Serial.println();
// 
//
////encoder
//
//  if (encoder.CHANGING) {
//    Serial1.println("Enc Val: " + String(encoder.VALUE));
//    if (encoder.CLOCKWISE) {
//      Serial1.println("Enc mov cw");
//    }
//    else if (encoder.COUNTERCLOCKWISE) {
//      Serial1.println("Enc mov ccw");
//    }
//  }
//
////check sensors every 100 milliseconds
//  if (sinceSense >= SensePeriodMs) {
//    //DPS
//      if (dps.temperatureAvailable()) {
//        dps_temp->getEvent(&temp_event);
//        //Serial1.print(F("Temperature = "));
//        //Serial1.print(temp_event.temperature);
//        //Serial1.println(" *C");
//        //Serial1.println();
//      //}
//
//      // Reading pressure also reads temp so don't check pressure
//      // before temp!
//      //if (dps.pressureAvailable()) {
//        dps_pressure->getEvent(&pressure_event);
//        //Serial1.print(F("Pressure = "));
//        //Serial1.print(pressure_event.pressure);
//        //Serial1.println(" hPa");
//      
//        //Serial1.println();
//      //}
//      }
//    //dps^^
//      //  /* Get new normalized sensor events */
//      lsm6ds.getEvent(&accel, &gyro, &temp);
//      lis3mdl.getEvent(&mag);
//
//      /* Display the results (acceleration is measured in m/s^2) */
//      //Serial.print("\t\tAccel X: ");
//      //Serial.print(accel.acceleration.x, 4);
//      //Serial.print(" \tY: ");
//      //Serial.print(accel.acceleration.y, 4);
//      //Serial.print(" \tZ: ");
//      //Serial.print(accel.acceleration.z, 4);
//      //Serial.println(" \tm/s^2 ");
//
//      /* Display the results (rotation is measured in rad/s) */
//      //Serial.print("\t\tGyro  X: ");
//      //Serial.print(gyro.gyro.x, 4);
//      //Serial.print(" \tY: ");
//      //Serial.print(gyro.gyro.y, 4);
//      //Serial.print(" \tZ: ");
//      //Serial.print(gyro.gyro.z, 4);
//      //Serial.println(" \tradians/s ");
//
//      /* Display the results (magnetic field is measured in uTesla) */
//      //Serial.print(" \t\tMag   X: ");
//      //Serial.print(mag.magnetic.x, 4);
//      //Serial.print(" \tY: ");
//      //Serial.print(mag.magnetic.y, 4);
//      //Serial.print(" \tZ: ");
//      //Serial.print(mag.magnetic.z, 4);
//      //Serial.println(" \tuTesla ");
//
//      //Serial.print("\t\tTemp   :\t\t\t\t\t");
//      //Serial.print(temp.temperature);
//      //Serial.println(" \tdeg C");
//      //Serial.println();
//      //delay(1000);
//}
