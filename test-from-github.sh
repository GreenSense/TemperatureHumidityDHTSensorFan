#!/bin/bash

echo ""
echo "Testing TemperatureHumidityDHTSensorFan project from github"
echo ""

BRANCH=$1

if [ $# -eq 0 ]
then
  BRANCH=$(git branch | sed -n -e 's/^\* \(.*\)/\1/p')
  echo "Branch not specified as argument. Using current branch: $BRANCH"
fi

TIMESTAMP=$(date +"%Y_%m_%d_%I_%M_%p_%s")
TEMPORARY_DIR="/tmp/$TIMESTAMP"

echo "Branch: $BRANCH"
echo "Tmp project dir:"
echo "  $TEMPORARY_DIR"

mkdir -p $TEMPORARY_DIR

cd $TEMPORARY_DIR

git clone http://github.com/GreenSense/TemperatureHumidityDHTSensorFan -b $BRANCH && \

cd TemperatureHumidityDHTSensorFan && \
sh init.sh && \
sh build.sh && \
sh upload.sh && \
sh upload-simulator.sh && \
sh test.sh

rm $TEMPORARY_DIR -rf

echo ""
echo "Finished testing SoilMoistureSensorCalibratedSerial project from github"
echo ""
