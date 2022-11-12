

//#include "MQTT.h"
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "Peripheral_Checking.h"
#include "FirstTime_Controller.h"
#include "SIM_Controller.h"
#include "Signal_Controller.h"
//#include "GSM_Controller.h"
#include "CCID_Controller.h"
#include "M95.h"
#include "Network_Controller.h"
uint8_t Peripheral_Flag;

unsigned char Peripheral_Controll(){

 	static unsigned char SecExec;
	uint8_t Peripheral_Flag;
 	if ( Peripheral_Flag && !SecExec ){

		Peripheral_Flag = 1;
		return  Peripheral_Flag;
		//return 1;
	}

}


int PeripheralStatus(){

	uint16_t PeripheralStatus_flag;
	
		
	if( SIM_Controll() )
	{
		SIM_Status();
			OLED_SHOW("SIM checked");
		HAL_Delay(100);
	}		
	if( Signal_Controll() )
	{
		OLED_SHOW((char*)Signal_Controll());
		HAL_Delay(1000);
		//	signal_checking();
		OLED_SHOW("Signal check");
		HAL_Delay(100);
	}
	if ( network_Controll() )
	{
		Network_Status();
		OLED_SHOW("Network check");
		HAL_Delay(100);
	}
	if ( CCID_Controll() )
	{
		CCID();
		OLED_SHOW("CCID");
		HAL_Delay(100);
	}
	if ( M95_Controll() )
	{
		M95_config();
		OLED_SHOW("M95");
		HAL_Delay(100);
	}

		
 PeripheralStatus_flag =1;

return PeripheralStatus_flag;
}