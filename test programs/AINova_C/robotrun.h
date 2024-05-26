/**************************************************************
 * company：深圳市幻尔科技有限公司
 * file：WonderCam.h
 * date&&author：20231218 && CuZn
 * brief：AINova板载 ESP32与STM32通讯模块
**************************************************************/
#ifndef ROBOTRUN_H_
#define ROBOTRUN_H_

#include <Arduino.h>
#include <Wire.h>
#include <HardwareSerial.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define ets_serial Serial2

typedef struct __hw_uart_obj_t {
    bool initilized;
    float volt;
    char version[8];
} hw_uart2_obj_t;

typedef struct __hw_ir_obj_t {
    uint16_t ir_key;
    QueueHandle_t ir_queue;
} hw_ir_obj_t;

typedef struct __hw_encoder_motor_obj_t {
    float pulse_p_r;
    uint8_t motor_type;
    bool counter_updated;
    float speed_1;
    float speed_2;
    int32_t count_1;
    int32_t count_2;
    int32_t count_base_1;
    int32_t count_base_2;
} hw_encoder_motor_obj_t;

extern hw_uart2_obj_t hw_uart2_obj;
extern hw_encoder_motor_obj_t hw_encoder_motor;

class robotrun
{
  private:
    //speed单位 度每秒
    float hw_encoder_motor_turn_base(float speed, float angle); 
    void hw_encoder_motor_set_speed_base(float new_speed1, float new_speed2);
    TaskHandle_t hw_rx_task_handle;
  public:
    void begin(void);

    //motor movement
    void set_motor_speed(int m1, int m2);                                 //set normal motor speed
    void hw_encoder_motor_set_motor_type(uint8_t motortype);              //set encoder motor type
    void hw_encoder_motor_set_speed(uint8_t motorid, float new_speed);    //set speed
    void hw_reset_encoder_counter(uint8_t motorid);                       //Reset motorid's encoder motor's encoder count value (i.e. set to 0)
    void hw_encoder_motor_get_speed(float items[]);                       //get speed of both motors
    void hw_encoder_motor_get_count(float items[]);                       //Get the encoder count value (i.e. the number of turns)
    void hw_encoder_motor_stop(uint8_t motorid);                          //stop the motorid's encoder motor
    void hw_encoder_motor_turn(float speed, float angle);                 //rotate angle in degrees per second

    //A & B Buttons
    bool read_button(uint8_t id);                                         //Read the A and B button values, id parameter: 1——A button, 2——B button
};


#endif //ROBOTRUN_H_
