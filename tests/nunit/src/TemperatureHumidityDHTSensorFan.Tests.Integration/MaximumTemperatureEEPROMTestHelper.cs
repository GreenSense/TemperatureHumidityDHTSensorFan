using System;

namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
	public class MaximumTemperatureEEPROMTestHelper : GreenSenseVentilatorHardwareTestHelper
	{
		public int MaximumTemperature = 30;

		public void TestMaximumTemperatureEEPROM()
		{
			WriteTitleText("Starting maximum temperature EEPROM test");

			Console.WriteLine("Maximum temperature: " + MaximumTemperature + "c");
			Console.WriteLine("");

			ConnectDevices();

			ResetDeviceSettings ();

			SendMaximumTemperatureCommand();

			ResetDeviceViaPin ();

			var dataEntry = WaitForDataEntry ();

			AssertDataValueEquals(dataEntry, "U", MaximumTemperature);
		}

		public void SendMaximumTemperatureCommand()
		{
			var command = "U" + MaximumTemperature;

			WriteParagraphTitleText("Sending maximum temperature command...");

			SendDeviceCommand(command);

			var dataEntry = WaitForDataEntry();

			WriteParagraphTitleText("Checking maximum temperature value...");

			AssertDataValueEquals(dataEntry, "U", MaximumTemperature);
		}
	}
}
