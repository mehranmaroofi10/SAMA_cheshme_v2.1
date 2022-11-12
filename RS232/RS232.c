#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "string.h"
#include "RS232.h"
#include "FirstTime_Controller.h"

void RS232(char*data){
	OLED_SHOW("RS232.............");
	HAL_Delay(100);
	//UART_HandleTypeDef huart4;
	//HAL_UART_Transmit(UART_RS232 ,(uint8_t*)data,strlen(data),1000);
}