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

            //get groupboxnames
            GetGroupBoxesToBeFilled();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            InitForm();
        }

        //*********************************************************************
        // Gets the list of names of Form empty group boxes 
        //*********************************************************************
        private List<string> GetGroupBoxesToBeFilled()
        {
            myGroupBoxNamesList.Add(groupBox_BridgeChip_Options.Name);
            myGroupBoxNamesList.Add(groupBox_DataTRansfer.Name);

            //TODO add other groupboxes if must to

            return myGroupBoxNamesList;
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
        // Gets the configuration data of the bridge from form controls
        //*********************************************************************
        byte[] GetConfigDataFromBridgeFormControls(string bridgeName)
        {
            byte[] retval = new byte[Defines.MAX_CONFIG_DATA_BYTES];

            for(int i=0; i< Defines.MAX_CONFIG_DATA_BYTES; i++)
            {
                retval[i] = 0;
            }

            switch(bridgeName)
            {
                case "CH341":
                    
                    if((this.Controls["groupBox_BridgeChip_Options"]).Controls.ContainsKey("CheckBox_SetStream_B7"))
                    {
                        CheckBox myB7CheckBox = (CheckBox)(this.Controls["groupBox_BridgeChip_Options"]).Controls["CheckBox_SetStream_B7"];
                        retval[0] |= (myB7CheckBox.Checked ? (byte)0x80 : (byte)0x00);
                    }

                    if ((this.Controls["groupBox_BridgeChip_Options"]).Controls.ContainsKey("CheckBox_SetStream_B2"))
                    {
                        CheckBox myB2CheckBox = (CheckBox)(this.Controls["groupBox_BridgeChip_Options"]).Controls["CheckBox_SetStream_B2"];
                        retval[0] |= (myB2CheckBox.Checked ? (byte)0x02 : (byte)0x00);
                    }

                    break;

                //TODO Configuration for all other bridges

                default:
                    break;
            }

            return retval;
        }

        //*********************************************************************
        // Attach or detach the created button callbacks to callbacks section functions
        //*********************************************************************
        private void ButtonsClickCallBacks(string operation)
        {           
            GroupBox myGroupBox;
            Button myButton;

            try
            {
                if (myGroupBoxNamesList != null)
                {
                    if (myGroupBoxNamesList.Count > 0)
                    {
                        if (this.Controls[myGroupBoxNamesList[Defines.CONFIG_GROUPBOX_LIST_INDEX]] != null)
                        {
                            myGroupBox = (GroupBox)this.Controls[myGroupBoxNamesList[Defines.CONFIG_GROUPBOX_LIST_INDEX]];

                            if (myGroupBox.Name == myGroupBoxNamesList[Defines.CONFIG_GROUPBOX_LIST_INDEX])
                            {
                                if (myGroupBox.Controls.ContainsKey("button_Send_Bridge_Config"))
                                {
                                    myButton = (Button)myGroupBox.Controls["button_Send_Bridge_Config"];

                                    switch (operation)
                                    {
                                        case Defines.CALLBACK_OPERATION_ATTACH:
                                            myButton.Click += DoOn_SendBridgeConfiguration;
                                            break;

                                        case Defines.CALLBACK_OPERATION_DETTACH:
                                        default:
                                            myButton.Click -= DoOn_SendBridgeConfiguration;
                                            break;
                                    }
                                }
                            }
                        }

                        if (this.Controls[myGroupBoxNamesList[Defines.DATA_GROUPBOX_LIST_INDEX]] != null)
                        {
                            myGroupBox = (GroupBox)this.Controls[myGroupBoxNamesList[Defines.DATA_GROUPBOX_LIST_INDEX]];

                            if (myGroupBox.Name == myGroupBoxNamesList[Defines.DATA_GROUPBOX_LIST_INDEX])
                            {
                                if (myGroupBox.Controls.ContainsKey("button_Write_To_Device"))
                                {
                                    myButton = (Button)myGroupBox.Controls["button_Write_To_Device"];

                                    switch (operation)
                                    {
                                        case Defines.CALLBACK_OPERATION_ATTACH:
                                            myButton.Click += DoOn_WriteToDevice;
                                            break;

                                        case Defines.CALLBACK_OPERATION_DETTACH:
                                        default:
                                            myButton.Click -= DoOn_WriteToDevice;
                                            break;
                                    }
                                }

                                if (myGroupBox.Controls.ContainsKey("button_Write_To_Device"))
                                {
                                    myButton = (Button)myGroupBox.Controls["button_Read_To_Device"];

                                    switch (operation)
                                    {
                                        case Defines.CALLBACK_OPERATION_ATTACH:
                                            myButton.Click += DoOn_ReadFromDevice;
                                            break;

                                        case Defines.CALLBACK_OPERATION_DETTACH:
                                        default:
                                            myButton.Click -= DoOn_ReadFromDevice;
                                            break;
                                    }
                                }
                            }
                        }
                    }
                }

                richTextBox_Log.AppendText("Bridge Buttons attach callbacks operation OK!" + Environment.NewLine);
            }
            catch(Exception ex)
            {
                richTextBox_Log.AppendText("Bridge Buttons attach callbacks operation ERROR!" + Environment.NewLine);
            }
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
                         int errorCreatingControls = Defines.CONTROLS_LOADED_UNKNOWN_ERROR;

                        //create form controls for bridge
                        richTextBox_Log.AppendText("Creating bridge: " + $"{bridgeSelected}" + " configuration controls..." + Environment.NewLine);

                        errorCreatingControls = SerialBridgeControls.CreateControlsFromBridgeConfigFile(this, bridgeSelected, myGroupBoxNamesList);
                        ButtonsClickCallBacks(Defines.CALLBACK_OPERATION_ATTACH); 

                        if (errorCreatingControls == Defines.CONTROLS_LOADED_OK)
                        {
                            richTextBox_Log.AppendText("OK!" + Environment.NewLine);

                            textBox_CommStatus.BackColor = Color.Yellow;
                            textBox_CommStatus.Text = "NOT CONFIGURED";

                            button_CloseBridge.Enabled = true;
                            button_Start_Bridge.Enabled = false;
                        }
                        else
                        {
                            switch (errorCreatingControls)
                            {
                                case Defines.CONTROLS_LOADED_FILE_NOT_EXIST:
                                    richTextBox_Log.AppendText("Failed, xml config file for " + $"{bridgeSelected}" + " does not exists, check path" + Environment.NewLine);
                                    break;

                                case Defines.CONTROLS_LOADED_EXCEPTION_GENERATED:
                                    richTextBox_Log.AppendText("Failed, exception generated" + Environment.NewLine);
                                    break;

                                default:
                                    richTextBox_Log.AppendText("Failed, unknonw error" + Environment.NewLine);
                                    break;
                            }
                        }
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

                int errorRemovingControls = Defines.CONTROLS_REMOVED_UNKNOWN_ERROR;

                //create form controls for bridge
                richTextBox_Log.AppendText("Removing bridge: " + $"{bridgeSelected}" + " configuration controls..." + Environment.NewLine);

                ButtonsClickCallBacks(Defines.CALLBACK_OPERATION_DETTACH);
                errorRemovingControls = SerialBridgeControls.RemoveControls(this, bridgeSelected, myGroupBoxNamesList);
                
                if(errorRemovingControls == Defines.CONTROLS_REMOVED_OK)
                {
                    richTextBox_Log.AppendText("OK!" + Environment.NewLine);

                    DisableBridgeControls();

                    textBox_CommStatus.BackColor = Color.Red;
                    textBox_CommStatus.Text = "NOT CONNECTED";

                    button_CloseBridge.Enabled = false;
                    button_Start_Bridge.Enabled = true;

                    mySerialBridgeLib = null;
                }
                else
                {
                    switch (errorRemovingControls)
                    {
                        case Defines.CONTROLS_REMOVED_EXCEPTION_GENERATED:
                            richTextBox_Log.AppendText("Failed To remove controls, exception generated" + Environment.NewLine);
                            break;

                        default:
                            richTextBox_Log.AppendText("Failed to remove controls, unknonw error" + Environment.NewLine);
                            break;
                    }
                }
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
            Clipboard.SetText(richTextBox_Log.Text);
        }

        //*********************************************************************
        // Form Buttons Bridge Operations Callbacks
        //*********************************************************************
        void DoOn_SendBridgeConfiguration(object sender, EventArgs e)
        {
            byte[] configData = GetConfigDataFromBridgeFormControls(bridgeSelected);

            richTextBox_Log.AppendText("Config sent to bridge:" + Environment.NewLine);
            
            for(int i=0; i < Defines.MAX_CONFIG_DATA_BYTES; i++)
            {
                richTextBox_Log.AppendText("0x" + configData[i].ToString("X2") + " ");
            }
            richTextBox_Log.AppendText(Environment.NewLine);

            mySerialBridgeLib.SendConfigData(configData);

            textBox_CommStatus.Text = "READY!";
            textBox_CommStatus.BackColor = Color.LightGreen;
        }

        void DoOn_WriteToDevice(object sender, EventArgs e)
        {            
            switch(bridgeSelected)
            {
                case "CH341":

                    if ((this.Controls["groupBox_DataTRansfer"]).Controls.ContainsKey("radioButton_SPI_CS0"))
                    {
                        RadioButton CS0myRadioButton = (RadioButton)(this.Controls["groupBox_DataTRansfer"]).Controls["radioButton_SPI_CS0"];
                        retval[1] |= (CS0myRadioButton.Checked ? (byte)0x01 : (byte)0x00);
                    }

                    if ((this.Controls["groupBox_DataTRansfer"]).Controls.ContainsKey("radioButton_SPI_CS1"))
                    {
                        RadioButton CS1myRadioButton = (RadioButton)(this.Controls["groupBox_DataTRansfer"]).Controls["radioButton_SPI_CS1"];
                        retval[1] |= (CS1myRadioButton.Checked ? (byte)0x02 : (byte)0x00);
                    }

                    if ((this.Controls["groupBox_DataTRansfer"]).Controls.ContainsKey("radioButton_SPI_CS2"))
                    {
                        RadioButton CS2myRadioButton = (RadioButton)(this.Controls["groupBox_DataTRansfer"]).Controls["radioButton_SPI_CS2"];
                        retval[1] |= (CS2myRadioButton.Checked ? (byte)0x04 : (byte)0x00);
                    }

                    break;
            }

            richTextBox_Log.AppendText("Send Bridge Data Click" + Environment.NewLine);
        }

        void DoOn_ReadFromDevice(object sender, EventArgs e)
        {
            richTextBox_Log.AppendText("Read Bridge Data Click" + Environment.NewLine);
        }
    }
}
