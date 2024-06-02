#ifndef DISPLAY_H
#define DISPLAY_H

#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

const int SDA_PIN = 21;
const int SCL_PIN = 22;


#include <Wire.h>
#include <LiquidCrystal_I2C.h>

void display_init();
void display_update();


#endif