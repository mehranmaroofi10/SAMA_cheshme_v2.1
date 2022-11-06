
#include "MQTT_Controller.h"
#include "MQTT.h"
#include "ERROR.h"



unsigned char MQTT_Controll(){

 	static unsigned char SecExec;
 	unsigned char MQTT_Flag;
 	
 	if ( MQTT_Flag && !SecExec ){

		SecExec = 1;
		return MQTT_Flag;
	}
}


int MQTT_Connetor(){

	unsigned char MQTT_Status;

	sprintf(AT_Command, "AT+QMTOPEN=0, \"%s\", \"%d\",60,1\r\n",Host, Port); //second step connect to server
	M95_Putstring(AT_Command);
	RS232((char*)buffer);


	if(strstr((char*)buffer,  "+QMTOPEN: 0,0")){  
		RS232("Connect...\r\n");
		MQTT_Status = 1;
		}else if(strstr((char*)buffer,  "+QMTOPEN: 0,2")){
			MQTT_Status = 0;
			ERROR_HANDLE(" MQTT identifier is occupied ");
		}else {
			MQTT_Status = 0;
			ERROR_HANDLE("ERROR 06");
			}
		return MQTT_Status;	
	}
	
	




