#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "string.h"
#include "RS232.h"

extern huart UART_HandleTypeDef huart4

void RS232(char*data){

	HAL_UART_Transmit(UART_RS232 ,(uint8_t*)data,strlen(data),1000);
}
