﻿using System;

namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
    public class ReadIntervalCommandTestHelper : SerialCommandTestHelper
    {
        public int ReadingInterval = 5;

        public void TestSetReadIntervalCommand ()
        {
            Letter = "I";
            Value = ReadingInterval;
            Label = "reading interval";

            TestCommand ();
        }
    }
}
