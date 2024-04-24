
#ifndef comms_H
#define comms_H


#include "BotleticsSIM7000.h"
Botletics_modem_LTE modem = Botletics_modem_LTE();

//Board Specific Definitions
#define UART_BAUD           9600
#define PIN_DTR             25
#define PIN_TX              27
#define PIN_RX              26
#define PWR_PIN             4

#define samplingRate 10 //Seconds

char imei[16] = {0}; //Device ID
uint8_t type;
uint16_t battLevel = 0; // Battery level (percentage)
float latitude, longitude, speed_kph, heading, altitude, second;
uint16_t year;
uint8_t month, day, hour, minute;
uint8_t counter = 0;

char URL[200];  // Make sure this is long enough for your request URL
char body[100]; // Make sure this is long enough for POST body
char latBuff[12], longBuff[12], locBuff[50], speedBuff[12],
     headBuff[12], altBuff[12], tempBuff[12], battBuff[12];

void initComms();
bool netStatus();





#endif 