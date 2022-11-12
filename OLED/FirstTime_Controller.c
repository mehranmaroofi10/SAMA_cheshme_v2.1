#include "FirstTime_Controller.h"
#include "RS232.h"
#include "M95.h"
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "string.h"
#include "ssd1306.h" 
#include "ssd1306_fonts.h"

//#include "peripheral_Checking.h"
void OLED_SHOW(char OLED_SHOW_VAL[100])
{
	ssd1306_SetCursor(1,10);
			ssd1306_Fill(Black);
			ssd1306_WriteString(OLED_SHOW_VAL , Font_7x10, White);
			ssd1306_UpdateScreen();		
}




void GSM_PowerOn(){

uint8_t gsm_OnFlag;
uint8_t AT_SEND;
			GSM_PIN_1
			HAL_Delay(1);
			GSM_PIN_2_off
			GSM_PIN_2_on
			HAL_Delay(10);
			OLED_SHOW("GSM RUN");
			RS232("GSM RUN");

	
}

void oled_Logo(){

	RS232("on state1");
	RS232("wellcome\r\n");
	HAL_Delay(100);
	OLED_SHOW(" wellcome");
	HAL_Delay(120);
	HAL_Delay(100);
	OLED_SHOW(" SAMA_CONTROL");
	HAL_Delay(120);
	HAL_Delay(100);
	OLED_SHOW(" arvin algorithm");
	HAL_Delay(120);

	//wellcome =1;

}

unsigned char firstTime(){

 	static unsigned char SecExec;
 	unsigned char FirstTimeFlag=1;
	RS232("fistTime\r\n");
 	if ( FirstTimeFlag && !SecExec ){

		SecExec = 1;
		return FirstTimeFlag;		
	}

	if ( FirstTimeFlag && SecExec ){

		FirstTimeFlag = 0;
	}

	return FirstTimeFlag;
		


} //end of firstTime()	







