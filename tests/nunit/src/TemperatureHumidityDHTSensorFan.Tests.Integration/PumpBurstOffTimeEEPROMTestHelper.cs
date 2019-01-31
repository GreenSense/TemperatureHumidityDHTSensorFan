﻿using System;

namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
	public class PumpBurstOffTimeEEPROMTestHelper : GreenSenseIrrigatorHardwareTestHelper
	{
		public int PumpBurstOffTime = 3;

		public void TestPumpBurstOffTimeEEPROM()
		{
			WriteTitleText("Starting pump burst off time EEPROM test");

			Console.WriteLine("Pump burst off time: " + PumpBurstOffTime + "%");
			Console.WriteLine("");

			ConnectDevices();

			ResetDeviceSettings ();

			SendPumpBurstOffTimeCommand();

			ResetDeviceViaPin ();

			var dataEntry = WaitForDataEntry ();

			AssertDataValueEquals(dataEntry, "O", PumpBurstOffTime);
		}

		public void SendPumpBurstOffTimeCommand()
		{
			var command = "O" + PumpBurstOffTime;

			WriteParagraphTitleText("Sending pump burst off time command...");

			SendDeviceCommand(command);

			var dataEntry = WaitForDataEntry();

			WriteParagraphTitleText("Checking pump burst off time value...");

			AssertDataValueEquals(dataEntry, "O", PumpBurstOffTime);
		}
	}
}
