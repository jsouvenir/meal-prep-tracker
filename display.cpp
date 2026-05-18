#include <Wire.h>
#include <Arduino.h>
#include "display.h"
#include <LiquidCrystal_I2C.h>
#include "users.h"
#include "cursor.h"
#include "button.h"
#include "sleep.h"


LiquidCrystal_I2C lcd(0x27, 16, 2);
screenState currentState;

void initDisplay() {

  lastActivity = millis();
  int selectedUser = 0;
  Wire.begin(21,22);
  lcd.init();
  lcd.backlight();
  screenState currentState = MAIN_MENU;
  
}

void handleDisplay() {

  
  updateCursor();

}

void handleMenu(ButtonStates buttons) {

  switch (currentState) {
    // Main Menu
    case MAIN_MENU:

      drawMainMenu();

      if(buttons.right) {

        delay(10);
        lastActivity = millis();
        moveCursorRight();
        //beepShort();
      }

      else if(buttons.left) {
        delay(10);

        lastActivity = millis();
        moveCursorLeft();
        //beepShort();
      }


      else if(buttons.select) {

        delay(10);
        Serial.print("button select pressed!");
        lastActivity = millis();
        currentState = USER_EDIT;
        lcd.clear();
        //beepLong();
      }
      
      break;
    
    // User select screen
    case USER_EDIT: 

      drawEditUser();

      if(buttons.right) {

        delay(10);
        lastActivity = millis();
        incrementMeals(selectedUser);
        //beepShort();

      }

      else if(buttons.left) {

        delay(10);
        lastActivity = millis();
        decrementMeals(selectedUser);
        //beepShort();

      }

      else if(buttons.select) {

        delay(10);
        lastActivity = millis();
        lcd.clear();
        
        currentState = MAIN_MENU;
        //beepLong();
      }
      break;

    case SLEEP_MODE:
      
      break;

    }
}