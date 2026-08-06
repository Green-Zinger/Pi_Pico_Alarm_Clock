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
#define BUZZER            14//This will set the buzzer as GPIO 14

#define NOT_SET           0//defines constants for set and not set.
#define SET               1   

#define ALARM_TIME        2
#define REG_TIME          3

#define PIN_BUZZER        14//This sets the buzzer transistor to GPIO 14


/*
* note:If lcd2004 uses PCF8574T, IIC's address is 0x27,
* or lcd2004 uses PCF8574AT, IIC's address is 0x3F.
*/
LiquidCrystal_I2C lcd(0x27,20,4);
RTC_DS3231 rtc;
int set = NOT_SET;
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
  pinMode(PIN_SET_BUTTON, INPUT);
  pinMode(PIN_PlUS_BUTTON, INPUT);
  pinMode(PIN_MINUS_BUTTON, INPUT);
  pinMode(PIN_ENTER_BUTTON, INPUT);
  pinMode(BUZZER, INPUT);
}
void loop() {
  displayTime();
  if(alarm_1.hour()==now.hour() && alarm1.minute==now.minute()){//check if alarm went off
    digitalWrite(BUZZER, HIGH);
    lcd.clear()
    lcd.setCursor(0, 0);
    lcd.print("ALARM IS GOING OFF");
    while(!isPressed(PIN_ENTER_BUTTON)){
      if(isPressed(PIN_ENTER_BUTTON)){
        break;
      }
    }
  }

  if(isPressed(PIN_SET_BUTTON)){
    setLoop();
  }

}

bool isPressed(int button){//This code checks a particular button status and includes debouncing.
    bool status =  false;
    if (digitalRead(button) == LOW) {
    delay(20);
    if (digitalRead(button) == LOW) {
      status = true;
    }
    while (digitalRead(PIN_BUTTON) == LOW);
    return status;//returns bool
  }
}

//Displays time on lcd screen stored in the rtc
void displayTime(){
  DateTime now = rtc.now();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.printf("Time: %02u:%02u:%02u", now.hour(), now.minute(), now.second()); 
  lcd.setCursor(0,1);
  lcd.print("Alarm at: %02u:%02u:%02u ", alarm1.hour(), alarm1.minute(), alarm1.second());
  if(set==NOT_SET){
    lcd.print("Not Set");
  }else{
    lcd.print("Set");
  }
}

void setLoop(){//Loop to set alarm or regular time
  bool setAlarm = true;
  bool notSet = true;
  bool changingTime = true;
  lcd.clear();
  while(notSet){
    lcd.setCursor(0, 0);
    if(setAlarm){
      lcd.printf("Set Alarm?")
    }else{
      lcd.printf("Set Time?")
    }
    
    if(isPressed(PIN_MINUS_BUTTON)||isPressed(PIN_PLUS_BUTTON)){
      setAlarm=!setAlarm;
    }

    if(isPressed(PIN_ENTER_BUTTON)){
      settingTime(setAlarm);  
    }
  }
}

void settingTime(bool setAlarm){//set either alarm or regular time
  
  if(setAlarm){
      while(true){//hour set
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Hour: %u", alarm1.hour())
        if(isPressed(PIN_PLUS_BUTTON)){
          if(alarm1.hour==23){
            alarm1.hour == 0;
          }else{
            alarm1.hour++;
          }
        }else if(isPressed(PIN_MINUS_BUTTON)){
          if(alarm1.hour == 0){
            alarm1.hour == 23;
          }else{
            alarm1.hour--;
          }
        }
        
        if(isPressed(PIN_ENTER_BUTTON)){
          break;
        }
      }

      while(true){//minute set
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Minute: %u", alarm1.minute())
        if(isPressed(PIN_PLUS_BUTTON)){
          if(alarm1.minute==59){
            alarm1.minute == 0;
          }else{
            alarm1.minute++;
          }
        }else if(isPressed(PIN_MINUS_BUTTON)){
          if(alarm1.minute == 0){
            alarm1.minute == 59;
          }else{
            alarm1.minute--;
          }
        }
        
        if(isPressed(PIN_ENTER_BUTTON)){
          break;
        }
      }   

  }else{
    DateTime now = rtc.now;
    while(true){//hour set
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Hour: %u", now.hour())
        if(isPressed(PIN_PLUS_BUTTON)){
          if(now.hour==23){
            now.hour == 0;
          }else{
            now.hour++;
          }
        }else if(isPressed(PIN_MINUS_BUTTON)){
          if(now.hour == 0){
            now.hour == 23;
          }else{
            now.hour--;
          }
        }
        
        if(isPressed(PIN_ENTER_BUTTON)){
          break;
        }
      }

      while(true){//minute set
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Minute: %u", now.minute())
        if(isPressed(PIN_PLUS_BUTTON)){
          if(now.minute==59){
            now.minute == 0;
          }else{
            now.minute++;
          }
        }else if(isPressed(PIN_MINUS_BUTTON)){
          if(now.minute == 0){
            now.minute == 59;
          }else{
            now.minute--;
          }
        }
        
        if(isPressed(PIN_ENTER_BUTTON)){
          break;
        }
      }   

    rtc.adjust(now);
  }

}
