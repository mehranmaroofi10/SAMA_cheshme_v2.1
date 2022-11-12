// state 

#include "RS232.h"
#include "state1.h"
#include "MQTT_Controller.h"
//#include "Signal_Controller.h"
#include "Process_Unit_Type.h"
#include "FirstTime_Controller.h"
#include "peripheral_Checking.h"
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "string.h"

//#include "Signal_Controller.h"



int start(){
	
		OLED_SHOW("switch");
		RS232("switch");
	

	for(int state=1; state <5; state++){
		

	switch (state)
		{
	case 1:
	//	pripheralStatus(&pripheralStatus_var); //?????
		if( firstTime() )
		{
			oled_Logo();
			GSM_PowerOn();
		//	RS232("case 1");
		}
		oled_Display();
		HAL_Delay(1000);
		OLED_SHOW("case1");
		//state = 2;
		
	break;
	case 2:
			OLED_SHOW("case 2");
			HAL_Delay(300);
		if( Peripheral_Controll() && MQTT_Controll() )
		{
				PeripheralStatus();
				MQTT_Connetor();
//			MQTT_Init();
		}
	break;
	
	case 3:
			RS232("case 3");
		if( Processing_Type() == 1 )
		{
			 
			First_Time_On_Server(); // GO To Online Mode && Check in First Time On Server Mode 
			OLED_SHOW("Online Mode");
			HAL_Delay(1000);
		}
			
		else if( Processing_Type() == 2 )
		{
			OLED_SHOW("Off line");
			// Go To Offline Mode
		}
	case 4:
			OLED_SHOW("case 4");	
	break;
	}

}
}
	

void oled_Display(){

////(pripheralStatus[])
		OLED_SHOW("oled_Display");
		HAL_Delay(1100);
		//RS232(" oledDisplay\r\n");
//	  OLED_SHOW((char*)(SignalQuality())); //show On Oled Signal Status
//		 HAL_Delay(5000);

//	OLED_SHOW(SIM_Status_Show()); //show On Oled Sim card

//	OLED_SHOW(Network_Status_Show()); //show On Oled Network Status

//	OLED_SHOW(Server_Status_Show()); //show On Oled online Or Ofline Mode 

}
//void oled_Display(){

//////(pripheralStatus[])
//		RS232(" oledDisplay\r\n");
////	OLED_SHOW(SignalQuality()); //show On Oled Signal Status

////	OLED_SHOW(SIM_Status_Show()); //show On Oled Sim card

////	OLED_SHOW(Network_Status_Show()); //show On Oled Network Status

////	OLED_SHOW(Server_Status_Show()); //show On Oled online Or Ofline Mode 

//}	



void oledDisplay(){
	
RS232(" oledDisplay\r\n");
}
