/*
*SpaceTrek_ExoNaut.h
*
*Author:	Andrew Gafford
*Email:		agafford@spacetrek.com
*Date:		Feb. 9th, 2024
*
*This library is for controlling the Space Trek ExoNaut Robot.  It provides
*control of the drive motors, sensors and camera module.
*
*/

#ifndef EXONAUT_h
#define EXONAUT_h

#include <Arduino.h>
#include <Wire.h>
#include <HardwareSerial.h>

#define ets_serial Serial2

#define ULTRASOUND_I2C_ADDR			0x77		//Ultrasonic sensor I2C address
#define DISDENCE_L					0			//Register with lower 8 bits of distance, unit mm
#define DISDENCE_H					1			//Register with upper 8 bits of distance, unit mm
#define RGB_WORK_MODE				2			//Register with RGB light mode, 0: user-defined mode 1: breathing light mode, default 0
#define RGB1_R						3			//Register with R value of probe No. 1, 0~255, default 0
#define RGB1_G						4			//Register with G value of probe No. 1, 0~255, default 0
#define RGB1_B						5			//Register with B value of probe No. 1, 0~255, default 255
#define RGB2_R						6			//Register with R value of probe No. 2, 0~255, default 0
#define RGB2_G						7			//Register with G value of probe No. 2, 0~255, default 0
#define RGB2_B						8			//Register with B value of probe No. 2, 0~255, default 255
#define RGB1_R_BREATHING_CYCLE		9			//Register with the breathing period of R of probe 1, the unit is 100ms, the default is 0, if the setting period is 3000ms, the value is 30
#define RGB1_G_BREATHING_CYCLE		10
#define RGB1_B_BREATHING_CYCLE		11
#define RGB2_R_BREATHING_CYCLE		12			//Probe No. 2
#define RGB2_G_BREATHING_CYCLE		13
#define RGB2_B_BREATHING_CYCLE		14

#define URGB_BRIGHTNESS				50			//Default RGB Brightness, 0-255
#define RGB_WORK_SIMPLE_MODE		0
#define RGB_WORK_BREATHING_MODE		1

class exonaut{
	public:
		void begin(void);
		void set_motor_type(uint8_t motortype);
		int set_motor_speed(float new_speed1, float new_speed2);

		void Ultrasound();
		bool wireWriteByte(uint8_t addr, uint8_t val);
		bool wireWriteDataArray(uint8_t addr, uint8_t reg,uint8_t *val,unsigned int len);
		int wireReadDataArray(uint8_t addr, uint8_t reg, uint8_t *val, unsigned int len);
		void Breathing(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2);
		void Color(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2);
		uint16_t GetDistance();
};




#endif //EXONAUT_h