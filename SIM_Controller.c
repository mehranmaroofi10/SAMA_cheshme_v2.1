

#include "SIM_Controller.h"
#include "peripheral_Checking.h"
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "MQTT.h"


unsigned char  SIM_Controll(){

 	static unsigned char SecExec;

 	unsigned char SiM_Flag;
 	if ( SiM_Flag && !SecExec ){

		SecExec = 1;
		return SiM_Flag;
	}
}
void SIM_Status(){
uint8_t Sim_Status =0;
	M95_Putstring("AT+QSIMSTAT?\r\n"); 
	if(strstr((char*)buffer, "+QSIMSTAT: 1,1")){       
		Sim_Status = 1;
	}else{
		Sim_Status =0;
		RS232(" NO SIM\r\n");
		ERROR_HANDLE("ERROR 01");
		OLED_SHOW("NO SIM");
	}
}

char* SIM_Status_Show(void){
	
	M95_Putstring("AT+QSIMSTAT?\r\n"); 

	if(strstr((char*)buffer, "+QSIMSTAT: 1,1")){       
		return " SIM Ok ";

	}else{
		
		return " No SIM ";
	}
}