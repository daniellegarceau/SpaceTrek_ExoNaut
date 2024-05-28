/**************************************************
 * L06_Variable_Speed.ino
 * An example program to make the ExoNaut robot turn right for 1 second
 *
 * Author: Andrew Gafford
 * Email: agafford@spacetrek.com
 * Date: May 20th, 2024
 *
 * Commands:
 * exonaut robot;                           //This command setups the exonaut robot object.  exonaut is the class and robot is the name of the object.
 *                                          //This is the object that handles all of the motor commands and the features on the CoreX controller.
 * 
 * robot.begin();                           //This command initializes or begins the things in the robot object.
 *                                          //It is used once at the beginning of the program
 * 
 * robot.set_motor_speed(left, right);      //This command sets both motor speeds.  It takes integer numbers for the left and right parameters.
 *                                          //Positive numbers will make the motor move forward, negative numbers will make it move backwards.
 * 
**************************************************/

#include <ExoNaut.h>                        //include the ExoNaut library

exonaut robot;                              //declare the exonaut object named robot
int speed = 50;                             //a variable 'speed' set to the value 50
int var = 5;                                //a variable for how much the value will change each time through the loop

void setup() {                              //the setup() function runs once
  robot.begin();                            //start the robot object
  robot.set_motor_speed(0,0);               //set the speed of both motors to ZERO
  delay(2000);                              //wait 0.5 seconds
}                                           //end of the setup() function

void loop() {                               //the loop() function runs forever in a loop
  if(speed >= 120 || speed <= 25){          //if the speed value is out of bounds
    var = -var;                             //reverse if var is adding or subtracting
  }
  speed = speed + var;                      //add speed and var each time through the loop to varry speed
  robot.set_motor_speed(speed, speed);      //send new speed to the robot
  delay(100);                               //wait 0.1 seconds
}