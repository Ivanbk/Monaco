#include "CAN.h"


//Declare ESP32 pinout to use
SPIClass vspi = SPIClass(VSPI);

//Declare CAN interrupt
volatile bool CANinterrupt = false;

//CAN frame struct from library
struct can_frame frame;

//MCP2515 object instansiation
MCP2515 mcp2515(10);

//IRQ handler function
void irqCAN() {
    CANinterrupt = true;
}

void setMCP2515() {
    mcp2515.reset();
    mcp2515.setBitrate(CAN_125KBPS);
    mcp2515.setNormalMode();
    attachInterrupt(INT_PIN, irqCAN, FALLING);
}

void Can_Loop(){
    if (CANinterrupt) {
        CANinterrupt = false;

        uint8_t irq = mcp2515.getInterrupts();

        if (irq & MCP2515::CANINTF_RX0IF) {
            if (mcp2515.readMessage(MCP2515::RXB0, &frame) == MCP2515::ERROR_OK) {
                //Check can structure for received data & ID

                // frame contains received from RXB0 message
                Serial.print("ID: ");
                Serial.println(frame.can_id, HEX);
                Serial.print("Data: ");
                Serial.println(frame.can_dlc, HEX);
                for (int i = 0; i < frame.can_dlc; i++) {
                    Serial.print(frame.data[i], HEX);
                    Serial.print(" ");
                }   
            }
        }

        if (irq & MCP2515::CANINTF_RX1IF) {
            if (mcp2515.readMessage(MCP2515::RXB1, &frame) == MCP2515::ERROR_OK) {
                // frame contains received from RXB1 message
            }
        }
    }
}