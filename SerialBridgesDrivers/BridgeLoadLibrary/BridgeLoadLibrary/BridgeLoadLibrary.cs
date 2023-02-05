using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Diagnostics;
using System.Reflection;

using System.IO;
using InterfaceSerialBridge;

namespace BridgeLoadLibraryLib
{
    [Serializable]
    public class BridgeLoadLibrary: MarshalByRefObject
    {
        public event EventInterruptReceived OnInterruptReceived;

        //interface to be load dinamically with the selected dll
        ISerialBridge mySerialBridge;

        private int _assemblyLoadedStatus;
        public int assemblyLoadedStatus
        {
            get
            {
                return IsRegistered();
            }
        }

        public BridgeLoadLibrary(string path)
        {
            if(mySerialBridge == null)
            {
                try
                {
                    if (!File.Exists(path))
                    {
                        _assemblyLoadedStatus = Defines.ASSEMBLY_PATH_NOT_FOUND;
                    }
                    else
                    {
                        Assembly assembly = Assembly.Load(AssemblyName.GetAssemblyName(path));                        

                        Type[] types = assembly.GetTypes();

                        foreach (Type t in types)
                        {
                            if (t.GetInterface("InterfaceSerialBridge.ISerialBridge") != null)
                            {
                                try
                                {
                                    string s = $"{t}";
                                    object o = Activator.CreateInstance(t);
                                    mySerialBridge = o as ISerialBridge;
                                }
                                catch (Exception ex)
                                {
                                    Debug.WriteLine(ex.Message);
                                }

                                if (mySerialBridge != null)
                                {
                                    //assembly loaded sucesfully
                                    AttachEvents();

                                    _assemblyLoadedStatus = Defines.ASSEMBLY_LOADED_OK;
                                }
                            }
                        }

                        //GetInterface(...) could not found the correct interface asked, wrong assembly 
                        if (_assemblyLoadedStatus != Defines.ASSEMBLY_LOADED_OK)
                        {
                            _assemblyLoadedStatus = Defines.ASSEMBLY_INTERFACE_TO_LOAD_NOT_PRESENT;
                        }
                    }
                }
                catch (Exception ex)
                {
                    Debug.WriteLine(ex.Message);
                }
            }
        }

        ~BridgeLoadLibrary()
        {
            try
            {
                if (_assemblyLoadedStatus == Defines.ASSEMBLY_LOADED_OK)
                {
                    DetachEvents();

                    mySerialBridge.Close();
                    mySerialBridge = null;
                }
                else
                {
                    _assemblyLoadedStatus = Defines.ASSEMBLY_UNLOADING_ERROR;
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
            }
        }

        private void AttachEvents()
        {
            mySerialBridge.OnInterruptReceived += DoOn_InterruptReceived;
        }

        private void DetachEvents()
        {
            mySerialBridge.OnInterruptReceived -= DoOn_InterruptReceived;
        }

        public int IsRegistered()
        {
            return _assemblyLoadedStatus;
        }

        public ISerialBridge GetSerialBridgeObject()
        {
            if (mySerialBridge != null)
            {
                return mySerialBridge;
            }
            else
            {
                return null;
            }
        }

        public void FinalizeSerialBridgeObject()
        {
            mySerialBridge.Close();
        }

        public void UnloadQrObject()
        {
            try
            {
                if (_assemblyLoadedStatus == Defines.ASSEMBLY_LOADED_OK)
                {
                    DetachEvents();
                    mySerialBridge.Close();
                    mySerialBridge = null;
                }
                else
                {
                    _assemblyLoadedStatus = Defines.ASSEMBLY_UNLOADING_ERROR;
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
            }
        }

        //*********************************************************************
        // Functions and procedures to Interface the Serial Bridge Object Loaded
        //*********************************************************************  
        public bool Open()
        {
            return mySerialBridge.Open();
        }

        public bool IsSerialBridgeOpen()
        {
            return mySerialBridge.IsOpen();
        }

        public bool Init()
        {
            return mySerialBridge.Init();
        }

        public bool Close()
        {
            return mySerialBridge.Close();
        }
         
        public bool SendConfigData(byte[] configData)
        {
            return mySerialBridge.SendConfigData(configData);
        }

        public bool SendData(byte[] dataToSend)
        {
            return mySerialBridge.SendData(dataToSend);
        }

        public byte[] ReceiveData()
        {
            return mySerialBridge.ReceiveData();
        }

        //*********************************************************************
        // Properties of the Serial Bridge Object
        //*********************************************************************  
        public string Model
        {
            get
            {
                return mySerialBridge.Model;
            }
        }

        public string Version
        {
            get
            {
                return mySerialBridge.Version;
            }
        }

        //*********************************************************************
        // Event callbacks for Serial Bridge Object Loaded
        //*********************************************************************  
        public void DoOn_InterruptReceived(byte[] interruptbytes)
        {
            OnInterruptReceived?.Invoke(interruptbytes);
        }
    }
}
