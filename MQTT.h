#ifndef __MQTT_H
#define __MQTT_H
#include "stm32f4xx_hal.h"
#include "main.h"
#include "string.h"


#define UART_SIM800 &huart5
#define FREERTOS    0
#define CMD_DELAY   2000

uint8_t rx_data = 0;
uint8_t rx_buffer[1460] = {0};
uint16_t rx_index = 0;

uint8_t mqtt_receive = 0;
char mqtt_buffer[1460] = {0};
uint16_t mqtt_index = 0;

//*****MQTT*********//

//*****MQTT***********//
uint8_t buffer[1000] = {0}; //uart5 buffer
uint8_t MQTT_Publish_Massege =0;
uint8_t MQTT_connetor_checker=0;
uint8_t msg[30]= "mehran";
uint8_t MQTT_Status =0;

char Host[] ="mqtt.samacontrol.com"; //130.185.77.147
uint16_t Port = 31512;
char AT_Command[80];

UART_HandleTypeDef huart5;
UART_HandleTypeDef huart4;



typedef struct {
    char *apn;
    char *apn_user;
    char *apn_pass;
} M95_t;

typedef struct {
    char *host;
    uint16_t port;
    uint8_t connect;
} mqttServer_t;

typedef struct {
    char *username;
    char *pass;
    char *clientID;
    unsigned short keepAliveInterval;
} mqttClient_t;

typedef struct {
    uint8_t newEvent;
    unsigned char dup;
    int qos;
    unsigned char retained;
    unsigned short msgId;
    unsigned char payload[64];
    int payloadLen;
    unsigned char topic[64];
    int topicLen;
} mqttReceive_t;

typedef struct {
    M95_t M95;
    mqttServer_t mqttServer;
    mqttClient_t mqttClient;
    mqttReceive_t mqttReceive;
} MQTT_M95_t;


void M95_Putstring(char *AT_Command);
void OLED_SHOW(char OLED_SHOW_VAL[100]);
int MQTT_Connetor();
int MQTT_Connetor_checker();
void RS232(char*data);
void MQTT_CONN(void );

void OLED_SHOW(char OLED_SHOW_VAL[100]);
void M95_Putstring(char *AT_Command);
int M95_SendCommand(char *command, char *reply, uint16_t delay);

void RS232(char*data);
//void MQTT_Connetor_checker();
void MQTT_Connetor();
void MQTT_CONN();
#endif
