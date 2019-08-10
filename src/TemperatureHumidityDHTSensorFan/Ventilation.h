#ifndef VENTILATION_H_
#define VENTILATION_H_

#include <Arduino.h>
#include "Common.h"

#define FAN_PIN 11

#define FAN_MODE_OFF 0
#define FAN_MODE_ON 1
#define FAN_MODE_AUTO 2

extern int maxTemperature;
extern int minTemperature;
extern int maxHumidity;
extern int minHumidity;

extern bool fanIsOn;
extern unsigned long fanStartTime;
extern unsigned long lastFanFinishTime;
extern int fanMode;

extern int maxTemperatureIsSetEEPROMFlagAddress;
extern int maxTemperatureEEPROMAddress;

extern int minTemperatureIsSetEEPROMFlagAddress;
extern int minTemperatureEEPROMAddress;

extern int maxHumidityIsSetEEPROMFlagAddress;
extern int maxHumidityEEPROMAddress;

extern int minTemperatureIsSetEEPROMFlagAddress;
extern int minTemperatureEEPROMAddress;

void setupVentilation();
void fanOn();
void fanOff();

void setFanMode(char* msg);
void setFanMode(int newMode);

void ventilateIfNeeded();
bool checkVentilationIsNeeded();

void setupMaxTemperature();
void setMaxTemperature(char* msg);
void setMaxTemperature(int newMaxTemperature);
int getMaxTemperature();
void restoreDefaultMaxTemperature();

void setupMinTemperature();
void setMinTemperature(char* msg);
void setMinTemperature(int newMaxTemperature);
int getMinTemperature();
void restoreDefaultMinTemperature();

void setupMaxHumidity();
void setMaxHumidity(char* msg);
void setMaxHumidity(int newMaxHumidity);
int getMaxHumidity();
void restoreDefaultMaxHumidity();

void setupMinHumidity();
void setMinHumidity(char* msg);
void setMinHumidity(int newMaxHumidity);
int getMinHumidity();
void restoreDefaultMinHumidity();

void removeMaxTemperatureEEPROMIsSetFlag();

void restoreDefaultVentilationSettings();
#endif
/* VENTILATION_H_ */
