#include <SoftwareSerial.h>

SoftwareSerial HC12(7, 8); // HC-12 TX Pin, HC-12 RX Pin

const int startButtonPin = 2;
const int recLEDPin = 3;
const int playLEDPin = 4; 
int buttonState = 1;
int oldButtonState = 1;

int timer = 12;

void setup(){
  Serial.begin(9600);
  HC12.begin(9600);
  
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(recLEDPin, OUTPUT);
  pinMode(playLEDPin, OUTPUT);
}

int counter = 0;
boolean runTimer = false;

void loop(){
  buttonState = digitalRead(startButtonPin);
  //  Serial.println(digitalRead(startButtonPin));
  if(buttonState != oldButtonState){
    if(buttonState == 0){
      //      Serial.println("pressed");
      runTimer = true;
      HC12.print(1);
    }
    oldButtonState = buttonState;
  }

  if(runTimer){
    recSession();
  }

}

void recSession(){
  if(timer!=0){
    timer--;
    Serial.println(timer);
    digitalWrite(recLEDPin, HIGH);
    digitalWrite(playLEDPin, LOW);
    delay(500);
    digitalWrite(recLEDPin, LOW);
    digitalWrite(playLEDPin, LOW);
    delay(500);
  } 
  else{
    runTimer = false;
    timer = 12;
    digitalWrite(recLEDPin, LOW);
    digitalWrite(playLEDPin, HIGH);
    HC12.print(2);
    Serial.println(1);
  }
}









