/**************************************************
 * L07_Line_Follower_Basic.ino
 * An example program to make the ExoNaut follow a line
 *
 * Author: Andrew Gafford
 * Email: agafford@spacetrek.com
 * Date: Feb. 16th, 2024
**************************************************/

//#include <Arduino.h>
#include <SpaceTrek_ExoNaut.h>                //include the ExoNaut library

exonaut robot;                                //declare the exonaut object named robot
//int speed = 50;                               //declare and initialize a variable speed set to the value 50
uint8_t lineData = 0;

void setup() {                                //the setup() function runs once
  Serial.begin(115200);                       //Start the serial port so data can be sent to the computer
  robot.begin();                              //start the robot object
  robot.set_motor_speed(0,0);                 //set the speed of both motors to ZERO
  delay(1000);                                //wait 1.0 seconds
  Serial.println("Starting...");
}                                             //end of the setup() function

void loop() {
  robot.readLineFollower(lineData);
  if(LF_CH1(lineData) && LF_CH2(lineData) && LF_CH3(lineData) && LF_CH4(lineData)){
    robot.set_motor_speed(0, 0);
  }
  else if(!LF_CH1(lineData) && !LF_CH2(lineData) && !LF_CH3(lineData) && !LF_CH4(lineData)){
    robot.set_motor_speed(0, 0);
  }
  else if(!LF_CH1(lineData) && LF_CH2(lineData) && LF_CH3(lineData) && !LF_CH4(lineData)){
    robot.set_motor_speed(40, 40);
  }
  else if(!LF_CH1(lineData) && LF_CH2(lineData) && !LF_CH3(lineData) && !LF_CH4(lineData)){
    robot.set_motor_speed(6, 40);
  }
  else if(!LF_CH1(lineData) && !LF_CH2(lineData) && LF_CH3(lineData) && !LF_CH4(lineData)){
    robot.set_motor_speed(40, 6);
  }
  delay(10);
}