﻿using System;

namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
    public class ReadIntervalCommandTestHelper : GreenSenseHardwareTestHelper
    {
        public int ReadInterval = 5;

        public ReadIntervalCommandTestHelper ()
        {
        }

        public void TestSetReadIntervalCommand ()
        {
            WriteTitleText ("Starting read interval command test");

            Console.WriteLine ("Read interval: " + ReadInterval);

            ConnectDevices (false);

            SetDeviceReadInterval (ReadInterval);

            var dataEntry = WaitForDataEntry ();

            AssertDataValueEquals (dataEntry, "I", ReadInterval);
        }
    }
}
