#ifndef SENSOR_SETUP_H
#define SENSOR_SETUP_H

#include <Adafruit_LSM6DS33.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_DPS310.h>

extern Adafruit_LSM6DS33 lsm6ds;
extern Adafruit_LIS3MDL lis3mdl;
extern Adafruit_DPS310 dps;
extern Adafruit_Sensor *dps_temp;
extern Adafruit_Sensor *dps_pressure;

void setupSensors()
{
    Serial1.println("Adafruit LSM6DS+LIS3MDL test!");

  bool lsm6ds_success, lis3mdl_success;

  // hardware I2C mode, can pass in address & alt Wire

  lsm6ds_success = lsm6ds.begin_I2C();
  lis3mdl_success = lis3mdl.begin_I2C();

  if (!lsm6ds_success) {
    Serial1.println("Failed to find LSM6DS chip");
  }
  if (!lis3mdl_success) {
    Serial1.println("Failed to find LIS3MDL chip");
  }
  if (!(lsm6ds_success && lis3mdl_success)) {
    while (1) {
      delay(10);
    }
  }

  Serial1.println("DPS310");
  if (! dps.begin_I2C(0x77)) {
    Serial1.println("Failed to find DPS");
    //while (1) yield();
  }
  else {
    Serial1.println("DPS OK!");

    // Setup highest precision
    dps.configurePressure(DPS310_64HZ, DPS310_64SAMPLES);
    dps.configureTemperature(DPS310_64HZ, DPS310_64SAMPLES);

    dps_temp->printSensorDetails();
    dps_pressure->printSensorDetails();
  }

  Serial1.println("LSM6DS and LIS3MDL Found!");

  // lsm6ds.setAccelRange(LSM6DS_ACCEL_RANGE_2_G);
  Serial1.print("Accelerometer range set to: ");
  switch (lsm6ds.getAccelRange()) {
    case LSM6DS_ACCEL_RANGE_2_G:
      Serial1.println("+-2G");
      break;
    case LSM6DS_ACCEL_RANGE_4_G:
      Serial1.println("+-4G");
      break;

    case LSM6DS_ACCEL_RANGE_8_G:

      Serial1.println("+-8G");

      break;

    case LSM6DS_ACCEL_RANGE_16_G:

      Serial1.println("+-16G");

      break;

  }



  // lsm6ds.setAccelDataRate(LSM6DS_RATE_12_5_HZ);

  Serial1.print("Accelerometer data rate set to: ");

  switch (lsm6ds.getAccelDataRate()) {

    case LSM6DS_RATE_SHUTDOWN:

      Serial1.println("0 Hz");

      break;

    case LSM6DS_RATE_12_5_HZ:

      Serial1.println("12.5 Hz");

      break;

    case LSM6DS_RATE_26_HZ:

      Serial1.println("26 Hz");

      break;

    case LSM6DS_RATE_52_HZ:

      Serial1.println("52 Hz");

      break;

    case LSM6DS_RATE_104_HZ:

      Serial1.println("104 Hz");

      break;

    case LSM6DS_RATE_208_HZ:

      Serial1.println("208 Hz");

      break;

    case LSM6DS_RATE_416_HZ:

      Serial1.println("416 Hz");

      break;

    case LSM6DS_RATE_833_HZ:

      Serial1.println("833 Hz");

      break;

    case LSM6DS_RATE_1_66K_HZ:

      Serial1.println("1.66 KHz");

      break;

    case LSM6DS_RATE_3_33K_HZ:

      Serial1.println("3.33 KHz");

      break;

    case LSM6DS_RATE_6_66K_HZ:

      Serial1.println("6.66 KHz");

      break;

  }



  // lsm6ds.setGyroRange(LSM6DS_GYRO_RANGE_250_DPS );

  Serial1.print("Gyro range set to: ");

  switch (lsm6ds.getGyroRange()) {

    case LSM6DS_GYRO_RANGE_125_DPS:

      Serial1.println("125 degrees/s");

      break;

    case LSM6DS_GYRO_RANGE_250_DPS:

      Serial1.println("250 degrees/s");

      break;

    case LSM6DS_GYRO_RANGE_500_DPS:

      Serial1.println("500 degrees/s");

      break;

    case LSM6DS_GYRO_RANGE_1000_DPS:

      Serial1.println("1000 degrees/s");

      break;

    case LSM6DS_GYRO_RANGE_2000_DPS:

      Serial1.println("2000 degrees/s");

      break;

    case ISM330DHCX_GYRO_RANGE_4000_DPS:

      Serial1.println("4000 degrees/s");

      break;

  }

  // lsm6ds.setGyroDataRate(LSM6DS_RATE_12_5_HZ);

  Serial1.print("Gyro data rate set to: ");

  switch (lsm6ds.getGyroDataRate()) {

    case LSM6DS_RATE_SHUTDOWN:

      Serial1.println("0 Hz");

      break;

    case LSM6DS_RATE_12_5_HZ:

      Serial1.println("12.5 Hz");

      break;

    case LSM6DS_RATE_26_HZ:

      Serial1.println("26 Hz");

      break;

    case LSM6DS_RATE_52_HZ:

      Serial1.println("52 Hz");

      break;

    case LSM6DS_RATE_104_HZ:

      Serial1.println("104 Hz");

      break;

    case LSM6DS_RATE_208_HZ:

      Serial1.println("208 Hz");

      break;

    case LSM6DS_RATE_416_HZ:

      Serial1.println("416 Hz");

      break;

    case LSM6DS_RATE_833_HZ:

      Serial1.println("833 Hz");

      break;

    case LSM6DS_RATE_1_66K_HZ:

      Serial1.println("1.66 KHz");

      break;

    case LSM6DS_RATE_3_33K_HZ:

      Serial1.println("3.33 KHz");

      break;

    case LSM6DS_RATE_6_66K_HZ:

      Serial1.println("6.66 KHz");

      break;

  }



  lis3mdl.setDataRate(LIS3MDL_DATARATE_155_HZ);

  // You can check the datarate by looking at the frequency of the DRDY pin

  Serial1.print("Magnetometer data rate set to: ");

  switch (lis3mdl.getDataRate()) {

    case LIS3MDL_DATARATE_0_625_HZ: Serial1.println("0.625 Hz"); break;

    case LIS3MDL_DATARATE_1_25_HZ: Serial1.println("1.25 Hz"); break;

    case LIS3MDL_DATARATE_2_5_HZ: Serial1.println("2.5 Hz"); break;

    case LIS3MDL_DATARATE_5_HZ: Serial1.println("5 Hz"); break;

    case LIS3MDL_DATARATE_10_HZ: Serial1.println("10 Hz"); break;

    case LIS3MDL_DATARATE_20_HZ: Serial1.println("20 Hz"); break;

    case LIS3MDL_DATARATE_40_HZ: Serial1.println("40 Hz"); break;

    case LIS3MDL_DATARATE_80_HZ: Serial1.println("80 Hz"); break;

    case LIS3MDL_DATARATE_155_HZ: Serial1.println("155 Hz"); break;

    case LIS3MDL_DATARATE_300_HZ: Serial1.println("300 Hz"); break;

    case LIS3MDL_DATARATE_560_HZ: Serial1.println("560 Hz"); break;

    case LIS3MDL_DATARATE_1000_HZ: Serial1.println("1000 Hz"); break;

  }



  lis3mdl.setRange(LIS3MDL_RANGE_4_GAUSS);

  Serial1.print("Range set to: ");

  switch (lis3mdl.getRange()) {

    case LIS3MDL_RANGE_4_GAUSS: Serial1.println("+-4 gauss"); break;

    case LIS3MDL_RANGE_8_GAUSS: Serial1.println("+-8 gauss"); break;

    case LIS3MDL_RANGE_12_GAUSS: Serial1.println("+-12 gauss"); break;

    case LIS3MDL_RANGE_16_GAUSS: Serial1.println("+-16 gauss"); break;

  }



  lis3mdl.setPerformanceMode(LIS3MDL_MEDIUMMODE);

  Serial1.print("Magnetometer performance mode set to: ");

  switch (lis3mdl.getPerformanceMode()) {

    case LIS3MDL_LOWPOWERMODE: Serial1.println("Low"); break;

    case LIS3MDL_MEDIUMMODE: Serial1.println("Medium"); break;

    case LIS3MDL_HIGHMODE: Serial1.println("High"); break;

    case LIS3MDL_ULTRAHIGHMODE: Serial1.println("Ultra-High"); break;

  }



  lis3mdl.setOperationMode(LIS3MDL_CONTINUOUSMODE);

  Serial1.print("Magnetometer operation mode set to: ");

  // Single shot mode will complete conversion and go into power down

  switch (lis3mdl.getOperationMode()) {

    case LIS3MDL_CONTINUOUSMODE: Serial1.println("Continuous"); break;

    case LIS3MDL_SINGLEMODE: Serial1.println("Single mode"); break;

    case LIS3MDL_POWERDOWNMODE: Serial1.println("Power-down"); break;

  }



  lis3mdl.setIntThreshold(500);

  lis3mdl.configInterrupt(false, false, true, // enable z axis

                          true, // polarity

                          false, // don't latch

                          true); // enabled!
}

#endif //SENSOR_SETUP_H
