#ifndef MAIN_CPP
#define MAIN_CPP
#include "mainSM.h"
#include <string.h>
//#include <sstream>
using namespace std;

#define LOG_PTR_ARRAY_MAX_SIZE 20

bool main_armed;
bool main_ignition;
bool main_cutoff;
bool main_apogee;
bool main_retracted;
bool main_ground;
bool main_done;
bool main_abortControls;
bool main_reset;
//Logger mainLogger;
int runNumber;
char* fileName;
//Logger* logPtrArray[LOG_PTR_ARRAY_MAX_SIZE];
int numLogs;
extern double cutoffTime;
extern bool motorRun;
extern bool motorRetract;

//dynamically allocate logs
bool main_MakeLog(int runNumber) {
    if (runNumber > LOG_PTR_ARRAY_MAX_SIZE) {
        return false;
    }
    else {
//        fileName = "LogFiles/Run_" + to_string(runNumber) + "_log.txt";
//        Logger* loggerPtr = new Logger(fileName);
//        logPtrArray[runNumber - 1] = loggerPtr;
//        ++numLogs;
//        return true;
    }
}

//free heap dynamic logs memory
void main_DeleteLogs() {
//    while (numLogs > 0) {
//        delete logPtrArray[numLogs - 1];
//        --numLogs;
//    }
}





static enum mainControlState {
    init_st, //initialize all global data and functions
    wait_arm_st, //wait on pad for arming
    arm_st, //armed and ready, waiting to detect ignition, maybe take in mission-specific initial conditions
    wait_cutoff_st, //wait for engine cuttoff, all while logging data, jump to update_st
    wait_apogee_st, //detects apogee reached
    retract_st, //retract paddles for safety during descent
    descent_st, //tracK data during descent
    done_st, //all doneeee, close data files, wait for recovery
    abort_st //emergency or manual abort
} CurrState, NextState; // current and next states



void main_Init() {
    main_armed = false;
    main_ignition = false;
    main_cutoff = false;
    main_apogee = false;
    main_retracted = false;
    main_ground = false;
    main_done = false;
    main_abortControls = false;
    main_reset = false;
    numLogs = 0;
    runNumber = 1;
    main_MakeLog(runNumber);
};


void main_Tick() {
    
    //state update, Mealy actions
    switch (CurrState) {
    case init_st:
        //initialize variables and functions, proceed to wait_arm_st
        NextState = wait_arm_st;
        break;

    case wait_arm_st:
        //wait for manual arm, then go to arm_st and enable sensors and data logging
        if (!main_armed) {
            NextState = wait_arm_st;
        }
        else {
            NextState = arm_st;
//            updateData_enable();
//            logPtrArray[runNumber - 1]->log_enable();
        }
        break;

    case arm_st:
        //wait for ignition detect, then go to wait_cutoff_st
        if (!main_ignition) {
            NextState = arm_st;
        }
        else {
            NextState = wait_cutoff_st;
        }
        break;

    case wait_cutoff_st:
        //stay physically dormant for powered portion of flight, then enable hardware control 
        if (!main_cutoff) {
            NextState = wait_cutoff_st;
        }
        else {
            NextState = wait_apogee_st;
//            hardwareControl_enable();
        }
        break;

    case wait_apogee_st:
        //main state for active controls, wait for apogee
        if (!main_apogee) {
            NextState = wait_apogee_st;
        }
        else {
            NextState = retract_st;
        }
        break;

    case retract_st:
        //wait for paddles to be retracted, then disable hardwareControl sm
        if (!main_retracted) {
            NextState = retract_st;
        }
        else {
            NextState = descent_st;
//            hardwareControl_disable();
        }
        break;

    case descent_st:
        //wait to detect touchdown, then start to shut down systems
        if (!main_ground) {
            NextState = descent_st;
        }
        else {
            NextState = done_st;
//            updateData_disable();
//            logPtrArray[runNumber - 1]->log_disable();
        }
        break;

    case done_st:
        //wait for manual reset, then go back to wait_arm_st and reset tracking variables
        if (!main_reset) {
            NextState = done_st;
        }
        //else if (turnoff) {
            ///dont make new logger
        //}
        else {
            NextState = wait_arm_st;
//            ++runNumber;
            main_armed = false;
            main_ignition = false;
            main_cutoff = false;
            main_apogee = false;
            main_retracted = false;
            main_ground = false;
            main_done = false;
            main_abortControls = false;
            main_reset = false;
//            main_MakeLog(runNumber);
        }
        break;

    case abort_st:
        NextState = done_st;
        break;

    default:
        break;

    }

    

    //state action, Moore actions
    switch (CurrState) {
    case init_st:
        break;

    case wait_arm_st:
        //armed = get button push();
        break;

    case arm_st:
//        if (update_getIgnition() == true) {
        if (sensorDataList[15]->getAcceleration() > 1){
            main_ignition = true;
        }
        break;

    case wait_cutoff_st:
//        if (update_getCutoff() == true) {
        if (sensorDataList[15]->getAcceleration() < 0){
            main_cutoff = true;
            cutoffTime = millis();
            motorRun = true;
        }
        break;

    //main control functionality
    case wait_apogee_st:
        if (sensorDataList[15]->getVelocity() < 1){
          main_apogee = true;
          motorRun = false;
          motorRetract = true;
        }
        
        break;

    case retract_st:
        break;

    case descent_st:
        break;

    case done_st:
        break;

    case abort_st:
        //make sure to have function that logs the error
//        updateData_disable();
//        logPtrArray[runNumber - 1]->log_disable();
        break;

    default:
        break;

    }

    //update state
    CurrState = NextState;

}



#endif
