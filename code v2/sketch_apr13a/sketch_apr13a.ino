const int sensor_pin = A1;/* Soil moisture sensor O/P pin */
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
const int ldrPin = A2;

void setup() {
  Serial.begin(9600);/* Define baud rate for serial communication */
  pinMode(ldrPin, INPUT);
  dht.begin();
}

void loop() {
  int ldrStatus = analogRead(ldrPin);
  float humidity = dht.readHumidity(); // for reading Humidity
 
  float temperature = dht.readTemperature(); //for reading Temperature
  float moisture_percentage;
  int sensor_analog;
  sensor_analog = analogRead(sensor_pin);
  moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
  Serial.print("Moisture Percentage = ");
  Serial.print(moisture_percentage);
  Serial.print("\t");
  Serial.print ("Humidity: ");
  Serial.print (humidity);
  Serial.print (" %\t");
  Serial.print ("Temperature: ");
  Serial.print (temperature);
  Serial.print (" *C\t ");
  Serial.print ("Light: ");
  Serial.print (ldrStatus);
  if(moisture_percentage < 40 && humidity > 50 && humidity < 70 && temperature > 25 && temperature < 35 && ldrStatus > 100 && ldrStatus < 150 ){
    delay(2000); //wait for few seconds between measurements
    Serial.print ("Plant is Healthy");
  }
  else if (moisture_percentage > 40){
    Serial.print("\nReduce Moisture");
    delay(2000);
  }
  else if (humidity < 50){
    Serial.print ("\nKeep your plant in humid environment");
    delay(2000);
  }  
  else if (humidity > 70){
    Serial.print("\nKeep your plant inside home");
    delay(2000);
  }
  else if (temperature < 25){
    Serial.print("\nKeep your plant warm.");
    delay(2000);
  }
  else if (temperature > 35){
    Serial.print("\nKeep your Plant in home");
    delay(2000);
  }
  else if (ldrStatus < 100) {
    Serial.print("Keep your plant in Sunlight\n");
  }
  else if (ldrStatus > 180) {
    Serial.print("Keep your plant in Shade");
  };
  Serial.print("\n\n");
}
