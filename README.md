
# 🟢 ᏒᎧᏰᏰᎥ 🤖

Robbie is an Arduino based robot which has Obstacle Avoiding, Computer Vision and Remote control functionality. 
It uses an ultrasonic distance sensor to avoid obstacles, a camera to keep track of users' gestures and a bluetooth module to communicate to the Python script/the app (according to the mode opted by the user). It's bluetooth module (HC-05) can be paired to only one device at a time.

## 🔶 The Robot 

![App Screenshot](https://user-images.githubusercontent.com/114488605/208926277-45c92411-7b17-4ed6-8533-5b03a1a36960.jpg)


## ◆ App for controlling the robot 📱

 ###  ◉ Code Blocks
![App Screenshot](https://github.com/Abhishek-Kanti/OA-RC-Robot/blob/main/Images/app_blocks.jpeg)

As I am not into app development for now, I used MIT App inventor to create my app :)

 ### ◉ The App 🕹️
![App Screenshot](https://user-images.githubusercontent.com/114488605/208926528-810db798-be83-4d88-86d1-6d146c2afd45.jpeg)

As soon as the user pushes the button, a character is sent to the Arduino via the bluetooth which is then stored in a variable. It then goes through a series of if-else conditions and the required command is sent to the motors.

## ◆ Computer Vision 👁️

![robot_gif](https://user-images.githubusercontent.com/114488605/212562040-3ce82f09-c8dd-45ce-884c-a83bfc2062e2.gif)

A Python Script consisting of the computer vision code runs on the PC and analyses our gestures. The ML model recognises the patterns fed to it by the hand tracking module. This ML model returns an index after it has made the predictions, which is then sent to the Arduino via the COM port assigned to the bluetooth module HC-05. This index then goes through the if-else conditions and the desired commands are given to the motors.

To have a look on the process and the working of the robot use the link: https://drive.google.com/file/d/1ZKSbjOFSNHMDaIJ48R3JdZmeByd2y-gf/view?usp=share_link
 
 ## ◆ Circuit Diagram
![App Screenshot](https://user-images.githubusercontent.com/114488605/208926716-aaa025e3-9435-4683-bbe1-b2ca6aa4f4c0.jpg)

My circuit was pretty much same as above, difference being that I used 4 motors instead of two and I used two sets of batteries, one to power the arduino and the other to power the servo. I did this to
prevent the Arduino from the back emf that is being generated by the servo motor which might interfere with the other pwm signals. It might also lead to the failure of Arduino.
