using System;

namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
	public class MinimumHumidityEEPROMTestHelper : GreenSenseVentilatorHardwareTestHelper
	{
		public int MinimumHumidity = 30;

		public void TestMinimumHumidityEEPROM()
		{
			WriteTitleText("Starting minimum humidity EEPROM test");

			Console.WriteLine("Minimum humidity: " + MinimumHumidity + "c");
			Console.WriteLine("");

			ConnectDevices();

			ResetDeviceSettings ();

			SendMinimumHumidityCommand();

			ResetDeviceViaPin ();

			var dataEntry = WaitForDataEntry ();

			AssertDataValueEquals(dataEntry, "G", MinimumHumidity);
		}

		public void SendMinimumHumidityCommand()
		{
			var command = "G" + MinimumHumidity;

			WriteParagraphTitleText("Sending minimum humidity command...");

			SendDeviceCommand(command);

			var dataEntry = WaitForDataEntry();

			WriteParagraphTitleText("Checking minimum humidity value...");

			AssertDataValueEquals(dataEntry, "G", MinimumHumidity);
		}
	}
}
