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

bool temperatureHumidityDHTSensorIsOn = true;
long lastSensorOnTime = 0;
int delayAfterTurningTemperatureHumidityDHTSensorOn = 3 * 1000;

bool temperatureHumidityDHTSensorReadingHasBeenTaken = false;
long temperatureHumidityDHTSensorReadingIntervalInSeconds = 5;
long lastTemperatureHumidityDHTSensorReadingTime = 0; // Milliseconds

float temperatureValue = 0;
float humidityValue = 0;

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

  // If the interval is less than specified delay then turn the sensor on and leave it on (otherwise it will be turned on each time it's needed)
  if (secondsToMilliseconds(temperatureHumidityDHTSensorReadingIntervalInSeconds) <= delayAfterTurningTemperatureHumidityDHTSensorOn)
  {
    turnTemperatureHumidityDHTSensorOn();
  }
}

/* Sensor On/Off */
void turnTemperatureHumidityDHTSensorOn()
{
  if (isDebugMode)
    Serial.println("Turning sensor on");

  digitalWrite(temperatureHumidityDHTSensorPowerPin, HIGH);

  lastSensorOnTime = millis();

  temperatureHumidityDHTSensorIsOn = true;
}

void turnTemperatureHumidityDHTSensorOff()
{
  if (isDebugMode)
    Serial.println("Turning sensor off");

  digitalWrite(temperatureHumidityDHTSensorPowerPin, LOW);

  temperatureHumidityDHTSensorIsOn = false;
}

/* Sensor Readings */
void takeTemperatureHumidityDHTSensorReading()
{
  bool sensorReadingIsDue = lastTemperatureHumidityDHTSensorReadingTime + secondsToMilliseconds(temperatureHumidityDHTSensorReadingIntervalInSeconds) < millis()
    || lastTemperatureHumidityDHTSensorReadingTime == 0;

  if (sensorReadingIsDue)
  {
    if (isDebugMode)
      Serial.println("Sensor reading is due");

  	bool sensorGetsTurnedOff = secondsToMilliseconds(temperatureHumidityDHTSensorReadingIntervalInSeconds) > delayAfterTurningTemperatureHumidityDHTSensorOn;
  
  	bool sensorIsOffAndNeedsToBeTurnedOn = !temperatureHumidityDHTSensorIsOn && sensorGetsTurnedOff;
  
  	bool postSensorOnDelayHasPast = lastSensorOnTime + delayAfterTurningTemperatureHumidityDHTSensorOn < millis();
  
  	bool temperatureHumidityDHTSensorIsOnAndReady = temperatureHumidityDHTSensorIsOn && (postSensorOnDelayHasPast || !sensorGetsTurnedOff);

    bool temperatureHumidityDHTSensorIsOnButSettling = temperatureHumidityDHTSensorIsOn && !postSensorOnDelayHasPast && sensorGetsTurnedOff;

    /*if (isDebugMode)
    {
        Serial.print("  Sensor is on: ");
        Serial.println(temperatureHumidityDHTSensorIsOn);
        
        Serial.print("  Last sensor on time: ");
        Serial.print(millisecondsToSecondsWithDecimal(millis() - lastSensorOnTime));
        Serial.println(" seconds ago");
        
        Serial.print("  Sensor gets turned off: ");
        Serial.println(sensorGetsTurnedOff);
        
        Serial.print("  Sensor is off and needs to be turned on: ");
        Serial.println(sensorIsOffAndNeedsToBeTurnedOn);
        
        Serial.print("  Post sensor on delay has past: ");
        Serial.println(postSensorOnDelayHasPast);
        
        Serial.print("  Sensor is off and needs to be turned on: ");
        Serial.println(sensorIsOffAndNeedsToBeTurnedOn);
        
        Serial.print("  Sensor is on and ready: ");
        Serial.println(temperatureHumidityDHTSensorIsOnAndReady);
        
        Serial.print("  Sensor is on but settling: ");
        Serial.println(temperatureHumidityDHTSensorIsOnButSettling);
        
        if (temperatureHumidityDHTSensorIsOnButSettling)
        {
          Serial.print("    Time remaining to settle: ");
          long timeRemainingToSettle = lastSensorOnTime + delayAfterTurningTemperatureHumidityDHTSensorOn - millis();
          Serial.print(millisecondsToSecondsWithDecimal(timeRemainingToSettle));
          Serial.println(" seconds");
        }
    }*/

    if (sensorIsOffAndNeedsToBeTurnedOn)
    {
      turnTemperatureHumidityDHTSensorOn();
    }
    else if (temperatureHumidityDHTSensorIsOnButSettling)
    {
      // Skip this loop. Wait for the sensor to settle in before taking a reading.
      if (isDebugMode)
        Serial.println("Soil moisture sensor is settling after being turned on");
    }
    else if (temperatureHumidityDHTSensorIsOnAndReady)
    {
      if (isDebugMode)
        Serial.println("Preparing to take reading");

      lastTemperatureHumidityDHTSensorReadingTime = millis();
      
      // Remove the delay (after turning soil moisture sensor on) from the last reading time to get more accurate timing
      if (sensorGetsTurnedOff)
        lastTemperatureHumidityDHTSensorReadingTime = lastTemperatureHumidityDHTSensorReadingTime - delayAfterTurningTemperatureHumidityDHTSensorOn;
        
      delay(dht.getMinimumSamplingPeriod());
      
      humidityValue = dht.getHumidity();
      temperatureValue = dht.getTemperature();

      if (isDebugMode)
      {
        Serial.println("Humidity:");
        Serial.println(humidityValue);
        Serial.println("Temperature:");
        Serial.println(temperatureValue);
      }

      temperatureHumidityDHTSensorReadingHasBeenTaken = true;

      if (secondsToMilliseconds(temperatureHumidityDHTSensorReadingIntervalInSeconds) > delayAfterTurningTemperatureHumidityDHTSensorOn)
      {
        turnTemperatureHumidityDHTSensorOff();
      }
    }
  }
  else
  {
    /*if (isDebugMode)
    {
      Serial.println("Sensor reading is not due");
      
      Serial.print("  Last soil moisture sensor reading time: ");
      Serial.print(millisecondsToSecondsWithDecimal(lastTemperatureHumidityDHTSensorReadingTime));
      Serial.println(" seconds");
      
      Serial.print("  Last soil moisture sensor reading interval: ");
      Serial.print(temperatureHumidityDHTSensorReadingIntervalInSeconds);
      Serial.println(" seconds");
    
      int timeLeftUntilNextReading = lastTemperatureHumidityDHTSensorReadingTime + secondsToMilliseconds(temperatureHumidityDHTSensorReadingIntervalInSeconds) - millis();
      Serial.print("  Time left until next soil moisture sensor reading: ");
      Serial.print(millisecondsToSecondsWithDecimal(timeLeftUntilNextReading));
      Serial.println(" seconds");
    }*/
  }
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
  else
  {
    if (isDebugMode)
      Serial.println("EEPROM read interval value has not been set. Using defaults.");
  }
}

void setTemperatureHumidityDHTSensorReadingInterval(char* msg)
{
    int value = readInt(msg, 1, strlen(msg)-1);

    setTemperatureHumidityDHTSensorReadingInterval(value);
}

void setTemperatureHumidityDHTSensorReadingInterval(long newValue)
{
  if (isDebugMode)
  {
    Serial.print("Set sensor reading interval: ");
    Serial.println(newValue);
  }

  EEPROMWriteLong(temperatureHumidityDHTSensorReadingIntervalAddress, newValue);

  setEEPROMFlag(temperatureHumidityDHTSensorReadIntervalIsSetFlagAddress);

  temperatureHumidityDHTSensorReadingIntervalInSeconds = newValue; 

  serialOutputIntervalInSeconds = newValue;
  
  if (secondsToMilliseconds(newValue) <= delayAfterTurningTemperatureHumidityDHTSensorOn)
    turnTemperatureHumidityDHTSensorOn();
}

long getTemperatureHumidityDHTSensorReadingInterval()
{
  long value = EEPROMReadLong(temperatureHumidityDHTSensorReadingIntervalAddress);

  if (value == 0
      || value == 255)
    return temperatureHumidityDHTSensorReadingIntervalInSeconds;
  else
  {
    if (isDebugMode)
    {
      Serial.print("Read interval found in EEPROM: ");
      Serial.println(value);
    }

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

  temperatureHumidityDHTSensorReadingIntervalInSeconds = 5;
  serialOutputIntervalInSeconds = 5;

  setTemperatureHumidityDHTSensorReadingInterval(temperatureHumidityDHTSensorReadingIntervalInSeconds);
}

