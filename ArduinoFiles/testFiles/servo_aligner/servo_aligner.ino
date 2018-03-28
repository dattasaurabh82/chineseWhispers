#include <Servo.h>
#include "ServoEaser.h"


const int servo1Pin  = 13; // 13, 12, 11, 10
const int servo2Pin  = 12; // 13, 12, 11, 10
const int servo3Pin  = 11; // 13, 12, 11, 10
const int servo4Pin  = 10; // 13, 12, 11, 10

int servoFrameMillis = 20;  // minimum time between servo updates
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

ServoEaser servo1Easer;
ServoEaser servo2Easer;
ServoEaser servo3Easer;
ServoEaser servo4Easer;

int haltDuration = 5000;
int easeDuration = 5000;
int delayBetweenNext = 300;
int repetitions = 1;
int steps = 4;

ServoMove servoMoves[] = {
  // angle, duration
  {
    180, easeDuration                                                          }
  ,
  {
    180, haltDuration                                                          }
  ,
  {
    105, easeDuration                                                          }
  ,
  {
    105, delayBetweenNext                                                          }
  ,
  {
    25, easeDuration
  }
  ,
  {
    25, haltDuration
  }
  ,
  {
    105, easeDuration
  }

};

void setup(){

  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);

  servo1Easer.begin(servo1, servoFrameMillis);
  servo1Easer.useMicroseconds(true);
  servo2Easer.begin(servo2, servoFrameMillis);
  servo2Easer.useMicroseconds(true);
  servo3Easer.begin(servo3, servoFrameMillis);
  servo3Easer.useMicroseconds(true);
  servo4Easer.begin(servo4, servoFrameMillis);
  servo4Easer.useMicroseconds(true);  

  servo1.write(110);
  servo2.write(110);
  servo3.write(110);
  servo4.write(110);

  servo1Easer.play(servoMoves, steps, repetitions);
  //  servo2Easer.play(servoMoves, steps, repetitions);
  //  servo3Easer.play(servoMoves, steps, repetitions);
  //  servo4Easer.play(servoMoves, steps, repetitions);
}

void loop(){
  servo1Easer.update();
  servo2Easer.update();
  servo3Easer.update();
  servo4Easer.update();
}






