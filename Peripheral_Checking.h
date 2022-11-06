#ifndef __PERIPHERAL_CHECKING_H
#define __PERIPHERAL_CHECKING_H


#include "MQTT.h"
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "state1.h"
#include "FirstTime_Controller.h"


uint8_t Peripheral_Flag;
uint8_t First_Time_On_ServerFalg;
unsigned char Peripheral_Controll();
int PeripheralStatus();
#endif



