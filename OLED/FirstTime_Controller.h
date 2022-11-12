#ifndef __FIRSTTIME_CONTROLLER_H
#define __FIRSTTIME_CONTROLLER_H
#include "stm32f4xx_hal.h"


#define GSM_PIN_1      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
#define GSM_PIN_2_off  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
#define GSM_PIN_2_on	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);

//uint8_t wellcome;
void OLED_SHOW(char OLED_SHOW_VAL[100]);
//unsigned char FirstTimeFlag=1;
unsigned char firstTime();
void GSM_PowerOn(void);
void oled_Logo(void);
#endif