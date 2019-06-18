using System;

namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
    public class MinimumHumidityCommandTestHelper : SerialCommandTestHelper
    {
        public int MinimumHumidity = 30;

        public void TestMinimumHumidityCommand ()
        {      
            Letter = "G";
            Value = MinimumHumidity;
            Label = "minimum humidity";

            TestCommand ();
        }
    }
}
