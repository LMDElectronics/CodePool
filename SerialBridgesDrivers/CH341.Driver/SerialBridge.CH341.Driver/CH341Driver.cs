using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Diagnostics;
using CH341;
using InterfaceSerialBridge;

using System.Configuration;

namespace SerialBridgeCH341Driver
{
    public class CH341Driver: SerialBridge
    {
        CH341A myCH341Bridge;

        byte chipSelectToUse;
        string spiInterfaceSpeed;
        bool spiCountSingle;
        bool bitOrderMsb;

        byte[] dataRecv;

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

        public override event EventDataReceived OnDataReceived;
        public override event EventDataTransmited OnDataTransmitted;

        public override event EventInterruptReceived OnInterruptReceived;

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
            bool retVal = false;

            try
            {
                myCH341Bridge.CloseDevice();
                retVal = true;
            }
            catch(Exception ex)
            {
                Debug.WriteLine(ex.Message);
            }            

            return retVal;
        }

        public override bool Init()
        {
            bool retVal = false;
            byte configData = 0;

            ExeConfigurationFileMap cfgFile = new ExeConfigurationFileMap();

            cfgFile.ExeConfigFilename = $@"{System.Reflection.Assembly.GetExecutingAssembly().Location}.config";

            Configuration config = ConfigurationManager.OpenMappedExeConfiguration(cfgFile, ConfigurationUserLevel.None); 

            Debug.WriteLine($"{config}"); System.Diagnostics.Debug.WriteLine($"{config?.AppSettings.Settings["Serial Port Name"]?.Value}");

            try
            {
                chipSelectToUse = byte.Parse(config?.AppSettings.Settings["ChipSelectToUse"]?.Value);
                spiInterfaceSpeed = config?.AppSettings.Settings["InterfaceSpeedInKhz"]?.Value;
                spiCountSingle = (config?.AppSettings.Settings["SPIIOCount"]?.Value == "single") ? true : false;
                bitOrderMsb = (config?.AppSettings.Settings["BitOrder"]?.Value == "MSB") ? true : false;

                switch (spiInterfaceSpeed)
                {
                    case "20":
                        configData |= 0x00;
                        break;

                    case "100":
                        configData |= 0x01;
                        break;

                    case "400":
                        configData |= 0x02;
                        break;

                    case "750":
                        configData |= 0x03;
                        break;

                    default:
                        configData |= 0x01;
                        break;
                }

                if (spiCountSingle)
                {
                    configData &= 0xfb;
                }
                else
                {
                    configData |= 0x04;
                }                    
                
                if(bitOrderMsb)
                {
                    configData |= 0x80;
                }
                else
                {
                    configData &= 0x7F;
                }

                myCH341Bridge.SetStream((uint)configData);

                retVal = true;
            }
            catch(Exception ex)
            {
                Debug.WriteLine(ex.Message);
            }

            return retVal;
        }

        public override bool IsOpen()
        {
            throw new NotImplementedException();
        }

        public override bool SendData(byte[] dataToSend)
        {
            byte iChipSelectConfig = 0;

            switch(chipSelectToUse)
            {
                case 0: iChipSelectConfig = 0x80; break;
                case 1: iChipSelectConfig = 0x81; break;
                case 2: iChipSelectConfig = 0x82; break;
            }

            myCH341Bridge.StreamSPI4(iChipSelectConfig, ref dataToSend);

            dataRecv = dataToSend.ToArray();

            OnDataTransmitted.Invoke();
            OnDataReceived.Invoke(dataToSend);

            return true;
        }

        public override byte[] ReceiveData()
        {
            return dataRecv;
        }        
    }
}
