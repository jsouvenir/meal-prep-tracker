#include "display.h"
#include <Arduino.h>
#include "users.h"
#include "button.h"
#include "cursor.h"
#include "sleep.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  initDisplay();
  initButtons();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(250); // this speeds up the simulation


  ButtonStates buttons = readButtons();
  handleMenu(buttons);
  handleDisplay();
  handleSleepTimer();

}
