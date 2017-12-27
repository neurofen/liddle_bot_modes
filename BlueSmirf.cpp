#include <SoftwareSerial.h>
#include "Arduino.h"
#include "BlueSmirf.h"


SoftwareSerial *bluetooth;

BlueSmirf::BlueSmirf(uint8_t tx, uint8_t rx) {
  /* We receive date from bluetooth module over bluetoothTx 
     and send over bluetooth via bluetoothRx */
  SoftwareSerial cereal(tx, rx);
  bluetooth = &cereal;
}

void BlueSmirf::Initialise() {
  bluetooth->begin(115200);
  /* Enter bluetooth command mode $$$ */
  bluetooth->print("$");
  bluetooth->print("$");
  bluetooth->print("$");
  /* allow bluesmirf to indicate 
  it's entered command mode by returning CMD */
  delay(100); 
  /* Change baud rate to 9600 */
  bluetooth->println("U,9600,N"); 
  bluetooth->begin(9600);
  Serial.println("Bluetooth initialised at 9600 baud");  
}

int BlueSmirf::Available() {
  return bluetooth->available();
}

char BlueSmirf::Read() {
  return bluetooth->read();
}

