
#ifndef COMMS_H
#define COMMS_H


#include "BotleticsSIM7000.h"
//extern Botletics_modem_LTE modem;

//Board Specific Definitions
#define UART_BAUD           9600
#define PIN_DTR             25
#define PIN_TX              27
#define PIN_RX              26
#define PWR_PIN             4

#define samplingRate 10 //Seconds


extern char imei[16];
extern uint8_t type;
extern uint16_t battLevel;
extern float latitude, longitude, speed_kph, heading, altitude, second;
extern uint16_t year;
extern uint8_t month, day, hour, minute;
extern uint8_t counter;

extern char URL[200];  // Make sure this is long enough for your request URL
extern char body[100]; // Make sure this is long enough for POST body
extern char latBuff[12], longBuff[12], locBuff[50], speedBuff[12],
     headBuff[12], altBuff[12], tempBuff[12], battBuff[12];

void initComms();
bool netStatus();
bool getGPS();
void sendToServer();




#endif 