#ifndef MAINSM_H
#define MAINSM_H
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "Logger.h"
#include "Parameters.h"
#include "SensorData.h"


extern SensorData* sensorDataList[16];

//isr tick function
void main_Tick();

//main initialization function
void main_Init();

void updateEnable();
//void logEnable();
//void hardwarecontrols_enable();
bool update_getIgnition();
bool update_getCutoff();


#endif
