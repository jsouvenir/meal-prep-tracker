#pragma once 

#include "button.h"
#include <LiquidCrystal_I2C.h>
extern LiquidCrystal_I2C lcd;

enum screenState {
  MAIN_MENU,
  USER_EDIT,
  SLEEP_MODE
};

extern screenState currentState;

void handleDisplay();
void initDisplay();
//void sleep();
void handleMenu(ButtonStates buttons);