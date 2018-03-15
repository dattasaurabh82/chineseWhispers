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
int haltDuration = 5000;
int easeDuration = 1600;
int delayBetweenNext = 30;
int repetitions = 1;
int steps = 4;

ServoMove servoMoves[] = {
  // angle, duration
  {
    180, easeDuration                                        }
  ,
  {
    180, haltDuration                                        }
  ,
  {
    110, easeDuration                                        }
  ,
  {
    110, delayBetweenNext                                        }
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

int stepCountHeadOne = 0;
int stepCountHeadTwo = 0;
int stepCountHeadThree = 0;
int stepCountHeadFour = 0;

void moveSecondHead(int currPos, int mIndex){
  stepCountHeadOne = mIndex+1;
  // Serial.println(stepCountHeadOne);
  // if last step is reached
  if(stepCountHeadOne == steps){
    servo2Easer.play(servoMoves, steps, repetitions);
    servo2Easer.setArrivedFunc(moveThirdHead);
  }
}

void moveThirdHead(int currPos, int mIndex){
  stepCountHeadTwo = mIndex+1;
  // Serial.println(stepCountHeadTwo);
  // if last step is reached
  if(stepCountHeadTwo == steps){
    servo3Easer.play(servoMoves, steps, repetitions);
    servo3Easer.setArrivedFunc(moveFourthHead);
  }
}

void moveFourthHead(int currPos, int mIndex){
  stepCountHeadThree = mIndex+1;
  // Serial.println(stepCountHeadThree);
  // if last step is reached
  if(stepCountHeadThree == steps){
    servo4Easer.play(servoMoves, steps, repetitions);
    servo4Easer.setArrivedFunc(lastStep);
  }
}

void lastStep(int currPos, int mIndex){
  stepCountHeadFour = mIndex+1;
  // Serial.println(stepCountHeadFour);
  // if last step is reached
  if(stepCountHeadFour == steps){
    // do something later
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

void loop(){
  servo1Easer.update();
  servo2Easer.update();
  servo3Easer.update();
  servo4Easer.update();

  swOneState = digitalRead(swOnePin);
  swTwoState = digitalRead(swTwoPin);
  swThreeState = digitalRead(swThreePin);
  swFourState = digitalRead(swFourPin);

  Serial.println("switch staetes");
  Serial.println(swOneState);
  Serial.println(swTwoState); 
  Serial.println(swThreeState); 
  Serial.println(swFourState);
  Serial.println("-----------");
  Serial.println();

  // if headOne turns at 180
  // and presses the button
  if(swOneState != oldSwOneState){
    if(swOneState == 0){
      // record from head two
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
      // record from head three
      digitalWrite(rThreePin, LOW);
      // turn on the play relay of Head Two for an instance only once 
      digitalWrite(pTwoPin, LOW);
      delay(120);
      digitalWrite(pTwoPin, HIGH); 
    }
    else{
      // stop the recording of Third head here
      digitalWrite(rThreePin, HIGH);
    }
    oldSwTwoState = swTwoState;
  }

  // if headThree turns at 180
  // and presses the button
  if(swThreeState != oldSwThreeState){
    if(swThreeState == 0){
      // record from head three
      digitalWrite(rFourPin, HIGH);
      // turn on the play relay of Head Two for an instance only once 
      digitalWrite(pThreePin, LOW);
      delay(120);
      digitalWrite(pThreePin, HIGH); 
    }
    else{
      // stop the recording from Fourth head here
      digitalWrite(rFourPin, LOW);
    }
    oldSwThreeState = swThreeState;
  }
  
  // if headFour turns at 180
  // and presses the button
  if(swFourState != oldSwFourState){
    if(swFourState == 0){
      // record from head five
      //digitalWrite(rFivePin, HIGH);
      // turn on the play relay of Head Two for an instance only once 
      digitalWrite(pFourPin, HIGH);
      delay(120);
      digitalWrite(pFourPin, LOW); 
    }
    else{
      // stop the recording from fifth head here
      // digitalWrite(rFivePin, LOW);
    }
    oldSwFourState = swFourState;
  }
}

int eventData = 0;

void serialEvent3(){
  eventData = Serial3.read()-'0';
  Serial.println("serial data:");
  Serial.println(eventData);
  Serial.println("---------");

  if(eventData==1){
    // turn on the record relay of first doll to start recording
    digitalWrite(rOnePin, LOW);
  }
  else if(eventData==2){
    // turn off the record relay of the first doll
    digitalWrite(rOnePin, HIGH);
    // turn the first ead to speak
    servo1Easer.play(servoMoves, steps, repetitions);
    servo1Easer.setArrivedFunc(moveSecondHead);
  }
  else{
    Serial.println("garbage signal from switch");
  }
}













































