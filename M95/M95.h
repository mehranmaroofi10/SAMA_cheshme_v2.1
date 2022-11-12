#ifndef __MQTT_H
#define __MQTT_H
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stm32f4xx_hal.h"

//uint8_t rx_index;
//uint8_t GSM_start; 
#define UART_M95 &huart5


void M95_Putstring(char *AT_Command);
void clearRxBuffer(void);
//int M95_SendCommand(char *command, char *reply, uint16_t delay);
unsigned char M95_Controll();
void M95_config();

#endif