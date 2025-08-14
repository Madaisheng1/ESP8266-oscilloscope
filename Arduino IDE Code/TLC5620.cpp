#include "TLC5620.h"
#include <Arduino.h>
void TLC_sendbit(uint8_t a)//输入一个字节
{
  digitalWrite(TLC_DATA,a);
  TLC_DELAY;
  digitalWrite(TLC_CLK,LOW);
  TLC_DELAY;
  digitalWrite(TLC_CLK,HIGH);
  TLC_DELAY;
}

void TLC_PUTOUT()//输出电压
{
  digitalWrite(TLC_LOAD,LOW);
  TLC_DELAY;
  digitalWrite(TLC_LOAD,HIGH);
  TLC_DELAY;
  digitalWrite(TLC_LDAC,LOW);
  TLC_DELAY;
  digitalWrite(TLC_LDAC,HIGH);
  TLC_DELAY;
}

void TLC_init()//初始化
{
  pinMode(TLC_DATA,OUTPUT);
  pinMode(TLC_CLK,OUTPUT);
  pinMode(TLC_LDAC ,OUTPUT);
  pinMode(TLC_LOAD,OUTPUT);
  digitalWrite(TLC_CLK,HIGH);
  digitalWrite(TLC_LDAC,HIGH);
  digitalWrite(TLC_LOAD,HIGH);
}

void TLC_load(uint8_t val)//加载并输出电压
{
  TLC_sendbit(0);
  TLC_sendbit(1);
  TLC_sendbit(0);
  for(int i=0;i<8;i++)
  {
    if(val&0x80)
    {
      TLC_sendbit(1);
    }
    else
    {
      TLC_sendbit(0);
    }
    val=val<<1;
  }
  TLC_PUTOUT();
}