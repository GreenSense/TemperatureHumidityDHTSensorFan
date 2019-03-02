echo "Injecting version into sketch..."

VERSION=$(cat version.txt)
BUILD_NUMBER=$(cat buildnumber.txt)

FULL_VERSION="$VERSION-$BUILD_NUMBER"

echo "Version: $FULL_VERSION"

SOURCE_FILE="src/TemperatureHumidityDHTSensorFan/TemperatureHumidityDHTSensorFan.ino"

echo "Source file:"
echo "$SOURCE_FILE"

sed -i "s/#define VERSION .*/#define VERSION \"$FULL_VERSION\"/" $SOURCE_FILE || exit 1

echo "Done"
