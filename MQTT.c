
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "string.h"
#include "MQTT.h"



#if FREERTOS == 1
#include <cmsis_os.h>
#endif




int M95_SendCommand(char *command, char *reply, uint16_t delay)
{
    HAL_UART_Transmit_IT(UART_M95, (unsigned char *)command,
                         (uint16_t)strlen(command));

#if FREERTOS == 1
    osDelay(delay);
#else
    HAL_Delay(delay);
#endif

    if (strstr(mqtt_buffer, reply) != NULL)
    {
        clearRxBuffer();
        return 0;
    }
    clearRxBuffer();
    return 1;
}
//***********************Clear Rx buffer**********************************************
void clearRxBuffer(void)
{
    rx_index = 0;
    memset(rx_buffer, 0, sizeof(rx_buffer));
}
//***************************************************************************************
//************************ \Clear Mqtt buffer/ ******************************************
void clearMqttBuffer(void)
{
    mqtt_receive = 0;
    mqtt_index = 0;
    memset(mqtt_buffer, 0, sizeof(mqtt_buffer));
}
//***************************************************************************************
//****************************MQTT Init**************************************************
int MQTT_Init(void)
{
    M95.mqttServer.connect = 0;
    int error = 0;
    char str[32] = {0};
    HAL_UART_Receive_IT(UART_M95, &rx_data, 1);

    M95_SendCommand("AT\r\n", "OK\r\n", CMD_DELAY);
    M95_SendCommand("AT&W0\r\n", "OK\r\n", CMD_DELAY);
    error += M95_SendCommand("AT+QCGTIND?\r\n", "SHUT OK\r\n", CMD_DELAY);
    error += M95_SendCommand("AT+CGATT=1\r\n", "OK\r\n", CMD_DELAY);
    error += M95_SendCommand("AT+QISCON?\r\n", "OK\r\n", CMD_DELAY);

    snprintf(str, sizeof(str), "AT+QIREGAPP=\"%s\",\"%s\",\"%s\"\r\n", M95.sim.apn, M95.sim.apn_user,
             M95.sim.apn_pass);
    error += M95_SendCommand(str, "OK\r\n", CMD_DELAY);

    error += M95_SendCommand("AT+QIACT\r\n", "OK\r\n", CMD_DELAY);
    M95_SendCommand("AT+QILOCIP\r\n", "", CMD_DELAY);
    if (error == 0)
    {
        MQTT_Connect();
        return error;
    }
    else
    {
        return error;
    }
}
//***************************************************************************************
// ****************************MQTT_Connector_Checker************************************

int MQTT_Connetor_checker(){

	unsigned char MQTT_connetor_checker;
	M95_Putstring("AT+QMTOPEN=?");
	HAL_Delay(200);
	if(strstr((char*)buffer, "+QMTOPEN:")){ // mqtt connection check 
		MQTT_connetor_checker =1;
		return MQTT_connetor_checker;
	}else if(strstr((char*)buffer, "ERROR ")){
		ERROR_HANDLE("ERROR 04");
		MQTT_connetor_checker= 0;
		return MQTT_connetor_checker;
	}	
	
} 
//***************************************************************************************
void MQTT_CONN(){
	if(MQTT_Status == 1){
		M95_Putstring("AT+QMTCONN?\r\n");
		RS232((char*)buffer);
	}else if(strstr((char*)buffer, "+CME ERROR")){
		ERROR_HANDLE("ERROR 05");
		MQTT_Status =0;
	}
}
//****************************************************************************************
void MQTT_PubUint8(char *topic, uint8_t payload)
{
    char str[32] = {0};
    sprintf(str, "%u", payload);
    MQTT_Pub(topic, str);
}
//*****************************************************************************************
void MQTT_Sub(char *topic)
{
    unsigned char buf[256] = {0};

    MQTTString topicString = MQTTString_initializer;
    topicString.cstring = topic;

    
    HAL_UART_Transmit_IT(UART_SIM800, buf, mqtt_len);
#if FREERTOS == 1
    osDelay(100);
#else
    HAL_Delay(100);
#endif
}