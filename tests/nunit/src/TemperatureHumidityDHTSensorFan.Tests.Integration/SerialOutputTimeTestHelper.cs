﻿using System;
namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
	public class SerialOutputTimeTestHelper : GreenSenseHardwareTestHelper
	{
		public int ReadInterval = 3;

		public void TestSerialOutputTime()
		{
			WriteTitleText("Starting serial output time test");

			Console.WriteLine("Read interval: " + ReadInterval);

			ConnectDevices(false);

			SetDeviceReadInterval(ReadInterval);

			ReadFromDeviceAndOutputToConsole();

			// Skip some data
			WaitForData(3);

			// Get the time until the next data line
			var secondsBetweenDataLines = WaitUntilDataLine();

			var expectedTimeBetweenDataLines = ReadInterval;

			Console.WriteLine("Time between data lines: " + secondsBetweenDataLines + " seconds");

			AssertIsWithinRange("serial output time", expectedTimeBetweenDataLines, secondsBetweenDataLines, TimeErrorMargin);
		}
	}
}
