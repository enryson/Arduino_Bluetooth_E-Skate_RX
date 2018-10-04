//Skate
#include <PWMServo.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
//Setup Ports
SoftwareSerial mySerial(6, 5); 
PWMServo myservo;  

///Resistors
float vPow = 5;
float r1 = 47000;
float r2 = 10000;

////////////
String inString = "";
int voltcheck = 0;
int conectioncheck = 0;
int x;

///LEDS
#define ledFront 03
#define ledBreak 10

void setup() {
  //Leds Lights
  pinMode(ledFront, OUTPUT);
  pinMode(ledBreak, OUTPUT);
  /////////////
  Serial.begin(9600);
  mySerial.begin(9600);
  myservo.attach(9);
  myservo.write(30);
  ///////////// 
  digitalWrite(ledFront, HIGH);
  digitalWrite(ledBreak, LOW);
}

void loop() {
  //ReadBlutooth data
  while (mySerial.available() > 0) {
    int inChar = mySerial.read();
    conectioncheck = 0;
    if (isDigit(inChar)) {
      inString += (char)inChar;      
    }
    //Recilver pulse to the motor    
    if (inChar == 'n') {
      x = inString.toInt();
      digitalWrite(ledBreak, LOW); //LedON
      //Make motor run
      if (x <= 180){    
        //Serial.println(x);
        myservo.write(x);
        if(x > 90){
          digitalWrite(ledBreak, HIGH); //LedOff
          }
        }
      inString = "";
    }
    //Send Voltage to the APP
    if (inChar == 'm') {
      if (voltcheck == 10){
        getv();
        voltcheck = 0;
      }
      else { voltcheck++; }
    }
    //Control Front Led
    if (inChar == 'L') {
      digitalWrite(ledFront, HIGH);
    }
    if (inChar == 'O') {
      digitalWrite(ledFront, LOW);
    }
  }
  while (mySerial.available()== NULL){
    if (conectioncheck == 15000){      
      //Serial.println("desconectado");
      
      myservo.write(70);
      conectioncheck = 0;
    }
    else {conectioncheck++; }
  }
}
//Get Voltage
static void getv() {
  float v = (analogRead(5) * 5.0) / 1024.0;
  float v2 = v / (r2 / (r1 + r2));  
  mySerial.print(0);
  mySerial.print(v2);
  mySerial.println("v");
}


