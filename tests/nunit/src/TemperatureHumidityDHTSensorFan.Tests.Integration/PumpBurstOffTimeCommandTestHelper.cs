﻿using System;
namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
	public class PumpBurstOffTimeCommandTestHelper : GreenSenseIrrigatorHardwareTestHelper
	{
		public int PumpBurstOffTime = 1;

		public void TestPumpBurstOffTimeCommand()
		{
			WriteTitleText("Starting pump burst off time command test");

			Console.WriteLine("Pump burst off time: " + PumpBurstOffTime);
			Console.WriteLine("");

			ConnectDevices(false);

			var cmd = "O" + PumpBurstOffTime;

			SendDeviceCommand(cmd);

			var dataEntry = WaitForDataEntry();

			AssertDataValueEquals(dataEntry, "O", PumpBurstOffTime);
		}
	}
}