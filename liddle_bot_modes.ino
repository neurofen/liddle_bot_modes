#include "BlueSmirf.h"
#include "Motor.h"
#include "Ping.h"


const int MOTOR1_ENABLE = 6;
const int MOTOR1_1 = 4;
const int MOTOR1_2 = 7;

const int MOTOR2_ENABLE = 5;
const int MOTOR2_3 = 3;
const int MOTOR2_4 = 2;

Motor motor1(MOTOR1_ENABLE, MOTOR1_1, MOTOR1_2);
Motor motor2(MOTOR2_ENABLE, MOTOR2_3, MOTOR2_4);

Ping pingSensor(8);

const int BLUE_TX = 10;
const int BLUE_RX = 11;

BlueSmirf blueSmirf(BLUE_TX, BLUE_RX);

const int MANUAL = 'M';
const int AVOIDANCE = 'A';
const int FOLLOW = 'T';

const char FWD = 'F';
const char BCK = 'B';
const char LFT = 'L';
const char RHT = 'R';
const char STP = 'S';

int mode;
char navCommand;
char prevNavCommand;

void setup() {
  Serial.begin(9600);
  blueSmirf.Initialise();
  // start in manual mode
  mode = MANUAL;
  navCommand = STP;
  prevNavCommand = navCommand;
  Serial.println("Starting in MANUAL mode!");
}

void loop() {
  checkForCharsSentByBluetooth();
  switch(mode){
    case AVOIDANCE:
      handleObstacleAvoidance();
      break;
    case FOLLOW:
      handleLineFollowing();
      break;
    default:
      handleRemoteControl();   
  }
}

/*
 * Check for mode and nav commands, received over blueSmirf
 */
void checkForCharsSentByBluetooth() {
  if(blueSmirf.Available()) { 
    char commandChar = blueSmirf.Read(); 
    Serial.print("Received: ");
    Serial.println(commandChar);
    switch(commandChar) {
      case MANUAL:
      case AVOIDANCE:
      case FOLLOW:  
        mode = commandChar;
        break;
      case FWD:
      case BCK:
      case LFT:
      case RHT:
      case STP:
        navCommand = commandChar;
        break;
      default:
        Serial.print("Unrcognised command: ");
        Serial.println(commandChar);
    }
  }
}

void handleObstacleAvoidance() {
  int distanceFromObstacle = pingSensor.ObstacleDistanceInCM();

  if(distanceFromObstacle > 2 && distanceFromObstacle <= 25) {
    Serial.print("Distance from obstacle: ");
    Serial.println(distanceFromObstacle);
    Serial.println("turn left");
    turnLeft(); 
  }
  else {
    forward();
  }
}

void handleLineFollowing() {
  
}

void handleRemoteControl() {
  if(prevNavCommand != 'S' && prevNavCommand == navCommand) 
    return;
  
  switch(navCommand) {
    case FWD:
      Serial.println("forward");
      forward();
      break;
    case BCK:
      Serial.println("reverse");
      reverse();
    break;
    case LFT:
      Serial.println("turn left");
      turnLeft();
      break;
    case RHT:
      Serial.println("turn right");
      turnRight();
      break;
    default:
      Serial.println("stop");
      stop();
  }
  prevNavCommand = navCommand;
}

void forward() {
  motor1.Forward(200);
  motor2.Forward(200);    
}

void reverse() {
  motor1.Reverse(200);
  motor2.Reverse(200);    
}

void turnLeft() {
  motor1.Forward(200); 
  motor2.Reverse(95);
}

void turnRight() {
  motor2.Forward(200); 
  motor1.Reverse(95);   
}

void stop() {
  motor1.Stop(); 
  motor2.Stop();   
}


