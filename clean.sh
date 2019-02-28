#pio run --target clean

SOURCE_FILE="src/TemperatureHumidityDHTSensorFan/TemperatureHumidityDHTSensorFan.ino"

sed -i "s/#define VERSION .*/#define VERSION \"1-0-0-0\"/" $SOURCE_FILE

if [ -d tests/nunit/src/TemperatureHumidityDHTSensorFan.Tests.Integration/obj ]; then
  rm tests/nunit/src/TemperatureHumidityDHTSensorFan.Tests.Integration/obj -R
fi
