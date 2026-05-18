#include "button.h"
#include <Arduino.h>

void initButtons() {
  pinMode(BTN_RIGHT, INPUT_PULLUP);
  
  pinMode(BTN_LEFT, INPUT_PULLUP);
  
  pinMode(BTN_SELECT, INPUT_PULLUP);
}


ButtonStates readButtons(){

  ButtonStates b;

  b.right = (digitalRead(BTN_RIGHT) == LOW);
  b.left =  (digitalRead(BTN_LEFT) == LOW);
  b.select = (digitalRead(BTN_SELECT) == LOW);

  //returns struct
  return b;
}

/* Reading button press logic true = pressed

bool rightPressed{ digitalRead(BTN_RIGHT) == LOW };
bool leftPressed{ digitalRead(BTN_RIGHT) == LOW };
bool selectPressed{ digitalRead(BTN_SELECT) == LOW };

*/

