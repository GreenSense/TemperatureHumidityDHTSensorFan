docker run -i --rm --device /dev/ttyUSB0 --device /dev/ttyUSB1 --device /dev/ttyUSB2 --device /dev/ttyUSB3 -v /var/run/docker.sock:/var/run/docker.sock -v $PWD:/project-src compulsivecoder/ubuntu-arm-iot-mono /bin/bash -c "rsync -azvh /project-src/ /project-dest/ && cd /project-dest && sh init.sh && sh build.sh && sh upload.sh && sh upload-simulator.sh && sh test.sh"

