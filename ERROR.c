
#include "ERROR.h"


							

void ERROR_HANDLE(char* ERROR_QUEUE[100]){

uint8_t error;

	if (ERROR_QUEUE == "ERROR 01"){
		error =1;
	}
	if (ERROR_QUEUE == "ERROR 02"){
		error =2;
	}
	if (ERROR_QUEUE == "ERROR 03"){
		error =3;
	}
	if (ERROR_QUEUE == "ERROR 04"){
		error = 4;
	}
	if (ERROR_QUEUE == "ERROR 05"){
		error = 5;
	}
	if (ERROR_QUEUE == "ERROR 06"){  //can't Connect to Mqtt 
		error = 6;
	}
	if (ERROR_QUEUE == "ERROR 07"){
		error = 7;
	}
	if (ERROR_QUEUE == "ERROR 08"){
		error = 8;
	}
	else{
		error = 9;
		OLED_SHOW(ERROR_QUEUE);
	}


	swich (error){
	
		case 1:
			OLED_SHOW("ERROR 01");
	break;
		case 2:
			OLED_SHOW("ERROR 02");
	break;
		case 3:
			OLED_SHOW("ERROR 03");
	break;
		case 4:
			OLED_SHOW("ERROR 04");
	break;
		case 5:
			OLED_SHOW("ERROR 05");
	break;
		case 6:
			OLED_SHOW("ERROR 06 ");
	break;
		case 7:
			OLED_SHOW("ERROR 07");
		}
	break;
		case 8:
			OLED_SHOW("ERROR 08");
		
	}

