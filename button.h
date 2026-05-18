#pragma once


#define BTN_RIGHT 33
#define BTN_LEFT 32
#define BTN_SELECT 25

struct ButtonStates {
  bool right;
  bool left;
  bool select;
};

ButtonStates readButtons();

void initButtons();
