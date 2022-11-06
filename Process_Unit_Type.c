// Select Processing Type In Server or Offline Mode
#include "Process_Unit_Type.h"

int unit;
uint8_t Server;
uint8_t Offline;
uint8_t First_Time_On_ServerFalg;

unsigned char type(){
	static unsigned char Mode;

	if ( Server && !Mode ){
		Mode =1;
		return Mode;
	}
	if ( Offline && !Mode ){
		Mode =2:
		return Mode;
	}
}

// begin of func 
int  Processing_Type(){
//if MQTT Connection is Ok Work on Server Or User Other choose //--- check MQTT Connection in domin mqtt.samacontrol.com 
	int Mode;

	if ( type() == 1){
		Mode = 1;
	}else {
		Mode = 2;
	}
	switch(Mode){
	 	case 1:
	 	// Continue in Server Mode  
	 	return Mode;
	 		break;
	 	case 2:
	 	// Continue in Offline Mode 
	 	return Mode;
	 		break;
	 }		
}	// end of func 

// begin of func 
unsigned char First_Time_On_Server(void){
 	static unsigned char SecExec;
 	

	if ( First_Time_On_ServerFalg && !SecExec ){
		SecExec = 1;
		return First_Time_On_ServerFalg;
	}
	if ( First_Time_On_ServerFalg && !SecExec ){

		First_Time_On_ServerFalg = 0;
	}
	return First_Time_On_ServerFalg;
} // end of func 



// begin of func 
const char* Online_OR_Offline(void){
		char mode[20] = "On line";
	if ( Processing_Type() == 1 ){
		
		return "On line";
	}
	else if( Processing_Type() == 2 ){
		return " off line ";
		printf("Off Line");
	}
} // end of func 

