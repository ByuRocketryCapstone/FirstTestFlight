#ifndef MOTOR_FCNS_H
#define MOTOR_FCNS_H

//function to step motor when it's supposed to
uint16_t StepMotor(bool motor_direction) {

  if (motor_direction) {
    sd.step();
    //Serial.print('1'); //move it up
    sinceStep = 0;
    return 1;//return 1 for up
  }

//1 encoder pulse is 360/400 of a revolution about .9 degrees

  else if (!motor_direction) {
    sd.step();
    //Serial.print('2');
    sinceStep = 0;
    return 2;//return 2 for down
  }

  else {
    return 0;//return 0 for no move
  }
}


void motor_tick()
{
  
}



#endif
