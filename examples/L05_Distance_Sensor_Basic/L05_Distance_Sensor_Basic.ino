/**************************************************
 * L05_Distance_Sensor_Basic.ino
 * An example program to change the LEDs on the distance sensor
 * and stop the robot when too close to an object.
 *
 * Author: Andrew Gafford
 * Email: agafford@spacetrek.com
 * Date: Feb. 15th, 2024
**************************************************/

//#include <Arduino.h>
#include <SpaceTrek_ExoNaut.h>                //include the ExoNaut library

exonaut robot;                                //declare the exonaut object named robot
uint8_t lineData = 0;

void setup() {                                //the setup() function runs once
  Serial.begin(115200);                       //Start the serial port so data can be sent to the computer
  robot.begin();                              //start the robot object
  robot.set_motor_speed(0,0);                 //set the speed of both motors to ZERO
  delay(1000);                                //wait 1.0 seconds
  Serial.println("Starting...");
}                                             //end of the setup() function

void loop() {
  while(robot.getDistance() >= 50){
    robot.set_motor_speed(0, 0);
  }
  robot.set_motor_speed(0, 0);
}