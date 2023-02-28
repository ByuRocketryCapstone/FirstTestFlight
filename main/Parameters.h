#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "SensorData.h"

enum LogLevels{TESTING, FLIGHT};

class Consts
{
    public:
    static constexpr double ROCKET_DRY_MASS = 50.0;     //FIXME: change to actual value
    static constexpr double ROCKET_CD = 0.2;            //FIXME: change to actual value
    static constexpr double TARGET_HEIGHT = 3048;       //meters (10,000 feet)
    static constexpr double AIR_VISCOSITY = 1.0;        //FIXME: change to actual value
};



#endif //PARAMETERS_H
