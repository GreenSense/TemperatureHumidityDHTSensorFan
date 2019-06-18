using System;

namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
    public class MaximumTemperatureCommandTestHelper : SerialCommandTestHelper
    {
        public int MaximumTemperature = 30;

        public void TestMaximumTemperatureCommand ()
        {      
            Letter = "U";
            Value = MaximumTemperature;
            Label = "maximum temperature";

            TestCommand ();
        }
    }
}
