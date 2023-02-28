#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

/*
Container class to hold useful sensor data.

This is not meant for raw sensor data. This class is meant to hold the post-processed
data that the flight algorithm needs to make its predictions.

Each instance of the class is information about the rocket at one point in time.
*/

#include "Logger.h"
#include "Parameters.h"

//extern Logger logger;

class SensorData
{
    public:
    SensorData(double height, 
                double velocity, 
                double acceleration, 
                double pitchAngle,
                double timestamp);

    double getHeight();
    double getVelocity();
    double getAcceleration();
    double getPitchAngle();
    double getTimestamp();

    private:
    double height;          // m
    double velocity;        // m/s
    double acceleration;    // m/s^2
    double pitchAngle;      // degrees
    double timestamp;       // s

};

#endif //SENSOR_DATA_H
