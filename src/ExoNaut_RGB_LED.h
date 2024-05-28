/*
*ExoNaut_RGB_LED.h
*
*Author:	Andrew Gafford
*Email:		agafford@spacetrek.com
*Date:		May 20th, 2024
*
*This library is for controlling the Space Trek ExoNaut Robot's RGB Ultrasonic
*distance sensor.  It provides functions to read the distance and set the RGB LEDS.
*
*/

#ifndef __EXONAUT_RGBLED_h
#define __EXONAUT_RGBLED_h

#include "ExoNaut.h"
#include <Adafruit_NeoPixel.h>

//RGB LED Definitions



class RGB{
	public:
		void begin(uint8_t port);
		//LED control
		void setColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
		void setColorAll(uint8_t r, uint8_t g, uint8_t b);
		void show(void);
		void clear(void);
	
	private:
	
	
};

extern Adafruit_NeoPixel pixels2;

#endif //end __EXONAUT_RGBLED_h