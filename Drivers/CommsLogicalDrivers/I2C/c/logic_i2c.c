

#include "C:\Users\MAX PC\Documents\repositories\CodePool\Common\MCU\global_def.h"
#include "logic_i2c.h"

#include "C:\Users\MAX PC\Documents\repositories\CodePool\Drivers\CommsLogicalDrivers\I2C\c\MCU\KL82Z128\physical_i2c.h"

//callbacks for event
void DoOn_I2C_Physical_Event_Write(UINT8 port, UINT8 *dataBuffer, UINT8 count);
void DoOn_I2C_Physical_Event_Read(UINT8 port, UINT8 *dataBuffer, UINT8 count);
void DoOn_I2C_Physical_Event_Error(UINT8 port, UINT8 error);

//events to be launched to app
OnWriteI2C 		OnI2cWriteData;
OnReadI2C 		OnI2cReadData;
OnErrorI2C 		OnI2cError;

TI2C_Status I2CPortStatus[MAX_DEF_PORTS];

//*****************************************************************************
TI2C_Status Logical_I2C_Start(UINT8 i2cPort)
//*****************************************************************************
//
//*****************************************************************************
{
	if( i2cPort <= MAX_DEF_PORTS)
	{
		if( I2C_Start(i2cPort) != ERROR)
		{
			return I2CPortStatus[i2cPort] = I2C_PORT_INITIALIZED;
		}
		else
		{
			return I2CPortStatus[i2cPort] = I2C_ERROR_INIT_OPERATION;
		}
	}
	else
	{
		return I2CPortStatus[i2cPort] = I2C_UNREACHABLE_BUS;
	}
}

//*****************************************************************************
TI2C_Status Logical_I2C_Stop(UINT8 i2cPort)
//*****************************************************************************
//
//*****************************************************************************
{
	if(i2cPort <= MAX_DEF_PORTS)
	{
		if( I2C_Stop(i2cPort) != ERROR)
		{
			return I2CPortStatus[i2cPort] = I2C_PORT_STOP;
		}
		else
		{
			return I2CPortStatus[i2cPort] = I2C_ERROR_STOP_OPERATION;
		}
	}
	else
	{
		return I2CPortStatus[i2cPort] = I2C_UNREACHABLE_BUS;
	}
}

//*****************************************************************************
TI2CMCUFeatures *Logical_I2C_Features(void)
//*****************************************************************************
//
//*****************************************************************************
{
	return I2C_AskPeripheralFeatures();
}

//*****************************************************************************
TI2C_Status Logical_I2C_Config(TI2cLogicConfigHandler *I2C_Config_Handler)
//*****************************************************************************
//
//*****************************************************************************
{
	TI2cPhysicalConfigHandler I2c_Phy_Config_Handler;

	//prepare config data for physical driver
	I2c_Phy_Config_Handler.portNumber = I2C_Config_Handler->portNumber;
	I2c_Phy_Config_Handler.busSpeed = I2C_Config_Handler->busSpeed;
	I2c_Phy_Config_Handler.I2CTimeout = I2C_Config_Handler->I2CTimeout;
	I2c_Phy_Config_Handler.slave10AddressBitsOn = I2C_Config_Handler->slave10AddressBitsOn;
	I2c_Phy_Config_Handler.pinoutLocation = I2C_Config_Handler->pinoutLocation;

	I2c_Phy_Config_Handler.callbackWriteI2c = DoOn_I2C_Physical_Event_Write;
	I2c_Phy_Config_Handler.callbackReadI2c = DoOn_I2C_Physical_Event_Read;
	I2c_Phy_Config_Handler.callbackErrorI2c = DoOn_I2C_Physical_Event_Error;

	//wiring events to callbacks from app layer
	OnI2cWriteData 	= I2C_Config_Handler->WriteI2C_Callback;
	OnI2cReadData 	= I2C_Config_Handler->ReadI2C_Callback;
	OnI2cError 			= I2C_Config_Handler->ErrorI2C_Callback;

	if(I2C_Config_Handler->portNumber <= MAX_DEF_PORTS)
	{
		//Configuring the port
		if( I2C_Config(	&I2c_Phy_Config_Handler) != ERROR)
		{
			return I2CPortStatus[I2C_Config_Handler->portNumber] = I2C_PORT_CONFIGURED;
		}
		else
		{
			return I2CPortStatus[I2C_Config_Handler->portNumber] = I2C_ERROR_CONFIG_OPERATION;
		}
	}
	else
	{
		return I2CPortStatus[I2C_Config_Handler->portNumber] = I2C_UNREACHABLE_BUS;
	}
}

//*****************************************************************************
TI2C_Status Logical_I2C_Restart(UINT8 i2cPort)
//*****************************************************************************
//
//*****************************************************************************
{
	if(i2cPort <= MAX_DEF_PORTS)
	{
		if( I2C_SendRestart(i2cPort) != ERROR)
		{
			return I2CPortStatus[i2cPort] = I2C_LAST_TRANSACTION_OK;
		}
		else
		{
			return I2CPortStatus[i2cPort] = I2C_ERROR_RESTART_OPERATION;
		}
	}
	else
	{
		return I2CPortStatus[i2cPort] = I2C_UNREACHABLE_BUS;
	}
}

//*****************************************************************************
TI2C_Status Logical_I2C_WriteData(UINT8 i2cPort, UINT8 deviceAddr, UINT8 reg, UINT8 *dataBuff, UINT8 count)
//*****************************************************************************
//
//*****************************************************************************
{
	UINT8 opstatus=ERROR;

	if(i2cPort <= MAX_DEF_PORTS)
	{
		opstatus = I2C_WriteData(i2cPort, deviceAddr, reg, dataBuff, count);

		switch (opstatus)
		{
			case I2C_LAST_TRANSACTION_OK:							return I2CPortStatus[i2cPort] = I2C_WRITE_OPERATION_OK;	break;
			case I2C_LAST_TRANSACTION_ERROR_TIMEOUT: 	return I2CPortStatus[i2cPort] = I2C_ERROR_TIMEOUT; 			break;
			case I2C_LAST_TRANSACTION_ERROR_ACK: 			return I2CPortStatus[i2cPort] = I2C_ERROR_ACK; 					break;
			default:														 			return I2CPortStatus[i2cPort] = I2C_ERROR_UNKNOWN;			break;
		}
	}
	else
	{
		return I2CPortStatus[i2cPort] = I2C_UNREACHABLE_BUS;
	}
}

//*****************************************************************************
TI2C_Status Logical_I2C_ReadData(UINT8 i2cPort, UINT8 deviceAddr, UINT8 reg, UINT8 *dataBuff, UINT8 count)
//*****************************************************************************
//
//*****************************************************************************
{
	UINT8 opstatus=ERROR;

	if(i2cPort <= MAX_DEF_PORTS)
	{
		opstatus = I2C_ReadData(i2cPort, deviceAddr, reg, dataBuff, count);

		switch (opstatus)
		{
			case I2C_LAST_TRANSACTION_OK:							return I2CPortStatus[i2cPort] = I2C_READ_OPERATION_OK;	break;
			case I2C_LAST_TRANSACTION_ERROR_TIMEOUT: 	return I2CPortStatus[i2cPort] = I2C_ERROR_TIMEOUT; 			break;
			case I2C_LAST_TRANSACTION_ERROR_ACK: 			return I2CPortStatus[i2cPort] = I2C_ERROR_ACK; 					break;
			default:														 			return I2CPortStatus[i2cPort] = I2C_ERROR_UNKNOWN;			break;
		}
	}
	else
	{
		return I2CPortStatus[i2cPort] = I2C_UNREACHABLE_BUS;
	}
}

//*****************************************************************************
// Event Callbacks
//*****************************************************************************

//*****************************************************************************
void DoOn_I2C_Physical_Event_Write(UINT8 port, UINT8 *dataBuffer, UINT8 count)
//*****************************************************************************
//
//*****************************************************************************
{
	I2CLogicalReturnData data;

	data.dataBuff = dataBuffer;
	data.port = port;
	data.count = count;
	data.error = 0;

	if(OnI2cWriteData) OnI2cWriteData(data);
}

//*****************************************************************************
void DoOn_I2C_Physical_Event_Read(UINT8 port, UINT8 *dataBuffer, UINT8 count)
//*****************************************************************************
//
//*****************************************************************************
{
	I2CLogicalReturnData data;

	data.dataBuff = dataBuffer;
	data.port = port;
	data.count = count;
	data.error = 0;

	OnI2cReadData(data);
}

//*****************************************************************************
void DoOn_I2C_Physical_Event_Error(UINT8 port, UINT8 error)
//*****************************************************************************
//
//*****************************************************************************
{
	I2CLogicalReturnData data;

	data.dataBuff = NULL;
	data.port = port;
	data.count = 0;
	data.error = error;

	OnI2cError(data);
}
