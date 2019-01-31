﻿using System;
namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
	public class PumpCommandTestHelper : GreenSenseIrrigatorHardwareTestHelper
	{
		public PumpStatus PumpCommand = PumpStatus.Auto;

		public void TestPumpCommand()
		{
			WriteTitleText("Starting pump command test");

			Console.WriteLine("Pump command: " + PumpCommand);
			Console.WriteLine("");

			ConnectDevices(false);

			var cmd = "P" + (int)PumpCommand;

			SendDeviceCommand(cmd);

			var dataEntry = WaitForDataEntry();
			dataEntry = WaitForDataEntry();
			AssertDataValueEquals(dataEntry, "P", (int)PumpCommand);
		}
	}
}