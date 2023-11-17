## Plant Health Monitoring System
### Introduction
The circuit is made up of 4 sensors, temperature, humidity, soil moisture and light. The whole system runs off an Arduino Uno. 
![Alt Text]('https://github.com/SriCharanK2002/PlantHealthMonitoring/blob/main/plant-status-schema_BDtIxaiaEA.png')

### Components
- Arduino Uno
- Soil Moisture Sensor
- DHT11 Temperature and Humidity Sensor
- Photoresistor
- 220 Ohm Resistor
- Breadboard

### Future Improvements
The system can scaled up with multiple sensors and multiple plants. The system is designed to be modular and can be easily expanded. We simply have to add a soil moisture sensor for each plant and a light sensor for each section of the farm/garden. 

If there are multiple arduinos, we can use a Raspberry Pi to collect the data from each arduino and send it to a server. The server can then be used to display the data in a web app.
