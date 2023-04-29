using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.Configuration;

using BridgeLoadLibraryLib;

namespace SPI_Device_Configurator
{    
    public partial class Form1 : Form
    {
        BridgeLoadLibrary mySerialBridgeLib;        

        string bridgeSelected = "";

        List<string> myGroupBoxNamesList = new List<string>();

        public Form1()
        {
            InitializeComponent();
        }

        private void DisableBridgeControls()
        {
            button_CloseBridge.Enabled = false;            
        }

        private void EnableBridgeControls()
        {
            button_CloseBridge.Enabled = true;
        }

        private void InitForm()
        {
            if (comboBox_BridgeChip.Items.Count > 0)
            {
                comboBox_BridgeChip.SelectedIndex = 0;
            }

            textBox_CommStatus.BackColor = Color.Red;

            //disable bridge controls
            DisableBridgeControls();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            InitForm();
        }

        //*********************************************************************
        // Loads the selected bridge Assembly
        //*********************************************************************
        private bool LoadAssembly(string serialbridgeText)
        {
            string pathToAssembly = "";
            bool retVal = false;

            try
            {
                pathToAssembly = ConfigurationManager.AppSettings.Get(Defines.CH341_DRIVER_ASSEMBLY_PATH);
                mySerialBridgeLib = new BridgeLoadLibrary(pathToAssembly);

                if(mySerialBridgeLib.assemblyLoadedStatus == BridgeLoadLibraryLib.Defines.ASSEMBLY_LOADED_OK)
                {
                    richTextBox_Log.AppendText("Device: " + $"{serialbridgeText }" + " Loaded OK!..." + Environment.NewLine);
                }
                else
                {
                    richTextBox_Log.AppendText("Device: " + $"{serialbridgeText }" + " Failed to load assembly..." + Environment.NewLine);
                }                

                retVal = true;
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
                richTextBox_Log.AppendText("Device: " + $"{serialbridgeText }" + " Not found in path: " + $"{pathToAssembly}");

                retVal = false;
            }

            return retVal;
        }

        //*********************************************************************
        // Starts the operations to communicate  and configure the selected bridge
        //*********************************************************************
        private void button_Start_Bridge_Click(object sender, EventArgs e)
        {
            try
            {
                bridgeSelected = comboBox_BridgeChip.SelectedItem.ToString();

                richTextBox_Log.AppendText("Starting Bridge: " + $"{bridgeSelected}" + Environment.NewLine);

                if (LoadAssembly(bridgeSelected))
                {                    
                    if (mySerialBridgeLib.Open())
                    {
                        if(mySerialBridgeLib.Init())
                        {
                            textBox_CommStatus.Text = "CONNECTED";
                            textBox_CommStatus.BackColor = Color.LightGreen;                            

                            EnableBridgeControls();

                            richTextBox_Log.AppendText("Bridge: " + $"{bridgeSelected}" + " " + " Initialized OK"  + Environment.NewLine);
                            richTextBox_Log.AppendText("Bridge Model: " + $"{mySerialBridgeLib.Model}" + " " + " " + Environment.NewLine);
                            richTextBox_Log.AppendText("Bridge FW Version: " + $"{mySerialBridgeLib.Version}" + " " + Environment.NewLine);
                        }
                        else
                        {
                            richTextBox_Log.AppendText("Failed Initializing the bridge: " + $"{bridgeSelected}" + Environment.NewLine);
                        }
                    }
                    else
                    {
                        richTextBox_Log.AppendText("Failed Opening the bridge: " + $"{bridgeSelected}" + Environment.NewLine);
                    }
                }
                else
                {
                    richTextBox_Log.AppendText("Failed, loading bridge driver: " + $"{bridgeSelected}" + Environment.NewLine);
                }
            }
            catch(Exception ex)
            {
                Debug.WriteLine(ex.Message);
            }
        }

        //*********************************************************************
        // Starts the operations to end communication with the selected bridge
        //*********************************************************************
        private void button_CloseBridge_Click(object sender, EventArgs e)
        {
            try
            {
                richTextBox_Log.AppendText("Stopping Bridge: " + $"{bridgeSelected}" + Environment.NewLine);                               

                if(mySerialBridgeLib != null)
                {
                    mySerialBridgeLib.Close();
                    mySerialBridgeLib = null;

                    textBox_CommStatus.Text = "NOT CONNECTED";
                    textBox_CommStatus.BackColor = Color.Red;                    

                    DisableBridgeControls();
                }                               

                //start garbage collector
                System.GC.Collect();
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
            }
        }

        private void button_Tx_Data_Click(object sender, EventArgs e)
        {
            //TODO extract data from tx file 
            int counter = 0;
            string txDataFilePath = "";
            int i = 0;

            byte[] dataArrayToSend;

            if (mySerialBridgeLib == null)
            {
                return;
            }

            txDataFilePath = ConfigurationManager.AppSettings.Get(Defines.TX_DATA_FILE_PATH);

            try
            {
                // Read the file line by line  
                foreach (string line in System.IO.File.ReadLines(txDataFilePath))
                {
                    //jump over comments
                    if (line[0] != '#')
                    {
                        //read each character and create a byte array with the data
                        string[] values = line.Split(' ');
                        dataArrayToSend = new byte[values.Length];

                        //hex string to valid byte 
                        int count = 0;
                        foreach (string dataByte in values)
                        {
                            dataArrayToSend[count] = byte.Parse(values[count], System.Globalization.NumberStyles.AllowHexSpecifier);
                            count++;
                        }
                        count = 0;

                        richTextBox_Log.AppendText("Sending Data: ");
                        foreach (byte dataByte in dataArrayToSend)
                        {
                            richTextBox_Log.AppendText(string.Format("0x{0:X2} ", dataByte));
                        }
                        richTextBox_Log.AppendText(Environment.NewLine);

                        mySerialBridgeLib.SendData(dataArrayToSend);                        
                    }
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
            }
        }

        private void button_Rx_Data_Click(object sender, EventArgs e)
        {
            byte[] dataRcv;
            int i;

            dataRcv = mySerialBridgeLib.ReceiveData();

            richTextBox_Log.AppendText("Data Received: ");
            foreach (byte dataByte in dataRcv)
            {
                richTextBox_Log.AppendText(string.Format("0x{0:X2} ", dataByte));
            }
            richTextBox_Log.AppendText(Environment.NewLine);
        }

        private void button_Clear_Log_Click(object sender, EventArgs e)
        {
            richTextBox_Log.Clear();
        }

        private void button_CopyText_Click(object sender, EventArgs e)
        {
            try
            {
                Clipboard.SetText(richTextBox_Log.Text);
            }       
            catch(Exception ex)
            {
                Debug.WriteLine(ex.Message);
            }
        }
    }
}
