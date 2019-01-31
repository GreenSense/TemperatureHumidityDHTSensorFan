﻿using System;

namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
	public class ThresholdEEPROMTestHelper : GreenSenseIrrigatorHardwareTestHelper
	{
		public int Threshold = 30;

		public void TestThresholdEEPROM()
		{
			WriteTitleText("Starting threshold EEPROM test");

			Console.WriteLine("Threshold: " + Threshold + "%");
			Console.WriteLine("");

			ConnectDevices();

			ResetDeviceSettings ();

			SendThresholdCommand();

			ResetDeviceViaPin ();

			var dataEntry = WaitForDataEntry ();

			AssertDataValueEquals(dataEntry, "T", Threshold);
		}

		public void SendThresholdCommand()
		{
			var command = "T" + Threshold;

			WriteParagraphTitleText("Sending threshold command...");

			SendDeviceCommand(command);

			var dataEntry = WaitForDataEntry();

			WriteParagraphTitleText("Checking threshold value...");

			AssertDataValueEquals(dataEntry, "T", Threshold);
		}
	}
}
