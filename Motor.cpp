#include "Motor.h"
#include "Arduino.h"

Motor::Motor(int mEnable, int mPin1, int mPin2) {
  motorEnable = mEnable;
  pin1 = mPin1;
  pin2 = mPin2;
  pinMode(motorEnable, OUTPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
}

void Motor::Forward(int speed) {
  analogWrite(motorEnable, speed); 
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
}

void Motor::Reverse(int speed) {
  analogWrite(motorEnable, speed); 
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH); 
}

void Motor::Stop() {
  analogWrite(motorEnable, 0); 
}


