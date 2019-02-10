using System;
namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
	public class MaximumTemperatureCommandTestHelper : GreenSenseVentilatorHardwareTestHelper
	{
		public int MaximumTemperature = 30;

		public void TestMaximumTemperatureCommand()
		{
			WriteTitleText("Starting maximum temperature command test");

			Console.WriteLine("Maximum temperature: " + MaximumTemperature + "%");
			Console.WriteLine("");

			ConnectDevices(false);

			SendMaximumTemperatureCommand();
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
