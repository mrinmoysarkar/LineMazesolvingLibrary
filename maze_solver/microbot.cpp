//author: Mrinmoy Sarkar
//email:mrinmoy.pol@gmail.com

#include "microbot.h"

microbot::microbot()
{
  pinMode(LEFT_MOTOR_PINL,OUTPUT);
  pinMode(LEFT_MOTOR_PINR,OUTPUT);
  pinMode(RIGHT_MOTOR_PINL,OUTPUT);
  pinMode(RIGHT_MOTOR_PINR,OUTPUT);
  
  pinMode(DECODER_BIT0,OUTPUT);
  pinMode(DECODER_BIT1,OUTPUT);
  pinMode(DECODER_BIT2,OUTPUT);
  
  pinMode(MUX_SELECTOR_BIT0,OUTPUT);
  pinMode(MUX_SELECTOR_BIT1,OUTPUT);
  pinMode(MUX_SELECTOR_BIT2,OUTPUT);
  
  pinMode(ENCODER_LEFT_A,INPUT);
  pinMode(ENCODER_LEFT_B,INPUT);
  pinMode(ENCODER_RIGHT_A,INPUT);
  pinMode(ENCODER_RIGHT_B,INPUT);
  
  pinMode(BUZZER_PIN,OUTPUT);
  
  pinMode(IR_RECEIVE_PIN,INPUT);
  pinMode(BUTTON_SONOR_RECEIVE_PIN,INPUT);
  pinMode(SONOR_TRIGGER,OUTPUT);
}
void microbot::go_cm(int distance,int speed)
{
  int degree = distance;
  int counter1 = 0;
  int counter2 = 0;
  int state1 = LOW;
  int previous_state1 = LOW;
  int state2 = LOW;
  int previous_state2 = LOW;
  if(degree < 0)
  {
    left_motor_speed(-speed);
    right_motor_speed(-speed);
  }
  else
  {
    left_motor_speed(speed);
    right_motor_speed(speed);
  }
  boolean flag1 = false;
  boolean flag2 = false;
  degree = abs(degree);
  while(true)
  {
    state1 = digitalRead(ENCODER_RIGHT_A);
    state2 = digitalRead(ENCODER_RIGHT_B);
    if(state1 != previous_state1)
    {
      counter1++;
    }
    if(state2 != previous_state2)
    {
      counter2++;
    }
    if(counter1 == degree)
    {
      flag1 = true;
    }
    if(counter2 == degree)
    {
      flag2 = true;
    }
    if(flag1 && flag2)
    {
      break;
    }
    previous_state1 = state1;
    previous_state2 = state2;
    
  }
    left_motor_speed(0);
    right_motor_speed(0);
 
}
void microbot::turn(int degree,int speed)
{
  int counter1 = 0;
  int counter2 = 0;
  int state1 = LOW;
  int previous_state1 = LOW;
  int state2 = LOW;
  int previous_state2 = LOW;
  if(degree < 0)
  {
    left_motor_speed(speed);
    right_motor_speed(-speed);
  }
  else
  {
    left_motor_speed(-speed);
    right_motor_speed(speed);
  }
  boolean flag1 = false;
  boolean flag2 = false;
  degree = 0.147 * abs(degree);
  while(true)
  {
    state1 = digitalRead(ENCODER_RIGHT_A);
    state2 = digitalRead(ENCODER_RIGHT_B);
    if(state1 != previous_state1)
    {
      counter1++;
    }
    if(state2 != previous_state2)
    {
      counter2++;
    }
    if(counter1 == degree)
    {
      flag1 = true;
    }
    if(counter2 == degree)
    {
      flag2 = true;
    }
    if(flag1 && flag2)
    {
      break;
    }
    previous_state1 = state1;
    previous_state2 = state2;
    
  }
    left_motor_speed(0);
    right_motor_speed(0);
}

void microbot::left_motor_speed(int speed)
{
  speed = constrain(speed,-255,255);
  if(speed <= 0)
  {
    analogWrite(LEFT_MOTOR_PINL,abs(speed));
    digitalWrite(LEFT_MOTOR_PINR,LOW);
  }
  else
  {
    analogWrite(LEFT_MOTOR_PINR,abs(speed));
    digitalWrite(LEFT_MOTOR_PINL,LOW);
  }
}
void microbot::right_motor_speed(int speed)
{
  speed = constrain(speed,-255,255);
  if(speed <= 0)
  {
    analogWrite(RIGHT_MOTOR_PINL,abs(speed));
    digitalWrite(RIGHT_MOTOR_PINR,LOW);
  }
  else
  {
    analogWrite(RIGHT_MOTOR_PINR,abs(speed));
    digitalWrite(RIGHT_MOTOR_PINL,LOW);
  }
}
void microbot::blow_buzzer(unsigned int frequency)
{
  if(frequency == 0)
  {
    noTone(BUZZER_PIN);
  }
  else
  {
    tone(BUZZER_PIN,frequency);
  }
}
void microbot::led(byte led_no)
{
  led_no = constrain(led_no,0,7);
  switch(led_no)
  {
    case 0:
      {
          digitalWrite(DECODER_BIT2,LOW);
          digitalWrite(DECODER_BIT1,LOW);
          digitalWrite(DECODER_BIT0,LOW);
      }
      break;
    case 1:
      {
          digitalWrite(DECODER_BIT2,LOW);
          digitalWrite(DECODER_BIT1,LOW);
          digitalWrite(DECODER_BIT0,HIGH);      
      }
      break;
    case 2:
      {
          digitalWrite(DECODER_BIT2,LOW);
          digitalWrite(DECODER_BIT1,HIGH);
          digitalWrite(DECODER_BIT0,LOW);
      }
      break;
    case 3:
      {
          digitalWrite(DECODER_BIT2,LOW);
          digitalWrite(DECODER_BIT1,HIGH);
          digitalWrite(DECODER_BIT0,HIGH);
      }
      break;
    case 4:
      {
          digitalWrite(DECODER_BIT2,HIGH);
          digitalWrite(DECODER_BIT1,LOW);
          digitalWrite(DECODER_BIT0,LOW);      
      }
      break;
    case 5:
      {
          digitalWrite(DECODER_BIT2,HIGH);
          digitalWrite(DECODER_BIT1,LOW);
          digitalWrite(DECODER_BIT0,HIGH);
      }
      break;
    case 6:
      {
          digitalWrite(DECODER_BIT2,HIGH);
          digitalWrite(DECODER_BIT1,HIGH);
          digitalWrite(DECODER_BIT0,LOW);      
      }
      break;
    case 7:
      {
          digitalWrite(DECODER_BIT2,HIGH);
          digitalWrite(DECODER_BIT1,HIGH);
          digitalWrite(DECODER_BIT0,HIGH);
      }
      break;
  }
}
int microbot::read_ir(byte ir_pin)
{
  ir_pin = constrain(ir_pin,0,7);
  switch(ir_pin)
  {
    case 0:
      {
        digitalWrite(MUX_SELECTOR_BIT2,HIGH);
        digitalWrite(MUX_SELECTOR_BIT1,LOW);
        digitalWrite(MUX_SELECTOR_BIT0,HIGH);
        delayMicroseconds(1);
        return analogRead(IR_RECEIVE_PIN); 
      }
      break;
    case 1:
      {
        digitalWrite(MUX_SELECTOR_BIT2,HIGH);
        digitalWrite(MUX_SELECTOR_BIT1,HIGH);
        digitalWrite(MUX_SELECTOR_BIT0,HIGH);
        delayMicroseconds(1);
        return analogRead(IR_RECEIVE_PIN); 
      }
      break;
    case 2:
      {
        digitalWrite(MUX_SELECTOR_BIT2,HIGH);
        digitalWrite(MUX_SELECTOR_BIT1,HIGH);
        digitalWrite(MUX_SELECTOR_BIT0,LOW);
        delayMicroseconds(1);
        return analogRead(IR_RECEIVE_PIN); 
      }
      break;
    case 3:
      {
        digitalWrite(MUX_SELECTOR_BIT2,HIGH);
        digitalWrite(MUX_SELECTOR_BIT1,LOW);
        digitalWrite(MUX_SELECTOR_BIT0,LOW);
        delayMicroseconds(1);
        return analogRead(IR_RECEIVE_PIN); 
      }
      break;
    case 4:
      {
        digitalWrite(MUX_SELECTOR_BIT2,LOW);
        digitalWrite(MUX_SELECTOR_BIT1,HIGH);
        digitalWrite(MUX_SELECTOR_BIT0,LOW);
        delayMicroseconds(1);
        return analogRead(IR_RECEIVE_PIN); 
      }
      break;
    case 5:
      {
        digitalWrite(MUX_SELECTOR_BIT2,LOW);
        digitalWrite(MUX_SELECTOR_BIT1,LOW);
        digitalWrite(MUX_SELECTOR_BIT0,HIGH);
        delayMicroseconds(1);
        return analogRead(IR_RECEIVE_PIN); 
      }
      break;
    case 6:
      {
        digitalWrite(MUX_SELECTOR_BIT2,LOW);
        digitalWrite(MUX_SELECTOR_BIT1,LOW);
        digitalWrite(MUX_SELECTOR_BIT0,LOW);
        delayMicroseconds(1);
        return analogRead(IR_RECEIVE_PIN); 
      }
      break;
      case 7:
      {
        digitalWrite(MUX_SELECTOR_BIT2,LOW);
        digitalWrite(MUX_SELECTOR_BIT1,HIGH);
        digitalWrite(MUX_SELECTOR_BIT0,HIGH);
        delayMicroseconds(1);
        return analogRead(IR_RECEIVE_PIN); 
      }
      break;
  }
  return 0;
}
double microbot::get_distance(byte sonor_pin)
{
  sonor_pin = constrain(sonor_pin,0,4);
  switch(sonor_pin)
  {
    case 0:
      {
        digitalWrite(MUX_SELECTOR_BIT2,LOW);
        digitalWrite(MUX_SELECTOR_BIT1,LOW);
        digitalWrite(MUX_SELECTOR_BIT0,HIGH);
        delayMicroseconds(1);
        digitalWrite(SONOR_TRIGGER,HIGH);
        delayMicroseconds(10);
        digitalWrite(SONOR_TRIGGER,LOW);
        int i = pulseIn(BUTTON_SONOR_RECEIVE_PIN,HIGH);
        double distance = 0.017 * i;//distance in cm
        return distance;
      }
      break;
    case 1:
      {
        digitalWrite(MUX_SELECTOR_BIT2,LOW);
        digitalWrite(MUX_SELECTOR_BIT1,LOW);
        digitalWrite(MUX_SELECTOR_BIT0,LOW);
        delayMicroseconds(1);
        digitalWrite(SONOR_TRIGGER,HIGH);
        delayMicroseconds(10);
        digitalWrite(SONOR_TRIGGER,LOW);
        int i = pulseIn(BUTTON_SONOR_RECEIVE_PIN,HIGH);
        double distance = 0.017 * i;//distance in cm
        return distance;
      }
      break;
    case 2:
      {
        digitalWrite(MUX_SELECTOR_BIT2,LOW);
        digitalWrite(MUX_SELECTOR_BIT1,HIGH);
        digitalWrite(MUX_SELECTOR_BIT0,LOW);
        delayMicroseconds(1);
        digitalWrite(SONOR_TRIGGER,HIGH);
        delayMicroseconds(10);
        digitalWrite(SONOR_TRIGGER,LOW);
        int i = pulseIn(BUTTON_SONOR_RECEIVE_PIN,HIGH);
        double distance = 0.017 * i;//distance in cm
        return distance;
      }
      break;
    case 3:
      {
        digitalWrite(MUX_SELECTOR_BIT2,HIGH);
        digitalWrite(MUX_SELECTOR_BIT1,LOW);
        digitalWrite(MUX_SELECTOR_BIT0,HIGH);
        delayMicroseconds(1);
        digitalWrite(SONOR_TRIGGER,HIGH);
        delayMicroseconds(10);
        digitalWrite(SONOR_TRIGGER,LOW);
        int i = pulseIn(BUTTON_SONOR_RECEIVE_PIN,HIGH);
        double distance = 0.017 * i;//distance in cm
        return distance;
      }
      break;
    case 4:
      {
        digitalWrite(MUX_SELECTOR_BIT2,HIGH);
        digitalWrite(MUX_SELECTOR_BIT1,HIGH);
        digitalWrite(MUX_SELECTOR_BIT0,HIGH);
        delayMicroseconds(1);
        digitalWrite(SONOR_TRIGGER,HIGH);
        delayMicroseconds(10);
        digitalWrite(SONOR_TRIGGER,LOW);
        int i = pulseIn(BUTTON_SONOR_RECEIVE_PIN,HIGH);
        double distance = 0.017 * i;//distance in cm
        return distance;
      }
      break;
  }
  return 0;
}
 
byte microbot::button()
{
  digitalWrite(MUX_SELECTOR_BIT2,HIGH);
  digitalWrite(MUX_SELECTOR_BIT1,HIGH);
  digitalWrite(MUX_SELECTOR_BIT0,LOW);
  delayMicroseconds(1);
  byte val = analogRead(BUTTON_SONOR_RECEIVE_PIN) < 100 ?1:0;
  delay(10); 
  digitalWrite(MUX_SELECTOR_BIT2,HIGH);
  digitalWrite(MUX_SELECTOR_BIT1,LOW);
  digitalWrite(MUX_SELECTOR_BIT0,LOW);
  delayMicroseconds(1);
  val = analogRead(BUTTON_SONOR_RECEIVE_PIN) < 100 ?2:val; 
  if(val>0)
  {
    blow_buzzer(1000);
    delay(200);
    blow_buzzer(0);
  }
  return val;
}
