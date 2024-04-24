#include "comms.h"

/*

The code uses a mix of Bolteics SIM7000 library and the LilyGo Github Examples to initialize the SIM7000 and work with it.

For more information please read the following links:
LilyGo Github: https://github.com/Xinyuan-LilyGO/LilyGO-T-SIM7000G/tree/master
Botletics SIM7000: https://github.com/botletics/Botletics-SIM7000

*/


void initComms(){
    Serial.println("Initializing comms");
    Serial1.begin(UART_BAUD, SERIAL_8N1, PIN_RX, PIN_TX);   //Initialize Serial1 with Custom RX and TX pins (No Software Serial)
    modem.powerOn(PWR_PIN);                                 //Power on the SIM7000
    uint8_t imeiLen = modem.getIMEI(imei);
    if (imeiLen > 0) {
        Serial.print("Module IMEI: "); 
        Serial.println(imei);
    }
    modem.setFunctionality(1);
    //modem.setNetworkSettings(F("your APN"), F("your username"), F("your password")); //Configure if neccesary
    //modem.setHTTPSRedirect(true); //Uncomment if you want to use HTTPS

    // Initialize GPS
    while (!modem.enableGPS(true)) {
        Serial.println(F("Failed to turn on GPS, retrying..."));
        delay(2000); // Retry every 2s
    }
    Serial.println(F("Turned on GPS!"));

    // Initialize GPRS
    //Missing  if !modem.enableGPRS(false) before while
    while (!modem.enableGPRS(true)) {
        Serial.println(F("Failed to enable GPRS, retrying..."));
        delay(2000); // Retry every 2s
    }
    Serial.println(F("Enabled GPRS!"));
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



