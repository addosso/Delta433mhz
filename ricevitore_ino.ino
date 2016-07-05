#include <VirtualWire.h>


#define RX_pin 13
#define RELAY 12
void setup()
{
  
   
    vw_set_rx_pin(RX_pin); //Non servirebbe: il default è 11
    vw_setup(3000);        // Bits per sec
    vw_rx_start();         // Inizio il processo di ricezione
    Serial.begin(9600);    // Solo per debug
    Serial.println("Ricevitore attivo: ");
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
      
	buf[buflen]='\0'; // Metto il terminatore di stringa
        if (strncmp((char *)buf,"MOTOR_ON",buflen)==0){
               digitalWrite(RELAY,HIGH);
        }
        if (strncmp((char *)buf,"MOTOR_OFF",buflen)==0){
             digitalWrite(RELAY,LOW);    
        }
           
         
       
     }
}
