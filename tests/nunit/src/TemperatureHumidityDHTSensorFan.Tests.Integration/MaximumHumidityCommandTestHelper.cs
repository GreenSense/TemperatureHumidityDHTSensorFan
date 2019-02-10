using System;
namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
	public class MaximumHumidityCommandTestHelper : GreenSenseVentilatorHardwareTestHelper
	{
		public int MaximumHumidity = 30;

		public void TestMaximumHumidityCommand()
		{
			WriteTitleText("Starting maximum humidity command test");

			Console.WriteLine("Maximum humidity: " + MaximumHumidity + "%");
			Console.WriteLine("");

			ConnectDevices(false);

			SendMaximumHumidityCommand();
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
