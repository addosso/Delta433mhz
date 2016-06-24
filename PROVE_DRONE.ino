
#include <Servo.h>
#include <IRremote.h>
#define RELAY 10

Servo myServo;
int pos=0;
int posit = 0;
int RECV_PIN = 13;

IRrecv irrecv(RECV_PIN);


 
decode_results results;

void dump(decode_results *results) {
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
  }
    else if (results->decode_type == NEC) {
    Serial.print("Decoded NEC: ");
  }
  else if (results->decode_type == SONY) {
    Serial.print("Decoded SONY: ");
  }
  else if (results->decode_type == RC5) {
    Serial.print("Decoded RC5: ");
  }
  else if (results->decode_type == RC6) {
    Serial.print("Decoded RC6: ");
  }
  else if (results->decode_type == SAMSUNG) {
    Serial.print("Decoded SAMSUNG: ");
  }
  else if (results->decode_type == JVC) {
    Serial.print("Decoded JVC: ");
  }
  else if (results->decode_type == PANASONIC) {
    Serial.print("Decoded Panasonic: ");
  }
  Serial.print(results->value, HEX);
  Serial.print("(");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
  Serial.print("#define Something_DEC ");
  Serial.println(results->value, DEC);
  Serial.print("#define Something_HEX ");
  Serial.println(results->value, HEX);
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");
  for (int i = 0; i < count; i++) {
    if ((i % 2) == 1) {
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    } 
    else {
      Serial.print(-(int)results->rawbuf[i]*USECPERTICK, DEC);
    }
    Serial.print(" QW");
  }
  Serial.println("QW");
}
void setup(){
 pinMode(RELAY, OUTPUT);
 myServo.attach(9);
 Serial.begin(9600);
  irrecv.enableIRIn();
 
}

void loop(){
  if (irrecv.decode(&results)) {
    dump(&results);
    irrecv.resume(); // Receive the next value
  }
  
  
  digitalWrite(RELAY,HIGH);           // Turns ON Relays 1
delay(2000);
digitalWrite(RELAY, LOW);
delay(2000);
if(posit == 0){
 for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
                         // waits 15ms for the servo to reach the position
  }
  posit = 1;
}else{
  for (pos = 180; pos >= 0; pos -=1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
                         // waits 15ms for the servo to reach the position
  }
  posit = 0;
}
  delay(2000);

}
