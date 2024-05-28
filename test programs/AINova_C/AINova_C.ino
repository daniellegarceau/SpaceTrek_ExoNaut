/**************************************************************
 * company：Hiwonder
 * date&&author：20231220 && CuZn
 * description：AiNova test program
 * functions: Pressing button A will make the car move forward for 1 second, while pressing button B will make it move backward.
**************************************************************/
#include <Arduino.h>
#include "robotrun.h"

//Underlying control object
robotrun rb;


int speed = 50;         // Speed variable, range[ -180 , 180]

float encoderCount[2];

void setup() {
  //Enable serial port
  Serial.begin(115200);
  //Underlying control initialization
  rb.begin();
  //Set encoder motor
  rb.hw_encoder_motor_set_motor_type(1);

  delay(2000);
  //Serial port printing
  Serial.println("START");
}


void loop() {
  if(rb.read_button(1)) //When button A is pressed
  {
    rb.hw_encoder_motor_set_speed(0,speed);   //both motors forward
    delay(1000);
    rb.hw_encoder_motor_set_speed(0,0);
    rb.hw_encoder_motor_get_count(encoderCount);
    Serial.print(encoderCount[0], 3); Serial.print(", "); Serial.println(encoderCount[1], 3);
  }
  if(rb.read_button(2)) //When button B is pressed
  {
    rb.hw_encoder_motor_set_speed(0,-speed);    //both motors in reverse
    delay(1000);
    rb.hw_encoder_motor_set_speed(0,0);
  }
}
