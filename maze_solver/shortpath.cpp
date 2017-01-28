//author: Mrinmoy Sarkar
//email:mrinmoy.pol@gmail.com

#include "shortpath.h"
shortpath::shortpath()
{
}
String shortpath::get_short_path(String total_path)
{
  int len = total_path.length();
  int i = 0;
  while(true)
  {
    i = total_path.indexOf("U");
    if(i == -1)
    {
      break;
    }
    i -= 1; 
    String sub = total_path.substring(i,i+3);
    if(sub.equals("LUL") || sub.equals("RUR"))
    {
      total_path = total_path.substring(0,i)+"S"+total_path.substring(i+3,len);
    }
    else if(sub.equals("SUR") || sub.equals("RUS"))
    { 
      total_path = total_path.substring(0,i)+"L"+total_path.substring(i+3,len);
    }
    else if(sub.equals("SUL") || sub.equals("LUS"))
    { 
      total_path = total_path.substring(0,i)+"R"+total_path.substring(i+3,len);
    }
    else if(sub.equals("RUL") || sub.equals("LUR") || sub.equals("SUS"))
    { 
      total_path = total_path.substring(0,i)+"U"+total_path.substring(i+3,len);
    }
  }
  len = total_path.length();
  for(int i = 0;i < len;i++)
  {
    if(total_path[i] == 'R')
    {
      total_path[i] = 'L';
    }
    else if(total_path[i] == 'L')
    {
      total_path[i] = 'R';
    }
  }
  String tem = total_path;
  for(int i = 0;i < len;i++)
  {
    total_path[i] = tem[len-i-1];
  }
  return total_path;
}
//old version
/*
String shortpath::get_short_path(String total_path)
{
  int len = total_path.length();
   for(int i=0;i<len-2;i++)
   { 
    String sub = total_path.substring(i,i+3);
    if(sub.equals("LUL") || sub.equals("RUR"))
    {
      total_path = total_path.substring(0,i)+"S"+total_path.substring(i+3,len);
      len = total_path.length();
     // i=-1;
     i = i == 0?-1:i-2;
    }
    else if(sub.equals("SUR") || sub.equals("RUS"))
    { 
      total_path = total_path.substring(0,i)+"L"+total_path.substring(i+3,len);
      len = total_path.length();
     // i=-1;
     i = i == 0?-1:i-2;
    }
    else if(sub.equals("SUL") || sub.equals("LUS"))
    { 
      total_path = total_path.substring(0,i)+"R"+total_path.substring(i+3,len);
      len = total_path.length();
      //i=-1;
      i = i == 0?-1:i-2;
    }
    else if(sub.equals("RUL") || sub.equals("LUR") || sub.equals("SUS"))
    { 
      total_path = total_path.substring(0,i)+"U"+total_path.substring(i+3,len);
      len = total_path.length();
      //i=-1;
      i = i == 0?-1:i-2;
    }
  }
  len = total_path.length();
  for(int i = 0;i < len;i++)
  {
    if(total_path[i] == 'R')
    {
      total_path[i] = 'L';
    }
    else if(total_path[i] == 'L')
    {
      total_path[i] = 'R';
    }
  }
  String tem = total_path;
  for(int i = 0;i < len;i++)
  {
    total_path[i] = tem[len-i-1];
  }
  return total_path;
}
*/
