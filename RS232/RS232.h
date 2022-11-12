

#ifndef __RS232_H
#define __RS232_H
#include "stm32f4xx_hal.h"
#define UART_RS232 &huart4
#define RS232_ACTIVE HAL_UART_Transmit(&huart4,(uint8_t*)buffer,strlen(buffer),1000)



void RS232(char*buffer);
#endif