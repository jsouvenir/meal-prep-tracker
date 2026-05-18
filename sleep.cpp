#include "esp_sleep.h"
#include <Arduino.h>
#include "button.h"
#include "users.h"
#include "display.h"

unsigned long lastActivity = 0;
bool sleeping = 0;
void handleSleepTimer() {

    if(millis() - lastActivity > 30000 && !sleeping){

        esp_sleep_enable_ext0_wakeup((gpio_num_t)BTN_SELECT, 0);
        Serial.println("Going to Sleep");

        delay(100);
        lcd.noBacklight();
        lcd.clear();
        
        esp_deep_sleep_start();
        sleeping = 1;

    }
}