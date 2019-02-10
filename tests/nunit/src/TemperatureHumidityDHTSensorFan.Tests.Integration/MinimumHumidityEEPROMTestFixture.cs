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
	[TestFixture(Category = "Integration")]
	public class MinimumHumidityEEPROMTestFixture : BaseTestFixture
	{
		[Test]
		public void Test_SetMinimumHumidity_25()
		{
			using (var helper = new MinimumHumidityEEPROMTestHelper())
			{
				helper.MinimumHumidity = 25;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestMinimumHumidityEEPROM();
			}
		}

		[Test]
		public void Test_SetMinimumHumidity_40()
		{
			using (var helper = new MinimumHumidityEEPROMTestHelper())
			{
				helper.MinimumHumidity = 40;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestMinimumHumidityEEPROM();
			}
		}

	}
}
