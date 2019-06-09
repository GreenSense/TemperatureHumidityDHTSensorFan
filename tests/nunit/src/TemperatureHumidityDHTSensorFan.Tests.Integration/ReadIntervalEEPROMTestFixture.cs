using System;
using NUnit.Framework;
using duinocom;
using System.Threading;
using ArduinoSerialControllerClient;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.IO.Ports;

namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
    [TestFixture (Category = "Integration")]
    public class ReadIntervalEEPROMTestFixture : BaseTestFixture
    {
        [Test]
        public void Test_SetReadInterval_5sec ()
        {
            using (var helper = new ReadIntervalEEPROMTestHelper ()) {
                helper.ReadInterval = 5;

                helper.DevicePort = GetDevicePort ();
                helper.DeviceBaudRate = GetDeviceSerialBaudRate ();

                helper.SimulatorPort = GetSimulatorPort ();
                helper.SimulatorBaudRate = GetSimulatorSerialBaudRate ();

                helper.TestReadIntervalEEPROM ();
            }
        }

        [Test]
        public void Test_SetReadInterval_6sec ()
        {
            using (var helper = new ReadIntervalEEPROMTestHelper ()) {
                helper.ReadInterval = 6;

                helper.DevicePort = GetDevicePort ();
                helper.DeviceBaudRate = GetDeviceSerialBaudRate ();

                helper.SimulatorPort = GetSimulatorPort ();
                helper.SimulatorBaudRate = GetSimulatorSerialBaudRate ();

                helper.TestReadIntervalEEPROM ();
            }
        }

    }
}
