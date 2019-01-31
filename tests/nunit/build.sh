echo "Starting build for project"
echo "Dir: $PWD"

DIR=$PWD

xbuild src/TemperatureHumidityDHTSensorFan.sln /p:Configuration=Release
