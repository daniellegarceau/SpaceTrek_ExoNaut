/**************************************************
 * L11_Distance_Sensor_LEDs.ino
 * An example program that shows how to change the LEDs on the distance sensor

 *
 * Author: Andrew Gafford
 * Email: agafford@spacetrek.com
 * Date: May 20th, 2024
**************************************************/

#include <ExoNaut.h>                    //include the ExoNaut library
#include <ExoNaut_Ultrasonic.h>         //include the ultrasonic distance sensor library

exonaut robot;                          //declare the exonaut object named robot
ultrasonic us;                          //declare the ultrasonic object name us

void setup(){                           //the setup() function runs once
  robot.begin();                        //start the robot object
  robot.set_motor_speed(0,0);           //set the speed of both motors to ZERO
  us.color(0, 0, 0, 0, 0, 0);           //set LED1 to r=0, g=0, b=0 (OFF) and LED2 to r=0, g=0, b=0 (OFF)
  delay(1500);                          //wait 1.5 seconds
}                                       //end of the setup() function

void loop(){                            //the loop() function runs forever in a loop
  us.color(150, 0, 0, 0, 150, 0);       //set LED1 to red=150, green=0, blue=0 and LED2 to red=0, green = 150, blue=0
}