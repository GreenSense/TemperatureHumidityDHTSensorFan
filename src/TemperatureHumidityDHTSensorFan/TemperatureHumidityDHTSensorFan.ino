#include <Arduino.h>
#include <EEPROM.h>
#include <duinocom.h>

#include "Common.h"
#include "TemperatureHumidityDHTSensor.h"
#include "Ventilation.h"

//#define SERIAL_MODE_CSV 1
//#define SERIAL_MODE_QUERYSTRING 2
//int serialMode = SERIAL_MODE_CSV;

#define VERSION "1-0-0-1"
#define BOARD_TYPE "uno"

void setup()
{
  Serial.begin(9600);

  Serial.println("Starting DHT ventilator");
  Serial.println("");
  
  serialPrintDeviceInfo();

  setupTemperatureHumidityDHTSensor();

  setupVentilation();

  serialOutputIntervalInSeconds = temperatureHumidityDHTSensorReadingIntervalInSeconds;

}

void loop()
{
// Disabled. Used for debugging
//  Serial.print(".");

  if (isDebugMode)
    loopNumber++;

  serialPrintLoopHeader();

  checkCommand();

  takeTemperatureHumidityDHTSensorReading();

  serialPrintData();

  ventilateIfNeeded();

  serialPrintLoopFooter();
  
  delay(1);
}

void serialPrintDeviceInfo()
{
  Serial.println("");
  Serial.println("-- Start Device Info");
  Serial.println("Family: GrowSense");
  Serial.println("Group: ventilator");
  Serial.println("Project: TemperatureHumidityDHTSensorFan");
  Serial.print("Board: ");
  Serial.println(BOARD_TYPE);
  Serial.print("Version: ");
  Serial.println(VERSION);
  Serial.println("ScriptCode: ventilator");
  Serial.println("-- End Device Info");
  Serial.println("");
}


/* Commands */
void checkCommand()
{
  /*if (isDebugMode)
  {
    Serial.println("Checking incoming serial commands");
  }*/

  if (checkMsgReady())
  {
    char* msg = getMsg();
        
    char letter = msg[0];

    int length = strlen(msg);

    Serial.print("Received message: ");
    Serial.println(msg);

    switch (letter)
    {
      case '#':
        serialPrintDeviceInfo();
        break;
      case 'F':
        setFanMode(msg);
        break;
      case 'S':
        setMinTemperature(msg);
        break;
      case 'U':
        setMaxTemperature(msg);
        break;
      case 'G':
        setMinHumidity(msg);
        break;
      case 'J':
        setMaxHumidity(msg);
        break;
      case 'I':
        setTemperatureHumidityDHTSensorReadingInterval(msg);
        break;
      case 'X':
        restoreDefaultSettings();
        break;
      case 'Z':
        Serial.println("Toggling IsDebug");
        isDebugMode = !isDebugMode;
        break;
      // The following are only used for automated testing to bypass the sensor
      case 'T':
        setTemperature(msg);
        break;
      case 'H':
        setHumidity(msg);
        break;
      case 'D':
        temperatureHumidityDHTSensorIsEnabled = false;
        Serial.println("Disabling DHT sensor.");
        break;
    }
    forceSerialOutput();
  }
  delay(1);
}

void forceSerialOutput()
{
//  lastSerialOutputTime = millis()-secondsToMilliseconds(serialOutputIntervalInSeconds) + minimumTemperatureHumidityDHTSensorReadingIntervalInSeconds;
    lastSerialOutputTime = lastSerialOutputTime - secondsToMilliseconds(serialOutputIntervalInSeconds) + minimumTemperatureHumidityDHTSensorReadingIntervalInSeconds;
}

/* Settings */
void restoreDefaultSettings()
{
  Serial.println("Restoring default settings");

  restoreDefaultTemperatureHumidityDHTSensorSettings();
  restoreDefaultVentilationSettings();
}

/* Serial Output */
void serialPrintData()
{
  bool isTimeToPrintData = lastSerialOutputTime + secondsToMilliseconds(serialOutputIntervalInSeconds) < millis();

  bool isReadyToPrintData = isTimeToPrintData && temperatureHumidityDHTSensorReadingHasBeenTaken;

  if (isReadyToPrintData)
  {
    /*if (isDebugMode)
    {
      Serial.println("Printing serial data");
    }*/
    
    bool ventilationIsNeeded = checkVentilationIsNeeded();

    // TODO: Remove if not needed. Should be obsolete
    //if (serialMode == SERIAL_MODE_CSV)
    //{
      Serial.print("D;"); // This prefix indicates that the line contains data.
      Serial.print("A:");
      Serial.print((int)temperatureValue);
      Serial.print("c ");
      Serial.print((int)humidityValue);
      Serial.print("%");
      Serial.print(";");
      Serial.print("T:");
      Serial.print(temperatureValue);
      Serial.print(";");
      Serial.print("U:");
      Serial.print(maxTemperature);
      Serial.print(";");
      Serial.print("S:");
      Serial.print(minTemperature);
      Serial.print(";");
      Serial.print("H:");
      Serial.print(humidityValue);
      Serial.print(";");
      Serial.print("G:");
      Serial.print(minHumidity);
      Serial.print(";");
      Serial.print("J:");
      Serial.print(maxHumidity);
      Serial.print(";");
      Serial.print("F:");
      Serial.print(fanMode);
      Serial.print(";");
      Serial.print("I:");
      Serial.print(temperatureHumidityDHTSensorReadingIntervalInSeconds);
      Serial.print(";");
      Serial.print("VN:"); // Ventilation needed
      Serial.print(ventilationIsNeeded);
      Serial.print(";");
      Serial.print("FO:"); // Fan on
      Serial.print(fanIsOn);
      Serial.print(";");
      Serial.print("V:");
      Serial.print(VERSION);
      Serial.print(";;");
      Serial.println();
    //}
    // TODO: Remove if not needed. Should be obsolete
    /*else
    {
      Serial.print("raw=");
      Serial.print(temperatureHumidityLevelRaw);
      Serial.print("&");
      Serial.print("calibrated=");
      Serial.print(temperatureHumidityLevelCalibrated);
      Serial.print("&");
      Serial.print("maxTemperature=");
      Serial.print(maxTemperature);
      Serial.print("&");
      Serial.print("waterNeeded=");
      Serial.print(temperatureHumidityLevelCalibrated < maxTemperature);
      Serial.print("&");
      Serial.print("fanMode=");
      Serial.print(fanMode);
      Serial.print("&");
      Serial.print("readingInterval=");
      Serial.print(temperatureHumidityDHTSensorReadingIntervalInSeconds);
      Serial.print("&");
      Serial.print("fanBurstOnTime=");
      Serial.print(fanBurstOnTime);
      Serial.print("&");
      Serial.print("fanBurstOffTime=");
      Serial.print(fanBurstOffTime);
      Serial.print("&");
      Serial.print("fanOn=");
      Serial.print(fanIsOn);
      Serial.print("&");
      Serial.print("secondsSinceFanOn=");
      Serial.print((millis() - lastFanFinishTime) / 1000);
      Serial.print("&");
      Serial.print("dry=");
      Serial.print(drySoilMoistureCalibrationValue);
      Serial.print("&");
      Serial.print("wet=");
      Serial.print(wetSoilMoistureCalibrationValue);
      Serial.print(";;");
      Serial.println();
    }*/

/*    if (isDebugMode)
    {
      Serial.print("Last fan start time:");
      Serial.println(fanStartTime);
      Serial.print("Last fan finish time:");
      Serial.println(lastFanFinishTime);
    }*/

    lastSerialOutputTime = millis();
  }
/*  else
  {
    if (isDebugMode)
    {    
      Serial.println("Not ready to serial print data");

      Serial.print("  Is time to serial print data: ");
      Serial.println(isTimeToPrintData);
      if (!isTimeToPrintData)
      {
        Serial.print("    Time remaining before printing data: ");
        Serial.print(millisecondsToSecondsWithDecimal(lastSerialOutputTime + secondsToMilliseconds(serialOutputIntervalInSeconds) - millis()));
        Serial.println(" seconds");
      }
      Serial.print("  Soil moisture sensor reading has been taken: ");
      Serial.println(temperatureHumidityDHTSensorReadingHasBeenTaken);
      Serial.print("  Is ready to print data: ");
      Serial.println(isReadyToPrintData);

    }
  }*/
}
