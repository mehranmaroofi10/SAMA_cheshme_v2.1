// state 

#include "Process_Unit_Type.h"
#include "FirstTime_Controller.h"
#include "peripheral_Checking.h"
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "string.h"



void OLED_SHOW(char OLED_SHOW_VAL[100]);
void M95_Putstring(char *AT_Command);
void RS232(char*data);

int main(){
int state =1;
	
	switch (state)
		{
	case 1:
	//	pripheralStatus(&pripheralStatus_var); //?????
		if( firstTime() )
		{
			oled_Logo();
			GSM_PowerOn();
		}
		oled_Display();
		state = 2;
	break;

	case 2:
		if( Peripheral_Controll()  && MQTT_Controll())
		{
			PeripheralStatus();
			MQTT_Connetor();
			MQTT_Init();
		}
	break;
	
	case 3:
		if( Processing_Type() ==1 )
		{
			 
			First_Time_On_Server(); // GO To Online Mode && Check in First Time On Server Mode 
		}
			
		else if( Processing_Type ==2 )
		{
			// Go To Offline Mode
		}	
	break;
	}

}

	


void oled_Display(){

//(pripheralStatus[])

	OLED_SHOW(SignalQuality()); //show On Oled Signal Status

	OLED_SHOW(SIM_Status_Show()); //show On Oled Sim card

	OLED_SHOW(Network_Status_Show()); //show On Oled Network Status

	OLED_SHOW(Server_Status_Show()); //show On Oled online Or Ofline Mode 

}	



void oledDisplay(){

if(FirstTimeFlag ==1){ 
	printf("hi");
}
}