using System;

namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
    public class MaximumHumidityCommandTestHelper : SerialCommandTestHelper
    {
        public int MaximumHumidity = 30;

        public void TestMaximumHumidityCommand ()
        {
            Letter = "J";
            Value = MaximumHumidity;
            Label = "maximum humidity";

            TestCommand ();
        }
    }
}
