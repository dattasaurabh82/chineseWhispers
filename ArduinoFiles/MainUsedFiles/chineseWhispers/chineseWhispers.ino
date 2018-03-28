#include <Servo.h>
#include "ServoEaser.h"

const int servo1Pin  = 13;
const int servo2Pin  = 12;
const int servo3Pin  = 11;
const int servo4Pin  = 10;

int servoFrameMillis = 20;  // minimum time between servo updates

Servo servo1; 
Servo servo2; 
Servo servo3; 
Servo servo4; 

ServoEaser servo1Easer;
ServoEaser servo2Easer;
ServoEaser servo3Easer;
ServoEaser servo4Easer;

int servoMovesCount = 2;
int haltDuration = 7000;
int easeDuration = 4000;
int delayBetweenNext = 500;
int repetitions = 1;
int steps = 4;

ServoMove forwardMoves[] = {
  // angle, duration
  {
    180, easeDuration                                                                                                                                        }
  ,
  {
    180, haltDuration                                                                                                                                        }
  ,
  {
    105, easeDuration                                                                                                                                        }
  ,
  {
    105, delayBetweenNext                                                                                                                                        }
  ,
};

ServoMove backwardMoves[] = {
  // angle, duration
  {
    25, easeDuration                                                                                                                                        }
  ,
  {
    25, haltDuration                                                                                                                                        }
  ,
  {
    105, easeDuration                                                                                                                                        }
  ,
  {
    105, delayBetweenNext                                                                                                                                        }
  ,
};


const int swOnePin = 6;
const int swTwoPin = 5;
const int swThreePin = 4;
const int swFourPin = 3;

const int pOnePin = 28; // LOW
const int pTwoPin = 30; // LOW 
const int pThreePin = 32; // LOW
const int pFourPin = 34; // HIGH

const int rOnePin = 29; // LOW
const int rTwoPin = 31; // LOW
const int rThreePin = 33; // LOW
const int rFourPin = 35; //  HIGH

void setup(){

  pinMode(swOnePin, INPUT_PULLUP);
  pinMode(swTwoPin, INPUT_PULLUP);
  pinMode(swThreePin, INPUT_PULLUP);
  pinMode(swFourPin, INPUT_PULLUP);

  pinMode(pOnePin, OUTPUT); 
  digitalWrite(pOnePin, HIGH);// LOW
  pinMode(pTwoPin, OUTPUT); 
  digitalWrite(pTwoPin, HIGH);// LOW
  pinMode(pThreePin, OUTPUT); 
  digitalWrite(pThreePin, HIGH);// LOW
  pinMode(pFourPin, OUTPUT); 
  digitalWrite(pFourPin, LOW);// HIGH

  pinMode(rOnePin, OUTPUT); 
  digitalWrite(rOnePin, HIGH);// LOW
  pinMode(rTwoPin, OUTPUT); 
  digitalWrite(rTwoPin, HIGH);// LOW
  pinMode(rThreePin, OUTPUT); 
  digitalWrite(rThreePin, HIGH);// LOW
  pinMode(rFourPin, OUTPUT); 
  digitalWrite(rFourPin, LOW);// HIGH

  Serial.begin(9600);
  Serial3.begin(9600); 

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

  // First ease to default position
  servo1.write(110);
  servo2.write(110);
  servo3.write(110);
  servo4.write(110);
}

int step1FCount = 0;
int step2FCount = 0;
int step3FCount = 0;
int step4FCount = 0;

int step1BCount = 0;
int step2BCount = 0;
int step3BCount = 0;
int step4BCount = 0;

void moveSecondHeadForward(int currPos, int mIndex){
  //  stepCountHeadOne = mIndex+1;
  step2FCount = mIndex+1;
  // Serial.println(stepCountHeadOne);
  // if last step is reached
  if(step2FCount == steps){
    servo2Easer.play(forwardMoves, steps, repetitions);
    servo2Easer.setArrivedFunc(moveThirdHeadForward);
    step2FCount = 0;
  }
}

void moveThirdHeadForward(int currPos, int mIndex){
  //  stepCountHeadTwo = mIndex+1;
  step3FCount = mIndex+1;
  // Serial.println(stepCountHeadTwo);
  // if last step is reached
  if(step3FCount == steps){
    servo3Easer.play(forwardMoves, steps, repetitions);
    servo3Easer.setArrivedFunc(moveFourthHeadBackward);
    step3FCount = 0;
  }
}

void moveFourthHeadBackward(int currPos, int mIndex){
  //  stepCountHeadThree = mIndex+1;
  step4FCount = mIndex+1;
  // Serial.println(stepCountHeadThree);
  // if last step is reached
  if(step4FCount == steps){
    servo4Easer.play(backwardMoves, steps, repetitions);
    servo4Easer.setArrivedFunc(moveThirdHeadBackward);
    step4FCount = 0;
  }
}

void moveThirdHeadBackward(int currPos, int mIndex){
  //  stepCountHeadThree = 0;
  //  stepCountHeadFour = mIndex+1;
  step3BCount = mIndex+1;
  // Serial.println(stepCountHeadTwo);
  // if last step is reached
  if(step3BCount == steps){
    servo3Easer.play(backwardMoves, steps, repetitions);
    servo3Easer.setArrivedFunc(moveSecondHeadBackward);
    step3BCount = 0;
  }
}

void moveSecondHeadBackward(int currPos, int mIndex){
  //  stepCountHeadFour = 0;
  //  stepCountHeadOne = mIndex+1;
  step2BCount = mIndex+1;
  // Serial.println(stepCountHeadOne);
  // if last step is reached
  if(step2BCount == steps){
    servo2Easer.play(backwardMoves, steps, repetitions);
    servo2Easer.setArrivedFunc(moveFirstHeadForward);
    step2BCount = 0;
  }
}

void moveFirstHeadForward(int currPos, int mIndex){
  step1FCount = mIndex+1;
  if(step1FCount == steps){
    servo1Easer.play(forwardMoves, steps, repetitions);
    servo1Easer.setArrivedFunc(moveSecondHeadForward);
    step1FCount = 0;
  }
}

int swOneState = 1;
int swTwoState = 1;
int swThreeState = 1;
int swFourState = 1;

int oldSwOneState = 1;
int oldSwTwoState = 1;
int oldSwThreeState = 1;
int oldSwFourState = 1;

boolean recOne = false;
boolean recTwo = false;
boolean recThree = false;
boolean recFour = false;

int evenCountForHeadOne = 0;
int evenCountForHeadTwo = 0;
int evenCountForHeadThree = 0;
int evenCountForHeadFour = 0;

void loop(){
  servo1Easer.update();
  servo2Easer.update();
  servo3Easer.update();
  servo4Easer.update();

  swOneState = digitalRead(swOnePin);
  swTwoState = digitalRead(swTwoPin);
  swThreeState = digitalRead(swThreePin);
  swFourState = digitalRead(swFourPin);

  //  Serial.println("switch staetes");
  //  Serial.println(swOneState);
  //  Serial.println(swTwoState); 
  //  Serial.println(swThreeState); 
  //  Serial.println(swFourState);
  //  Serial.println("-----------");
  //  Serial.println();

  // if headOne turns at 180
  // and presses the button
  if(swOneState != oldSwOneState){
    if(swOneState == 0){
      // record head two
      digitalWrite(rTwoPin, LOW);
      // turn on the play relay of Head One for an instance only once 
      digitalWrite(pOnePin, LOW);
      delay(120);
      digitalWrite(pOnePin, HIGH); 
    }
    else{
      // stop the recording of second head here
      digitalWrite(rTwoPin, HIGH);
    }
    oldSwOneState = swOneState;
  }

  // if headTwo turns at 180
  // and presses the button
  if(swTwoState != oldSwTwoState){
    if(swTwoState == 0){

      evenCountForHeadTwo = evenCountForHeadTwo+1;
      Serial.println(evenCountForHeadTwo);

      if(evenCountForHeadTwo%2==0){
        //  Serial.println("Back routine 2");
        //-------->> BACKWARD ROUTINE
        // record head one and not head three
        digitalWrite(rOnePin, LOW);
        digitalWrite(rThreePin, HIGH);
        // play head two
        digitalWrite(pTwoPin, LOW);
        delay(120);
        digitalWrite(pTwoPin, HIGH);

        evenCountForHeadTwo = 0;
      }
      else{
        //-------->> FORWARD ROUTINE
        // Serial.println("Forward routine 2");
        // record head three and not head one
        digitalWrite(rThreePin, LOW);
        digitalWrite(rOnePin, HIGH);
        // play head two 
        digitalWrite(pTwoPin, LOW);
        delay(120);
        digitalWrite(pTwoPin, HIGH);
      }
    }
    else{
      // stop the recording
      digitalWrite(rThreePin, HIGH);
      digitalWrite(rOnePin, HIGH);
    }
    oldSwTwoState = swTwoState;
  }

  // if headThree turns at 180
  // and presses the button
  if(swThreeState != oldSwThreeState){
    if(swThreeState == 0){

      evenCountForHeadThree = evenCountForHeadThree+1;
      Serial.println(evenCountForHeadThree);

      if(evenCountForHeadThree%2==0){
        //  Serial.println("Back routine 3");
        //-------->> BACKWARD ROUTINE
        // record head Two and not head Four
        digitalWrite(rTwoPin, LOW);
        digitalWrite(rFourPin, LOW);
        // play head Three 
        digitalWrite(pThreePin, LOW);
        delay(120);
        digitalWrite(pThreePin, HIGH);
      }
      else{
        //  Serial.println("Forward routine 3");
        //-------->> FORWRAD ROUTINE
        // record head Four and not head Two
        digitalWrite(rFourPin, HIGH);
        digitalWrite(rTwoPin, HIGH);
        // play head Three 
        digitalWrite(pThreePin, LOW);
        delay(120);
        digitalWrite(pThreePin, HIGH); 
      }
    }
    else{
      // stop the recording
      digitalWrite(rFourPin, LOW);
      digitalWrite(rTwoPin, HIGH);
    }
    oldSwThreeState = swThreeState;
  }

  // if headFour turns at 180
  // and presses the button
  if(swFourState != oldSwFourState){
    if(swFourState == 0){
      //  Send the signal to raspberry pi to start transcriber
      Serial.println(6);
      delay(80); 
      // record head three
      digitalWrite(rThreePin, LOW);
      // turn on the play relay of Head Two for an instance only once 
      digitalWrite(pFourPin, HIGH);
      delay(120);
      digitalWrite(pFourPin, LOW); 
    }
    else{
      // stop the recording
      digitalWrite(rThreePin, HIGH);
    }
    oldSwFourState = swFourState;
  }
}

int eventData = 0;

void serialEvent3(){
  eventData = Serial3.read()-'0';
  //  Serial.println("serial data:");
  //  Serial.println(eventData);
  //  Serial.println("---------");

  if(eventData==1){
    // turn on the record relay of first doll to start recording
    digitalWrite(rOnePin, LOW);
  }
  else if(eventData==2){
    // turn off the record relay of the first doll
    digitalWrite(rOnePin, HIGH);
    // turn the first head to speak
    servo1Easer.play(forwardMoves, steps, repetitions);
    servo1Easer.setArrivedFunc(moveSecondHeadForward);
  }
  else{
    Serial.println("garbage signal from switch");
  }
}








































































