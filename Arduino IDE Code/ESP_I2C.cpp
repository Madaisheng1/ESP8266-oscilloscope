#include <Arduino.h>
#include "ESP_I2C.h"

void I2Cinit()
{
  pinMode(SCL_PIN,OUTPUT);//设置GPIO2为输出模式
  pinMode(SDA_PIN,OUTPUT);//设置GPIO2为输出模式
}

uint8_t I2C_READ_SDA()
{
  I2C_DELAY;
  return digitalRead(SDA_PIN);
}
//SDA设置输入
void I2CSDA_IN()
{
  pinMode(SDA_PIN,INPUT);
}

void I2CSDA_OUT()
{
  pinMode(SDA_PIN,OUTPUT);
}

void I2C_Start(void)
{
  digitalWrite(SDA_PIN,HIGH);
  I2C_DELAY;
  digitalWrite(SCL_PIN,HIGH);
  I2C_DELAY;
  digitalWrite(SDA_PIN,LOW);
  I2C_DELAY;
  digitalWrite(SCL_PIN,LOW);
  I2C_DELAY;
}


void I2C_Stop(void)
{
  digitalWrite(SDA_PIN,LOW);
  I2C_DELAY;
  digitalWrite(SCL_PIN,HIGH);
  I2C_DELAY;
  digitalWrite(SDA_PIN,HIGH);
  I2C_DELAY;
}


void I2C_SendByte(uint8_t Byte)
{
  uint8_t i;
	for(i=0;i<8;i++)
	{
		if(Byte&0x80)
    {
      digitalWrite(SDA_PIN,HIGH);
      I2C_DELAY;
    }
    else
    {
      digitalWrite(SDA_PIN,LOW);
      I2C_DELAY;
    }
		digitalWrite(SCL_PIN,HIGH);
    I2C_DELAY;
		digitalWrite(SCL_PIN,LOW);
    I2C_DELAY;
    Byte=Byte<<1;
	}
}


uint8_t I2C_ReceiveByte(void)
{
	uint8_t i,Byte=0x00;
	digitalWrite(SDA_PIN,HIGH);
  I2C_DELAY;
  I2CSDA_IN();
	for(i=0;i<8;i++)
	{
		digitalWrite(SCL_PIN,HIGH);
    I2C_DELAY;
		if(I2C_READ_SDA()==1){Byte|=(0x80>>i);}//0000 0000|1000 0000=1000 0000取最高位置1 （I2C_SDA=1 Byte=1 ；I2C_SDA=0 Byte=0）
		digitalWrite(SCL_PIN,LOW);
    I2C_DELAY;
	}
  I2CSDA_OUT();
	return Byte;
}

void I2C_SendAck(uint8_t AckBit)
{
  if(AckBit)
  {
    digitalWrite(SDA_PIN,HIGH);
    I2C_DELAY;
  }
  else
  {
    digitalWrite(SDA_PIN,LOW);
    I2C_DELAY;
  }
	digitalWrite(SDA_PIN,HIGH);
  I2C_DELAY;
	digitalWrite(SCL_PIN,LOW);
  I2C_DELAY;
}

uint8_t I2C_ReceiveAck(void)
{
	uint8_t AckBit;
	digitalWrite(SDA_PIN,HIGH);
  I2C_DELAY;
	digitalWrite(SCL_PIN,HIGH);
  I2C_DELAY;
  I2CSDA_IN();
	AckBit=I2C_READ_SDA();
	digitalWrite(SCL_PIN,LOW);
  I2C_DELAY;
  I2CSDA_OUT();
	return AckBit;
}