#include "Signal_Controller.h"
#include "FirstTime_Controller.h"
#include "M95.h"
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "main.h"
//#include "MQTT.h"



unsigned char  Signal_Controll(){

 	static unsigned char SecExec;

 	unsigned char SiM_Flag;
 	if ( SiM_Flag && !SecExec ){

		SecExec = 1;
		return SiM_Flag;
	}
}

//void signal_checking(){
//unsigned char Signal_Status = 0;
//uint8_t SignalStrength =0;
//uint8_t buffer[80] = {0};
//	M95_Putstring("AT+CSQ\r\n");
//	if(strstr((char*)buffer, "+CSQ:")){
//		char *ret;		
//		ret = strchr((char*)buffer,' ');
//		SignalStrength = atio(ret);
//	if (SignalStrength>0 && SignalStrength<31 ){
//			Signal_Status = 1;
//	}else{
//		Signal_Status = 0;
//	//	OLED_SHOW("NO SIGNAl");
//	//	ERROR_HANDLE("ERROR 02");
//	}

//	   }	
//			}


char* SignalQuality(void){    //This is func To Show Status Signal on Oled 
	uint8_t buffer[80] = {0};
	unsigned char Signal_Status = 0;
	uint8_t SignalStrength =0;
	int digit = 27; // Just for Test 
	M95_Putstring("AT+CSQ\r\n");

	if(strstr((char*)buffer, "+CSQ:")){
		char *ret;		
		ret = strchr((char*)buffer,' ');
		
	//	SignalStrength = atio(ret);
			SignalStrength = 30;
	if (SignalStrength>0 && SignalStrength<31 ){
			Signal_Status = 1;
		return "Signal Ok";
		
	}
	else
	{
		return "No Signal";
		
		}
	}
}