
#include <Servo.h>

#define RELAY 12


// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output
 
 Servo myServo;
 int pos = 0;
 int maxPos = 180;
 int xAxis = 504;
 int yAxis = 520;
 int posit = 0;
 // Motor State 1 = acceso , 0 = spento
 int motorState = 0;
boolean moved =false; 
void setup() {
  pinMode(RELAY, OUTPUT);
  myServo.attach(13);
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(115200);
}
 
void loop() {
if(analogRead(Y_pin) == 1023 && moved){

  for (pos = 90; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
   
   
    moved = true; // in steps of 1 degree
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
                          // waits 15ms for the servo to reach the position
  }
  moved= false;
}
if(analogRead(Y_pin) == 0 && moved){
  Serial.print("AVANTI");
    for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    moved= true;
    myServo.write(pos);              // tell servo to go to position in variable 'pos' 
                          // waits 15ms for the servo to reach the position
  }
  moved= false;
  
}

if(analogRead(Y_pin) == 520){
  moved= true;
  myServo.write(90);
}
Serial.println(digitalRead(SW_pin));

if(digitalRead(SW_pin) == 0 && motorState == 1){

  motorState = 0;
  digitalWrite( RELAY, LOW);
  Serial.println("Accesosss");
  delay(1000);
}


if(digitalRead(SW_pin) == 0 && motorState== 0){
  motorState = 1;
  digitalWrite(RELAY, HIGH);
  Serial.println("Acceso");

  
}


 delay(500);
}
