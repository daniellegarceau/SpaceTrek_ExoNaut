/*
*ExoNaut_Ultrasonic.h
*
*Author:	Andrew Gafford
*Email:		agafford@spacetrek.com
*Date:		May 20th, 2024
*
*This library is for controlling the Space Trek ExoNaut Robot's RGB Ultrasonic
*distance sensor.  It provides functions to read the distance and set the RGB LEDS.
*
*/

#ifndef __EXONAUT_ULTRASONIC_h
#define __EXONAUT_ULTRASONIC_h

#include "ExoNaut.h"



//Ultrasonic Sensor Definitions
#define ULTRASOUND_I2C_ADDR			0x77		//Ultrasonic sensor I2C address

#define DISTANCE_L_REG				0			//Register with lower 8 bits of distance, unit mm
#define DISTANCE_H_REG				1			//Register with upper 8 bits of distance, unit mm
#define RGB_WORK_MODE_REG			2			//Register with RGB light mode, 0: user-defined mode 1: breathing light mode, default 0
#define RGB1_R_REG					3			//Register with R value of probe No. 1, 0~255, default 0
#define RGB1_G_REG					4			//Register with G value of probe No. 1, 0~255, default 0
#define RGB1_B_REG					5			//Register with B value of probe No. 1, 0~255, default 255
#define RGB2_R_REG					6			//Register with R value of probe No. 2, 0~255, default 0
#define RGB2_G_REG					7			//Register with G value of probe No. 2, 0~255, default 0
#define RGB2_B_REG					8			//Register with B value of probe No. 2, 0~255, default 255
#define RGB1_R_BREATHING_CYCLE_REG	9			//Register with the breathing period of R of probe 1, the unit is 100ms, the default is 0, if the setting period is 3000ms, the value is 30
#define RGB1_G_BREATHING_CYCLE_REG	10			//Register with the breathing period of G of probe 1, the unit is 100ms, the default is 0, if the setting period is 3000ms, the value is 30
#define RGB1_B_BREATHING_CYCLE_REG	11			//Register with the breathing period of B of probe 1, the unit is 100ms, the default is 0, if the setting period is 3000ms, the value is 30
#define RGB2_R_BREATHING_CYCLE_REG	12			//Register with the breathing period of R of probe 2, the unit is 100ms, the default is 0, if the setting period is 3000ms, the value is 30
#define RGB2_G_BREATHING_CYCLE_REG	13			//Register with the breathing period of G of probe 2, the unit is 100ms, the default is 0, if the setting period is 3000ms, the value is 30
#define RGB2_B_BREATHING_CYCLE_REG	14			//Register with the breathing period of B of probe 2, the unit is 100ms, the default is 0, if the setting period is 3000ms, the value is 30

#define URGB_BRIGHTNESS				50			//Default RGB Brightness, 0-255
#define RGB_WORK_SIMPLE_MODE		0
#define RGB_WORK_BREATHING_MODE		1


class ultrasonic{
	public:
		uint8_t rgb1[3];
		uint8_t rgb2[3];
		
		void breathing(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2);
		void color(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2);
		uint16_t getDistance();
		void getColor();
		void getBreathing();
		uint8_t getBrightness();
		uint8_t getLEDMode();
	
	private:
		bool wireWriteByte(uint8_t addr, uint8_t val);
		bool wireWriteDataArray(uint8_t addr, uint8_t reg,uint8_t *val,unsigned int len);
		int wireReadDataArray(uint8_t addr, uint8_t reg, uint8_t *val, unsigned int len);
	
};



#endif