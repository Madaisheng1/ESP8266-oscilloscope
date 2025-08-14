#ifndef TLC5620__H
#define TLC5620__H

#include <stdint.h>

#define TLC_DATA 25
#define TLC_CLK  33
#define TLC_LDAC 26
#define TLC_LOAD 27
#define TLC_DELAY delayMicroseconds(1)
void TLC_load(uint8_t val);//加载并输出数据
void TLC_init();//初始化
#endif