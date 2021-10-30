#include <Servo.h>

// C++ code
//

//some constants
int speedOfSound=344;//it is in Metre/sec.
float front_DistanceFromObstacle;
float left_DistanceFromObstacle;
float right_DistanceFromObstacle;
float microSec=0.000001;//converting from from microsec to sec
String msg="Object is at the distance of: ";

//SERVO
int servoPin=11;
Servo myServo;

//HC-SR04
int trigPin=10;
int echoPin=9;
int pulseTravelTime;


//MOTOR

int mSpeed=200;
int turningSpeed=150;
//rm means RightSide Motor
int rmSpeedPin=8;
int rmDir1Pin=7;
int rmDir2Pin=6;

//lm means LeftSide Motor
int lmSpeedPin=5;
int lmDir1Pin=4;
int lmDir2Pin=3;

void setup()
{
  pinMode(servoPin,OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin,INPUT);
  
  pinMode(rmSpeedPin,OUTPUT);
  pinMode(rmDir1Pin,OUTPUT);
  pinMode(rmDir2Pin,OUTPUT);
  
  pinMode(lmSpeedPin,OUTPUT);
  pinMode(lmDir1Pin,OUTPUT);
  pinMode(lmDir2Pin,OUTPUT);
  
  Serial.begin(9600);
  myServo.attach(servoPin);
}

void loop()
{
  digitalWrite(trigPin,LOW);
  delay(10);
  digitalWrite(trigPin,HIGH);
  delay(25);
  digitalWrite(trigPin,LOW);
  pulseTravelTime=pulseIn(echoPin,HIGH);
  Serial.println(pulseTravelTime);
  delay(10);
  
  //calculate the distance from object in metres.
  front_DistanceFromObstacle=0.5*speedOfSound*pulseTravelTime*microSec;
  Serial.print(msg);
  Serial.println(front_DistanceFromObstacle);
  
  if(front_DistanceFromObstacle>0.15){
    digitalWrite(rmSpeedPin,mSpeed);
    digitalWrite(lmSpeedPin,mSpeed);
    digitalWrite(rmDir1Pin,HIGH);
    digitalWrite(rmDir2Pin,LOW);
    digitalWrite(lmDir1Pin,HIGH);
    digitalWrite(lmDir2Pin,LOW);
  }
  
  if(front_DistanceFromObstacle<0.15){
    digitalWrite(rmSpeedPin,0);
    digitalWrite(lmSpeedPin,0);
    
    //measure distance from left obstacle
    myServo.write(0);
    digitalWrite(trigPin,LOW);
  	delay(10);
  	digitalWrite(trigPin,HIGH);
    delay(25);
 	digitalWrite(trigPin,LOW);
  	pulseTravelTime=pulseIn(echoPin,HIGH);
  	Serial.println(pulseTravelTime);
  	delay(10);
    left_DistanceFromObstacle=0.5*speedOfSound*pulseTravelTime*microSec;
    delay(200);
    
    //measure right from right Obstacle
    myServo.write(180);
    digitalWrite(trigPin,LOW);
  	delay(10);
  	digitalWrite(trigPin,HIGH);
    delay(25);
 	digitalWrite(trigPin,LOW);
  	pulseTravelTime=pulseIn(echoPin,HIGH);
  	Serial.println(pulseTravelTime);
  	delay(10);
    right_DistanceFromObstacle=0.5*speedOfSound*pulseTravelTime*microSec;
    delay(200);
    
    //check which has more distance then turn to that side
    
    //turning right side
    if(left_DistanceFromObstacle>right_DistanceFromObstacle){
      digitalWrite(rmSpeedPin,turningSpeed);
      digitalWrite(lmSpeedPin,mSpeed);
      digitalWrite(rmDir1Pin,LOW);
      digitalWrite(rmDir2Pin,HIGH);
      digitalWrite(lmDir1Pin,HIGH);
      digitalWrite(lmDir2Pin,LOW);
      myServo.write(90);
    }
    
    //turning left side
    if(left_DistanceFromObstacle<right_DistanceFromObstacle){
      digitalWrite(rmSpeedPin,mSpeed);
      digitalWrite(lmSpeedPin,turningSpeed);
      digitalWrite(rmDir1Pin,HIGH);
      digitalWrite(rmDir2Pin,LOW);
      digitalWrite(lmDir1Pin,LOW);
      digitalWrite(lmDir2Pin,HIGH);
      myServo.write(90);
    }
    
    
  }
  
}