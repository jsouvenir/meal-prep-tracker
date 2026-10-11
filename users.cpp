#include "users.h"
#include "display.h"
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#define USER_COUNT 4

int selectedUser{};
int lastSelectedUser{-1};

 RTC_DATA_ATTR User users[4] {
  {"RM", 0},
  {"JS", 0},
  {"JV", 0},
  {"LJ", 0}
};



/*Takes in selected user and increments meals figure out selection
  and button press logic
*/
void incrementMeals(int userID) {
  users[userID].meals++;
}

void decrementMeals(int userID) {
  if (users[userID].meals > 0) {
    users[userID].meals--;
  }
}

//Figure out how to print users based on struct

void drawMainMenu() {
  
  lcd.setCursor(1,0);
  lcd.print(users[0].name);
  lcd.print(": ");
  lcd.print(users[0].meals);


  lcd.setCursor(7,0);
  lcd.print("|");

  lcd.setCursor(9,0);
  lcd.print(users[1].name);
  lcd.print(": ");
  lcd.print(users[1].meals);

  lcd.setCursor(1,1);
  lcd.print(users[2].name);
  lcd.print(": ");
  lcd.print(users[2].meals);

  lcd.setCursor(7,1);
  lcd.print("|");

  lcd.setCursor(9,1);
  lcd.print(users[3].name);
  lcd.print(": ");
  lcd.print(users[3].meals);
}

void drawEditUser(){

  lcd.setCursor(5,0);
  lcd.print(users[selectedUser].name);
  lcd.print(": ");
  lcd.print(users[selectedUser].meals);

  lcd.setCursor(2,1);
  lcd.print("-");

  lcd.setCursor(7,1);
  lcd.print("+");

  lcd.setCursor(12, 1);
  lcd.print("SAVE");

}
