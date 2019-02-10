#ifndef TEMPERATUREHUMIDITYDHTSENSOR_H_
#define TEMPERATUREHUMIDITYDHTSENSOR_H_

extern int temperatureValue;
extern int humidityValue;

extern long lastTemperatureHumidityDHTSensorReadingTime;
extern long temperatureHumidityDHTSensorReadingIntervalInSeconds;
extern int temperatureHumidityDHTSensorReadIntervalIsSetFlagAddress;

extern int drySoilMoistureCalibrationValue;
extern int wetSoilMoistureCalibrationValue;

extern bool temperatureHumidityDHTSensorIsEnabled;
extern long lastSensorOnTime;
extern bool temperatureHumidityDHTSensorReadingHasBeenTaken;

void setupTemperatureHumidityDHTSensor();

void setupTemperatureHumidityDHTSensorReadingInterval();

void turnTemperatureHumidityDHTSensorOn();

void turnTemperatureHumidityDHTSensorOff();

void takeTemperatureHumidityDHTSensorReading();

void setTemperature(char* msg);
void setTemperature(long readInterval);

void setHumidity(char* msg);
void setHumidity(long readInterval);

void setTemperatureHumidityDHTSensorReadingInterval(char* msg);
void setTemperatureHumidityDHTSensorReadingInterval(long readInterval);

long getTemperatureHumidityDHTSensorReadingInterval();

void setEEPROMTemperatureHumidityDHTSensorReadingIntervalIsSetFlag();
void removeEEPROMTemperatureHumidityDHTSensorReadingIntervalIsSetFlag();

void restoreDefaultTemperatureHumidityDHTSensorSettings();
void restoreDefaultTemperatureHumidityDHTSensorReadingIntervalSettings();
#endif
/* TEMPERATUREHUMIDITYDHTSENSOR_H_ */
