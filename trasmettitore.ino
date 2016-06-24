#include <VirtualWire.h>
#define TX_pin 13
#define LED_pin 11
#define PB_pin 3
int prec_Stato=-1;
const char *msg_ON = "CIAO CAPOSSELE";
const char *msg_OFF = "LED_OFF";

void setup()
{
  Serial.begin(9600);
  pinMode(LED_pin,OUTPUT);
  pinMode(PB_pin,INPUT);
  digitalWrite(LED_pin, LOW);
  vw_set_tx_pin(TX_pin); // Imposto il pin per la trasmissione
  vw_setup(3000);        // Bits per sec
}

void loop()
{
  int buttonState =  digitalRead(PB_pin);
   vw_send((uint8_t *)msg_ON, strlen(msg_ON));
    Serial.println("Stato:mandato");
     vw_wait_tx();
 
}
