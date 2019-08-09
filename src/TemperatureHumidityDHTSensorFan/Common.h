#ifndef COMMON_H_
#define COMMON_H_

extern const int ANALOG_MAX;

extern long lastSerialOutputTime; // Milliseconds
extern long serialOutputIntervalInSeconds;

extern bool isDebugMode;

extern long loopNumber;

void serialPrintLoopHeader();
void serialPrintLoopFooter();

void EEPROMWriteLong(int address, long value);
long EEPROMReadLong(int address);

void setEEPROMFlag(int eepromFlagAddress);

long secondsToMilliseconds(int seconds);
float millisecondsToSecondsWithDecimal(int milliseconds);

void forceSerialOutput();

#endif
/* COMMON_H_ */
