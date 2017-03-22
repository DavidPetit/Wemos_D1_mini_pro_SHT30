# Wemos_D1_mini_pro_SHT30
Arduino based code with Wemos D1 mini Pro and SHT30 shield.

My goal is to have the SHT30 connected to the internet through wifi and publish data on a MQTT broker (Mosquitto). 
It should work with any ESP8266 board as well.

## How to install:
1. Install Wemos D1 mini with board manager in Arduino IDE (Board manager URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json)
2. Install ESP8266 Arduino libraries from Arduino IDE library manager
3. Install Wemos SHT3x Arduino library: https://github.com/wemos/WEMOS_SHT3x_Arduino_Library
4. Install PubSub Arduino library from Arduino IDE library manager
5. Download the Wemos_D1_mini_pro_SHT30.ino file from this repo, customize it and upload to your board to try it.
