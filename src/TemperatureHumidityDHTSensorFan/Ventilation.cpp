#include <Arduino.h>

#include <EEPROM.h>

#include <duinocom.h>

#include "Common.h"
#include "TemperatureHumidityDHTSensor.h"
#include "Ventilation.h"

int maxTemperature = 40;
int minTemperature = 1;
int maxHumidity = 60;
int minHumidity = 1;

bool fanIsOn = 0;
long fanStartTime = 0;
long lastFanFinishTime = 0;

int fanMode = FAN_MODE_AUTO;

#define maxTemperatureIsSetEEPROMFlagAddress 20
#define maxTemperatureEEPROMAddress 21

#define minTemperatureIsSetEEPROMFlagAddress 24
#define minTemperatureEEPROMAddress 25

#define maxHumidityIsSetEEPROMFlagAddress 28
#define maxHumidityEEPROMAddress 29

#define minHumidityIsSetEEPROMFlagAddress 33
#define minHumidityEEPROMAddress 34

/* Setup */
void setupVentilation()
{
  if (isDebugMode)
  {
    Serial.println("Setting up ventilation...");
  }

  pinMode(FAN_PIN, OUTPUT);

  setupMaxTemperature();
  setupMinTemperature();
  setupMaxHumidity();
  setupMinHumidity();
}

void setupMaxTemperature()
{
  bool eepromIsSet = EEPROM.read(maxTemperatureIsSetEEPROMFlagAddress) == 99;

  if (eepromIsSet)
  {
    if (isDebugMode)
    	Serial.println("EEPROM max temperature value has been set. Loading.");

    maxTemperature = getMaxTemperature();
  }
  else
  {
    if (isDebugMode)
      Serial.println("EEPROM max temperature value has not been set. Using defaults.");
    
    //setMaxTemperature(maxTemperature);
  }
}

void setupMinTemperature()
{
  bool eepromIsSet = EEPROM.read(minTemperatureIsSetEEPROMFlagAddress) == 99;

  if (eepromIsSet)
  {
    if (isDebugMode)
    	Serial.println("EEPROM min temperature value has been set. Loading.");

    minTemperature = getMinTemperature();
  }
  else
  {
    if (isDebugMode)
      Serial.println("EEPROM min temperature value has not been set. Using defaults.");
    
    //setMinTemperature(minTemperature);
  }
}

void setupMaxHumidity()
{
  bool eepromIsSet = EEPROM.read(maxHumidityIsSetEEPROMFlagAddress) == 99;

  if (eepromIsSet)
  {
    if (isDebugMode)
    	Serial.println("EEPROM max humidity value has been set. Loading.");

    maxHumidity = getMaxHumidity();
  }
  else
  {
    if (isDebugMode)
      Serial.println("EEPROM max humidity value has not been set. Using defaults.");
    
    //setMaxHumidity(maxHumidity);
  }
}

void setupMinHumidity()
{
  bool eepromIsSet = EEPROM.read(minHumidityIsSetEEPROMFlagAddress) == 99;

  if (eepromIsSet)
  {
    if (isDebugMode)
    	Serial.println("EEPROM min humidity value has been set. Loading.");

    minHumidity = getMinHumidity();
  }
  else
  {
    if (isDebugMode)
      Serial.println("EEPROM min humidity value has not been set. Using defaults.");
    
    //setMinHumidity(minHumidity);
  }
}

/* Ventilation */
void ventilateIfNeeded()
{
  if (isDebugMode)
  {
    Serial.println("Ventilating (if needed)");
  }

  if (fanMode == FAN_MODE_AUTO)
  {
    bool ventilationIsNeeded = checkVentilationIsNeeded();
    bool fanIsReady = true; // lastFanFinishTime + secondsToMilliseconds(fanBurstOffTime) < millis() || lastFanFinishTime == 0; // TODO: Reimplement

    if (fanIsOn)
    {
      if (!ventilationIsNeeded)
      {
        if (isDebugMode)
          Serial.println("  Fan is turning off");
        
        fanOff();
      }
    }
    else if (ventilationIsNeeded && fanIsReady)
    {
      if (isDebugMode)
        Serial.println("  Fan is turning on");
      fanOn();
    }
  }
  else if(fanMode == FAN_MODE_ON)
  {
    if (!fanIsOn)
      fanOn();
  }
  else
  {
    if (fanIsOn)
      fanOff();
  }
}

bool checkVentilationIsNeeded()
{
  if (isDebugMode)
  {
    Serial.println("Checking whether ventilation is needed...");
  }

  bool readingHasBeenTaken = lastTemperatureHumidityDHTSensorReadingTime > 0;
    
  if (isDebugMode)
  {
    Serial.print("Reading has been taken: ");
    Serial.println(readingHasBeenTaken);
  }
  
  bool temperatureIsOutsideRange = temperatureValue >= maxTemperature ||
    temperatureValue <= minTemperature;
    
  if (isDebugMode)
  {
    Serial.print("Temperature is outside range: ");
    Serial.println(temperatureIsOutsideRange);
  }
  
  bool humidityIsOutsideRange = humidityValue >= maxHumidity ||
    humidityValue <= minHumidity;
    
  if (isDebugMode)
  {
    Serial.print("Humidity is outside range: ");
    Serial.println(humidityIsOutsideRange);
  }
  
  bool ventilationIsNeeded = readingHasBeenTaken &&
    (temperatureIsOutsideRange || humidityIsOutsideRange);
  
  if (isDebugMode)
  {
    Serial.print("Ventilation is needed: ");
    Serial.println(ventilationIsNeeded);
  }
  
  return ventilationIsNeeded;
}

void fanOn()
{
  digitalWrite(FAN_PIN, HIGH);
  fanIsOn = true;

  fanStartTime = millis();
}

void fanOff()
{
  digitalWrite(FAN_PIN, LOW);
  fanIsOn = false;

  lastFanFinishTime = millis();
}

void setFanMode(char* msg)
{
  int length = strlen(msg);

  if (length != 2)
  {
    Serial.println("Invalid fan status:");
    printMsg(msg);
  }
  else
  {
    int value = readInt(msg, 1, 1);

//    Serial.println("Value:");
//    Serial.println(value);

    setFanMode(value);
  }
}

void setFanMode(int newStatus)
{
  fanMode = newStatus;
}

void setMaxTemperature(char* msg)
{
  int length = strlen(msg);

  int value = readInt(msg, 1, length-1);

//    Serial.println("Value:");
//    Serial.println(value);

  setMaxTemperature(value);
}

void setMaxTemperature(int newMaxTemperature)
{
  maxTemperature = newMaxTemperature;

  if (isDebugMode)
  {
    Serial.print("Setting max temperature to EEPROM: ");
    Serial.println(maxTemperature);
  }

  EEPROM.write(maxTemperatureEEPROMAddress, maxTemperature);

  setEEPROMFlag(maxTemperatureIsSetEEPROMFlagAddress);
}

int getMaxTemperature()
{
  int value = EEPROM.read(maxTemperatureEEPROMAddress);

  if (value <= 0
      || value >= 100)
    return maxTemperature;
  else
  {
    int maxTemperature = value;

    if (isDebugMode)
    {
      Serial.print("Max temperature found in EEPROM: ");
      Serial.println(maxTemperature);
    }

    return maxTemperature;
  }
}

void setMinTemperature(char* msg)
{
  int length = strlen(msg);

  int value = readInt(msg, 1, length-1);

//    Serial.println("Value:");
//    Serial.println(value);

  setMinTemperature(value);
}

void setMinTemperature(int newMinTemperature)
{
  minTemperature = newMinTemperature;

  if (isDebugMode)
  {
    Serial.print("Setting min temperature to EEPROM: ");
    Serial.println(minTemperature);
  }

  EEPROM.write(minTemperatureEEPROMAddress, newMinTemperature);
  
  setEEPROMFlag(minTemperatureIsSetEEPROMFlagAddress);
}

int getMinTemperature()
{
  int value = EEPROM.read(minTemperatureEEPROMAddress);

  if (value <= 0
      || value >= 100)
    return minTemperature;
  else
  {
    int minTemperature = value; // Must multiply by 4 to get the original value

    if (isDebugMode)
    {
      Serial.print("Min temperature found in EEPROM: ");
      Serial.println(minTemperature);
    }

    return minTemperature;
  }
}

void setMaxHumidity(char* msg)
{
  int length = strlen(msg);

  int value = readInt(msg, 1, length-1);

//    Serial.println("Value:");
//    Serial.println(value);

  setMaxHumidity(value);
}

void setMaxHumidity(int newMaxHumidity)
{
  maxHumidity = newMaxHumidity;

  if (isDebugMode)
  {
    Serial.print("Setting max temperature to EEPROM: ");
    Serial.println(maxHumidity);
  }

  EEPROM.write(maxHumidityEEPROMAddress, newMaxHumidity);
  
  setEEPROMFlag(maxHumidityIsSetEEPROMFlagAddress);
}

int getMaxHumidity()
{
  int value = EEPROM.read(maxHumidityEEPROMAddress);

  if (value <= 0
      || value >= 100)
    return maxHumidity;
  else
  {
    int maxHumidity = value; // Must multiply by 4 to get the original value

    if (isDebugMode)
    {
      Serial.print("Max humidity found in EEPROM: ");
      Serial.println(maxHumidity);
    }

    return maxHumidity;
  }
}

void setMinHumidity(char* msg)
{
  int length = strlen(msg);

  int value = readInt(msg, 1, length-1);

  setMinHumidity(value);
}

void setMinHumidity(int newMinHumidity)
{
  minHumidity = newMinHumidity;

  if (isDebugMode)
  {
    Serial.print("Setting min humidity to EEPROM: ");
    Serial.println(minHumidity);
  }

  EEPROM.write(minHumidityEEPROMAddress, newMinHumidity);
  
  setEEPROMFlag(minHumidityIsSetEEPROMFlagAddress);
}

int getMinHumidity()
{
  int value = EEPROM.read(minHumidityEEPROMAddress);

  if (value <= 0
      || value >= 100)
    return minHumidity;
  else
  {
    int minHumidity = value; // Must multiply by 4 to get the original value

    if (isDebugMode)
    {
      Serial.print("Min humidity found in EEPROM: ");
      Serial.println(minHumidity);
    }

    return minHumidity;
  }
}

/* Restore defaults */
void restoreDefaultVentilationSettings()
{
  Serial.println("Reset default settings");

  restoreDefaultMaxTemperature();
}

void restoreDefaultMaxTemperature()
{
  Serial.println("Reset max temperature");

  removeMaxTemperatureEEPROMIsSetFlag();

  maxTemperature = 30;

  setMaxTemperature(maxTemperature);
}

void removeMaxTemperatureEEPROMIsSetFlag()
{
    EEPROM.write(maxTemperatureIsSetEEPROMFlagAddress, 0);
}
