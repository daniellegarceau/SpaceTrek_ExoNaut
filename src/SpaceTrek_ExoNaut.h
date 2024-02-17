/*
*
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

//Serial for motor control (possible other CoreX features)
#define ets_serial Serial2

//Ultrasonic Sensor Registers
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

//Ultrasonic Sensor Definitions
#define URGB_BRIGHTNESS				50			//Default RGB Brightness, 0-255
#define RGB_WORK_SIMPLE_MODE		0
#define RGB_WORK_BREATHING_MODE		1

//Line Follower Definitions
#define LINE_FOLLOWER_I2C_ADDR		0x78
#define LF_CH1(x)					(x & 0x01)
#define LF_CH2(x)					((x>>1) & 0x01)
#define LF_CH3(x)					((x>>2) & 0x01)
#define LF_CH4(x)					((x>>3) & 0x01)

class exonaut{
	public:
		//Motor control
		void begin(void);
		void set_motor_type(uint8_t motortype);
		int set_motor_speed(float new_speed1, float new_speed2);

		//Ultrasonic sensor
		//void Ultrasound();
		void Breathing(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2);
		void Color(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2);
		uint16_t getDistance();
		
		//line follower
		bool readLineFollower(uint8_t &val);
		
	private:
		bool wireWriteByte(uint8_t addr, uint8_t val);
		bool wireWriteDataArray(uint8_t addr, uint8_t reg,uint8_t *val,unsigned int len);
		int wireReadDataArray(uint8_t addr, uint8_t reg, uint8_t *val, unsigned int len);
};




#endif //EXONAUT_h