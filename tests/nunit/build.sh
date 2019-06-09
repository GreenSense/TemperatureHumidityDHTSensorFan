echo "Building project tests"
echo "Dir: $PWD"


xbuild src/TemperatureHumidityDHTSensorFan.sln /p:Configuration=Release /verbosity:quiet || exit 1

echo "Finished building project tests."
