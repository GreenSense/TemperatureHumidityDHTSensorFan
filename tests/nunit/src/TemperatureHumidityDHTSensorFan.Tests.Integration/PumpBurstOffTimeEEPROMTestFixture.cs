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
	[TestFixture(Category = "Integration")]
	public class PumpBurstOffTimeEEPROMTestFixture : BaseTestFixture
	{
		[Test]
		public void Test_SetPumpBurstOffTime_1sec()
		{
			using (var helper = new PumpBurstOffTimeEEPROMTestHelper())
			{
				helper.PumpBurstOffTime = 1;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestPumpBurstOffTimeEEPROM();
			}
		}

		[Test]
		public void Test_SetPumpBurstOffTime_5sec()
		{
			using (var helper = new PumpBurstOffTimeEEPROMTestHelper())
			{
				helper.PumpBurstOffTime = 5;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestPumpBurstOffTimeEEPROM();
			}
		}

	}
}
