using System;

namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
	public class GrowSenseVentilatorHardwareTestHelper : GrowSenseHardwareTestHelper
	{
		public int SimulatorFanPin = 2;

		public GrowSenseVentilatorHardwareTestHelper()
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
