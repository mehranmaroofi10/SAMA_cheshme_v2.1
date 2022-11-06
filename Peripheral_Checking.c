

#include "MQTT.h"
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "Peripheral_Checking.h"
#include "FirstTime_Controller.h"
#include "GSM_Controller.h"
#include "CCID_Controller.h"
#include "M95.h"
#include "Network_Controller.h"



unsigned char Peripheral_Controll(){

 	static unsigned char SecExec;
 	
 	if ( Peripheral_Flag && !SecExec ){

		Peripheral_Flag = 1;
		return  Peripheral_Flag;
	}

}


int PeripheralStatus(){

	uint16_t PeripheralStatus_flag;
	
		
	if( SIM_Controll() )
	{
		SIM_Status();
	}
	if( Signal_Controll() )
	{
		signal_checking();
	}
	if ( network_Controll() )
	{
		Network_Status();
	}
	if ( CCID_Controll() )
	{
		CCID();
	}
	if ( M95_Controll() )
	{
		M95_config();
	}
		
 PeripheralStatus_flag =1;

return PeripheralStatus_flag;
}