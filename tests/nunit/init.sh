echo "Initializing nunit tests for TemperatureHumidityDHTSensorFan project"

DIR=$PWD

cd lib && \
sh get-libs.sh && \
cd $DIR
