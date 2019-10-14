using System;
using System.Collections.Generic;
using System.Threading;
using NUnit.Framework;

namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
    public class FanTestHelper : GrowSenseVentilatorHardwareTestHelper
    {
        public FanMode FanCommand = FanMode.Auto;
        public int SimulatedTemperature = 50;
        public int SimulatedHumidity = 50;
        public int MinTemperature = 1;
        public int MaxTemperature = 60;
        public int MinHumidity = 1;
        public int MaxHumidity = 60;
        public int DurationToCheckFan = 5;

        public void TestFan ()
        {
            WriteTitleText ("Starting fan test");

            Console.WriteLine ("Fan command: " + FanCommand);
            Console.WriteLine ("Simulated temperature: " + SimulatedTemperature + "c");
            Console.WriteLine ("Simulated humidity: " + SimulatedHumidity + "%");
            Console.WriteLine ("Maximum temperature: " + MaxTemperature + "c");
            Console.WriteLine ("Minimum temperature: " + MinTemperature + "c");
            Console.WriteLine ("Maximum humidity: " + MaxHumidity + "%");
            Console.WriteLine ("Minimum humidity: " + MinHumidity + "%");
            Console.WriteLine ("");

            ConnectDevices ();

            ResetDeviceSettings ();

            var cmd = "F" + (int)FanCommand;

            SendDeviceCommand (cmd);
			
            //SimulateDHTSensor(SimulatedTemperature, SimulatedHumidity);

            SendDeviceCommand ("S" + MinTemperature);
            SendDeviceCommand ("U" + MaxTemperature);
            SendDeviceCommand ("G" + MinHumidity);
            SendDeviceCommand ("J" + MaxHumidity);

            // Disable the sensor readings
            SendDeviceCommand ("D");

            // Set the temperature and humidity via commands
            SendDeviceCommand ("T" + SimulatedTemperature);
            SendDeviceCommand ("H" + SimulatedHumidity);

            WaitForData (1);

            var dataEntry = WaitForDataEntry ();

            CheckDataValues (dataEntry);
        }

        public void CheckDataValues (Dictionary<string, string> dataEntry)
        {
            AssertDataValueEquals (dataEntry, "F", (int)FanCommand);
            AssertDataValueEquals (dataEntry, "U", MaxTemperature);
            AssertDataValueEquals (dataEntry, "S", MinTemperature);
            AssertDataValueEquals (dataEntry, "J", MaxHumidity);
            AssertDataValueEquals (dataEntry, "G", MinHumidity);

            // TODO: Check PO value matches the fan

            AssertDataValueEquals (dataEntry, "T", SimulatedTemperature);
            AssertDataValueEquals (dataEntry, "H", SimulatedHumidity);

            switch (FanCommand) {
            case FanMode.Off:
                CheckFanIsOff ();
                break;
            case FanMode.On:
                CheckFanIsOn ();
                break;
            case FanMode.Auto:
                CheckFanIsAuto ();
                break;
            }
        }

        public void CheckFanIsOff ()
        {
            AssertSimulatorPinForDuration ("fan", SimulatorFanPin, false, DurationToCheckFan);
        }

        public void CheckFanIsOn ()
        {
            AssertSimulatorPinForDuration ("fan", SimulatorFanPin, true, DurationToCheckFan);
        }

        public void CheckFanIsAuto ()
        {
            var ventilationIsNeeded = IsVentilationNeeded ();

            Console.WriteLine ("Ventilation is needed");

            if (ventilationIsNeeded) {
                CheckFanIsOn ();

            } else {
                CheckFanIsOff ();
            }
        }

        public bool IsVentilationNeeded ()
        {
            var temperatureIsOutsideRange = SimulatedTemperature > MaxTemperature ||
                                            SimulatedTemperature < MinTemperature;

            var humidityIsOutsideRange = SimulatedHumidity > MaxHumidity ||
                                         SimulatedHumidity < MinHumidity;

            return temperatureIsOutsideRange || humidityIsOutsideRange;
        }
    }
}