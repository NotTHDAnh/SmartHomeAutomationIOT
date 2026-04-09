# Introduction
This is our group IOT project in SP26 Trimester of FPT University, an Smart Home Automation system using **Arduino UNO R3**,**ESP8266**,Light sensor **LDR**, Humidity and Temperature **DHT11**, Motion Sensor **SR501**, and **Relay Module**. This system will based on sensors' data and process in order to save energy. It will check the motion sensor and range of 3 second, if the temperature is higher than thresold fan will be automaticlly turned on, if the room is dark, the light bulb will be turned on, All the sensors' data will be send to third party IOT platfrom **Blynk** for illustration.

# How it works
This will detect motion using SR501, if any motion is detected, the system will check temperature and light conditions, light and fan will be turned on if the conditions is matched. After that, the data including humidity, light, temperature, led status, fan status

# Feature
- Real-time data
- Data illustration
- Energy saving

# Discussion
This system can be use only ESP8266 for both data processing and communication. This will lead to the simple in wiring and coding, the use of 2 files of code is not needed, less wiring is required. If use both ESP8266 and Arduino, the Arduino will be the "Brain" processing data and ESP8266 will be the communication between the system and **Blynk** platform, and it will communicate through Serial so TX,RX of Arduino must be reverse wired with TX,RX of ESP8266, the code of these 2 components is seperated. Moreover, the code must be load seperately before wiring TX,RX of these 2. Next, the use of relay module in this project is not necessary, because led light don't really need relay module to turn it on. But when use the high power led bulb, the relay module is required. The communication is only for data illutrations, the system can't be remote monitoring. It will be developed easily to do this. Also, Humidity in this system is not needed yet. But potentinally will be used in the future feature. Thresold must be test more for the accuracy.

# Contributing
List of contributor is listed in the Final Report
