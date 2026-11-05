# esp32s3-simon-says
Simon Says game for the ESP32-S3, written in Arduino C++. Four lit buttons, a START button, a buzzer, and an SSD1306 OLED that shows the level and score. Built as a non-blocking state machine (millis(), no delay()) with a separate module for each piece of hardware, and the high score is saved to flash.


## Wiring

### Lit buttons (4)

Each lit button has an LED and a switch. The LED anode is driven by a GPIO output, and the switch connects to a GPIO input.

| Color  | LED anode (output) | Button switch (input) |
|--------|--------------------|-----------------------|
| Green  | GPIO 40            | GPIO 15               |
| Red    | GPIO 41            | GPIO 16               |
| Yellow | GPIO 38            | GPIO 17               |
| Blue   | GPIO 39            | GPIO 18               |

Circuit for each lit button:

    LED GPIO -> LED anode -> LED cathode -> 330 ohm resistor -> GND
                                         \-> button switch -> button GPIO

The switch connects the LED cathode node to its input GPIO. The inputs use `INPUT_PULLUP`, so a press reads LOW. The code ignores these inputs while an LED is lit, because the LED current lifts the cathode node above ground and the reading is unreliable.

### START button

    GPIO 0 -> button -> GND

No resistor is needed, because the internal pull-up is used.

### Buzzer

| Part                | Pin     |
|---------------------|---------|
| Buzzer signal       | GPIO 45 |
| Buzzer other side   | GND     |

### OLED (0.96", SSD1306, I2C, address 0x3C)

| OLED pin | Connects to |
|----------|-------------|
| VCC      | 3V3         |
| GND      | GND         |
| SDA      | GPIO 13     |
| SCL      | GPIO 12     |

### Pin notes

- GPIO 35, 36 and 37 are not used. On ESP32-S3 modules with octal PSRAM they are tied to the PSRAM, and driving them can hang the board at startup.
- GPIO 0 (START) and GPIO 45 (buzzer) are strapping pins. Don't hold START while the board resets or powers on, or it will enter download mode.