#include "SensorData.h"

SensorData::SensorData(double height, 
                double velocity, 
                double acceleration, 
                double pitchAngle,
                double timestamp)
{
    this->height = height;
    this->velocity = velocity;
    this->acceleration = acceleration;
    this->pitchAngle = pitchAngle;
    this->timestamp = timestamp;
}


double SensorData::getHeight() {return height;}

double SensorData::getVelocity() {return velocity;}

double SensorData::getAcceleration() {return acceleration;}

double SensorData::getPitchAngle() {return pitchAngle;}

double SensorData::getTimestamp() {return timestamp;}




