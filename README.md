# esp32-pyphox-bmp280
A simple project for reading the values of a BMP280 sensor of your choice with an ESP32 and reading them out over the app phyphox.
___
### About
With this code you can use a bmp280 sensor for a handful of experiments with the phyphox application on your smartphone.
A few different views have been implemented to allow reading of the raw data (though all the values have been slightly filtered) as well as reading of your height over sea level or simple height measurements.
### How to use
Load the phyphox file in the [phyphox editor](https://phyphox.org/editor/) and generate a QR code to be read by the app. Or scan the convenient QR code at the end of this file.
Wire the sensor acording to your microcontrollers output and your sensor of choice.
Upload the code with the Arduino IDE.
When you start the experiment you can connect to the ESP32 and start your measurments.
### Dependencies
Some Adafruit libraries are necessary, as well as the Espressif ESP32 board files.
### Known issues
- The App might have some trouble to read some ESP32 boards
  - Try hitting reset on the board and connecting directly after
  - Using the Wemos Lolin32 board appears to create no issues

### QR Code for the Experiment
![Online QR code for the experiment](https://raw.githubusercontent.com/dont-ask-why/esp32-pyphox-bmp280/main/QR_Code.png)
