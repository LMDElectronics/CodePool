using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SPI_Device_Configurator
{
	class Defines
	{
		public const int CONFIG_GROUPBOX_LIST_INDEX = 0;
		public const int DATA_GROUPBOX_LIST_INDEX = 1;

		public const int MAX_CONFIG_DATA_BYTES = 16;

		public const string CALLBACK_OPERATION_ATTACH = "ATTACH CALLBACKS";
		public const string CALLBACK_OPERATION_DETTACH = "DETTACH CALLBACK";

		public const string CH341_DRIVER_ASSEMBLY_PATH = "CH341ExternalDriverAssembly";
		public const string CH341_DRIVER_ASSEMBLY = "CH341";

		public const int CONTROLS_LOADED_OK = 0;
		public const int CONTROLS_REMOVED_OK = 0;

		public const int CONTROLS_LOADED_UNKNOWN_ERROR = 255;
		public const int CONTROLS_LOADED_FILE_NOT_EXIST = 1;
		public const int CONTROLS_LOADED_EXCEPTION_GENERATED = 2;

		public const int CONTROLS_REMOVED_UNKNOWN_ERROR = 254;
		public const int CONTROLS_REMOVED_EXCEPTION_GENERATED = 3;

		public const int BUTTON_CLICK_CALLBACKS_ATTACH_ERROR = 253;
		public const int BUTTON_CLICK_CALLBACKS_DETTACH_ERROR = 252;
		public const int BUTTON_CLICK_CALLBACKS_ATTACHED_OK = 0;
	}
}
