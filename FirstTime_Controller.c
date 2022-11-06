
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "string.h"

#include "peripheral_Checking.h"



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

void oled_Logo(){

	RS232("on state1");
	RS232("wellcome\r\n");

	OLED_SHOW(" wellcome");
	HAL_Delay(120);

	OLED_SHOW(" SAMA_CONTROL");
	HAL_Delay(120);

	OLED_SHOW(" arvin algorithm");
	HAL_Delay(120);

	wellcome =1;

}

unsigned char firstTime(){

 	static unsigned char SecExec;
 	
 	if ( FirstTimeFlag && !SecExec ){

		SecExec = 1;
		return FirstTimeFlag;
	}

	if ( FirstTimeFlag && SecExec ){

		FirstTimeFlag = 0;
	}

	return FirstTimeFlag;



} //end of firstTime()	







