using NUnit.Framework;

namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
    [TestFixture (Category = "Integration")]
    public class SerialOutputTimeTestFixture : BaseTestFixture
    {
        [Test]
        public void Test_SerialOutputTime_5Seconds ()
        {
            using (var helper = new SerialOutputTimeTestHelper ()) {
                helper.ReadInterval = 5;

                helper.DevicePort = GetDevicePort ();
                helper.DeviceBaudRate = GetDeviceSerialBaudRate ();

                helper.SimulatorPort = GetSimulatorPort ();
                helper.SimulatorBaudRate = GetSimulatorSerialBaudRate ();

                helper.TestSerialOutputTime ();
            }
        }

        [Test]
        public void Test_SerialOutputTime_6Seconds ()
        {
            using (var helper = new SerialOutputTimeTestHelper ()) {
                helper.ReadInterval = 6;

                helper.DevicePort = GetDevicePort ();
                helper.DeviceBaudRate = GetDeviceSerialBaudRate ();

                helper.SimulatorPort = GetSimulatorPort ();
                helper.SimulatorBaudRate = GetSimulatorSerialBaudRate ();

                helper.TestSerialOutputTime ();
            }
        }
    }
}
