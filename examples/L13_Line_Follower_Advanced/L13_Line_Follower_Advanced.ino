/**************************************************
 * L13_Line_Follower_Advanced.ino
 * An example program to make the ExoNaut follow a line
 *
 * Author: Andrew Gafford
 * Email: agafford@spacetrek.com
 * Date: May 20th, 2024
**************************************************/

#include <ExoNaut.h>                          //include the ExoNaut library
#include <ExoNaut_LineFollower.h>             //include the ExoNaut Line Follower library

exonaut robot;                                //declare the exonaut object named robot
lineFollower lf;

uint8_t lineData = 0;                         //a variable to store the line data in

void setup() {                                //the setup() function runs once
  robot.begin();                              //start the robot object
  robot.set_motor_speed(0,0);                 //set the speed of both motors to ZERO
  delay(1500);                                //wait 1.0 seconds
}                                             //end of the setup() function


void loop() {
  lf.readLineFollower(lineData);
  switch(lineData){
    case 0b0000:                              //all detect white
      robot.set_motor_speed(0, 0);
      break;
    case 0b0001:                              //only sensor 1 detects black. Sensor 2, 3 and 4 detect white
      //what to do?
      break;
    case 0b0010:                              //only sensor 2 detects black. Sensor 1, 3 and 4 detect white
      robot.set_motor_speed(6, 40);
      break;
    case 0b0011:                              //Sensor 1 and 2 detect black. Sensor 3 and 4 detect white
      robot.set_motor_speed(-5, 40);
      break;
    case 0b0100:                              //only sensor 3 detects black. Sensor 1, 2 and 4 detect white
      robot.set_motor_speed(40, 6);
      break;
    case 0b0110:                              //Sensor 2 and 3 detect black. Sensor 1 and 4 detect white
      robot.set_motor_speed(40, 40);
      break;
    case 0b0111:                              //Sensor 1, 2 and 3 detect black. Only sensor 4 detects white
      //what to do?
      break;
    case 0b1000:                              //only sensor 4 detects black. Sensor 1, 2 and 3 detect white
      //what to do?
      break;
    case 0b1100:                              //Sensor 3 and 4 detect black. Sensor 1 and 2 detect white
      robot.set_motor_speed(40, -5);
      break;
    case 0b1110:                              //Sensor 2, 3 and 4 detect black. Only sensor 1 detects white
      //what to do?
      break;
    case 0b1111:                              //all detect black
      robot.set_motor_speed(0, 0);
      break;

    //Not needed
    case 0b0101:                              //Sensor 1 and 3 detect black. Sensor 2 and 4 detect white
      //what to do?
      break;
    case 0b1001:                              //Sensor 1 and 4 detect black. Sensor 2 and 3 detect white
      //what to do?
      break;
    case 0b1010:                              //Sensor 2 and 4 detect black. Sensor 1 and 3 detect white
      //what to do?
      break;
    case 0b1011:                              //Sensor 1, 2 and 4 detect black. Only sensor 3 detects white
      //what to do?
      break;
    case 0b1101:                              //Sensor 1, 3 and 4 detect black. Only sensor 2 detects white
      //what to do?
      break;
    default:                                  //unexpected value in lineData
      robot.set_motor_speed(0, 0);            
      break;
  }
  delay(5);
}