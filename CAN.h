#ifndef CAN_H
#define CAN_H

#include "esp32-hal-spi.h"
#include <SPI.h>
#include <mcp2515.h>
#include <Arduino.h>

#define INT_PIN 0

extern SPIClass vspi;
extern volatile bool CAN_interrupt;
extern struct can_frame frame;

void setMCP2515();
void irqCAN();
void Can_Loop();

#endif