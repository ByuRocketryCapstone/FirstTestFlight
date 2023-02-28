#ifndef SENSOR_FCNS_H
#define SENSOR_FCNS_H

SensorData* pullData()
{
  sensors_event_t accel, gyro, temp, pressure_event;
  int avgNum = 5;
  
  double P = 0;
  if (dps.temperatureAvailable()) {
    
    for (int i = 0; i < avgNum; i++) {
      dps_pressure->getEvent(&pressure_event);
      P += pressure_event.pressure;
    }
  }
  P /= avgNum;
  P *= 100;   //convert from hPa to Pa
  
  double a = 0;
  for (int i = 0; i < avgNum; i++)
  {
    lsm6ds.getEvent(&accel, &gyro, &temp);
    a += accel.acceleration.x;    //FIXME: decide actual axis to use (x, y, or z)
  }
  a /= avgNum;

  
  double t = millis() / 1000;

  double h = (1 - pow((P/101325), 0.190263)) / (2.25577*pow(10,-5));  //convert altimeter pressure to height in m using curve fit from https://www.engineeringtoolbox.com/air-altitude-pressure-d_462.html        
  double dt = t - sensorDataList[15]->getTimestamp();
  double tempV1 = sensorDataList[15]->getVelocity() + ((sensorDataList[15]->getAcceleration() + a)/2) * dt;
  double tempV2 = (h - sensorDataList[15]->getHeight()) / dt;
  double V = (tempV1+tempV2) / 2;

  double theta = 0;       //FIXME: decide axis for gyroscope to get pitch angle

  SensorData* new_sd = new SensorData(h, V, a, theta, t);
  return new_sd;
}

void updateSensorData()
{
  SensorData* new_sd = pullData();
  for (int i = 0; i < 15; i++)
  {
    delete sensorDataList[i];
    sensorDataList[i] = sensorDataList[i+1];
  }
  sensorDataList[15] = new_sd;
}

void sensor_tick()
{
  updateSensorData();
}





#endif
