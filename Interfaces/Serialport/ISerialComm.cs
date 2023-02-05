using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ISerialComms
{
    public delegate void EventDataReady(byte[] data, int dataLength);

    public interface ISerialComm
    {
        //functions and methods
        bool Open();
        bool Close();

        bool WriteData(byte[] data);
        byte[] ReadData();

        bool isCommPortOpen();

        //events
        event EventDataReady OnDataReady;
    }
}
