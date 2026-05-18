#include "cursor.h"
#include "users.h"
#include <LiquidCrystal_I2C.h>
#include "display.h"
#include <Arduino.h>



void moveCursorRight() {
  Serial.print("button r pressed!");

  selectedUser++;
  Serial.print(selectedUser);

  //Handle cursor Wrap around
  if(selectedUser > 3)
    selectedUser = 0;
    
}

void moveCursorLeft() {
  Serial.print("button l pressed!");

  selectedUser--;
  Serial.print(selectedUser);
  
  //Handle cursor Wrap around
  if (selectedUser < 0)
    selectedUser = 3;
}

void updateCursor() {

  int row{};
  int col{};
  int lastRow{};
  int lastCol{};


  if(currentState == MAIN_MENU){
    row = selectedUser / 2;
    col = selectedUser % 2 == 0 ? 0 : 8;

  
    if(lastSelectedUser != -1){

      lastRow = lastSelectedUser / 2;
      lastCol = lastSelectedUser % 2 == 0 ? 0 : 8;

      lcd.setCursor(lastCol, lastRow);
      lcd.print(" ");
    }

  
    
      lcd.setCursor(col, row);
      lcd.print(">");

    lastSelectedUser = selectedUser;
  }
}