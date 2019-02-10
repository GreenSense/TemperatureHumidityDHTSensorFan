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
	public class MaximumTemperatureCommandTestFixture : BaseTestFixture
	{
		[Test]
		public void Test_SetMaximumTemperature_15()
		{
			using (var helper = new MaximumTemperatureCommandTestHelper())
			{
				helper.MaximumTemperature = 15;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestMaximumTemperatureCommand();
			}
		}

		[Test]
		public void Test_SetMaximumTemperature_25()
		{
			using (var helper = new MaximumTemperatureCommandTestHelper())
			{
				helper.MaximumTemperature = 25;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestMaximumTemperatureCommand();
			}
		}
	}
}
