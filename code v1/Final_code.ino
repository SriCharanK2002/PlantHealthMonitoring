#include <SoftwareSerial.h> 
#include "DHT.h"
#include <Wire.h>

#define DHTPIN 12     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22

int sensorPin = A0;
int sensorValue = 0;
int percentValue = 0;
const int ldrPin = A1;
 
// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);
 
char inchar; // Will hold the incoming character from the GSM shield

int bluetoothTx = 7;
int bluetoothRx = 8; 
 
SoftwareSerial blue( bluetoothTx, bluetoothRx); // bluetooth module will be connected here.

int powerb = 6; 
String TextForSms ;
String TextForSms2 ;
String TextForSms3 ;
String humidity = " Humidity: %";
String temperature = "   Temperature";
String sign = " *C";

#define trigPin 13
#define echoPin 11

 
void setup()
{
  Serial.begin(9600);
  blue.begin(9600); // original 19200
  pinMode(powerb, OUTPUT); 
  digitalWrite(powerb, HIGH); 
  dht.begin();
  pinMode(trigPin, OUTPUT);
  Wire.begin();
  pinMode(echoPin, INPUT);
  pinMode(ldrPin, INPUT);
}
 
 
void loop()
{
  if(blue.available() == 0);
  {
    if(blue.available() >0)
    {
      inchar=blue.read(); 
      Serial.println(inchar);
      delay(20);
      if (inchar=='x')
      {
        delay(10);
        Serial.println(inchar);
        delay(2000);
        int h = dht.readHumidity();
        // Read temperature as Celsius
        int t = dht.readTemperature();
        // Read temperature as Fahrenheit
        int f = dht.readTemperature(true);  
        // Check if any reads failed and exit early (to try again).
        if (isnan(h) || isnan(t) || isnan(f))
        {
          Serial.println("Failed to read from DHT sensor!");
          return;
        }
        sensorValue = analogRead(sensorPin);
        Serial.print("\n\nAnalogValue:");
        Serial.print(sensorValue);
        
        percentValue = map(sensorValue, 1023, 200, 0, 100);
        Serial.print("\nPercentValue: ");
        Serial.print(percentValue);
        Serial.print("%");
        Serial.print("Soil Moisture");
        Serial.print("Percent: ");
        Serial.print(percentValue);
        Serial.print("% \n\n\n");
        delay(5000);
        
        sensorValue = analogRead(sensorPin);
        Serial.print(sensorValue); 
        // Compute heat index
        int hi = dht.computeHeatIndex(f, h);
        Serial.print("Humidity: "); 
        Serial.print(h);
        Serial.print(" %\t");
        Serial.print("Temperature: "); 
        Serial.print(t);
        Serial.print(" *C ");
        
        int ldrStatus = analogRead(ldrPin);
        Serial.print(ldrStatus);
        delay(1000);
        
        TextForSms = TextForSms + "AIR HUMIDITY: ";
        TextForSms.concat(h);
        TextForSms = TextForSms + "% AIR TEMPERATURE: ";
        TextForSms.concat(t);
        TextForSms = TextForSms + "*C";
        blue.print(TextForSms);
        Serial.println(TextForSms);
        delay(2000);
        TextForSms = " ";
        TextForSms2 = TextForSms2 + "    SOIL HUMIDITY: ";
        TextForSms2.concat(percentValue) + "%";
        blue.print(TextForSms2 + "%");
        Serial.println(TextForSms2 + "%");
        delay(2000);
        TextForSms2 = " ";

        if (ldrStatus > 400)
        {
          TextForSms3 = TextForSms3 + "  LUMINOSITY: ";
          TextForSms3.concat(ldrStatus);
          TextForSms3 = TextForSms3 + " (Good light)\n";
          blue.print(TextForSms3);
          Serial.println(TextForSms3);
          delay(2000);
          TextForSms3 = " ";
        }
        else if (ldrStatus > 150 && ldrStatus < 500)
        {
          TextForSms3 = TextForSms3 + "  LUMINOSITY: ";
          TextForSms3.concat(ldrStatus);
          TextForSms3 = TextForSms3 + " (Medium light)\n";
          blue.print(TextForSms3);
          Serial.println(TextForSms3);
          delay(2000);
          TextForSms3 = " ";
        }
        else
        {
          TextForSms3 = TextForSms3 + "  LUMINOSITY: ";
          TextForSms3.concat(ldrStatus);
          TextForSms3 = TextForSms3 + " (Bad light)\n";
          blue.print(TextForSms3);
          Serial.println(TextForSms3);
          delay(2000);
          TextForSms3 = " ";
        }
      }
    }
    else if(blue.available() > 0)
    {
      int servopos = blue.read(); // save the received number to servopos
      Serial.println(servopos); // serial print servopos current number received from bluetooth
    //myservo.write(servopos); // rotate the servo the angle received from the android app
    }
  }
}
