using System;
using System.Threading;
using NUnit.Framework;

namespace TemperatureHumidityDHTSensorFan.Tests.Integration
{
    public class GrowSenseHardwareTestHelper : HardwareTestHelper
    {
        public int RawValueMarginOfError = 25;
        public int CalibratedValueMarginOfError = 3;
        public double TimeErrorMargin = 0.3;

        public GrowSenseHardwareTestHelper ()
        {
        }

        #region Enable Devices Functions

        public override void ConnectDevices (bool enableSimulator)
        {
            base.ConnectDevices (enableSimulator);

            PrepareDeviceForTest ();
        }

        #endregion

        #region Prepare Device Functions

        public virtual void PrepareDeviceForTest ()
        {
            PrepareDeviceForTest (true);
        }

        public virtual void PrepareDeviceForTest (bool consoleWriteDeviceOutput)
        {
            ResetDeviceSettings ();

            SetDeviceReadInterval (5);

            if (consoleWriteDeviceOutput)
                ReadFromDeviceAndOutputToConsole ();
        }

        #endregion

        #region General Device Command Settings

        public void SendDeviceCommand (string command)
        {
            WriteToDevice (command);

            WaitForMessageReceived (command);
        }

        public void WaitForMessageReceived (string message)
        {
            Console.WriteLine ("");
            Console.WriteLine ("Waiting for received message: " + message);

            var output = String.Empty;
            var wasMessageReceived = false;

            var startTime = DateTime.Now;

            while (!wasMessageReceived) {
                output += ReadLineFromDevice ();

                var expectedText = "Received message: " + message;
                if (output.Contains (expectedText)) {
                    wasMessageReceived = true;
                }

                var hasTimedOut = DateTime.Now.Subtract (startTime).TotalSeconds > TimeoutWaitingForResponse;
                if (hasTimedOut && !wasMessageReceived) {
                    ConsoleWriteSerialOutput (output);

                    Assert.Fail ("Timed out waiting for message received (" + TimeoutWaitingForResponse + " seconds)");
                }
            }
        }

        #endregion

        #region Specific Device Command Functions

        public void ResetDeviceSettings ()
        {
            var cmd = "X";

            Console.WriteLine ("");
            Console.WriteLine ("Resetting device default settings...");
            Console.WriteLine ("  Sending '" + cmd + "' command to device");
            Console.WriteLine ("");

            SendDeviceCommand (cmd);
        }

        public void SetDeviceReadInterval (int numberOfSeconds)
        {
            var cmd = "I" + numberOfSeconds;

            Console.WriteLine ("");
            Console.WriteLine ("Setting device read interval to " + numberOfSeconds + " second(s)...");
            Console.WriteLine ("  Sending '" + cmd + "' command to device");
            Console.WriteLine ("");

            SendDeviceCommand (cmd);
        }

        #endregion
    }
}
