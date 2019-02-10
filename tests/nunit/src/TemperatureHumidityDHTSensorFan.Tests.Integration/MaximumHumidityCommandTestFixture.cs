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
	public class MaximumHumidityCommandTestFixture : BaseTestFixture
	{
		[Test]
		public void Test_SetMaximumHumidity_15()
		{
			using (var helper = new MaximumHumidityCommandTestHelper())
			{
				helper.MaximumHumidity = 15;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestMaximumHumidityCommand();
			}
		}

		[Test]
		public void Test_SetMaximumHumidity_25()
		{
			using (var helper = new MaximumHumidityCommandTestHelper())
			{
				helper.MaximumHumidity = 25;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestMaximumHumidityCommand();
			}
		}
	}
}
