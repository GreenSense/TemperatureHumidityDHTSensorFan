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
	public class FanModeCommandTestFixture : BaseTestFixture
	{
		[Test]
		public void Test_SetFanToOn()
		{
			using (var helper = new FanModeCommandTestHelper())
			{
				helper.FanMode = FanMode.On;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestFanCommand();
			}
		}

		[Test]
		public void Test_SetFanToOff()
		{
			using (var helper = new FanModeCommandTestHelper())
			{
				helper.FanMode = FanMode.Off;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestFanCommand();
			}
		}

		[Test]
		public void Test_SetFanToAuto()
		{
			using (var helper = new FanModeCommandTestHelper())
			{
				helper.FanMode = FanMode.Auto;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestFanCommand();
			}
		}
	}
}
