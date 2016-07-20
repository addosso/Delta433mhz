#include <VirtualWire.h>
#include <ServoTimer2.h>


#define SERVO_MOTOR_SX 11
#define SERVO_MOTOR_DX 10
#define RX_pin 13
#define RELAY 12

ServoTimer2 servoSx;
ServoTimer2 servoDx;

void setup()
{
  
   
    vw_set_rx_pin(RX_pin); //Non servirebbe: il default è 11
    vw_setup(1000);        // Bits per sec
    vw_rx_start();         // Inizio il processo di ricezione
    servoSx.attach(SERVO_MOTOR_SX);
    servoDx.attach(SERVO_MOTOR_DX);
    servoDx.write(1400);
    servoSx.write(1400); 
     delay(1000); 
    Serial.begin(9600);    // Solo per debug
    Serial.println("Ricevitore attivo: ");
}



void loop()
{
 
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
      Serial.println("azz");
      
	buf[buflen]='\0'; // Metto il terminatore di stringa
        if (strncmp((char *)buf,"MOTOR_ON",buflen)==0){
               digitalWrite(RELAY,HIGH);
        }
        if (strncmp((char *)buf,"MOTOR_OFF",buflen)==0){
             digitalWrite(RELAY,LOW);    
        }
        if(strncmp((char *)buf, "CAB", buflen)==0){
           servoSx.write(2000);
            servoDx.write(2000);
            Serial.println("cabrata attivo: ");
        }          
        if(strncmp((char *)buf, "PIC", buflen)==0){
            servoSx.write(900);
           servoDx.write(900);
           Serial.println("picchiata ");
        }
        if(strncmp((char *)buf, "DX", buflen)==0){
          servoSx.write(2000);
          Serial.println("dx: ");
        } 
        if(strncmp((char *)buf, "SX", buflen)==0){
          servoDx.write(2000);
          Serial.println("sx ");
        }
        if(strncmp((char *)buf, "STAY", buflen)==0){
           servoDx.write(1400);
           servoSx.write(1400);
           Serial.println("stay: ");
        }
      }  
}
