/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"

#include "string.h"
#include "RS232.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
char AT_Command[80];
uint8_t buffer[50] = {0};
uint16_t Port= 31512;									// Port
char Host[] ="mqtt.samacontrol.com"; //130.185.77.147 // SERVER Name
char clientID[] = "SAMA";

const char Topic[]=  "SAMA/862261042728951";  // client id / Imei

const char TopicToPub[] = "SERVER/862261042728951"; // Send To Server

char  IMEI[] = "862261042728951"; // Wiret On GSM
char  password[] = "\r";

char message[] = "Mehran";

char ctrlZ[1];

// ********************* Flags begin***********************************************/
uint8_t gsm_OnFlag;
uint8_t state=1; 
static uint8_t mqtt_init;
uint8_t CCID[20];


uint8_t conn_flag=0;
uint8_t pub_flag=0;
uint8_t sub=0;
// ********************* Flags end*************************************************/
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define UART_M95 &huart5
#define MAX 40
//#define Ctrl_z  "Ctrl+Z\x1A"
#define Ctrl_z  0x1a
void GSM_PowerOn(void);
void M95_Putstring(char *AT_Command);
void M95_Putchar(uint8_t *data);
void MQTT_Init(void);
void mqttopen(void);
void mqttconn(void);
void mqttsub(void);
void mqttpub(void);
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_UART4_Init(void);
static void MX_UART5_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_UART4_Init();
  MX_UART5_Init();
	GSM_PowerOn();
	MQTT_Init();
  /* USER CODE BEGIN 2 */
	
		if( mqtt_init ==1 ){
			mqttconn();
			
			mqtt_init = 0;
		}
		if ( 		conn_flag ==1 ){
	//	while(!sub){
			RS232("Try\r\n");
			mqttsub();
			conn_flag = 0;
		//}		
		}
		if ( sub ==1 ){
			mqttpub();
			pub_flag =0;
			RS232("Something\r\n");
		} 
		
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		//mqttsub();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 115200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief UART5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART5_Init(void)
{

  /* USER CODE BEGIN UART5_Init 0 */

  /* USER CODE END UART5_Init 0 */

  /* USER CODE BEGIN UART5_Init 1 */

  /* USER CODE END UART5_Init 1 */
  huart5.Instance = UART5;
  huart5.Init.BaudRate = 115200;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART5_Init 2 */

  /* USER CODE END UART5_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB0 PB1 PB2 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void GSM_PowerOn(){  // To On GSM


	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
			HAL_Delay(10);
			//OLED_SHOW("GSM RUN");
			RS232("GSM RUN\r\n");
			gsm_OnFlag = 1;

} //end of func

void M95_Putstring(char *AT_Command)  // This function Use For Send AT Command To GSM M95 And Save Date From Rx In Queue (Mqtt Command)
{ 
		memset(buffer,0,sizeof(buffer));
		HAL_UART_Transmit(UART_M95,(uint8_t *)AT_Command,strlen(AT_Command),100);
		HAL_UART_Receive(UART_M95, (uint8_t*)buffer, 100, 1000); 	
		
}

void M95_Putchar(uint8_t *data)
{
	HAL_UART_Transmit(UART_M95, data, 7,100);
}


void MQTT_Init()
{
	


	for(state=1; state<12; state++){

		
	switch(state){
		case 1:
			M95_Putstring("AT+QIFGCNT=0\r"); // Command Find The Internet 
			RS232((char*)buffer);
			M95_Putstring("AT+QICSGP=1\r"); // Command TO Network
			RS232((char*)buffer);
			M95_Putstring("AT+QIREGAPP\r"); // Start TCPIP Task And Set APN User Name
			RS232((char*)buffer);
			HAL_Delay(100);
		break;
		case 2:
		//	M95_Putstring("AT+QICSGP=1\r"); // Command TO Network
		//	RS232((char*)buffer);
			
			
		break;
		case 3:	
		//	M95_Putstring("AT+QIREGAPP\r"); // Start TCPIP Task And Set APN User Name
		//	RS232((char*)buffer);
			
			
		break;
		case 4:
			M95_Putstring("AT+CTZU=1\r"); //Network Time Synchroization And Up Data The RTC Time
			RS232((char*)buffer);
			
		
		break;
		case 5:
			M95_Putstring("AT+CSCS=\"GSM\"\r"); //GSM Network
			RS232((char*)buffer);
			
		
		break;
		case 6:			
			M95_Putstring("AT+QNITZ=1\r"); //Network Time Synchroization
			RS232((char*)buffer);
			
		
		break;
		case 7:
			M95_Putstring("AT+CTZU=3\r"); //
			RS232((char*)buffer);
			memset(buffer,'\0',sizeof(buffer));
		
		break;
		case 8:
			M95_Putstring("AT+QMTCFG=\"WILL\",0,1,1,1,\"SERVER/");
			RS232((char*)buffer);
			
		break;
		case 9:
			M95_Putstring("\",\"CONNECTION/0\"\r"); //Prints as last message when disconnected
			RS232((char*)buffer);
			
		break;
		case 10:
			M95_Putstring("AT+QMTCFG=\"KEEPALIVE\",0,60\r");
			RS232((char*)buffer);
			
		break;
		case 11:
			
			M95_Putstring("AT&W\r");
			RS232((char*)buffer);
			M95_Putstring("AT+CCID\r");
			RS232((char*)buffer);
			M95_Putstring("AT+CGMR\r");
			RS232((char*)buffer);
			//mqtt_init =1;
			mqttopen();
		}							
	}
}	

void mqttopen(){
	uint8_t J=0;
	while(!mqtt_init){
	sprintf(AT_Command,"AT+QMTOPEN=0,\"%s\",\"%d\",60,1\r", Host , 31512); // Host : "mqtt.samacontrol.com" 130.185.77.147 ---   // port : 31512
	M95_Putstring(AT_Command);
	
	if(strstr((char*)buffer,"+QMTOPEN: 0,0")){
		RS232((char*)buffer);
		RS232("open\r");
		mqtt_init =1;
	}
	else{
		
		RS232((char*)buffer);
		memset(buffer,0,MAX);
		RS232("Can't Open Network:\r\n");
		J++;
			}
		}	
}


void mqttconn(){
	//uint8_t j=0;
	while(!conn_flag){
		RS232(" Connect....\r\n ");
		
		sprintf(AT_Command,"AT+QMTCONN=0,\"%s\",\"%s\",\"%s\"",clientID,IMEI,""); // tcpconnectID, "clientExample" ,"username" ,"password"
		M95_Putstring(AT_Command);
		M95_Putstring("\r");
		if (strstr((char*)buffer,"+QMTCONN: 0,0,0")){
		conn_flag =1;
		RS232((char*)buffer);
		RS232("conn++++++++++++++++++++++++++++\r\n");
	}
	
	//else if (strstr((char*)buffer," +CME ERROR: 3518")){
	else{
		RS232((char*)buffer);
		memset(buffer,0,MAX);
		//M95_Putstring("AT+CFUN= 1,1\r");
			}
		}
}

void mqttsub(){
	while(!sub){
	sprintf(AT_Command,"AT+QMTSUB=0,1,\"%s\",\%d",Topic,1); //  "SAMA/862261042728951"
	M95_Putstring(AT_Command);
	M95_Putstring("\r");
		if (strstr((char*)buffer,"+QMTSUB:")){
			RS232((char*)buffer);
			RS232("sub\r\n");
			sub =1;
	}
		
	else{
		
		RS232((char*)buffer);
		memset(buffer,0,MAX);
		}
	}

}

//void ccid(){
//	M95_Putstring("AT+CCID\r");
//	uint8_t i=0;
//	char ch , *ret;
//	
//	ret = strchr(buffer, '"');
//	memset(ret, ' ', 1);
//	
//	for (i=0; i<20; i++)
//	{
//		ch =ret[i+1];
//		CCID[i]= atoi(&ch);
//	}
//	
//}



 void mqttpub(){
	

	sprintf(AT_Command,"AT+QMTPUB=0,0,0,0,\"SERVER/862261042728951\""); // SERVER And Imei
	M95_Putstring(AT_Command);
	M95_Putstring("\r");
	 

	RS232((char*)buffer);

while(!pub_flag){
		if (strstr((char*)buffer,">")){
		
			M95_Putstring("INFO/SAMA/862261042728951");
			M95_Putstring("/");
			M95_Putstring("89981139000701439019");
			M95_Putstring("/");
			M95_Putstring("M95FAR02A08");
			M95_Putstring("CONNECTION/1\r");
			//M95_Putstring("\r");
			ctrlZ[0]=0x1a;
			M95_Putstring(ctrlZ);
			RS232("Send Message\r\n");
		}
		else{
			RS232((char*)buffer);
			memset(buffer,0,MAX);
			
			}
		
			if (strstr((char*)buffer,"+QMTPUB: 0,0,0")){
				RS232((char*)buffer);
		}
		else{
			RS232((char*)buffer);
			memset(buffer,0,MAX);
			}
		
			if (strstr((char*)buffer,"+QMTRECV:")){
				RS232((char*)buffer);
				pub_flag =1;
		}
		else{
			RS232((char*)buffer);
			memset(buffer,0,MAX);
		}	
	}
}





/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
