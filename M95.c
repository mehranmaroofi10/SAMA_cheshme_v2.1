
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "M95.h"
#include "MQTT.h"
unsigned char M95_Controll(){
 	
static unsigned char SecExec;
uint8_t M95_Flag;

 	if ( M95_Flag && !SecExec ){

		M95_Flag = 1;
		return  M95_Flag;
	}

}



void M95_config()
{

uint8_t M95_Config=0;
uint8_t GSM_start;
while(!M95_Config){
	
	if (GSM_start ==1){
		      
		
		M95_Putstring("AT+QIFGCNT=0\r\n");
		RS232((char*)buffer);
		M95_Putstring("AT+QICSGP=1\r\n");  //Select CSD or GPRS as the Bearer
		RS232((char*)buffer);
		M95_Putstring("AT+CTZU=1\r\n"); //Network Time Synchronization and Update the RTC
		RS232((char*)buffer);
		M95_Putstring("AT+CSCS=\"GSM\"\r\n");  //GSM network command    
		RS232((char*)buffer);
		M95_Putstring("AT+QNITZ=1\r");
		RS232((char*)buffer);
		M95_Putstring("AT+CTZU=3\r"); //Update localized time and time zone to RTC, and save time zone into NVRAM. // ***mode set on 3 
		RS232((char*)buffer);
		M95_Putstring("AT+QMTCFG=\"WILL\",0,1,1,1,\"SERVER/");//When the connection is lost    
		RS232((char*)buffer);
		M95_Putstring("\",\"CONNECTION/0\"\r"); //Prints as last message when disconnected		
		RS232((char*)buffer);
		M95_Putstring("AT+QMTCFG=\"KEEPALIVE\",0,60\r");
		RS232((char*)buffer);
		M95_Putstring("AT&W\r");
		RS232((char*)buffer);
		OLED_SHOW("config...");
		M95_Config =1;
				}
		}
}
