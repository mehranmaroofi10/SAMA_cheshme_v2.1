
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "M95.h"
#include "RS232.h"
#include "FirstTime_Controller.h"
//#include "MQTT.h"


uint8_t rx_buffer[30];
uint8_t mqtt_buffer[80];

//uint8_t GSM_start;
void M95_Putstring(char *AT_Command)
{
	UART_HandleTypeDef huart5;
	uint8_t buffer[80] = {0};
  memset(buffer,0,sizeof(buffer));
  HAL_UART_Transmit(&huart5,(uint8_t *)AT_Command,strlen(AT_Command),1000);
  HAL_UART_Receive (&huart5, buffer, 100, 1000);
}

void clearRxBuffer(void)
{
		uint8_t rx_index;
    rx_index = 0;
    memset(rx_buffer, 0, sizeof(rx_buffer));
}

//int M95_SendCommand(char *command, char *reply, uint16_t delay)
//{
//    HAL_UART_Transmit_IT(UART_M95, (unsigned char *)command,
//                         (uint16_t)strlen(command));
//    if (strstr(mqtt_buffer, reply) != NULL)
//    {
//        clearRxBuffer();
//        return 0;
//    }
//    clearRxBuffer();
//    return 1;
//}




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
uint8_t GSM_start;
uint8_t M95_Config=0;
uint8_t buffer[80] = {0};
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
		OLED_SHOW("GSM Config Done");
		HAL_Delay(1000);
		M95_Config =1;
				}
		}
}
