#include "display.h"

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS); // set the LCD address to 0x27 for a 16 chars and 2 line display

void display_init(){
    Wire.begin(SDA_PIN, SCL_PIN);
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Monaco V1.0");
}

void display_update(){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bat:");
}
