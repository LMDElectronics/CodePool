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
                        //TODO load configuration from file
                    }
                    else
                    {
                        richTextBox_Log.AppendText("Failed Opening the bridge: " + $"{bridgeSelected}" + Environment.NewLine);
                    }
                }
                else
                {
                    richTextBox_Log.AppendText("Failed, Openning the device " + $"{bridgeSelected}" + Environment.NewLine);
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

                mySerialBridgeLib = null;
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
            }
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

        void DoOn_WriteToDevice(object sender, EventArgs e)
        {
            richTextBox_Log.AppendText("Send Bridge Data Click" + Environment.NewLine);
        }

        void DoOn_ReadFromDevice(object sender, EventArgs e)
        {
            richTextBox_Log.AppendText("Read Bridge Data Click" + Environment.NewLine);
        }
    }
}
