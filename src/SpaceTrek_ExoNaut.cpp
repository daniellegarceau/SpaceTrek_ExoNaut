#include "SpaceTrek_ExoNaut.h"
#include <Wire.h>

void exonaut::begin(void){
	ets_serial.begin(115200);
	
	this->set_motor_type(1);
}

void exonaut::set_motor_type(uint8_t motortype){
    if (motortype == 1 || motortype == 2) {
        uint8_t buf[] = {0x55, 0x55, 0x04, 55, 1, 0};
        buf[5] = motortype;
        ets_serial.write(buf,6);
    }
}


int exonaut::set_motor_speed(float new_speed1, float new_speed2){
    uint8_t buf[] = {0x55, 0x55, 0x05, 55, 0x02, 0x00, 0x00};
    float rps1 = (float)(-new_speed1) / 60.0f;
    float rps2 = (float)(-new_speed2) / 60.0f;
    float pps1 = rps1 * 680;
    float pps2 = rps2 * 680;
    buf[5] = (uint8_t)((int)round(pps1 * 0.01f));
    buf[6] = (uint8_t)((int)round(pps2 * 0.01f));
    ets_serial.write(buf,7);
    return 0;
}



void exonaut::Ultrasound(){
	Wire.begin();
	Wire.setClock(90000);
}

//write byte
bool exonaut::wireWriteByte(uint8_t addr, uint8_t val){
	Wire.beginTransmission(addr);
	Wire.write(val);
	if(Wire.endTransmission() != 0){
		return false;
	}
	return true;
}

//Write multiple bytes
bool exonaut::wireWriteDataArray(uint8_t addr, uint8_t reg,uint8_t *val,unsigned int len){
	unsigned int i;
	Wire.beginTransmission(addr);
	Wire.write(reg);
	for(i = 0; i < len; i++){
		Wire.write(val[i]);
	}
	if(Wire.endTransmission() != 0){
		return false;
	}
	return true;
}

//Read specified length of bytes
int exonaut::wireReadDataArray(uint8_t addr, uint8_t reg, uint8_t *val, unsigned int len){
	unsigned char i = 0;  
	if(!wireWriteByte(addr, reg)){				/* Indicate which register we want to read from */
		return -1;
	}
	Wire.requestFrom(addr, len, false);
	while(Wire.available()){					/* Read block data */
		if(i >= len){
			return -1;
		}
		val[i] = Wire.read();
		i++;
    }    
    return i;
}

//Set ultrasonic rgb to breathing light mode
//r1, g1, b1 represent the breathing cycle of the right rgb light, such as 20, 20, 20, which represents a cycle of 2s
//r2, g2, b2 represent the breathing cycle of the left rgb light
void exonaut::Breathing(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2){
	uint8_t breathing[6];
	uint8_t value = RGB_WORK_BREATHING_MODE;
	wireWriteDataArray(ULTRASOUND_I2C_ADDR, RGB_WORK_MODE, &value, 1);
	breathing[0] = r1;breathing[1] = g1;breathing[2] = b1;							//RGB1 Blue
	breathing[3] = r2;breathing[4] = g2;breathing[5] = b2;							//RGB2
	wireWriteDataArray(ULTRASOUND_I2C_ADDR, RGB1_R_BREATHING_CYCLE,breathing,6);	//Send breathing values, (Address, start register, six breathing bytes in RGB[])
}

//Set the color of ultrasonic rgb light
//r1, g1, b1 represent the ratio of the three primary colors of the right rgb light, ranging from 0-255
//r2, g2, b2 represent the ratio of the three primary colors of the left RGB light, ranging from 0-255
void exonaut::Color(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2){
	uint8_t RGB[6];
	uint8_t value = RGB_WORK_SIMPLE_MODE;
	wireWriteDataArray(ULTRASOUND_I2C_ADDR, RGB_WORK_MODE,&value,1);
	RGB[0] = r1;RGB[1] = g1;RGB[2] = b1;											//RGB1
	RGB[3] = r2;RGB[4] = g2;RGB[5] = b2;											//RGB2
	wireWriteDataArray(ULTRASOUND_I2C_ADDR, RGB1_R,RGB,6);							//Send color values, (Address, start register, six color bytes in RGB[])
}

//Get the distance unit measured by ultrasonic wave in mm
uint16_t exonaut::GetDistance(){
	uint16_t distance;
	wireReadDataArray(ULTRASOUND_I2C_ADDR, 0,(uint8_t *)&distance,2);
	return distance;
}