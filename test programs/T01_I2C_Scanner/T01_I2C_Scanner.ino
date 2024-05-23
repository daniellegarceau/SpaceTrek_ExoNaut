/**************************************************
 * T01_I2C_Scanner.ino
 * A test program to scan for I2C devices
 *
 * Author: Andrew Gafford
 * Email: agafford@spacetrek.com
 * Date: May. 8th, 2024
**************************************************/

// #include <SpaceTrek_ExoNaut.h>                //include the ExoNaut library
#include <Wire.h>

// exonaut robot;                                //declare the exonaut object named robot
// int speed = 50;                               //declare and initialize a variable speed set to the value 50

void setup() {                                //the setup() function runs once
  Wire.begin();
  Serial.begin(115200);
  delay(2000);
  Serial.println("I2C Scanner");

  // robot.begin();                              //start the robot object
  // delay(1000);                                //wait 0.5 seconds
  // robot.set_motor_speed(speed, speed);        //set the speed of both motors to the value of the speed variable
  // delay(1000);                                //wait for 1 second
  // robot.set_motor_speed(0,0);                 //set the speed of both motors to ZERO
}                                             //end of the setup() function

void loop() {
  // Nothing in loop()
  uint8_t error;
  uint8_t address;
  uint8_t nDevices = 0;

  for(address = 1; address < 127; address++){
    delay(10);
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if(error == 0){
      Serial.print("I2C device found at address 0x");
      if(address < 16) Serial.print("0");
      Serial.println(address, HEX);
      nDevices++;
    }
    else if(error == 4){
      Serial.print("Unknown error at address 0x");
      if(address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }

  if(nDevices == 0) Serial.println("No I2C devices found\n");
  else Serial.println("done\n");

  delay(5000);
}