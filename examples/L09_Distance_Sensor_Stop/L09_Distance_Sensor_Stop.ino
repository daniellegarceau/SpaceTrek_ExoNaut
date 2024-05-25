/**************************************************
 * L11_Distance_Sensor_LEDs.ino
 * An example program that shows how to change the LEDs on the distance sensor

 *
 * Author: Andrew Gafford
 * Email: agafford@spacetrek.com
 * Date: May 20th, 2024
**************************************************/

#include <ExoNaut.h>                                //include the ExoNaut library
#include <ExoNaut_Ultrasonic.h>                     //include the ultrasonic distance sensor library

#define STOP_DISTANCE     100                       //the distance in mm to stop the robot

exonaut robot;                                      //declare the exonaut object named robot
ultrasonic us;                                      //declare the ultrasonic object name us

void setup(){                                       //the setup() function runs once
  robot.begin();                                    //start the robot object
  robot.set_motor_speed(0,0);                       //set the speed of both motors to ZERO
  delay(2000);                                      //wait 2.0 seconds
}                                                   //end of the setup() function

void loop(){                                        //the loop() function runs forever in a loop
  if(us.getDistance() <= STOP_DISTANCE){            //if the distance sensor dected an object closser than STOP_DISTANCE
    robot.set_motor_speed(0, 0);                    //set both motors to stop
  }
  else{                                             //otherwise
    robot.set_motor_speed(30, 30);                  //set both motors to turn at 30 rpm
  }
}




