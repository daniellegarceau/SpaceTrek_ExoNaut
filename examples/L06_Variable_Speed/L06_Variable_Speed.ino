/**************************************************
 * L06_Variable_Speed.ino
 * An example program to make the ExoNaut robot turn right for 1 second
 *
 * Author: Andrew Gafford
 * Email: agafford@spacetrek.com
 * Date: May 20th, 2024
**************************************************/

#include <ExoNaut.h>                          //include the ExoNaut library

exonaut robot;                                //declare the exonaut object named robot
int speed = 50;                               //declare and initialize a variable speed set to the value 50
int var = 5;

void setup() {                                //the setup() function runs once
  robot.begin();                              //start the robot object
  robot.set_motor_speed(0,0);                 //set the speed of both motors to ZERO
  delay(2000);                                //wait 0.5 seconds
}                                             //end of the setup() function

void loop() {
  if(speed >= 120 || speed <= 25){
    var = -var;
  }
  speed = speed + var;
  robot.set_motor_speed(speed, speed);
  delay(100);
}