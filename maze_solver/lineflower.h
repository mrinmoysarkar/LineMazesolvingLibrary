//author: Mrinmoy Sarkar
//email:mrinmoy.pol@gmail.com

#ifndef lineflower_h
#define lineflower_h

#include "Arduino.h"
#include "microbot.h"
class lineflower
{
  public:
    int speed;  
    lineflower(microbot _mb,int _kp,int _kd,int _ki,int _threshold,int _speed);
    void calibrate();
    void show_calibrate_data();
    void flow_line();
    void turn(int degree);
    int get_error();
    int error_l;
    int error_r;
    int kp;
  private:
    microbot mb;
    int max_v[8];
    int min_v[8];
    int threshold;
    int kd;
    int ki;
    int previous_error;
    int cumulated_error;
};



#endif
