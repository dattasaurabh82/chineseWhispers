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

void setup(){

  pinMode(swOnePin, INPUT_PULLUP);
  pinMode(swTwoPin, INPUT_PULLUP);
  pinMode(swThreePin, INPUT_PULLUP);
  pinMode(swFourPin, INPUT_PULLUP);

  //  pinMode(pOnePin, OUTPUT); 
  //  digitalWrite(pOnePin, HIGH);// LOW
  //  pinMode(pTwoPin, OUTPUT); 
  //  digitalWrite(pTwoPin, HIGH);// LOW
  //  pinMode(pThreePin, OUTPUT); 
  //  digitalWrite(pThreePin, HIGH);// LOW
  pinMode(pFourPin, OUTPUT); 
  digitalWrite(pFourPin, LOW);// HIGH
  //
  //  pinMode(rOnePin, OUTPUT); 
  //  digitalWrite(rOnePin, HIGH);// LOW
  //  pinMode(rTwoPin, OUTPUT); 
  //  digitalWrite(rTwoPin, HIGH);// LOW
  //  pinMode(rThreePin, OUTPUT); 
  //  digitalWrite(rThreePin, HIGH);// LOW
  pinMode(rFourPin, OUTPUT); 
  digitalWrite(rFourPin, LOW);// HIGH
  //
  Serial.begin(9600);
  //  Serial3.begin(9600);
  //
  delay(4000); 
  //
  digitalWrite(rFourPin, HIGH);
  delay(9000);
  digitalWrite(rFourPin, LOW);
  delay(3000);
  digitalWrite(pFourPin, HIGH);
  delay(120);
  digitalWrite(pFourPin, LOW);

  //  digitalWrite(rThreePin, LOW);
  //  delay(9000);
  //  digitalWrite(rThreePin, HIGH);
  //  delay(5000);
  //  digitalWrite(pThreePin, LOW);
  //  delay(120);
}



void loop(){
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
}























