using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Windows.Forms;
using System.Xml;
using System.Configuration;

using System.IO;
using System.Diagnostics;

using SPI_Device_Configurator.FormBridgeControlXmlSerializedClasses;
using SPI_Device_Configurator.XMLSerializer;

namespace SPI_Device_Configurator
{
	//****************************************************************************
	// Configuration manager clases
	//****************************************************************************
	public static class SerialBridgeControls
	{
		public static int CreateControlsFromBridgeConfigFile(Form myForm, string bridgeType, List<string> groupBoxNamesList)
		{
			int retVal = Defines.CONTROLS_LOADED_UNKNOWN_ERROR;

			GroupControlsCatalog mycatalog = new GroupControlsCatalog();
			GenericXMLSerializer myXmlSerializer = new GenericXMLSerializer();
			XmlDocument myXmlData = new XmlDocument();
			
			Control myGroupBoxToAddControls;						

			string pathtoXmlControlsCatalog = "";

			try
			{
				//load xml data into string 
				pathtoXmlControlsCatalog = ConfigurationManager.AppSettings.Get("pathToSerialBridgeControlsGeneration") + "\\" + bridgeType + ".xml";

				if (File.Exists(pathtoXmlControlsCatalog))
				{
					myXmlData.Load(pathtoXmlControlsCatalog);

					//deserialize xml string data
					mycatalog = myXmlSerializer.Deserialize<GroupControlsCatalog>(myXmlData.InnerXml);

					int i = 0;
					foreach (ControlsCataLog myGroupOfControls in mycatalog.groupCatalog)
					{
						if((myForm.Controls.ContainsKey(groupBoxNamesList[i]) == true) && (groupBoxNamesList.Count > 0) && (groupBoxNamesList != null))
						{
							//fill each groupBox control to be filled with the controls of the bridge selected
							myGroupBoxToAddControls = myForm.Controls[groupBoxNamesList[i]];

							if(myGroupOfControls.ButtonCatalog != null)
							{
								if ((myGroupOfControls.ButtonCatalog.listOfButton.Count > 0))
								{
									foreach (SerButton myControl in myGroupOfControls.ButtonCatalog.listOfButton)
									{
										myGroupBoxToAddControls.Controls.Add
										(
											new Button
											{
												Name = myControl.Name,
												Text = myControl.Text,
												Width = Int32.Parse(myControl.Width),
												Height = Int32.Parse(myControl.Height),
												Location = new System.Drawing.Point(myControl.xPosition, myControl.yPosition),
												TextAlign = myControl.textAlignment
											}
										); 
									}
								}
							}

							if(myGroupOfControls.CheckBoxCatalog != null)
							{
								if (myGroupOfControls.CheckBoxCatalog.listOfCheckBox.Count > 0)
								{
									foreach (SerCheckBox myControl in myGroupOfControls.CheckBoxCatalog.listOfCheckBox)
									{
										myGroupBoxToAddControls.Controls.Add
										(
											new CheckBox
											{
												Name = myControl.Name,
												Text = myControl.Text,
												AutoSize = bool.Parse(myControl.Autosize),
												Checked = bool.Parse(myControl.Checked),
												Location = new System.Drawing.Point(myControl.xPosition, myControl.yPosition)
											}
										);
									}
								}
							}

							//if (myGroupOfControls.RadioButtonCatalog != null)
							{
								if (myGroupOfControls.RadioButtonCatalog.listOfRadioButton.Count > 0)
								{
									foreach (SerRadioButton myControl in myGroupOfControls.RadioButtonCatalog.listOfRadioButton)
									{
										myGroupBoxToAddControls.Controls.Add
										(
											new RadioButton
											{
												Name = myControl.Name,
												Text = myControl.Text,
												Location = new System.Drawing.Point(myControl.xPosition, myControl.yPosition)
											}
										);
									}
								}
							}

							//get the next group of controls to be created in the next groupBox
							i++;
						}
					}
					i = 0;					

					retVal = Defines.CONTROLS_LOADED_OK;
				}
				else
				{
					retVal = Defines.CONTROLS_LOADED_FILE_NOT_EXIST;
					Debug.WriteLine("Error loading xml file: " + $"{pathtoXmlControlsCatalog}");
				}
			}
			catch (Exception ex)
			{
				retVal = Defines.CONTROLS_LOADED_EXCEPTION_GENERATED;
				Debug.WriteLine(ex.Message);
			}

			return retVal;
		}

		public static int RemoveControls(Form myForm, string bridgeType, List<string> groupBoxNamesList)
		{
			int retVal = Defines.CONTROLS_REMOVED_UNKNOWN_ERROR;				
			Control myGroupBoxToAddControls;

			try
			{
				int i = 0;
				foreach(string groupBoxName in groupBoxNamesList)
				{
					if(myForm.Controls.ContainsKey(groupBoxName))
					{
						myGroupBoxToAddControls = myForm.Controls[groupBoxNamesList[i]];

						if (myGroupBoxToAddControls.HasChildren)
						{
							myGroupBoxToAddControls.Controls.Clear();
							retVal = Defines.CONTROLS_REMOVED_OK;
						}
						else
						{
							retVal = Defines.CONTROLS_LOADED_UNKNOWN_ERROR;
						}
					}					

					i++;
				}
				i = 0;					
			}
			catch(Exception ex)
			{
				retVal = Defines.CONTROLS_REMOVED_EXCEPTION_GENERATED;
				Debug.WriteLine(ex.Message);
			}

			return retVal;
		}		
	}
}
