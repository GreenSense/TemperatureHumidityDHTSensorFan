#ifndef TEMPERATUREHUMIDITYDHTSENSOR_H_
#define TEMPERATUREHUMIDITYDHTSENSOR_H_

extern float temperatureValue;
extern float humidityValue;

extern long lastTemperatureHumidityDHTSensorReadingTime;
extern long temperatureHumidityDHTSensorReadingIntervalInSeconds;
extern int temperatureHumidityDHTSensorReadIntervalIsSetFlagAddress;

extern int drySoilMoistureCalibrationValue;
extern int wetSoilMoistureCalibrationValue;

extern bool temperatureHumidityDHTSensorIsOn;
extern long lastSensorOnTime;
extern int delayAfterTurningSensorOn;
extern bool temperatureHumidityDHTSensorReadingHasBeenTaken;

void setupTemperatureHumidityDHTSensor();

void setupTemperatureHumidityDHTSensorReadingInterval();

void turnTemperatureHumidityDHTSensorOn();

void turnTemperatureHumidityDHTSensorOff();

void takeTemperatureHumidityDHTSensorReading();

void setTemperatureHumidityDHTSensorReadingInterval(char* msg);
void setTemperatureHumidityDHTSensorReadingInterval(long readInterval);

long getTemperatureHumidityDHTSensorReadingInterval();

void setEEPROMTemperatureHumidityDHTSensorReadingIntervalIsSetFlag();
void removeEEPROMTemperatureHumidityDHTSensorReadingIntervalIsSetFlag();

void restoreDefaultTemperatureHumidityDHTSensorSettings();
void restoreDefaultTemperatureHumidityDHTSensorReadingIntervalSettings();
#endif
/* TEMPERATUREHUMIDITYDHTSENSOR_H_ */
