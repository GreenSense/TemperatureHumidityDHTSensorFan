using System;

namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
	public class ReadIntervalEEPROMTestHelper : GreenSenseIrrigatorHardwareTestHelper
	{
		public int ReadInterval = 3;

		public void TestReadIntervalEEPROM()
		{
			WriteTitleText("Starting read interval EEPROM test");

			Console.WriteLine("Read interval: " + ReadInterval + "%");
			Console.WriteLine("");

			ConnectDevices();

			ResetDeviceSettings ();

			SendReadIntervalCommand();

			ResetDeviceViaPin ();

			var dataEntry = WaitForDataEntry ();

			AssertDataValueEquals(dataEntry, "V", ReadInterval);
		}

		public void SendReadIntervalCommand()
		{
			var command = "V" + ReadInterval;

			WriteParagraphTitleText("Sending read interval command...");

			SendDeviceCommand(command);

			var dataEntry = WaitForDataEntry();

			WriteParagraphTitleText("Checking read interval value...");

			AssertDataValueEquals(dataEntry, "V", ReadInterval);
		}
	}
}
