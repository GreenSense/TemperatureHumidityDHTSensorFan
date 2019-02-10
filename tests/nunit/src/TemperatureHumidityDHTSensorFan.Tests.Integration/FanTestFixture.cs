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
	public class FanTestFixture : BaseTestFixture
	{
		[Test]
		public void Test_FanOn()
		{
			using (var helper = new FanTestHelper())
			{
				helper.FanCommand = FanMode.On;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestFan();
			}
		}

		[Test]
		public void Test_FanOff()
		{
			using (var helper = new FanTestHelper())
			{
				helper.FanCommand = FanMode.Off;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestFan();
			}
		}

		[Test]
		public void Test_FanAuto_VentilationNeeded_TooHot()
		{
			using (var helper = new FanTestHelper())
			{
				helper.FanCommand = FanMode.Auto;
				helper.SimulatedTemperature = 30;
				helper.SimulatedHumidity = 50;
				helper.MaxTemperature = 25;
				helper.MaxHumidity = 60;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestFan();
			}
		}

		[Test]
		public void Test_FanAuto_VentilationNeeded_TooCold()
		{
			using (var helper = new FanTestHelper())
			{
				helper.FanCommand = FanMode.Auto;
				helper.SimulatedTemperature = 50;
				helper.SimulatedHumidity = 50;
				helper.MaxTemperature = 100;
				helper.MinTemperature = 60;
				helper.MaxHumidity = 100;
				helper.MinHumidity = 1;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestFan();
			}
		}

		[Test]
		public void Test_FanAuto_VentilationNeeded_TooHumid()
		{
			using (var helper = new FanTestHelper())
			{
				helper.FanCommand = FanMode.Auto;
				helper.SimulatedTemperature = 50;
				helper.SimulatedHumidity = 50;
				helper.MaxTemperature = 100;
				helper.MinTemperature = 1;
				helper.MaxHumidity = 40;
				helper.MinHumidity = 1;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestFan();
			}
		}

		[Test]
		public void Test_FanAuto_VentilationNeeded_TooDry()
		{
			using (var helper = new FanTestHelper())
			{
				helper.FanCommand = FanMode.Auto;
				helper.SimulatedTemperature = 50;
				helper.SimulatedHumidity = 50;
				helper.MaxTemperature = 100;
				helper.MinTemperature = 1;
				helper.MaxHumidity = 100;
				helper.MinHumidity = 40;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestFan();
			}
		}

		[Test]
		public void Test_FanAuto_VentilationNotNeeded()
		{
			using (var helper = new FanTestHelper())
			{
				helper.FanCommand = FanMode.Auto;
				helper.SimulatedTemperature = 50;
				helper.SimulatedHumidity = 50;
				helper.MaxTemperature = 100;
				helper.MinTemperature = 1;
				helper.MaxHumidity = 100;
				helper.MinHumidity = 1;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestFan();
			}
		}
	}
}
