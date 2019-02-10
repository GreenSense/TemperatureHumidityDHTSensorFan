using System;

namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
	public class MinimumTemperatureEEPROMTestHelper : GreenSenseVentilatorHardwareTestHelper
	{
		public int MinimumTemperature = 30;

		public void TestMinimumTemperatureEEPROM()
		{
			WriteTitleText("Starting minimum temperature EEPROM test");

			Console.WriteLine("Minimum temperature: " + MinimumTemperature + "c");
			Console.WriteLine("");

			ConnectDevices();

			ResetDeviceSettings ();

			SendMinimumTemperatureCommand();

			ResetDeviceViaPin ();

			var dataEntry = WaitForDataEntry ();

			AssertDataValueEquals(dataEntry, "S", MinimumTemperature);
		}

		public void SendMinimumTemperatureCommand()
		{
			var command = "S" + MinimumTemperature;

			WriteParagraphTitleText("Sending minimum temperature command...");

			SendDeviceCommand(command);

			var dataEntry = WaitForDataEntry();

			WriteParagraphTitleText("Checking minimum temperature value...");

			AssertDataValueEquals(dataEntry, "S", MinimumTemperature);
		}
	}
}
