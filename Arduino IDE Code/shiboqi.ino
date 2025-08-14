#include <Arduino.h>
#include <WiFi.h>
#include "TLC5620.h"
#include "ADS.h"
#include <cmath>

const char ssd[]="esp32";
const char pasd[]="madaisheng";
WiFiServer server(2526);
WiFiClient client;
int gen[5]={};//0-标识,1-最大值,2-周期,3-占空比

//发生器参数
int t=0;//发生器时间常量
int T=0;//周期
double w=0;//角速度
int t1=0;//0电压输出时间
double k=0;//锯齿波斜率
int ymax=0;//最大输出电压
int rate=0;//占空比

//
int mission=0;//任务代号
uint8_t command[10]={};

int v=0;
uint8_t la=0;
int response=0;
void setup() {
  TLC_init();
  TLC_load(la);
  WiFi.softAP(ssd,pasd);//192.168.4.1
  server.begin();
}

void loop() {
  switch(mission)
  {
    case 0://等待接收客户
    {
        TLC_load(0);
        client=server.available();
        while(!client)
        {
          client=server.available();
        }
        mission=1;
        break;
    }
    case 1://等待客户指令
    {
      while(client.available()<=0)
      {
        if(client.connected())
        {

        }
        else
        {
          mission=0;
          break;
        }
      }
      if(client.connected())
      {
      if(client.available()>0)
      {
        client.read(command,2);
        if(command[1]=='2')
        {
          mission=2;//示波器
        }
        else if(command[1]=='3')
        {
          mission=3;//信号发生器
        }
        else if(command[1]=='1')
        {
          mission=1;
        }
        else
        {
          mission=0;
        }
      }
      }
      break;
    }
    case 2://示波器
    {
      ADS_init();
      ADS_SET_IN1();
      TLC_load(la);
      client.write(((char*)(&response)),4);
      while(1)
      {
        if(client.connected())
        {
          while(client.available()==0);
          client.read(command,1);
          if(command[0])
          {
              
              v=((int)(ADS_RB()*10));
              client.write(((char*)(&v)),4);
              //Serial.println(v);
          }
          else
          {
            client.write(((char*)(&response)),4);
            mission=1;
            break;
          }
        }
        else
        {
          mission=0;
          break;
        }
      }
      break;
    }
    case 3://信号发生器
    {
      client.write(((char*)(&response)),4);
      while(client.available()<=0);
      if(client.available()>0)
      {
        client.read((uint8_t*)gen,20);
      }
      ymax=gen[1];
      T=gen[2];
      rate=gen[3];
      if(gen[0]==1)//正弦
      {
        t=0;
        w=2*3.1415/T;
        int y=0;
        while(1)
        {
          if(client.connected())
          {
          if(client.available()>0)//再次接收到消息就结束
          {
            mission=1;
            break;
          }
          y=(sin(w*t)+1)*ymax/2;
          TLC_load(((uint8_t)(y*255/50)));
          t=t+50-((int)(t/T))*T;
          delayMicroseconds(49);
          }
          else
          {
            mission=0;
            break;
          }
        }
      }
      else if(gen[0]==2)//锯齿波
      {
        int y=0;
        t=0;
        t1=T*rate;
        k=(double)ymax/(T-t1);
        while(1)
        {
          if(client.connected())
          {
          if(client.available()>0)//再次接受到消息就结束
          {
            mission=1;
            break;
          }
          t=0;
          y=0;
          TLC_load(0);
          delayMicroseconds(t1);
          while(y<=ymax&&y<=50)
          {
            TLC_load(((uint8_t)(y*255/50)));
            y=y+k*t;
            delayMicroseconds(49);
            t=t+50;
          }
          }
          else
          {
            mission=0;
          }
        }
      }
      break;
    }
    default:
    break;
  }
}
