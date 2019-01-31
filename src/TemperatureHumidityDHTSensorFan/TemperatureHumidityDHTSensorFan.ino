#include <Arduino.h>
#include <EEPROM.h>
#include <duinocom.h>

#include "Common.h"
#include "TemperatureHumidityDHTSensor.h"
#include "Ventilation.h"

#define SERIAL_MODE_CSV 1
#define SERIAL_MODE_QUERYSTRING 2

#define VERSION "1-0-0-0"

int serialMode = SERIAL_MODE_CSV;

void setup()
{
  Serial.begin(9600);

  Serial.println("Starting DHT ventilator");

  setupTemperatureHumidityDHTSensor();

  setupVentilation();

  serialOutputIntervalInSeconds = temperatureHumidityDHTSensorReadingIntervalInSeconds;

}

void loop()
{
// Disabled. Used for debugging
//  Serial.print(".");

  loopNumber++;

  serialPrintLoopHeader();

  checkCommand();

  takeTemperatureHumidityDHTSensorReading();

  serialPrintData();

  ventilateIfNeeded();

  serialPrintLoopFooter();

  delay(1);
}

/* Commands */
void checkCommand()
{
  if (isDebugMode)
  {
    Serial.println("Checking incoming serial commands");
  }

  if (checkMsgReady())
  {
    char* msg = getMsg();
        
    char letter = msg[0];

    int length = strlen(msg);

    Serial.print("Received message: ");
    Serial.println(msg);

    switch (letter)
    {
      case 'P':
        setFanStatus(msg);
        break;
      case 'T':
        setMaxTemperature(msg);
        break;
      case 'H':
        setMaxHumidity(msg);
        break;
      case 'I':
        setTemperatureHumidityDHTSensorReadingInterval(msg);
        break;
      case 'X':
        restoreDefaultSettings();
        break;
      case 'N':
        Serial.println("Turning fan on");
        fanStatus = FAN_STATUS_ON;
        fanOn();
        break;
      case 'F':
        Serial.println("Turning fan off");
        fanStatus = FAN_STATUS_OFF;
        fanOff();
        break;
      case 'A':
        Serial.println("Turning fan to auto");
        fanStatus = FAN_STATUS_AUTO;
        ventilateIfNeeded();
        break;
      case 'Z':
        Serial.println("Toggling IsDebug");
        isDebugMode = !isDebugMode;
        break;
    }
    forceSerialOutput();
  }
  delay(1);
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
  bool isTimeToPrintData = lastSerialOutputTime + secondsToMilliseconds(serialOutputIntervalInSeconds) < millis()
      || lastSerialOutputTime == 0;

  bool isReadyToPrintData = isTimeToPrintData && temperatureHumidityDHTSensorReadingHasBeenTaken;

  if (isReadyToPrintData)
  {
    if (isDebugMode)
    {
      Serial.println("Printing serial data");
    }
    
    bool ventilationIsNeeded = checkVentilationIsNeeded();

    if (serialMode == SERIAL_MODE_CSV)
    {
      Serial.print("D;"); // This prefix indicates that the line contains data.
      Serial.print("T:");
      Serial.print(temperatureValue);
      Serial.print(";");
      Serial.print("MxT:");
      Serial.print(maxTemperature);
      Serial.print(";");
      Serial.print("MnT:");
      Serial.print(minTemperature);
      Serial.print(";");
      Serial.print("H:");
      Serial.print(humidityValue);
      Serial.print(";");
      Serial.print("MxH:");
      Serial.print(maxHumidity);
      Serial.print(";");
      Serial.print("MnH:");
      Serial.print(minHumidity);
      Serial.print(";");
      Serial.print("F:");
      Serial.print(fanStatus);
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
      Serial.print("Z:");
      Serial.print(VERSION);
      Serial.print(";;");
      Serial.println();
    }
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
      Serial.print("fanStatus=");
      Serial.print(fanStatus);
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
