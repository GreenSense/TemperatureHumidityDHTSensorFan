#include <Arduino.h>
#include <EEPROM.h>
#include <DHT.h>

#include <duinocom.h>

#include "Common.h"
#include "TemperatureHumidityDHTSensor.h"

DHT dht;

#define DHT11_PIN 7

#define temperatureHumidityDHTSensorPin A0
#define temperatureHumidityDHTSensorPowerPin 12

bool temperatureHumidityDHTSensorIsEnabled = true;
long lastSensorOnTime = 0;

bool temperatureHumidityDHTSensorReadingHasBeenTaken = false;
long temperatureHumidityDHTSensorReadingIntervalInSeconds = 2;
long lastTemperatureHumidityDHTSensorReadingTime = 0; // Milliseconds

int temperatureValue = 0;
int humidityValue = 0;

#define temperatureHumidityDHTSensorReadIntervalIsSetFlagAddress 10
#define temperatureHumidityDHTSensorReadingIntervalAddress 13

/* Setup */
void setupTemperatureHumidityDHTSensor()
{
  if (isDebugMode)
    Serial.println("Setting up temperature humidity DHT sensor...");

  dht.setup(DHT11_PIN);
  
  delay(dht.getMinimumSamplingPeriod());

  setupTemperatureHumidityDHTSensorReadingInterval();

  pinMode(temperatureHumidityDHTSensorPowerPin, OUTPUT);
}

/* Sensor Readings */
void takeTemperatureHumidityDHTSensorReading()
{
  bool sensorReadingIsDue = lastTemperatureHumidityDHTSensorReadingTime + secondsToMilliseconds(temperatureHumidityDHTSensorReadingIntervalInSeconds) < millis()
    || lastTemperatureHumidityDHTSensorReadingTime == 0;

  if (sensorReadingIsDue && temperatureHumidityDHTSensorIsEnabled)
  {
    //if (isDebugMode)
    //  Serial.println("Sensor reading is due");


    //if (isDebugMode)
    //  Serial.println("Preparing to take reading");

    lastTemperatureHumidityDHTSensorReadingTime = millis();
    
    delay(dht.getMinimumSamplingPeriod());
    
    humidityValue = dht.getHumidity();
    
    if (isnan(humidityValue))
      humidityValue = 0;
      
    temperatureValue = dht.getTemperature();

    if (isnan(temperatureValue))
      temperatureValue = 0;
      
    /*if (isDebugMode)
    {
      Serial.println("Humidity:");
      Serial.println(humidityValue);
      Serial.println("Temperature:");
      Serial.println(temperatureValue);
    }*/

    temperatureHumidityDHTSensorReadingHasBeenTaken = true;
  }
}

/* Temperature/Humidity */
void setTemperature(char* msg)
{
    int value = readInt(msg, 1, strlen(msg)-1);

    setTemperature(value);
}

void setTemperature(long newValue)
{
  /*if (isDebugMode)
  {
    Serial.print("Set temperature: ");
    Serial.println(newValue);
  }*/

  temperatureValue = newValue;
}

void setHumidity(char* msg)
{
  int value = readInt(msg, 1, strlen(msg)-1);

  setHumidity(value);
}

void setHumidity(long newValue)
{
  /*if (isDebugMode)
  {
    Serial.print("Set humidity: ");
    Serial.println(newValue);
  }*/

  humidityValue = newValue;
}

/* Reading interval */
void setupTemperatureHumidityDHTSensorReadingInterval()
{
  bool eepromIsSet = EEPROM.read(temperatureHumidityDHTSensorReadIntervalIsSetFlagAddress) == 99;

  if (eepromIsSet)
  {
    if (isDebugMode)
    	Serial.println("EEPROM read interval value has been set. Loading.");

    temperatureHumidityDHTSensorReadingIntervalInSeconds = getTemperatureHumidityDHTSensorReadingInterval();
  }
  /*else
  {
    if (isDebugMode)
      Serial.println("EEPROM read interval value has not been set. Using defaults.");
  }*/
}

void setTemperatureHumidityDHTSensorReadingInterval(char* msg)
{
    int value = readInt(msg, 1, strlen(msg)-1);

    setTemperatureHumidityDHTSensorReadingInterval(value);
}

void setTemperatureHumidityDHTSensorReadingInterval(long newValue)
{
  /*if (isDebugMode)
  {
    Serial.print("Set sensor reading interval: ");
    Serial.println(newValue);
  }*/
  
  // Set 3 as the minimum interval to avoid issues with reading from the sensor too quickly
  if (newValue < 2)
  {
    Serial.println("Setting interval to 3s. The DHT sensor cannot support faster readings.");
    newValue = 2;
  }

  EEPROMWriteLong(temperatureHumidityDHTSensorReadingIntervalAddress, newValue);

  setEEPROMFlag(temperatureHumidityDHTSensorReadIntervalIsSetFlagAddress);

  temperatureHumidityDHTSensorReadingIntervalInSeconds = newValue; 

  serialOutputIntervalInSeconds = newValue;
}

long getTemperatureHumidityDHTSensorReadingInterval()
{
  long value = EEPROMReadLong(temperatureHumidityDHTSensorReadingIntervalAddress);

  if (value == 0
      || value == 255)
    return temperatureHumidityDHTSensorReadingIntervalInSeconds;
  else
  {
    /*if (isDebugMode)
    {
      Serial.print("Read interval found in EEPROM: ");
      Serial.println(value);
    }*/

    return value;
  }
}

void removeEEPROMTemperatureHumidityDHTSensorReadingIntervalIsSetFlag()
{
    EEPROM.write(temperatureHumidityDHTSensorReadIntervalIsSetFlagAddress, 0);
}

void restoreDefaultTemperatureHumidityDHTSensorSettings()
{
  restoreDefaultTemperatureHumidityDHTSensorReadingIntervalSettings();
}

void restoreDefaultTemperatureHumidityDHTSensorReadingIntervalSettings()
{
  removeEEPROMTemperatureHumidityDHTSensorReadingIntervalIsSetFlag();

  temperatureHumidityDHTSensorReadingIntervalInSeconds = 2;
  serialOutputIntervalInSeconds = 2;

  setTemperatureHumidityDHTSensorReadingInterval(temperatureHumidityDHTSensorReadingIntervalInSeconds);
}

