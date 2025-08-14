#ifndef ESP_I2C__
#define ESP_I2C__
#include <stdint.h>

#define SCL_PIN 18
#define SDA_PIN 19
#define I2C_DELAY delayMicroseconds(10)
void I2Cinit();
void I2CSDA_IN();
void I2CSDA_OUT();
void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(uint8_t Byte);
uint8_t I2C_ReceiveByte(void);
void I2C_SendAck(uint8_t AckBit);
uint8_t I2C_ReceiveAck(void);
#endif