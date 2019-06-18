using System;

namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
    public class FanModeCommandTestHelper : SerialCommandTestHelper
    {
        public FanMode FanMode = FanMode.Auto;

        public void TestFanCommand ()
        {      
            Letter = "F";
            Value = (int)FanMode;
            Label = "fan mode";

            TestCommand ();
        }
    }
}
