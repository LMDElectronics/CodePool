using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace testch341
{
	public partial class Form1 : Form
	{

		public class CH341
		{
			const string DllName = "CH341DLL.DLL";
			int index = 0;

			[DllImport(DllName)]
			private static extern IntPtr CH341OpenDevice(uint iIndex);

			[DllImport(DllName)]
			private static extern void CH341CloseDevice(uint iIndex);

			[DllImport(DllName)]
			private static extern uint CH341GetVersion();

			public CH341()
			{
				index = 0;
			}

			public IntPtr OpenDevice()
			{
				return CH341OpenDevice(0);
			}
		}

		public Form1()
		{
			InitializeComponent();						
		}

		private void button1_Click(object sender, EventArgs e)
		{
			CH341 mybridge = new CH341();



			int i = 0;
		}
	}
}
