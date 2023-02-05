using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Diagnostics;
using CH341;
using InterfaceSerialBridge;

namespace SerialBridgeCH341Driver
{
    public class CH341Driver: SerialBridge
    {
        CH341A myCH341Bridge;

        public CH341Driver()
        {
            myCH341Bridge = new CH341A(0);
        }

        public CH341Driver(int devNumber)
        {
            myCH341Bridge = new CH341A((uint)devNumber);
        }

        ~CH341Driver()
        {

        }               

        public override bool Open()
        {
            bool retVal = false;

            try
            {
                if (myCH341Bridge.OpenDevice())
                {
                    Model = myCH341Bridge.GetDeviceName();
                    Version = myCH341Bridge.GetDrvVersion().ToString();
                    
                    retVal = true;
                }
                else
                {
                    retVal = false;
                }

                return retVal;
            }
            catch(Exception ex)
            {
                Debug.WriteLine(ex.Message);
                return retVal;
            }
        }

        public override bool Close()
        {
            throw new NotImplementedException();
        }

        public override bool Init()
        {
            throw new NotImplementedException();
        }

        public override bool IsOpen()
        {
            throw new NotImplementedException();
        }

        public override bool SendConfigData(byte[] configDataToSend)
        {
           return myCH341Bridge.SetStream(configDataToSend[0]);
        }

        public override bool SendData(byte[] dataToSend)
        {
            throw new NotImplementedException();
        }

        public override byte[] ReceiveData()
        {
            throw new NotImplementedException();
        }

        public override event EventInterruptReceived OnInterruptReceived;
    }
}
