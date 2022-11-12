
#include "MQTT_Controller.h"
#include "M95.h"
//#include "MQTT.h"
//#include "ERROR.h"
#include "RS232.h"
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "string.h"	

char AT_Command[80];

unsigned char MQTT_Controll(){

 	static unsigned char SecExec;
 	unsigned char MQTT_Flag;
 	
 	if ( MQTT_Flag && !SecExec ){

		SecExec = 1;
		return MQTT_Flag;
	}
}


int MQTT_Connetor(char *Host, char *Port){
	uint8_t buffer[80] = {0};
	unsigned char MQTT_Status;
	
	sprintf(AT_Command, "AT+QMTOPEN=0, \"%s\", \"%d\",60,1\r\n",Host, *Port); //second step connect to server
	M95_Putstring(AT_Command);
	RS232((char*)buffer);


//	if(strstr((char*)buffer,  "+QMTOPEN: 0,0")){  
		RS232("Connect...\r\n");
		MQTT_Status = 1;
//		}else if(strstr((char*)buffer,  "+QMTOPEN: 0,2")){
			MQTT_Status = 0;
	//		ERROR_HANDLE(" MQTT identifier is occupied ");
//		}else {
//			MQTT_Status = 0;
//			ERROR_HANDLE("ERROR 06");
//			}
//		return MQTT_Status;	
	}
	
	




