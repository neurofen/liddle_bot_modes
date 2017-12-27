#include "Ping.h"
#include "Arduino.h"


void sendPingPulse(int pin) {
/* Send bus pulse to activage PING */ 
  pinMode(pin, OUTPUT); 
  digitalWrite(pin, LOW);
  delayMicroseconds(5);    
  digitalWrite(pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pin, LOW);  
}
  
Ping::Ping(int pin) {
  pingPin = pin; 
  pinMode(pingPin, OUTPUT);  
}

int Ping::ObstacleDistanceInCM() {
  sendPingPulse(pingPin);
  /* listen for ping echo */
  pinMode(pingPin, INPUT);
  /* Measure lenght of incoming pulse */
  return int(pulseIn(pingPin, HIGH)/58);
}

