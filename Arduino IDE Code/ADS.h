#ifndef ADS__H
#define ADS__H
#include "ESP_I2C.h"
#include <stdint.h>
#define ADS_ADDR 0x90

#define REG_Conversion 0x00
#define REG_config		 0x01
#define REG_L_thresh 	 0x02
#define REG_H_thresh 	 0x03
 
 
/*****************寄存器EG_Conversion**********/
//存放着16位结果


/*****************寄存器REG_config的位**********/
#define OS 				1 		//操作状态或单发转换启动  （1位）
#define MUX0 			0x04 	//输入多路配置  通道0  （3位）
#define MUX1 			0x05 	//输入多路配置  通道0  （3位）
#define MUX2 			0x06 	//输入多路配置  通道0  （3位）
#define MUX3 			0x07 	//输入多路配置  通道0  （3位）
#define PGA 			0x00	//可编程增益放大器配置  量程 ±6.144  V  （3位）
#define MODE		  0x00	//设备运行方式  连续转换模式  （1位）
#define DR				0x03  //转换速率64SPS  （3位）
#define	COMP_MODE	0 		//比较器模式  传统比较器  （默认）（1位）
#define COMP_POL 	0			//比较器极性  低电平有效  （默认）（1位）
#define COMP_LAT	0 		//锁存比较器  非锁存比较器， 置位后ALERT / RDY引脚不锁存  （默认）（1位）
#define COMP_QUE	0x03 	//比较器置位和禁用  禁用 （默认）（2位）
 
#define config_MSB (OS << 7)|(MUX0 << 4)|(PGA << 1)|(MODE)//OS移动到高8位 MUX移动到高7位 PGA移动到高四位 MODE高一位
#define config_LSB (DR << 5)|(COMP_MODE << 4)|(COMP_POL << 3)|(COMP_LAT << 2)|(COMP_QUE)//DR移动到低8位，COMP_MODE移动到低5位，COMP_POL移动到低4位，COMP_LAT移动到低3位，COMP_QUE最后两位

#define config_MSB1 (OS << 7)|(MUX1 << 4)|(PGA << 1)|(MODE)//OS移动到高8位 MUX移动到高7位 PGA移动到高四位 MODE高一位
#define config_LSB1 (DR << 5)|(COMP_MODE << 4)|(COMP_POL << 3)|(COMP_LAT << 2)|(COMP_QUE)//DR移动到低8位，COMP_MODE移动到低5位，COMP_POL移动到低4位，COMP_LAT移动到低3位，COMP_QUE最后两位

#define config_MSB2 (OS << 7)|(MUX2 << 4)|(PGA << 1)|(MODE)//OS移动到高8位 MUX移动到高7位 PGA移动到高四位 MODE高一位
#define config_LSB2 (DR << 5)|(COMP_MODE << 4)|(COMP_POL << 3)|(COMP_LAT << 2)|(COMP_QUE)//DR移动到低8位，COMP_MODE移动到低5位，COMP_POL移动到低4位，COMP_LAT移动到低3位，COMP_QUE最后两位

#define config_MSB3 (OS << 7)|(MUX3 << 4)|(PGA << 1)|(MODE)//OS移动到高8位 MUX移动到高7位 PGA移动到高四位 MODE高一位
#define config_LSB3 (DR << 5)|(COMP_MODE << 4)|(COMP_POL << 3)|(COMP_LAT << 2)|(COMP_QUE)//DR移动到低8位，COMP_MODE移动到低5位，COMP_POL移动到低4位，COMP_LAT移动到低3位，COMP_QUE最后两位
 
 
/*****************寄存器REG_L_thresh REG_H_thresh值**********/
#define Lo_thresh	0x8000  // 比较器低阈值
#define Hi_thresh 0x7FFF  // 比较器高阈值


void ADS_init();
void ADS_SET_IN0();
void ADS_SET_IN1();
void ADS_SET_IN2();
void ADS_SET_IN3();
float ADS_RB();    //获取电压

#endif