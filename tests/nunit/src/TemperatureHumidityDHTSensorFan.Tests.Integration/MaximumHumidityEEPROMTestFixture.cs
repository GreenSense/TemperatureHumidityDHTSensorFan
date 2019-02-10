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
	public class MaximumHumidityEEPROMTestFixture : BaseTestFixture
	{
		[Test]
		public void Test_SetMaximumHumidity_25()
		{
			using (var helper = new MaximumHumidityEEPROMTestHelper())
			{
				helper.MaximumHumidity = 25;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestMaximumHumidityEEPROM();
			}
		}

		[Test]
		public void Test_SetMaximumHumidity_40()
		{
			using (var helper = new MaximumHumidityEEPROMTestHelper())
			{
				helper.MaximumHumidity = 40;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestMaximumHumidityEEPROM();
			}
		}

	}
}
