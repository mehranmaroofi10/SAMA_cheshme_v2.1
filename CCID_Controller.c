#include "peripheral_Checking.h"
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "CCID_Controller.h"
#include "MQTT.h"

unsigned char CCID_Controll(){

 	static unsigned char SecExec;
 	uint8_t CCID_Flag;
 	if ( CCID_Flag && !SecExec ){

		CCID_Flag = 1;
		return  CCID_Flag;
	}

}


void CCID(){
	M95_Putstring("AT+QCCID\r");
	OLED_SHOW((char*)buffer);
	RS232((char*)buffer);
	HAL_Delay(10000);
if(strstr((char*)buffer, " ")){
		
	}
}
