#include "peripheral_Checking.h"
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "Network_Controller.h"
#include "string.h"
#include "M95.h"
#include "FirstTime_Controller.h"
#include "RS232.h"

unsigned char   network_Controll(){

 	static unsigned char SecExec;

 	unsigned char SiM_Flag;
 	if ( SiM_Flag && !SecExec ){

		SecExec = 1;
		return SiM_Flag;
	}
}

void Network_Status(){
	uint8_t buffer[80] = {0};
uint8_t network_status =0;
	M95_Putstring("QIREGAPP\r");
	if(strstr((char*)buffer, "OK")){
		network_status =1;
	}else{
		OLED_SHOW("INTERNET ERROR");
	//	ERROR_HANDLE("ERROR 03");
		RS232("INTERNET ERROR\r\n");
	}

}


char* Network_Status_Show(void){
	uint8_t buffer[80] = {0};
	
	M95_Putstring("QIREGAPP\r");
	if(strstr((char*)buffer, "OK")){
		return " Network Ok ";
	}else{
		OLED_SHOW("INTERNET ERROR");
//		ERROR_HANDLE("ERROR 03");
		RS232("INTERNET ERROR\r\n");
		return " No Network  ";
	}

}
