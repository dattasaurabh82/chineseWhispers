#include "SevenSeg.h"

SevenSeg disp (10,9,8,7,6,11,12); //Defines the segments A-G: SevenSeg(A, B, C, D, E, F, G);
const int numOfDigits = 1;	      //number of 7 segments
int digitPins [numOfDigits]={
  4};  //CC(or CA) pins of segment

const int buzzer = 2; //buzzer - arduino pin 2

//Variables
int timer=9; //Count donw from e.g. 99
int flag;

void setup() {

  Serial.begin(9600);
  //Defines the number of digits to be "numOfDigits" and the digit pins to be the elements of the array "digitPins"
  disp.setDigitPins ( numOfDigits , digitPins );
  //Only for common cathode 7segments
  disp.setCommonCathode();
  //Control brightness (values 0-100);
  disp.setDutyCycle(50);

}

void loop(){
  //Counting down...
  if (timer!=0){
    timer--;
    disp.write(timer);
    delay(1000); // 1 sec. delay
  }
  else{
    disp.write("0");
    delay(4000);
    disp.write("");
    delay(1000);
  }

}



