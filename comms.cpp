#include "comms.h"

/*

The code uses a mix of Bolteics SIM7000 library and the LilyGo Github Examples to initialize the SIM7000 and work with it.

For more information please read the following links:
LilyGo Github: https://github.com/Xinyuan-LilyGO/LilyGO-T-SIM7000G/tree/master
Botletics SIM7000: https://github.com/botletics/Botletics-SIM7000

*/

Botletics_modem_LTE modem = Botletics_modem_LTE();

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

void initComms(){
    Serial.println("Initializing comms");
    modem.powerOn(PWR_PIN);                                 //Power on the SIM7000
    Serial.println("Modem powered on");
    Serial1.begin(UART_BAUD, SERIAL_8N1, PIN_RX, PIN_TX);   //Initialize Serial1 with Custom RX and TX pins (No Software Serial)
    Serial.println("Serial1 initialized");
    if (! modem.begin(Serial1)) {
        Serial.println(F("Couldn't find modem"));
        while (1); // Don't proceed if it couldn't find the device
    }
    uint8_t imeiLen = modem.getIMEI(imei);
    Serial.println("Getting IMEI");
    if (imeiLen > 0) {
        Serial.print("Module IMEI: "); 
        Serial.println(imei);
    }
    modem.setFunctionality(1);
    /* Adittional Functions & Configurations
    modem.setPreferredMode(38); // Use LTE only, not 2G
    modem.setPreferredLTEMode(1); // Use LTE CAT-M only, not NB-IoT
    modem.setOperatingBand("CAT-M", 12); // AT&T uses band 12
    modem.setNetworkSettings(F("your APN"), F("your username"), F("your password")); //Configure if neccesary
    modem.setHTTPSRedirect(true); //Uncomment if you want to use HTTPS
    modem.enableSleepMode(true);
    modem.set_eDRX(1, 4, "0010");
    modem.enablePSM(true);
    modem.setNetLED(true, 2, 64, 3000); // on/off, mode, timer_on, timer_off
    modem.setNetLED(false); // Disable network status LED
    */

    // Initialize GPS
    while (!modem.enableGPS(true)) {
        Serial.println(F("Failed to turn on GPS, retrying..."));
        delay(2000); // Retry every 2s
    }
    Serial.println(F("Turned on GPS!"));

    // Initialize GPRS
    //Missing  if !modem.enableGPRS(false) before while
    /*
    
    while (!modem.enableGPRS(true)) {
        Serial.println(F("Failed to enable GPRS, retrying..."));
        delay(2000); // Retry every 2s
    }
    Serial.println(F("Enabled GPRS!"));
    */
}


bool netStatus() {
    int n = modem.getNetworkStatus();
    
    Serial.print(F("Network status ")); Serial.print(n); Serial.print(F(": "));
    if (n == 0) Serial.println(F("Not registered"));
    if (n == 1) Serial.println(F("Registered (home)"));
    if (n == 2) Serial.println(F("Not registered (searching)"));
    if (n == 3) Serial.println(F("Denied"));
    if (n == 4) Serial.println(F("Unknown"));
    if (n == 5) Serial.println(F("Registered roaming"));

    if (!(n == 1 || n == 5)) return false;
    else return true;
}

bool getGPS() {
    if (modem.getGPS(&latitude, &longitude, &speed_kph, &heading, &altitude, &year, &month, &day, &hour, &minute, &second)) {
        Serial.print(F("Location: ")); Serial.print(latitude, 6); Serial.print(F(", ")); Serial.println(longitude, 6);
        Serial.print(F("Speed: ")); Serial.print(speed_kph); Serial.println(F(" kph"));
        Serial.print(F("Heading: ")); Serial.print(heading); Serial.println(F(" degrees"));
        Serial.print(F("Altitude: ")); Serial.print(altitude); Serial.println(F(" meters"));
        Serial.print(F("Time: ")); Serial.print(hour); Serial.print(F(":")); Serial.println(minute);
        Serial.print(F("Date: ")); Serial.print(day); Serial.print(F("/")); Serial.print(month); Serial.print(F("/")); Serial.println(year);
        return true;
    }
    else {
        Serial.println(F("Failed to get GPS data"));
        return false;
    }
}

/*

void sendToServer() {
    // Create the URL
    sprintf(URL, "http://yourserver.com/yourscript.php?lat=%s&lon=%s&speed=%s&heading=%s&alt=%s&temp=%s&batt=%s", latBuff, longBuff, speedBuff, headBuff, altBuff, tempBuff, battBuff);
    Serial.print(F("URL: ")); Serial.println(URL);

    // Create the body
    sprintf(body, "{\"lat\":%s,\"lon\":%s,\"speed\":%s,\"heading\":%s,\"alt\":%s,\"temp\":%s,\"batt\":%s}", latBuff, longBuff, speedBuff, headBuff, altBuff, tempBuff, battBuff);
    Serial.print(F("Body: ")); Serial.println(body);

    // Send the data
    if (modem.HTTP_POST(URL, body)) {
        Serial.println(F("Data sent successfully!"));
    }
    else {
        Serial.println(F("Failed to send data"));
    }
}

*/



