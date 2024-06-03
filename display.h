#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

extern LiquidCrystal_I2C lcd;

const int SDA_PIN = 21;
const int SCL_PIN = 22;

void display_init();
void display_update();


#endif