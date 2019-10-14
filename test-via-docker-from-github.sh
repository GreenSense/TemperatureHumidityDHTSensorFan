#!/bin/bash

docker run -i --rm --device /dev/ttyUSB0 --device /dev/ttyUSB1 -v /var/run/docker.sock:/var/run/docker.sock -v $PWD:/project compulsivecoder/ubuntu-arm-iot-mono /bin/bash -c "git clone http://github.com/GrowSense/TemperatureHumidityDHTSensorFan && cd TemperatureHumidityDHTSensorFan && sh init.sh && sh build.sh && sh upload.sh && sh upload-simulator.sh && sh test.sh"

