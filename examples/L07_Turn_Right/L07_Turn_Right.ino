/**************************************************
 * L07_Turn_Right.ino
 * An example program to make the ExoNaut robot turn right for one second
 *
 * Author: Andrew Gafford
 * Email: agafford@spacetrek.com
 * Date: May 20th, 2024
**************************************************/

#include <ExoNaut.h>                          //include the ExoNaut library

exonaut robot;                                //declare the exonaut object named robot

void setup() {                                //the setup() function runs once
  robot.begin();                              //start the robot object
  delay(2000);                                //wait two seconds
  robot.set_motor_speed(50, 25);              //set the speed of left motor to 50 and right motor to 35
                                              //To turn left make the left motor speed less than the right motor speed
  delay(2000);                                //wait for two seconds
  robot.set_motor_speed(0,0);                 //set the speed of both motors to ZERO
}                                             //end of the setup() function

void loop() {
  // Nothing in loop()

}