using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceSerialBridge
{
    public delegate void EventInterruptReceived(byte[] interruptBytes);

    public interface ISerialBridge
    {
        bool Open();
        bool IsOpen();

        bool Close();

        string Model { get; }
        string Version { get; }

        bool Init();

        bool SendConfigData(byte[] configDataToSend);

        bool SendData(byte[] dataToSend);
        byte[] ReceiveData();     
       
        event EventInterruptReceived OnInterruptReceived;        
    }

    // Abstract class as a guide to implement SerialBridges   
    //MarshalByRefObject class is neededto be able to be loaded dynamically
    public abstract class SerialBridge : MarshalByRefObject, ISerialBridge
    {
        public abstract bool Open();
        public abstract bool IsOpen();

        public abstract bool Close();

        public string Version { get; protected set; }
        public string Model { get; protected set; }

        public abstract bool Init();

        public abstract bool SendConfigData(byte[] configDataToSend);

        public abstract bool SendData(byte[] dataToSend);
        public abstract byte[] ReceiveData();       

        public abstract event EventInterruptReceived OnInterruptReceived;
    }
}
