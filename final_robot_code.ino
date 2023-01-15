
#include<Servo.h>
Servo myServo;             // object named myServo created.
const int trig=A1;         // defining all the pins.
const int echo=A2;
const int in1=7;
const int in2=6;
const int in3=5;
const int in4=4;
const int pos4=90;



void setup(){
   myServo.attach(9);        // attaching servo motor's signal pin to pin no. 9.
   pinMode(trig,OUTPUT);     // setting pins as input or output.
   pinMode(echo,INPUT);
   pinMode(in1,OUTPUT);
   pinMode(in2,OUTPUT);
   pinMode(in3,OUTPUT);
   pinMode(in4,OUTPUT);
   myServo.write(90);       // setting the initial angle of the servo to 90 degrees.
   Serial.begin(9600);      // setting the baud rate to 9600.
}


void forward(){             // function to move the robot forward
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,0);
  digitalWrite(in4,1);
}

void backward(){            // function to move the robot backward
  digitalWrite(in1,0);
  digitalWrite(in2,1);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
}

void left(){                // function to move the robot anticlockwise
  digitalWrite(in1,0);
  digitalWrite(in2,1);
  digitalWrite(in3,0);
  digitalWrite(in4,1);
}

void right(){               // function to move the robot clockwise
  digitalWrite(in3,1);
  digitalWrite(in4,0);
  digitalWrite(in1,1);
  digitalWrite(in2,0);
}

void stop(){                 // function to stop the robot 
 digitalWrite(in3,0);
  digitalWrite(in4,0);
  digitalWrite(in1,0);
  digitalWrite(in2,0);
}

float distanceData(){        // function to get distance data.
  float time;
  digitalWrite(trig,0);      // initially setting the trigger pin to low.
  delay(4);
  digitalWrite(trig,1);      // after a delay of 4 microsec, setting the trigger pin to high. 
  delay(10);                 // giving a delay of 10 microsec.
  digitalWrite(trig,0);      // setting the trigger pin to low.

  time=pulseIn(echo,1);      // fetching the time taken by the sound pulse after echoing, using the pulseIn function.
  float dis=time*0.0343/2;   // calculating the distance at which the obstacle is.
  return dis;                
}


void ServoLeft(){            // function to turn servo 160 degrees in anticlockwise direction.
      myServo.write(160);  
}
 
void ServoRight(){           // function to turn servo 160 degrees in clockwise direction.
      myServo.write(20);   
}

void loop(){
  obstacle();                // using the robot in obstacle avoiding mode.
  //bluetooth();
}

void bluetooth(){             // function to control the robot manually.
  if(Serial.available()>0){      // checking if there is any data in the serial buffer.
    char value=Serial.read();    // fetching the values being sent by the app. 
    if(value=='u'){              // according to the value received, respective functions are called to move the robot.
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

void computerVision(){                               // function to control the robot using hand gestures.
  if(Serial.available()>0){                          // checking if there is any data in the serial buffer. 
    String value=Serial.readStringUntil('\n');       // fetching the values being sent by the python script.  
    if(value == "f"){                                 // according to the value received, respective functions are called to move the robot.
      forward();
      Serial.write("f");
    } else if(value == "b"){
      backward();
      Serial.write("b");
    } else if(value == "l"){
      left();
      Serial.write("l");
    } else if(value == "r"){
      right();
      Serial.write("r");
    } else if (value == "s"){
      Stop();
      Serial.write("s");
    }
  }
}

void obstacle(){                  // function to operate the robot in obstacle avoiding mode.
  float Distance=distanceData();
  if(Distance<10){                // if the distance between the obstacle and the robot is less than 10 cm, then the
    stop();                       // robot moves back for 1 sec and checks the left and the right distances. 
    Serial.println("stop");
    delay(100);
    backward();
    Serial.println("back");
    delay(1000);
    stop();
    Serial.println("stop");
    ServoLeft();
    float Left=distanceData();
    delay(100);
    ServoRight();
    float Right=distanceData();
    myServo.write(90);
    
    if(Left<Right){             // after checking the left and the right distances, it moves in the direction having more space.
      right();
      Serial.println("right");
      delay(800);
    } else if(Left>Right){    
      left();
      Serial.println("left");
      delay(800);
    } else if(Left==Right){      // incase both the directions are equal in space, it takes a 360 degree turn.
      right();
      Serial.println("right 360");
      delay(1500);
    }
 }
 else{                          // if the distance between the obstacle and robot is greater than or equal to 10 cm, it keeps moving forward.
   forward();
  Serial.println("forward");  
 }
}
