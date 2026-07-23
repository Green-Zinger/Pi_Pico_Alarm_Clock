/**********************************************************************
  Filename    : Drive LiquidCrystal I2C to display characters
  Description : I2C is used to control the display characters of LCD2004.
  Auther      : www.freenove.com
  Modification: 2022/06/28
**********************************************************************/
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "RTClib.h"

#define PIN_SET_BUTTON    10//This block of code will set the buttons as GPIO 10, GPIO 11, GPIO 12, and GPIO 13
#define PIN_PLUS_BUTTON   11
#define PIN_MINUS_BUTTON  12
#define PIN_ENTER_BUTTON  13

#define PIN_BUZZER        14//This sets the buzzer transistor to GPIO 14


/*
* note:If lcd2004 uses PCF8574T, IIC's address is 0x27,
* or lcd2004 uses PCF8574AT, IIC's address is 0x3F.
*/
LiquidCrystal_I2C lcd(0x27,20,4);
RTC_DS3231 rtc;
int set = 0;
DateTime alarm_1 = DateTime(2000, 1, 1, 7, 30, 0);
void setup() {
  Wire.begin();
  lcd.init(); // LCD driver initialization
  lcd.backlight(); // Open the backlight
  if (!rtc.begin()) {  
	   lcd.print("RTC NOT FOUND");  
	   while (1);  
	 }  
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

}
void loop() {
  DateTime now = rtc.now();
  lcd.setCursor(0, 0);
  lcd.printf("Time: %02u:%02u:%02u", now.hour(), now.minute(), now.second()); 
  lcd.setCursor(0,1);
  lcd.print("Alarm:");
  if(set==0){
    lcd.print("Not Set");
  }else{
    lcd.print("Set");
  }
  
  if(alarm_1.hour()==now.hour() && alarm1.minute==now.minute()){

  }

}
