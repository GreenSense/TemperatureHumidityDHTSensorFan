using System;

namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
	public class MaximumHumidityEEPROMTestHelper : GreenSenseVentilatorHardwareTestHelper
	{
		public int MaximumHumidity = 30;

		public void TestMaximumHumidityEEPROM()
		{
			WriteTitleText("Starting maximum humidity EEPROM test");

			Console.WriteLine("Maximum humidity: " + MaximumHumidity + "c");
			Console.WriteLine("");

			ConnectDevices();

			ResetDeviceSettings ();

			SendMaximumHumidityCommand();

			ResetDeviceViaPin ();

			var dataEntry = WaitForDataEntry ();

			AssertDataValueEquals(dataEntry, "J", MaximumHumidity);
		}

		public void SendMaximumHumidityCommand()
		{
			var command = "J" + MaximumHumidity;

			WriteParagraphTitleText("Sending maximum humidity command...");

			SendDeviceCommand(command);

			var dataEntry = WaitForDataEntry();

			WriteParagraphTitleText("Checking maximum humidity value...");

			AssertDataValueEquals(dataEntry, "J", MaximumHumidity);
		}
	}
}
