//author: Mrinmoy Sarkar
//email:mrinmoy.pol@gmail.com

#include "lineflower.h"
lineflower::lineflower(microbot _mb,int _kp,int _kd,int _ki,int _threshold,int _speed)
{
  mb = _mb;
  kp = _kp;
  ki= _ki;
  kd = _kd;
  threshold = _threshold;
  previous_error = 0;
  cumulated_error = 0;
  speed = _speed;
  
  for(int i = 0; i < 8; i++)
  {
      max_v[i] = 0;
      min_v[i] = 1024;
  }
}
void lineflower::calibrate()
{
  int spd = 100;
  boolean flag = true;
  unsigned long duration = 7000;
  mb.left_motor_speed(spd);
  mb.right_motor_speed(-spd);
  unsigned long start_time = millis();
  while((millis()-start_time) < duration)
  {
    for(int i = 0; i < 8; i++)
    {
      int s_val = mb.read_ir(i);
      max_v[i] = max_v[i] > s_val?max_v[i]:s_val;
      min_v[i] = min_v[i] < s_val?min_v[i]:s_val;
      mb.led(i);
    }
    if(flag && (duration/2)<(millis()-start_time))
    {
      flag = false;
      mb.left_motor_speed(-spd);
      mb.right_motor_speed(spd);
    }
  }
  mb.left_motor_speed(0);
  mb.right_motor_speed(0);
  show_calibrate_data();
  mb.blow_buzzer(10000);
  delay(100);
  mb.blow_buzzer(0);
}
int lineflower::get_error()
{
    error_l = 0;
    error_r = 0;
    for(int i = 0; i < 8; i++)
    {
      int s_val = mb.read_ir(i);
      s_val = constrain(s_val,min_v[i],max_v[i]);
      s_val = map(s_val,min_v[i],max_v[i],0,256);
      if(s_val > threshold)
      {
        mb.led(i);
        switch(i)
        {
          case 0:
          {
            error_l -= 6;
          }
          break;
          case 1:
          {
            error_l -= 3;
          }
          break;
          case 2:
          {
            error_l -= 2;
          }
          break;
          case 3:
          {
            error_l -= 1;
          }
          break;
          case 4:
          {
            error_r += 1;
          }
          break;
          case 5:
          {
            error_r += 2;
          }
          break;
          case 6:
          {
            error_r += 3;
          }
          break;
          case 7:
          {
            error_r += 6;
          }
          break;                   
        }
      }
    }
    return (error_l + error_r);
}



void lineflower::flow_line()
{
  int error = get_error();
  cumulated_error += error;
  int total_error = kp*error + ki*cumulated_error + kd*(error - previous_error);
  mb.left_motor_speed(speed+total_error);
  mb.right_motor_speed(speed-total_error);
  previous_error = error;
}


void lineflower::turn(int degree)
{
  int spd = speed;
  speed = 120;
  if(degree == -90 || degree == 180)
  {
     mb.left_motor_speed(-speed); 
     mb.right_motor_speed(speed);
  }
  else if(degree == 90)
  {
     mb.left_motor_speed(speed); 
     mb.right_motor_speed(-speed);
  }
  if(degree == 90 || degree == -90)
  {
    delay(600);
  }
  else
  {
    delay(1100);
  }
  speed = spd;
}

void lineflower::show_calibrate_data()
{
  Serial.println("calibrated value start:");
  for(int i = 0; i < 8; i++)
  {
      Serial.print("MAX: ");
      Serial.print(max_v[i]);
      Serial.print(" MIN: ");
      Serial.print(min_v[i]);
      Serial.println();
  }
 Serial.println("calibrated value stop:"); 
}
