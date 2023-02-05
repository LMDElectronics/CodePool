using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BridgeLoadLibraryLib
{
	public static class Defines
	{
		public const int ASSEMBLY_LOADING_ERROR					= 255;
		public const int ASSEMBLY_UNLOADING_ERROR				= 254;
		public const int ASSEMBLY_PATH_NOT_FOUND				= 253;
		public const int ASSEMBLY_INTERFACE_TO_LOAD_NOT_PRESENT = 252;
		public const int ASSEMBLY_LOADED_OK						= 0;
	}
}
