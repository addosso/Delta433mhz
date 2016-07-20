#include <VirtualWire.h>

#define MOTORE 7
#define RED 8
#define BLUE 10
#define GREEN 9

#define X_PIN 0
#define Y_PIN 1
#define SW_PIN 2

#define TX_pin 13

const char *motor_ON = "MOTOR_ON";
const char *motor_OFF = "MOTOR_OFF";
const char *sx = "SX";
const char *dx = "DX";
const char *cabrata = "CAB";
const char *picchiata = "PIC";
const char *stay = "STAY";


int motore_acceso = 0;
int lastState = 0;
void setup() {
  Serial.begin(9600);
  vw_set_tx_pin(TX_pin); // Imposto il pin per la trasmissione
  vw_setup(3000);        // Bits per sec
  pinMode(SW_PIN, INPUT);
  pinMode(MOTORE, INPUT);
digitalWrite(SW_PIN, HIGH);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
 
   analogWrite(RED, HIGH);
    analogWrite(BLUE, 0);
    analogWrite(GREEN, 0);
}


void loop(){
  
  if(analogRead(Y_PIN) == 0 ){
  vw_send((uint8_t *) picchiata, strlen(picchiata));
    vw_wait_tx();
     Serial.println(analogRead(X_PIN));
  
}

  if(analogRead(Y_PIN) == 1023 ){
  vw_send((uint8_t *) cabrata, strlen(cabrata));
    vw_wait_tx();
     Serial.println(analogRead(X_PIN));
  
}
 if(analogRead(X_PIN) == 0 ){
  vw_send((uint8_t *) dx, strlen(dx));
    vw_wait_tx();
}

 if(analogRead(X_PIN) == 1023 ){
  vw_send((uint8_t *) sx, strlen(sx));
    vw_wait_tx();
}

  motore_acceso = digitalRead(MOTORE);
 set_motor_led();

}

void set_motor_led(){
  if(motore_acceso == HIGH ){
    analogWrite(RED, LOW);
    analogWrite(BLUE, LOW);
    analogWrite(GREEN, 255);
    lastState = !lastState;
    if(!lastState){
    vw_send((uint8_t *) motor_OFF, strlen(motor_OFF));
    vw_wait_tx();
    Serial.println("MOTORE_SPENTO");
    }else{
    vw_send((uint8_t *) motor_ON, strlen(motor_ON));
    vw_wait_tx();
    Serial.println("MOTORE_ACCESO");  
      }
    delay(100);  
  }else if(motore_acceso == LOW && lastState == 0){
     analogWrite(RED, 255);
    analogWrite(BLUE, LOW);
    analogWrite(GREEN, LOW);
    
  }
  
}
