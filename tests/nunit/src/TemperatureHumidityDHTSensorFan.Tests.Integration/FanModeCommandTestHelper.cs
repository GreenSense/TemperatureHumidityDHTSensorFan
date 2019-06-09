using System;
namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
	public class FanModeCommandTestHelper : GreenSenseVentilatorHardwareTestHelper
	{
		public FanMode FanMode = FanMode.Auto;

		public void TestFanCommand()
		{
			WriteTitleText("Starting fan mode command test");

			Console.WriteLine("Fan mode: " + FanMode);
			Console.WriteLine("");

			ConnectDevices(false);

			var cmd = "F" + (int)FanMode;

			SendDeviceCommand(cmd);

			var dataEntry = WaitForDataEntry();
			dataEntry = WaitForDataEntry();
			AssertDataValueEquals(dataEntry, "F", (int)FanMode);
		}
	}
}
