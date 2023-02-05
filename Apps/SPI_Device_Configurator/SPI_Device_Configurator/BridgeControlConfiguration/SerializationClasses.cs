using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using System.Drawing;
using System.Windows.Forms;

namespace SPI_Device_Configurator.FormBridgeControlXmlSerializedClasses
{
	//****************************************************************************
	// Load control classes from XML file
	//****************************************************************************
	public class SerBasicControl
	{
		[XmlElement(ElementName = "Name")]
		public string Name { get; set; }
		[XmlElement(ElementName = "Text")]
		public string Text { get; set; }
		[XmlElement(ElementName = "XPosition")]
		public string XPosition { get; set; }
		[XmlElement(ElementName = "YPosition")]
		public string YPosition { get; set; }

		public int xPosition { get => Int32.Parse(XPosition); }
		public int yPosition { get => Int32.Parse(YPosition); }
	}

	//*************************************************************************
	// Serialized available control classes
	//*************************************************************************
	[XmlRoot(ElementName = "label")]
	public class SerLabel : SerBasicControl
	{
	}

	[XmlRoot(ElementName = "radioButton")]
	public class SerRadioButton : SerBasicControl
	{
	}

	[XmlRoot(ElementName = "Button")]
	public class SerButton : SerBasicControl
	{
		[XmlElement(ElementName = "Height")]
		public string Height { get; set; }
		[XmlElement(ElementName = "Width")]
		public string Width { get; set; }
		[XmlElement(ElementName = "TextAlign")]
		public string TextAlignment { get; set; }

		public ContentAlignment textAlignment
		{
			get
			{
				ContentAlignment retVal = ContentAlignment.MiddleCenter;
				Enum.TryParse<ContentAlignment>(TextAlignment, out retVal);
				return retVal;
			}
		}

		public int width { get => Int32.Parse(Width); }
		public int height { get => Int32.Parse(Height); }
	}

	[XmlRoot(ElementName = "CheckBox")]
	public class SerCheckBox : SerBasicControl
	{
		[XmlElement(ElementName = "AutoSize")]
		public string Autosize { get; set; }
		[XmlElement(ElementName = "Checked")]
		public string Checked { get; set; }
	}

	//*************************************************************************
	// Control catalog list of controls 
	//*************************************************************************
	[XmlRoot(ElementName = "LabelCatalog")]
	public class LabelCatalog
	{
		[XmlElement(ElementName = "label")]
		public List<SerLabel> listOfLabel { get; set; }
	}

	[XmlRoot(ElementName = "RadioButtonCatalog")]
	public class RadioButtonCatalog
	{
		[XmlElement(ElementName = "RadioButton")]
		public List<SerRadioButton> listOfRadioButton { get; set; }
	}

	[XmlRoot(ElementName = "ButtonCatalog")]
	public class ButtonCatalog
	{
		[XmlElement(ElementName = "Button")]
		public List<SerButton> listOfButton { get; set; }
	}

	[XmlRoot(ElementName = "CheckBoxCatalog")]
	public class CheckBoxCatalog
	{
		[XmlElement(ElementName = "CheckBox")]
		public List<SerCheckBox> listOfCheckBox { get; set; }
	}

	//*************************************************************************
	// Class to store the main control catalogs branches 
	//*************************************************************************
	[XmlRoot(ElementName = "GroupCatalog")]
	public class GroupCatalog
	{
		[XmlElement(ElementName = "LabelCatalog")]
		public LabelCatalog LabelCatalog { get; set; }
		[XmlElement(ElementName = "RadioButtonCatalog")]
		public RadioButtonCatalog RadioButtonCatalog { get; set; }
		[XmlElement(ElementName = "ButtonCatalog")]
		public ButtonCatalog ButtonCatalog { get; set; }
		[XmlElement(ElementName = "CheckBoxCatalog")]
		public CheckBoxCatalog CheckBoxCatalog { get; set; }
	}

	//*************************************************************************
	// Class to store each main branch
	//*************************************************************************
	[XmlRoot(ElementName = "ControlsCataLog")]
	public class ControlsCataLog : GroupCatalog
	{

	}

	//*************************************************************************
	// Class to store the root branch of the xml file
	//*************************************************************************
	[XmlRoot(ElementName = "GroupControlsCatalog")]
	public class GroupControlsCatalog
	{
		[XmlElement(ElementName = "ControlsCataLog")]		
		public List<ControlsCataLog> groupCatalog { get; set; }
	}	
}

