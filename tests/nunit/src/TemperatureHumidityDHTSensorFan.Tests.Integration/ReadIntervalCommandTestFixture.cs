using NUnit.Framework;

namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
    [TestFixture (Category = "Integration")]
    public class ReadIntervalCommandTestFixture : BaseTestFixture
    {
        [Test]
        public void Test_SetReadIntervalCommand_5Second ()
        {
            using (var helper = new ReadIntervalCommandTestHelper ()) {
                helper.ReadingInterval = 5;

                helper.DevicePort = GetDevicePort ();
                helper.DeviceBaudRate = GetDeviceSerialBaudRate ();

                helper.SimulatorPort = GetSimulatorPort ();
                helper.SimulatorBaudRate = GetSimulatorSerialBaudRate ();

                helper.TestSetReadIntervalCommand ();
            }
        }

        [Test]
        public void Test_SetReadIntervalCommand_6Seconds ()
        {
            using (var helper = new ReadIntervalCommandTestHelper ()) {
                helper.ReadingInterval = 6;

                helper.DevicePort = GetDevicePort ();
                helper.DeviceBaudRate = GetDeviceSerialBaudRate ();

                helper.SimulatorPort = GetSimulatorPort ();
                helper.SimulatorBaudRate = GetSimulatorSerialBaudRate ();

                helper.TestSetReadIntervalCommand ();
            }
        }
    }
}
