using System;

namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
	public class GreenSenseVentilatorHardwareTestHelper : GreenSenseHardwareTestHelper
	{
		public int SimulatorFanPin = 2;

		public GreenSenseVentilatorHardwareTestHelper()
		{
		}

		public override void PrepareDeviceForTest(bool consoleWriteDeviceOutput)
		{
			base.PrepareDeviceForTest(false);

			if (consoleWriteDeviceOutput)
				ReadFromDeviceAndOutputToConsole();
		}
	}
}
