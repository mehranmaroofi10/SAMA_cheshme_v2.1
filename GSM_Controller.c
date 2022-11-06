
#include "GSM_Controller.h"
#include "stm32f4xx_hal.h"
#include "Peripheral_Checking.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "MQTT.h"

unsigned char GSM_Controll(){

 	static unsigned char SecExec;
 	uint8_t gsm_Flag;
 	if ( gsm_Flag && !SecExec ){

		gsm_Flag = 1;
		return  gsm_Flag;
	}

}





void GSM_PowerOn(){
uint8_t gsm_OnFlag;
uint8_t AT_SEND;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
			HAL_Delay(10);
			OLED_SHOW("GSM RUN");
			RS232("GSM RUN");
	M95_Putstring("AT\r\n");
	if( strstr((char*)(buffer), "OK")){                          
		gsm_OnFlag =1;
	}else if (strstr((char*)buffer, "ERROR")){
		gsm_OnFlag =0;
		OLED_SHOW("GSM ERROR");
	}
	
}