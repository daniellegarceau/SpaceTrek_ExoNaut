/**************************************************
 * L10_Distance_Sensor_Stop_Buttons.ino
 * An example program to stop the robot when it gets too close to an object
 * with the addition of using the A and B buttons to control if the robot
 * is allowed to move or not.
 *
 * Press the A button to make the robot start moving
 * Press the B button to make the robot stop moving
 * When moving, if the robot gets within STOP_DISTANCE of an object it will stop
 *
 * Author: Andrew Gafford
 * Email: agafford@spacetrek.com
 * Date: May 20th, 2024
**************************************************/

#include <ExoNaut.h>                                //include the ExoNaut library
#include <ExoNaut_Ultrasonic.h>                     //include the ultrasonic distance sensor library

#define STOP_DISTANCE     100                       //the distance in mm to stop the robot

volatile bool buttonA = false;                      //A variable to store if the A button has been pressed or not  
                                                    //It is volatile because it is accessed from within an interrupt service routine
volatile bool buttonB = false;                      //A variable to store if the B button has been pressed or not

exonaut robot;                                      //declare the exonaut object named robot
ultrasonic us;                                      //declare the ultrasonic object name us

bool move = false;                                  //a variable to store if the robot should be moving or not

void setup(){                                       //the setup() function runs once
  attachInterrupt(BUTTON_A_PIN, isrA, FALLING);     //attach button A to an interrupt routine.  Button A has a LOW voltage when pressed
  attachInterrupt(BUTTON_B_PIN, isrB, RISING);      //attach button B to an interrupt routine.  Button B has a HIGH voltage when pressed
  robot.begin();                                    //start the robot object
  robot.set_motor_speed(0,0);                       //set the speed of both motors to ZERO
  delay(1000);                                      //wait 1.0 seconds
}                                                   //end of the setup() function

void loop(){                                        //the loop() function runs forever in a loop
  if(buttonA){                                      //if buttonA is true the button has been pressed
    buttonA = false;                                //make sure you set buttonA back to false
    move = true;                                    //set move to true so the robot will move
  }

  if(buttonB){                                      //if buttonB is true the button has been pressed
    buttonB = false;                                //make sure you set buttonA back to false
    move = false;                                   //set move to false so the robot stop moving
  }

  if(us.getDistance() <= STOP_DISTANCE){            //if the distance sensor dected an object closser than STOP_DISTANCE
    move = false;                                   //then set the move variable to false so the robot stops moving
  }

  if(move){                                         //if the move variable is true
    robot.set_motor_speed(30, 30);                  //set both motors to turn at 30 rpm
  }
  else{                                             //otherwise
    robot.set_motor_speed(0, 0);                    //set both motors to stop
  }
}

void isrA(){                                        //the interrupt service routine for button A
  if(digitalRead(BUTTON_A_PIN) == LOW){             //confirm that button A is LOW to reduce button bounce
    buttonA = true;                                 //if button A is LOW, then set buttonA to true
  }
}

void isrB(){                                        //the interrupt service routine for button B
  if(digitalRead(BUTTON_B_PIN) == HIGH){            //confirm that button B is HIGH to reduce button bounce
    buttonB = true;                                 //if button B is HIGH, then set buttonB to true
  }
}
