#include "ADS.h"
void ADS_init()
{
  I2Cinit();
}

void ADS_SET_IN0()
{
	I2C_Start();
	I2C_SendByte(ADS_ADDR);
	I2C_ReceiveAck();
	I2C_SendByte(REG_config);
	I2C_ReceiveAck();
	I2C_SendByte(config_MSB);
	I2C_ReceiveAck();
  I2C_SendByte(config_LSB);
	I2C_ReceiveAck();
	I2C_Stop();
}

void ADS_SET_IN1()
{
	I2C_Start();
	I2C_SendByte(ADS_ADDR);
	I2C_ReceiveAck();
	I2C_SendByte(REG_config);
	I2C_ReceiveAck();
	I2C_SendByte(config_MSB1);
	I2C_ReceiveAck();
  I2C_SendByte(config_LSB1);
	I2C_ReceiveAck();
	I2C_Stop();
}

void ADS_SET_IN2()
{
	I2C_Start();
	I2C_SendByte(ADS_ADDR);
	I2C_ReceiveAck();
	I2C_SendByte(REG_config);
	I2C_ReceiveAck();
	I2C_SendByte(config_MSB2);
	I2C_ReceiveAck();
  I2C_SendByte(config_LSB2);
	I2C_ReceiveAck();
	I2C_Stop();
}
void ADS_SET_IN3()
{
	I2C_Start();
	I2C_SendByte(ADS_ADDR);
	I2C_ReceiveAck();
	I2C_SendByte(REG_config);
	I2C_ReceiveAck();
	I2C_SendByte(config_MSB3);
	I2C_ReceiveAck();
  I2C_SendByte(config_LSB3);
	I2C_ReceiveAck();
	I2C_Stop();
}

float ADS_RB()
{
  float ret=0; 
  unsigned int ad=0;
	I2C_Start();
	I2C_SendByte(ADS_ADDR);
	I2C_ReceiveAck();
	I2C_SendByte(REG_Conversion);
	I2C_ReceiveAck();

	I2C_Start();
	I2C_SendByte(ADS_ADDR|0x01);
	I2C_ReceiveAck();
	ad=I2C_ReceiveByte();
  ad = (ad<<8)|I2C_ReceiveByte();
	I2C_SendAck(1);
	I2C_Stop();

  if(ad>0x8000)//如果是负压
	{
		ret =(float)(((0xFFFF-ad)*6.144)/32768);//分辨率：6.144÷2^15  电压=分辨率*AD值
	}
  else
	{
		ret =(float)ad*(6.144/32768);
	}

	return ret;
}


