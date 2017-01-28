//author: Mrinmoy Sarkar
//email:mrinmoy.pol@gmail.com


#include "microbot.h"
#include "shortpath.h"
#include "lineflower.h"

int threshold = 100;
int kp = 14;
int kd = 1;
int ki = 0;
int speed = 150;
int forward_speed = 120;
int turn_speed = 150;//130
int return_speed = 160;
int time_constant = 250;
const int stop_conter = 140;
int normal_delay = 100;
microbot m;
lineflower bot(m,kp,kd,ki,threshold,speed);
shortpath pathfinder;
int v = 3;
String path="";
boolean flag = false;
boolean btn_option = true;

unsigned long time;// = millis();
unsigned long time1;// = millis();
unsigned long time2;
unsigned long time3;
void setup()
{
  Serial.begin(115200);
}
void loop()
{
  int btn = m.button();
  if(btn == 1)
  {
    if(btn_option)
    {
      bot.calibrate();
      btn_option = false;
    }
    else
    {
      delay(700);
      out_of_circle();
      time = millis();
      time1 = millis();
      time2 = millis();
      time3 = millis();
      int counter1 = 0;
      int stop_counter = 0;
stopr:
      while(stop_counter < stop_conter)//millis()-time<63000)
      {
        bot.flow_line();
        if(bot.error_r > 10 && (millis()-time1)>time_constant)
        {
right_turn:       
          m.left_motor_speed(forward_speed);
          m.right_motor_speed(forward_speed);
          while(bot.error_r > 6 || bot.error_l < -6)
          {
            bot.get_error();
            stop_counter++;
            if(stop_counter > stop_conter) goto stopr;
          }
          stop_counter = 0;
          m.left_motor_speed(0);
          m.right_motor_speed(0);
          m.turn(-90,turn_speed);
          delay(normal_delay);
          m.left_motor_speed(forward_speed);
          m.right_motor_speed(forward_speed);
          while(bot.error_r > 6 || bot.error_l < -6)
          {
            bot.get_error();
          }
          time1 = millis();
          counter1 = 0;
          path += "R";
        }
        else if(bot.error_l < -10 && (millis()-time2)>time_constant)
        {
          counter1 = 0;
          m.left_motor_speed(forward_speed);
          m.right_motor_speed(forward_speed);
          while(bot.error_r > 6 || bot.error_l < -6)
          {
            bot.get_error();
            if(bot.error_r > 10)
            {
              goto right_turn;
            }
          }

          m.left_motor_speed(0);
          m.right_motor_speed(0);
          delay(10);
          bot.get_error();
          if(bot.error_l == 0 && bot.error_r == 0)
          {
            m.turn(90,turn_speed);
            delay(normal_delay);
            m.left_motor_speed(forward_speed);
            m.right_motor_speed(forward_speed);
            while(bot.error_r > 6 || bot.error_l < -6)
            {
              bot.get_error();
            }
            path += "L";
          }
          else
          {
            path += "S";
          }
          time2 = millis();
        }
        else if(bot.error_l == 0 && bot.error_r == 0)
        {
          counter1++;
        }
        if(counter1 > 60 && (millis()-time3)>time_constant)
        {
          m.left_motor_speed(0);
          m.right_motor_speed(0);
          delay(normal_delay);
          m.turn(180,turn_speed);
          delay(normal_delay);
          counter1 = 0;
          time3 = millis();
          path += "U";
        }
      }
      flag = true;
    }
  }
  if(btn == 2)
  {
    delay(700);
    out_of_circle();
    time = millis();
    time1 = millis();
    time2 = millis();
    time3 = millis();
    int counter1 = 0;
    int stop_counter = 0;
stop:
    while(stop_counter < stop_conter)//millis()-time<63000)
    {
      bot.flow_line();
      if(bot.error_l < -10 && (millis()-time1)>time_constant)
      {
left_turn:       
        m.left_motor_speed(forward_speed);
        m.right_motor_speed(forward_speed);
        while(bot.error_r > 6 || bot.error_l < -6)
        {
          bot.get_error();
          stop_counter++;
          if(stop_counter > stop_conter) goto stop;
        }
        stop_counter = 0;
        m.left_motor_speed(0);
        m.right_motor_speed(0);
        m.turn(90,turn_speed);
        delay(normal_delay);
        m.left_motor_speed(forward_speed);
        m.right_motor_speed(forward_speed);
        while(bot.error_r > 6 || bot.error_l < -6)
        {
          bot.get_error();
        }
        time1 = millis();
        counter1 = 0;
        path += "L";
      }
      else if(bot.error_r > 10 && (millis()-time2)>time_constant)
      {
        counter1 = 0;
        m.left_motor_speed(forward_speed);
        m.right_motor_speed(forward_speed);
        while(bot.error_r > 6 || bot.error_l < -6)
        {
          bot.get_error();
          if(bot.error_l < -10)
          {
            goto left_turn;
          }
        }

        m.left_motor_speed(0);
        m.right_motor_speed(0);
        delay(10);
        bot.get_error();
        if(bot.error_l == 0 && bot.error_r == 0)
        {
          m.turn(-90,turn_speed);
          delay(normal_delay);
          m.left_motor_speed(forward_speed);
          m.right_motor_speed(forward_speed);
          while(bot.error_r > 6 || bot.error_l < -6)
          {
            bot.get_error();
          }
          path += "R";
        }
        else
        {
          path += "S";
        }
        time2 = millis();
      }
      else if(bot.error_l == 0 && bot.error_r == 0)
      {
        counter1++;
      }
      if(counter1 > 60 && (millis()-time3)>time_constant)
      {
        m.left_motor_speed(0);
        m.right_motor_speed(0);
        delay(normal_delay);
        m.turn(180,turn_speed);
        delay(normal_delay);
        counter1 = 0;
        time3 = millis();
        path += "U";
      }
    }
    flag = true;
  }
  if(flag)
  {
    m.left_motor_speed(0);
    m.right_motor_speed(0);
    delay(200);
    flag = false;
    //Serial.println(path);
    path = pathfinder.get_short_path(path);
    //Serial.println("short path");
    //Serial.println(path);
    //Serial.println("short path");
    m.turn(180,speed);
    out_of_circle();
    int i = 0;
    bot.speed = return_speed;//new added
    //turn_speed = 150;
    bot.kp = 15;
    time3 = millis();
    while(true)
    {
      if( i == path.length())
      {
        int counterx=0;
        while(counterx<100)
        {
          bot.flow_line();
          if(bot.error_l == 0 && bot.error_r == 0)
          {
            counterx++;
          }
          else
          {
            counterx = 0;
          }
        }
        break;
      }
      bot.flow_line();
      if((bot.error_l < -10 || bot.error_r > 10) && (millis()-time3)>time_constant)
      {
        m.left_motor_speed(forward_speed);
        m.right_motor_speed(forward_speed);
        while(bot.error_r > 6 || bot.error_l < -6)
        {
          bot.get_error();
        }
        m.left_motor_speed(0);
        m.right_motor_speed(0);
        delay(10);
        if(path.charAt(i) == 'L')
        {
          m.turn(90,turn_speed);
          delay(normal_delay);
        }
        else if(path.charAt(i) == 'R')
        {
          m.turn(-90,turn_speed);
          delay(normal_delay);
        }
        i++;
        
        m.left_motor_speed(forward_speed);
        m.right_motor_speed(forward_speed);
        while(bot.error_r > 6 || bot.error_l < -6)
        {
          bot.get_error();
        }
        time3 = millis();
      }
    }
    path = "";
  }
  m.left_motor_speed(0);
  m.right_motor_speed(0);

}
void out_of_circle()
{
    delay(300);
    m.left_motor_speed(forward_speed);
    m.right_motor_speed(forward_speed);
    while(bot.error_r > 6 || bot.error_l < -6)
    {
      bot.get_error();
    }
    m.left_motor_speed(0);
    m.right_motor_speed(0);
    delay(normal_delay);
}
/*
void left_priority()
 {
 unsigned long time = millis();
 unsigned long time1 = millis();
 unsigned long time2 = millis();
 unsigned long time3 = millis();
 int counter1 = 0;
 int stop_counter = 0;
 stop:
 while(stop_counter < stop_conter)//millis()-time<63000)
 {
 bot.flow_line();
 if(bot.error_l < -10 && (millis()-time1)>time_constant)
 {
 left_turn:       
 m.left_motor_speed(speed);
 m.right_motor_speed(speed);
 while(bot.error_r > 6 || bot.error_l < -6)
 {
 bot.get_error();
 stop_counter++;
 if(stop_counter > stop_conter) goto stop;
 }
 stop_counter = 0;
 m.left_motor_speed(0);
 m.right_motor_speed(0);
 m.turn(90,turn_speed);
 delay(10);
 m.left_motor_speed(speed);
 m.right_motor_speed(speed);
 while(bot.error_r > 6 || bot.error_l < -6)
 {
 bot.get_error();
 }
 time1 = millis();
 counter1 = 0;
 path += "L";
 }
 else if(bot.error_r > 10 && (millis()-time2)>time_constant)
 {
 counter1 = 0;
 m.left_motor_speed(speed);
 m.right_motor_speed(speed);
 while(bot.error_r > 6 || bot.error_l < -6)
 {
 bot.get_error();
 if(bot.error_l < -10)
 {
 goto left_turn;
 }
 }
 
 m.left_motor_speed(0);
 m.right_motor_speed(0);
 delay(10);
 bot.get_error();
 if(bot.error_l == 0 && bot.error_r == 0)
 {
 m.turn(-90,turn_speed);
 delay(10);
 m.left_motor_speed(speed);
 m.right_motor_speed(speed);
 while(bot.error_r > 6 || bot.error_l < -6)
 {
 bot.get_error();
 }
 path += "R";
 }
 else
 {
 path += "S";
 }
 time2 = millis();
 }
 else if(bot.error_l == 0 && bot.error_r == 0)
 {
 counter1++;
 }
 if(counter1 > 90 && (millis()-time3)>time_constant)
 {
 m.left_motor_speed(0);
 m.right_motor_speed(0);
 delay(10);
 m.turn(180,turn_speed);
 delay(10);
 counter1 = 0;
 time3 = millis();
 path += "U";
 }
 }
 flag = true;
 }
 
 
 
 void return_to_origin()
 {
 m.left_motor_speed(0);
 m.right_motor_speed(0);
 if(flag)
 {
 delay(200);
 flag = false;
 Serial.println(path);
 path = pathfinder.get_short_path(path);
 Serial.println("short path");
 Serial.println(path);
 Serial.println("short path");
 m.turn(180,speed);
 delay(300);
 m.left_motor_speed(speed);
 m.right_motor_speed(speed);
 while(bot.error_r > 6 || bot.error_l < -6)
 {
 bot.get_error();
 }
 int i = 0;
 while(true)
 {
 if( i == path.length())
 {
 int counterx=0;
 while(counterx<150)
 {
 bot.flow_line();
 if(bot.error_l == 0 && bot.error_r == 0)
 {
 counterx++;
 }
 else
 {
 counterx = 0;
 }
 }
 break;
 }
 bot.flow_line();
 if(bot.error_l < -10 || bot.error_r > 10)
 {
 m.left_motor_speed(speed);
 m.right_motor_speed(speed);
 while(bot.error_r > 6 || bot.error_l < -6)
 {
 bot.get_error();
 }
 m.left_motor_speed(0);
 m.right_motor_speed(0);
 if(path.charAt(i) == 'L')
 {
 m.turn(90,turn_speed);
 }
 else if(path.charAt(i) == 'R')
 {
 m.turn(-90,turn_speed);
 }
 i++;
 delay(10);
 m.left_motor_speed(speed);
 m.right_motor_speed(speed);
 while(bot.error_r > 6 || bot.error_l < -6)
 {
 bot.get_error();
 }
 }
 }
 path = "";
 }
 }
 
 
 
 void right_priority()
 {
 {
 unsigned long time = millis();
 unsigned long time1 = millis();
 unsigned long time2 = millis();
 unsigned long time3 = millis();
 int counter1 = 0;
 int stop_counter = 0;
 stopr:
 while(stop_counter < stop_conter)//millis()-time<63000)
 {
 bot.flow_line();
 if(bot.error_r > 10 && (millis()-time1)>time_constant)
 {
 right_turn:       
 m.left_motor_speed(speed);
 m.right_motor_speed(speed);
 while(bot.error_r > 6 || bot.error_l < -6)
 {
 bot.get_error();
 stop_counter++;
 if(stop_counter > stop_conter) goto stopr;
 }
 stop_counter = 0;
 m.left_motor_speed(0);
 m.right_motor_speed(0);
 m.turn(-90,speed);
 delay(10);
 m.left_motor_speed(speed);
 m.right_motor_speed(speed);
 while(bot.error_r > 6 || bot.error_l < -6)
 {
 bot.get_error();
 }
 time1 = millis();
 counter1 = 0;
 path += "R";
 }
 else if(bot.error_l < -10 && (millis()-time2)>time_constant)
 {
 counter1 = 0;
 m.left_motor_speed(speed);
 m.right_motor_speed(speed);
 while(bot.error_r > 6 || bot.error_l < -6)
 {
 bot.get_error();
 if(bot.error_r > 10)
 {
 goto right_turn;
 }
 }
 
 m.left_motor_speed(0);
 m.right_motor_speed(0);
 delay(10);
 bot.get_error();
 if(bot.error_l == 0 && bot.error_r == 0)
 {
 m.turn(90,speed);
 delay(10);
 m.left_motor_speed(speed);
 m.right_motor_speed(speed);
 while(bot.error_r > 6 || bot.error_l < -6)
 {
 bot.get_error();
 }
 path += "L";
 }
 else
 {
 path += "S";
 }
 time2 = millis();
 }
 else if(bot.error_l == 0 && bot.error_r == 0)
 {
 counter1++;
 }
 if(counter1 > 110 && (millis()-time3)>time_constant)
 {
 m.left_motor_speed(0);
 m.right_motor_speed(0);
 delay(10);
 m.turn(-180,speed);
 delay(10);
 counter1 = 0;
 time3 = millis();
 path += "U";
 }
 }
 flag = true;
 }
 }
 
 
/*
 
 */













/*
 int spd = 150;
 if(Serial.available())
 {
 char b = Serial.read();
 switch(b)
 {
 case '0':
 {
 m.left_motor_speed(spd);
 m.right_motor_speed(spd);
 v=3;
 m.led(3);
 }
 break;
 case '1':
 {
 m.left_motor_speed(-spd);
 m.right_motor_speed(-spd);
 v=4;
 m.led(4);
 }
 break;
 case '2':
 {
 m.left_motor_speed(-spd);
 m.right_motor_speed(spd);
 v=0;
 m.led(0);
 }
 break;
 case '3':
 {
 m.left_motor_speed(spd);
 m.right_motor_speed(-spd);
 v=7;
 m.led(7);
 }
 break;
 case 's':
 {
 m.left_motor_speed(0);
 m.right_motor_speed(0);
 m.blow_buzzer(2000);
 delay(700);
 m.blow_buzzer(0);
 
 }
 default:
 {
 m.led(v);
 }
 break;
 }
 }
 }
 //*/




