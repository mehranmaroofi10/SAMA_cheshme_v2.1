#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "SMS.h"
#include "MQTT.h"






void detect_number(char queue_text[100]){
	
	uint16_t i=0;
	char *ret;
	uint8_t	sms_detect_number=0;
	
	ret = strchr(queue_text,' ""');
	memset(ret, ' ', 1);
	
	if(memcmp(ret , sms_number1, sizeof(sms_number1)) ==0)
	{
		sms_detect_number =1;  //number is detect 
	}
if (sms_detect_number !=0) // no register number
	{
		ret = strchr(queue_text, '\n');
		memset(ret, ' ', 1);
	}	
	
}






void send_sms(){


	sprintf(AT_Command,"AT+CMGF=1\r\n"); //Select SMS Message Format  
	M95_Putstring(AT_Command);
  	memset(buffer,0,sizeof(buffer));
		
  
	sprintf(AT_Command,"AT+CMGS=\"%s\"\r\n",mobileNumber); //AT Command for Send SMS Message
	M95_Putstring(AT_Command);
	HAL_Delay(100);
		
  	sprintf(AT_Command,"Hello mehran%c",0x1a); //value for send as Sms
  	M95_Putstring(AT_Command);

  	memset(buffer,0,sizeof(buffer));		
}
void RecvSMS(){
	
	M95_Putstring("AT+CMGF=1\r\n"); //Select SMS Message Format  
	if(strstr((char*)buffer, "OK")){
		HAL_Delay(5);
	memset(buffer, 0,sizeof(buffer));
	HAL_Delay(200);
	}
	
	M95_Putstring("AT+CSCS=GSM\r\n"); //Select TE Character Set
	if(strstr((char*)buffer, "OK")){
		OLED_SHOW("GSM");
		HAL_Delay(5);
	memset(buffer, 0,sizeof(buffer));
	}
	
while(!RecvSMS1){
	
	sprintf(AT_Command,"AT+CNMI=2,2\r\n"); //New SMS Message Indications
	M95_Putstring(AT_Command);
	if(strstr((char*)buffer, "+CMT:")){
		OLED_SHOW("We have massage");
		HAL_Delay(2000);
			}else if(strstr((char*)buffer, "ERROR")){ //ERROR Report
		OLED_SHOW("ERROR");
			}
				if(strstr((char *)buffer,"ledon"))
      {
				OLED_SHOW("ledon");
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
				
      }
				if(strstr((char *)buffer,"ledoff"))
      {
				OLED_SHOW("ledoff");
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
      }
 }

}