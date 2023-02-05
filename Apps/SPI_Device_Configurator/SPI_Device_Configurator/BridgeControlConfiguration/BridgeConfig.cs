using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SPI_Device_Configurator
{
	class SerialBridgeConfig
	{
		public virtual void LoadConfig()
		{

		}
	}

	class CH341BridgeConfig: SerialBridgeConfig
	{
		public override void LoadConfig()
		{
			throw new NotImplementedException();
		}
	}

	//other bridges
	//TODO
}
