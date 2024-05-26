#include "robotrun.h"

#define PULSE_COUNT 1120 //一圈的计数 (Rotation Count)

#define BUTTON_A_PIN 0
#define BUTTON_B_PIN 2

bool low_power_flag;
bool action_finish = true;

typedef struct __hw_ir_event_t {
    uint16_t ir_code;
    int8_t event;
} hw_ir_event_t;

// create uart2 instance
hw_uart2_obj_t hw_uart2_obj = {
    .initilized = false,
    .volt = -1,
    // .version[0] = "\0",
};

// IR remote instance
hw_ir_obj_t hw_ir = {
    .ir_key = 0,
    .ir_queue = NULL,
};

//encode motor object instance
hw_encoder_motor_obj_t  hw_encoder_motor = {
    .pulse_p_r = PULSE_COUNT,
    .motor_type = 1,
    .counter_updated = false,
    .speed_1 = 0,
    .speed_2 = 0,
    .count_1 = 0,
    .count_2 = 0,
    .count_base_1 = 0,
    .count_base_2 = 0,
};

inline uint8_t hex2int(uint8_t ch)
{//rx_task
    if (ch >= '0' && ch <= '9') {
        return (ch - '0');
    }
    if (ch >= 'A' && ch <= 'F') {
        return (ch - 'A' + 10);
    }
    if (ch >= 'a' && ch <= 'f') {
        return (ch - 'a' + 10);
    }
    return (uint8_t) -1;
}

#define HEX_TO_INT(high, low)   ((uint8_t)((0xF0 & (((hex2int((high))) << 4))) | (0x0F & (hex2int((low))))))


void rx_task(void *pvParameter)
{
    static uint8_t rx_buf[64];
    static uint8_t cmd_buf[64];
    uint8_t i = 0, index = 0;
    int8_t  rxBytes;
    uint16_t ir_code = 0x0000;
    uint16_t ir_count = 0;
    //static uint32_t low_power_first_ms = 0;

    hw_ir.ir_queue = xQueueCreate(10, sizeof(hw_ir_event_t));
    hw_uart2_obj.initilized = true;

    rx_buf[0] = 0x55;
    rx_buf[1] = 0x55;
    rx_buf[2] = 0x02;
    rx_buf[3] = 0x12;
    // uart_flush(UART2_UART_NUM);
    ets_serial.flush();
    // while(ets_serial.read() >= 0){}
    ets_serial.write(rx_buf,4);

    for (;;) {
        rxBytes = ets_serial.available();
        if (rxBytes > 0) {
            rxBytes = rxBytes > 63 ? 63 : rxBytes;
            ets_serial.readBytes(rx_buf , rxBytes);
            for (i = 0; i < rxBytes; ++i) {
              
                if ('$' == rx_buf[i]) {
                    uint8_t cmd = cmd_buf[0];
                    cmd_buf[index] = '\0';
                    switch (cmd) {
                        case 'A':  /* voltage and recived ir code */
                            if (index == 7) {
                                if(hw_uart2_obj.volt == -1){
                                  hw_uart2_obj.volt = (((float)HEX_TO_INT(cmd_buf[1], cmd_buf[2])) * 51.765f);
                                }else{
                                  hw_uart2_obj.volt = hw_uart2_obj.volt * 0.99f + (((float)HEX_TO_INT(cmd_buf[1], cmd_buf[2])) * 51.765f * 0.01f);
                                }
                                ir_code = ((((uint16_t)(HEX_TO_INT(cmd_buf[5], cmd_buf[6]))) << 8) & 0xFF00) | (HEX_TO_INT(cmd_buf[3], cmd_buf[4]));
                                // if (low_power_flag && hw_uart2_obj.volt > 5000 && hw_uart2_obj.volt < 6300 && !disable_low_power_alarm) {
                                //     if (low_power_first_ms == 0){
                                //         low_power_first_ms = mp_hal_ticks_ms();
                                //     }
                                //     uint32_t cur_ms = mp_hal_ticks_ms();
                                //     if(cur_ms - low_power_first_ms > 8000){
                                //         low_power_flag = false;
                                //         esp_restart();
                                //     }
                                // } else {
                                //   low_power_first_ms = 0;
                                // }
                            }
                            if (index == 3) {
                                action_finish = true;
                            }
                            if (ir_code != hw_ir.ir_key) { /* 按键发生变化(Button state changes) */
                                if (ir_code != 0x00) { /*新的按键不等于0， 就是由没按下变按下(If the new button status is not equal to 0, it means a transition from not pressed to pressed.) */
                                    /* 按键按下(Button is pressed) */
                                    hw_ir_event_t event = {.ir_code = ir_code, .event = 1};
                                    // xQueueSend(hw_ir.ir_queue, &event, 0);
                                } else { /* 新的按键等于等于0，由按下变没按下(When the new button state is not equal to 0, it indicates a transition from not pressed to pressed) */
                                    if (ir_count >= 30) {
                                        /*从长按松开(Release from long press) */
                                        hw_ir_event_t event = {.ir_code = hw_ir.ir_key, .event = 5};
                                        // xQueueSend(hw_ir.ir_queue, &event, 0);
                                    } else {
                                        /*从短按松开(Release from short press) */
                                        hw_ir_event_t event = {.ir_code = hw_ir.ir_key, .event = 2};
                                        // xQueueSend(hw_ir.ir_queue, &event, 0);
                                    }
                                }
                                hw_ir.ir_key = ir_code;
                                ir_count = 0;
                            } else { /* 按键没变(Button state doesn't change) */
                                if (ir_code != 0) {
                                    if (ir_count == 30) {
                                        /* 按键已经被按下没有变化, 看计数，达到则触发长按(The button remains pressed without any change. Check the count, trigger a long press when reached.)*/
                                        hw_ir_event_t event = {.ir_code = ir_code, .event = 4};
                                        // xQueueSend(hw_ir.ir_queue, &event, 0);
                                    }
                                    ++ir_count;
                                } else {
                                    ir_count = 0;
                                }
                            }
                            break;
                        case 'V': /* coprocesser firmware version */
                            if (index == 4) {
                                memcpy(hw_uart2_obj.version, cmd_buf, index);
                                hw_uart2_obj.version[index + 1] = '\0';
                            }
                            break;
                        case 'I':    /* learned ir code */
                            if (index == 4) {
                                if (cmd_buf[1] == 'R' && cmd_buf[2] == 'O' && cmd_buf[3] == 'K') {  /* learnning ok */
                                    // play_tone_c(1000, 100, false);
                                    // play_tone_c(2000, 100, false);
                                }
                            }
                            break;
                        case 'S':
                            if (index == 5) {
                            }
                            break;
                        case 'E':
                            if (cmd_buf[1] == 'M' && cmd_buf[2] == 'M') {
                                union {
                                    uint8_t bytes[8];
                                    int32_t tol[2];
                                } i32a;
                                for (int i = 0, j = 18; i < 8; ++i, j -= 2) {
                                    i32a.bytes[i] = HEX_TO_INT(cmd_buf[j - 1], cmd_buf[j]);
                                }
                                hw_encoder_motor.count_1 = -i32a.tol[0];
                                hw_encoder_motor.count_2 = -i32a.tol[1];
                            }
                        default:
                            break;
                    }
                    memset(cmd_buf, 0, sizeof(cmd_buf));
                    index = 0;
                } else if (!('\n' == rx_buf[i])) {
                    cmd_buf[index++] = rx_buf[i];
                } else {
                    continue;
                }
            }
        }
        delay(20);
    }
}





void robotrun::begin(void)
{
  pinMode(BUTTON_A_PIN,INPUT);
  pinMode(BUTTON_B_PIN,INPUT);
  ets_serial.begin(115200);
  xTaskCreatePinnedToCore(rx_task, "rx_task", 3072, NULL, 2, &hw_rx_task_handle, 0);
  set_motor_speed(0, 0);
  hw_encoder_motor_set_speed_base(0, 0);
  hw_reset_encoder_counter(0);
}

void robotrun::set_motor_speed(int m1, int m2)
{
    uint8_t buf[6] = {0x55, 0x55, 0x04, 0x32, 0x00, 0x00};
    m1 = m1 > 100 ? 100 : m1;
    m2 = m2 > 100 ? 100 : m2;
    m1 = m1 < -100 ? -100 : m1;
    m2 = m2 < -100 ? -100 : m2;
    m1 = -m1;
    m2 = -m2;
    buf[4] = m2 & 0xFF;
    buf[5] = m1 & 0xFF;
    ets_serial.write(buf,6);
}

void robotrun::hw_encoder_motor_set_motor_type(uint8_t motortype)
{
    if (motortype == 1 || motortype == 2) {
        uint8_t buf[] = {0x55, 0x55, 0x04, 55, 1, 0};
        buf[5] = motortype;
        ets_serial.write(buf,6);
        switch (motortype) {
            case 1: {
                hw_encoder_motor.pulse_p_r = PULSE_COUNT;
                break;
            }
            case 2: {
                hw_encoder_motor.pulse_p_r = 1400 + 31;
                break;
            }
            default: {
                hw_encoder_motor.pulse_p_r = PULSE_COUNT;
                break;
            }
        }
    }
}

void robotrun::hw_encoder_motor_set_speed_base(float new_speed1, float new_speed2)
{
    uint8_t buf[] = {0x55, 0x55, 0x05, 55, 0x02, 0x00, 0x00};
    hw_encoder_motor.speed_1 = -new_speed1;
    hw_encoder_motor.speed_2 = -new_speed2;
    //1:55 -> 1:90
    new_speed1 = new_speed1 / 55 * 90;
    new_speed2 = new_speed2 / 55 * 90;

    float rps1 = (float)(-new_speed1) / 60.0f;
    float rps2 = (float)(-new_speed2) / 60.0f;
    float pps1 = rps1 * 680;
    float pps2 = rps2 * 680;
    buf[5] = (uint8_t)((int)round(pps1 * 0.01f));
    buf[6] = (uint8_t)((int)round(pps2 * 0.01f));
    ets_serial.write(buf,7);
}

void robotrun::hw_encoder_motor_set_speed(uint8_t motorid, float new_speed)
{
    /* 输入速度为单位为RPM，转化为RPS， 转化为PPS 转化为 PP10MS(The input speed is in RPM units, converted to RPS, then to PPS, and finally to PP10MS.) */
    float new_speed1 = 0, new_speed2 = 0;
    new_speed1 = -hw_encoder_motor.speed_1;
    new_speed2 = -hw_encoder_motor.speed_2;
    if (motorid == 0) {
        new_speed1 = new_speed;
        new_speed2 = new_speed1;
    } else if (motorid == 1) {
        new_speed1 = new_speed;
    } else if (motorid == 2) {
        new_speed2 = new_speed;
    } else {
    }
    hw_encoder_motor_set_speed_base(new_speed1, new_speed2);
}

void robotrun::hw_reset_encoder_counter(uint8_t motorid)
{
    uint8_t buf[] = {0x55, 0x55, 0x03, 55, 0x03};
    ets_serial.write(buf,5);
    delay(30);
    switch (motorid) {
        case 1: {
            hw_encoder_motor.count_base_1 = hw_encoder_motor.count_1;
            break;
        }
        case 2: {
            hw_encoder_motor.count_base_2 = hw_encoder_motor.count_2;
            break;
        }
        default: {
            hw_encoder_motor.count_base_1 = hw_encoder_motor.count_1;
            hw_encoder_motor.count_base_2 = hw_encoder_motor.count_2;
            break;
        }
    }
}

//获取2个轮子速度 (Acquire the speed of two wheels)
void robotrun::hw_encoder_motor_get_speed(float items[])
{
    items[0] = -hw_encoder_motor.speed_1;
    items[1] = -hw_encoder_motor.speed_2;
}

//获取编码器计数值（即转过的圈数）(Get the encoder count value (i.e., the number of rotations).)
void robotrun::hw_encoder_motor_get_count(float items[])
{
    uint8_t buf[] = {0x55, 0x55, 0x03, 55, 0x03};
    hw_encoder_motor.counter_updated = false;
    ets_serial.write(buf,5);
    delay(30);

    items[0] = (hw_encoder_motor.count_1 - hw_encoder_motor.count_base_1) / hw_encoder_motor.pulse_p_r;
    items[1] = (hw_encoder_motor.count_2 - hw_encoder_motor.count_base_2) / hw_encoder_motor.pulse_p_r;
}

void robotrun::hw_encoder_motor_stop(uint8_t motorid)
{
    uint8_t buf[] = {0x55, 0x55, 0x05, 55, 0x02, 0x00, 0x00};
    float new_speed1 = -hw_encoder_motor.speed_1;
    float new_speed2 = -hw_encoder_motor.speed_2;
    //1:55 -> 1:90
    new_speed1 = new_speed1 / 55 * 90;
    new_speed2 = new_speed2 / 55 * 90;

    float rps1 = (float)(-new_speed1) / 60.0f;
    float rps2 = (float)(-new_speed2) / 60.0f;
    float pps1 = rps1 * 680;
    float pps2 = rps2 * 680;
    buf[5] = (uint8_t)((int)round(pps1 * 0.01f));
    buf[6] = (uint8_t)((int)round(pps2 * 0.01f));
    switch (motorid) {
        case 1: {
            hw_encoder_motor.speed_1 = 0;
            buf[5] = 0;
            break;
        }
        case 2: {
            hw_encoder_motor.speed_2 = 0;
            buf[6] = 0;
            break;
        }
        default: {
            hw_encoder_motor.speed_1 = 0;
            hw_encoder_motor.speed_2 = 0;
            buf[5] = 0;
            buf[6] = 0;
            break;
        }
    }
    ets_serial.write(buf,7);
}

float robotrun::hw_encoder_motor_turn_base(float speed, float angle) //speed单位 度每秒 (Speed unit: degree/second)
{
    float motor_speed = angle > 0 ? 0.2988f * speed : -0.298f * speed;
    float time = (float)(fabs(angle)) / speed * 1000.0f; // 单位 ms (unit: ms)
    hw_encoder_motor_set_speed_base(motor_speed, -motor_speed);
    return time;
}

//以speed度每秒的速度转angle角度(Rotate at a 'speed' degrees per second to specific 'angle')
void robotrun::hw_encoder_motor_turn(float speed, float angle)
{
    float speed_1 = speed;
    float angle_1 = angle;
    float time = hw_encoder_motor_turn_base(speed_1, angle_1);
    delay((int)time);
}



//读取A、B按键值，id参数：1——A按键 ， 2——B按键(Read values of A and B buttons, with ID parameters: 1——A button, 2——B button)
bool robotrun::read_button(uint8_t id)
{
  if(id == 1)
  {
    if(digitalRead(BUTTON_A_PIN) == LOW)
      return true;
    else
      return false;
  }else{
    if(digitalRead(BUTTON_B_PIN) == HIGH)
      return true;
    else
      return false;
  }
}
