
#include<Servo.h>
Servo myServo;
const int trig=A1;
const int echo=A2;
const int in1=7;
const int in2=6;
const int in3=5;
const int in4=4;
const int pos4=90;



void setup(){
   myServo.attach(9);
   pinMode(trig,OUTPUT);
   pinMode(echo,INPUT);
   pinMode(in1,OUTPUT);
   pinMode(in2,OUTPUT);
   pinMode(in3,OUTPUT);
   pinMode(in4,OUTPUT);
   myServo.write(90);
   Serial.begin(9600);
}


void forward(){
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,0);
  digitalWrite(in4,1);
}

void backward(){
  digitalWrite(in1,0);
  digitalWrite(in2,1);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
}

void left(){
  digitalWrite(in1,0);
  digitalWrite(in2,1);
  digitalWrite(in3,0);
  digitalWrite(in4,1);
}

void right(){
  digitalWrite(in3,1);
  digitalWrite(in4,0);
  digitalWrite(in1,1);
  digitalWrite(in2,0);
}

void stop(){
 digitalWrite(in3,0);
  digitalWrite(in4,0);
  digitalWrite(in1,0);
  digitalWrite(in2,0);
}

float distanceData(){
  float time;
  digitalWrite(trig,0);
  delay(4);
  digitalWrite(trig,1);
  delay(10);
  digitalWrite(trig,0);

  time=pulseIn(echo,1);
  float dis=time*0.0343/2;
  return dis;
}


void ServoLeft(){
      myServo.write(160);
}
 
void ServoRight(){
      myServo.write(20);   
}

void loop(){
  obstacle();
  //bluetooth();
}

void bluetooth(){
  if(Serial.available()>0){
    char value=Serial.read();
    if(value=='u'){
      forward();
    } else if(value =='b'){
      backward();
    } else if(value=='l'){
      left();
    } else if(value =='r'){
      right();
    } else if (value=='s'){
      stop();
    }
  }
}

void obstacle(){
  float Distance=distanceData();
  if(Distance<10){
    stop();
    Serial.println("stop");
    delay(100);
    //backward();
    //Serial.println("back");
    //delay(1000);
    //stop();
    //Serial.println("stop");
    ServoLeft();
    float Left=distanceData();
    delay(100);
    ServoRight();
    float Right=distanceData();
    myServo.write(90);
    
    if(Left<Right){
      right();
      Serial.println("right");
      delay(800);
    } else if(Left>Right){
      left();
      Serial.println("left");
      delay(800);
    } else if(Left==Right){
      right();
      Serial.println("right 360");
      delay(1500);
    }
 }
 else{
   forward();
  Serial.println("forward");  
 }
}
