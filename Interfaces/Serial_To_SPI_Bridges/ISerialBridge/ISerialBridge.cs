using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceSerialBridge
{
    public delegate void EventInterruptReceived(byte[] interruptBytes);
    public delegate void EventDataTransmited();
    public delegate void EventDataReceived(byte[] dataReceived);

    public interface ISerialBridge
    {
        bool Open();
        bool IsOpen();

        bool Close();

        string Model { get; }
        string Version { get; }

        bool Init();

        bool SendData(byte[] dataToSend);
        byte[] ReceiveData();

        event EventDataReceived OnDataReceived;
        event EventDataTransmited OnDataTransmitted;

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

        public abstract bool SendData(byte[] dataToSend);
        public abstract byte[] ReceiveData();       

        public abstract event EventDataReceived OnDataReceived;
        public abstract event EventDataTransmited OnDataTransmitted;

        public abstract event EventInterruptReceived OnInterruptReceived;
    }
}
