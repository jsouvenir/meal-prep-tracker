# meal-prep-tracker

A compact fridge companion for tracking how many prepped meals each person has left. Built on an ESP32 with a 16x2 I2C LCD and three buttons. Four users share one device, each with their own meal counter, and the board drops into deep sleep when idle to save power.

<!-- Add your video here. On GitHub, edit this file in the web editor and drag the video
     into the editor; GitHub uploads it and inserts a link that renders as an inline player.
     Or link it: [![Demo](thumbnail.png)](https://your-video-link) -->
# Virtual Demo
https://github.com/user-attachments/assets/38fbccf8-f348-4351-8f5b-e973597e4876

# Physical Implementation
<img width="450" height="410" alt="Screenshot 2026-10-09 at 11 26 42 PM" src="https://github.com/user-attachments/assets/338ec6f8-8d90-4079-87ed-9627c135a541" />


## Features

- **Four users, one device.** Each user has a two-letter tag and a meal counter (defaults: `RM`, `JS`, `JV`, `LJ`).
- **Three-button interface.** Left, right and select are enough to navigate the whole UI.
- **Two screens.** A 2x2 main menu showing every user's count, and an edit screen for adjusting one user's count.
- **Wrap-around cursor.** Moving past the last user loops back to the first, and vice versa.
- **Deep sleep.** After 30 seconds without a button press the backlight turns off and the ESP32 enters deep sleep. Pressing select wakes it.
- **Counts survive sleep.** Meal counts live in RTC memory, so they are still there when the device wakes up.

## How it works

### Main menu

All four users are shown in a 2x2 grid with a `>` cursor next to the selected user.

```
 RM: 3 | JS: 2
 JV: 0 | LJ: 5
```

| Button | Action |
| ------ | ------ |
| Left   | Move cursor to the previous user (wraps around) |
| Right  | Move cursor to the next user (wraps around) |
| Select | Open the edit screen for the highlighted user |

### Edit screen

Shows the selected user's tag and count, with `-`, `+` and `SAVE` labels along the bottom row.

```
     RM: 3
  -    +    SAVE
```

| Button | Action |
| ------ | ------ |
| Left   | Decrease the meal count by one |
| Right  | Increase the meal count by one |
| Select | Return to the main menu |

Changes apply immediately to the stored count. Select simply takes you back to the main menu.

### Sleep and wake

Every button press resets an inactivity timer. After 30 seconds with no activity the device turns off the LCD backlight, clears the screen and enters deep sleep. Press the **select** button to wake it. On wake the ESP32 restarts the sketch from the top, restores the user counts from RTC memory and shows the main menu.

## Hardware

| Part | Notes |
| ---- | ----- |
| ESP32 development board | Any board that exposes GPIO 21, 22, 25, 32 and 33 |
| 16x2 character LCD with I2C backpack | Code expects I2C address `0x27` |
| 3 momentary push buttons | Wired between the GPIO and GND (internal pull-ups are used) |
| USB cable or other 5V supply | Power and programming |

### Wiring

| Signal | ESP32 pin |
| ------ | --------- |
| LCD SDA | GPIO 21 |
| LCD SCL | GPIO 22 |
| LCD VCC / GND | Per your module (commonly 5V and GND) |
| Left button | GPIO 32 to GND |
| Right button | GPIO 33 to GND |
| Select button | GPIO 25 to GND |

Buttons are active low: the pins use `INPUT_PULLUP`, so a press pulls the pin to GND. No external resistors are needed. GPIO 25 is also the deep sleep wake-up source, so the select button must stay on that pin (or you must change the wake-up pin in `sleep.cpp`).

## Getting started

### Prerequisites

- [Arduino IDE](https://www.arduino.cc/en/software) (or `arduino-cli`)
- The Espressif **esp32** board package
- The **LiquidCrystal_I2C** library (install from the Library Manager, and make sure the version you pick works with ESP32)

### Build and flash

1. Clone the repo:
   ```bash
   git clone https://github.com/jsouvenir/meal-prep-tracker.git
   ```
2. The Arduino IDE requires a sketch folder to have the same name as its `.ino` file. Since the entry file is `main.ino`, either rename the folder to `main` or let the IDE offer to move it into a `main` folder when you open it.
3. Open `main.ino`.
4. Select your board (for example **ESP32 Dev Module**) and the correct serial port.
5. Upload.
6. Optional: open the Serial Monitor at **115200 baud** to see debug output for button presses and sleep events.

## Project structure

| File | Responsibility |
| ---- | -------------- |
| `main.ino` | Entry point. `setup()` initializes serial, display and buttons. `loop()` runs the main cycle |
| `button.h` / `button.cpp` | Pin definitions, `INPUT_PULLUP` setup and `readButtons()`, which returns a `ButtonStates` struct |
| `display.h` / `display.cpp` | LCD instance, `screenState` enum, and `handleMenu()` which is the button-driven state machine |
| `users.h` / `users.cpp` | User data (`users[4]`), selection state, increment/decrement, and the two screen draw functions |
| `cursor.h` / `cursor.cpp` | Moves the selection and draws the `>` marker on the main menu |
| `sleep.h` / `sleep.cpp` | Inactivity timer, wake-up source setup and deep sleep entry |

### Main loop

Every 250 ms the loop runs these steps in order:

1. `readButtons()` samples the three buttons.
2. `handleMenu()` draws the current screen and reacts to button input.
3. `handleDisplay()` updates the cursor marker.
4. `handleSleepTimer()` checks the inactivity timer and sleeps if it has expired.

### Screen states

| State | Meaning |
| ----- | ------- |
| `MAIN_MENU` | Showing all users, choosing one |
| `USER_EDIT` | Adjusting the selected user's count |
| `SLEEP_MODE` | Declared but not used yet; sleep is handled directly in `sleep.cpp` |

## Configuration

| What to change | Where |
| -------------- | ----- |
| User tags and starting counts | `users[4]` in `users.cpp` (tags are 2 characters) |
| Button pins | `BTN_LEFT`, `BTN_RIGHT`, `BTN_SELECT` in `button.h` |
| I2C address or LCD size | `LiquidCrystal_I2C lcd(0x27, 16, 2)` in `display.cpp` |
| I2C pins | `Wire.begin(21, 22)` in `display.cpp` |
| Sleep timeout | The `30000` (milliseconds) check in `handleSleepTimer()` in `sleep.cpp` |
| Loop and button repeat speed | `delay(250)` in `main.ino` |

Changing the number of users is more involved. You would need to update the array size in `users.h` and `users.cpp`, the cursor wrap-around values in `cursor.cpp`, and the layout in `drawMainMenu()`, since a 16x2 display fits four entries at most in the current layout.

## Behavior notes and known limitations

- **Counts do not survive a power loss.** They are stored in RTC memory, which keeps its contents through deep sleep but is cleared when power is removed or the board is reset or reflashed. For permanent storage, use the ESP32 `Preferences` (NVS) library.
- **No lower limit.** The count can go below zero.
- **Buttons are polled, not edge-detected.** Holding a button repeats its action about four times per second. A quick tap usually registers once but may register twice.
- **Selection is not kept across sleep.** After waking, the cursor starts on the first user.
- **Buzzer hooks are stubbed.** `beepShort()` and `beepLong()` calls are commented out in `display.cpp`, so audio feedback is not implemented yet.

## Troubleshooting

| Problem | Things to check |
| ------- | --------------- |
| LCD is blank | Adjust the contrast potentiometer on the I2C backpack. Confirm the address is `0x27` (some modules use `0x3F`; an I2C scanner sketch will tell you) |
| Garbled characters | Confirm SDA/SCL are on GPIO 21/22 and the module is powered correctly |
| Buttons do nothing | Each button should connect its GPIO to GND. Watch the Serial Monitor for "button ... pressed!" messages |
| Will not wake from sleep | The select button must be on GPIO 25 and connect it to GND when pressed |
| Upload fails | Select the right board and port, and hold the BOOT button during upload if your board needs it |

## Ideas for future work

- Persist counts across power loss with NVS
- Clamp counts at zero
- Proper button debouncing and press detection
- Audible feedback with a buzzer
- Configurable user names without editing source
- Enclosure for fridge mounting

## License

No license specified yet. Add a `LICENSE` file if you want others to be able to reuse the code.

https://github.com/user-attachments/assets/216d2a9d-41d8-479f-95aa-6851937a7d64



https://github.com/user-attachments/assets/9d4b1291-bc1a-47cb-a17c-4a0031d8ede1

