﻿using System;
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
        public void Test_SetReadInterval_3sec ()
        {
            using (var helper = new ReadIntervalEEPROMTestHelper ()) {
                helper.ReadInterval = 3;

                helper.DevicePort = GetDevicePort ();
                helper.DeviceBaudRate = GetDeviceSerialBaudRate ();

                helper.SimulatorPort = GetSimulatorPort ();
                helper.SimulatorBaudRate = GetSimulatorSerialBaudRate ();

                helper.TestReadIntervalEEPROM ();
            }
        }

        [Test]
        public void Test_SetReadInterval_4sec ()
        {
            using (var helper = new ReadIntervalEEPROMTestHelper ()) {
                helper.ReadInterval = 4;

                helper.DevicePort = GetDevicePort ();
                helper.DeviceBaudRate = GetDeviceSerialBaudRate ();

                helper.SimulatorPort = GetSimulatorPort ();
                helper.SimulatorBaudRate = GetSimulatorSerialBaudRate ();

                helper.TestReadIntervalEEPROM ();
            }
        }

    }
}
