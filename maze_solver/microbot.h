//author: Mrinmoy Sarkar
//email:mrinmoy.pol@gmail.com

#ifndef microbot_h
#define microbot_h

#include "Arduino.h"
#include <EEPROM.h>

#define LEFT_MOTOR_PINL 9
#define LEFT_MOTOR_PINR 10
#define RIGHT_MOTOR_PINL 6
#define RIGHT_MOTOR_PINR 5

#define DECODER_BIT0 2
#define DECODER_BIT1 3
#define DECODER_BIT2 4

#define MUX_SELECTOR_BIT0 A3
#define MUX_SELECTOR_BIT1 A4
#define MUX_SELECTOR_BIT2 A5

#define ENCODER_LEFT_A 7
#define ENCODER_LEFT_B 8
#define ENCODER_RIGHT_A 12
#define ENCODER_RIGHT_B 13

#define BUZZER_PIN 11

#define IR_RECEIVE_PIN A1

#define BUTTON_SONOR_RECEIVE_PIN A2

#define SONOR_TRIGGER A0


class microbot
{
  public:
    microbot();//
    void left_motor_speed(int speed);//
    void right_motor_speed(int speed);//
    void blow_buzzer(unsigned int frequency);//
    void led(byte led_no);//
    int read_ir(byte ir_pin);//
    double get_distance(byte sonor_pin);//
    byte button();//
    void turn(int degree,int speed);
    void go_cm(int distance,int speed);
  private:
};

#endif
