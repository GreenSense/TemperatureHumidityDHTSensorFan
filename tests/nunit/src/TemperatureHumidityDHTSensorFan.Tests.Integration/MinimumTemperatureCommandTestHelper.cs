using System;

namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
    public class MinimumTemperatureCommandTestHelper : SerialCommandTestHelper
    {
        public int MinimumTemperature = 30;

        public void TestMinimumTemperatureCommand ()
        {
            Letter = "S";
            Value = MinimumTemperature;
            Label = "minimum temperature";

            TestCommand ();
        }
    }
}
