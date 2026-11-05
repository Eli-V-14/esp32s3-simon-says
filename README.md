# esp32s3-simon-says
Simon Says game for the ESP32-S3, written in Arduino C++. Four lit buttons, a START button, a buzzer, and an SSD1306 OLED that shows the level and score. Built as a non-blocking state machine (millis(), no delay()) with a separate module for each piece of hardware, and the high score is saved to flash.
