/**************************************************
 * L02_CoreX_LEDs.ino
 * An example program to demonstrate how to use the LEDs built into the CoreX controller.
 * The built in LEDs are RGB Neo Pixels.  These provide a full range of colors and are
 * convenient to use from Arduino.
 *
 * Author: Andrew Gafford
 * Email: agafford@spacetrek.com
 * Date: May 20th, 2024
**************************************************/

#include <ExoNaut.h>

exonaut robot;

void setup() {
  robot.begin();
  delay(1500);
}

void loop() {
  robot.setColorAll(150, 0, 0);
  delay(1000);
  robot.setColorAll(0, 150, 0);
  delay(1000);
  robot.setColorAll(0, 0, 150);
  delay(1000);
  robot.clear();
  delay(1000);

  for(int i = 0; i < NUM_PIXELS; i++){
    robot.setColor(i, 0, 0, 200);
    robot.show();
    delay(500);
  }
  delay(1000);
  robot.clear();
  delay(1000);

  robot.setColor(0, 200, 0, 0);
  robot.setColor(1, 0, 200, 0);
  robot.setColor(2, 0, 0, 200);
  robot.setColor(3, 200, 200, 0);
  robot.setColor(4, 200, 0, 200);
  robot.setColor(5, 0, 200, 200);
  robot.show();
  delay(2000);
  robot.clear();
  delay(1000);

  for(int i = 0; i < NUM_PIXELS; i++){
    robot.setColor(i, 200, 200, 200);
  }
  robot.show();
  delay(2000);

  robot.clear();
  delay(1000);

}
