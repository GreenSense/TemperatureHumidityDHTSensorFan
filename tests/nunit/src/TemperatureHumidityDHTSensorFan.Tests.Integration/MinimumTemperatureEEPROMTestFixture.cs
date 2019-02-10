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
	public class MinimumTemperatureEEPROMTestFixture : BaseTestFixture
	{
		[Test]
		public void Test_SetMinimumTemperature_25()
		{
			using (var helper = new MinimumTemperatureEEPROMTestHelper())
			{
				helper.MinimumTemperature = 25;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestMinimumTemperatureEEPROM();
			}
		}

		[Test]
		public void Test_SetMinimumTemperature_40()
		{
			using (var helper = new MinimumTemperatureEEPROMTestHelper())
			{
				helper.MinimumTemperature = 40;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestMinimumTemperatureEEPROM();
			}
		}

	}
}
