/**************************************************
 * L03_Pivot_Right.ino
 * An example program to make the ExoNaut robot pivot right for one second
 *
 * Author: Andrew Gafford
 * Email: agafford@spacetrek.com
 * Date: Feb. 12th, 2024
**************************************************/

#include <SpaceTrek_ExoNaut.h>                //include the ExoNaut library

exonaut robot;                                //declare the exonaut object named robot
int speed = 800;                               //declare and initialize a variable speed set to the value 50

void setup() {                                //the setup() function runs once
  robot.begin();                              //start the robot object
  delay(2000);                                //wait two seconds
  robot.set_motor_speed(speed, -speed);       //set the speed of both motors to the value of the speed variable
                                              //To pivot left make the left motor speed negative and the right motor speed positive
  delay(1000);                                //wait for one second
  robot.set_motor_speed(0,0);                 //set the speed of both motors to ZERO
}                                             //end of the setup() function

void loop() {
  // Nothing in loop()

}