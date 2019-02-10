using System;
namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
	public class MinimumTemperatureCommandTestHelper : GreenSenseVentilatorHardwareTestHelper
	{
		public int MinimumTemperature = 30;

		public void TestMinimumTemperatureCommand()
		{
			WriteTitleText("Starting minimum temperature command test");

			Console.WriteLine("Minimum temperature: " + MinimumTemperature + "%");
			Console.WriteLine("");

			ConnectDevices(false);

			SendMinimumTemperatureCommand();
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
