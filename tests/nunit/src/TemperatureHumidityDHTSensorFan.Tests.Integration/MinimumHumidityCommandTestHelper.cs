using System;
namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
	public class MinimumHumidityCommandTestHelper : GreenSenseVentilatorHardwareTestHelper
	{
		public int MinimumHumidity = 30;

		public void TestMinimumHumidityCommand()
		{
			WriteTitleText("Starting minimum humidity command test");

			Console.WriteLine("Minimum humidity: " + MinimumHumidity + "%");
			Console.WriteLine("");

			ConnectDevices(false);

			SendMinimumHumidityCommand();
		}

		public void SendMinimumHumidityCommand()
		{
			var command = "S" + MinimumHumidity;

			WriteParagraphTitleText("Sending minimum humidity command...");

			SendDeviceCommand(command);

			var dataEntry = WaitForDataEntry();

			WriteParagraphTitleText("Checking minimum humidity value...");

			AssertDataValueEquals(dataEntry, "S", MinimumHumidity);
		}
	}
}
