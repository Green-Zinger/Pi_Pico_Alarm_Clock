/**********************************************************************
  Filename    : Drive LiquidCrystal I2C to display characters
  Description : I2C is used to control the display characters of LCD2004.
  Auther      : www.freenove.com
  Modification: 2022/06/28
**********************************************************************/
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "RTClib.h"  

/*
* note:If lcd2004 uses PCF8574T, IIC's address is 0x27,
* or lcd2004 uses PCF8574AT, IIC's address is 0x3F.
*/
LiquidCrystal_I2C lcd(0x27,20,4);
RTC_DS3231 rtc;
int set = 0;

void setup() {
  Wire.begin();
  lcd.init(); // LCD driver initialization
  lcd.backlight(); // Open the backlight
  if (!rtc.begin()) {  
	   lcd.print("RTC NOT FOUND");  
	   while (1);  
	 }  


}
void loop() {
  DateTime now = rtc.now(); 
  lcd.setCursor(0, 0);
  lcd.printf("Time: %02u:%02u:%02u", now.hour(), now.minute(), now.second()); 
  lcd.setCursor(1,0);
  lcd.print("Alarm:");
  if(set==0){
    lcd.print("Not Set");
  }else{
    lcd.print("Set");
  }

}
