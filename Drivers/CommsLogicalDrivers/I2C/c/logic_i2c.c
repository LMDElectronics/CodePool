#include "C:\Users\MAX PC\Documents\repositories\CodePool\Common\MCU\global_def.h"
#include "logic_i2c.h"

//
TLogicI2cConfig Logical_I2C_Port_Config_Handler[MAX_DEF_PORTS];
TI2C_Status I2CPortStatus[MAX_DEF_PORTS];

//*****************************************************************************
TI2C_Status Logical_I2C_PortInit(UINT8 i2cPort)
//*****************************************************************************
//
//*****************************************************************************
{
	if(i2cPort <= MAX_DEF_PORTS)
	{
		if(i2c_Init(i2cPort) != ERROR)
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
		if(i2c_Stop(i2cPort) != ERROR)
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
TI2C_Status Logical_I2C_PortConfig(UINT8 i2cPort, TLogicI2cConfig Logical_I2C_Config_Handler[])
//*****************************************************************************
//
//*****************************************************************************
{
	if(i2cPort <= MAX_DEF_PORTS)
	{
		//Configuring the port
		if( i2c_Config(	Logical_I2C_Port_Config_Handler[i2cPort].PortNumber,
												Logical_I2C_Port_Config_Handler[i2cPort].busSpeed,
												Logical_I2C_Port_Config_Handler[i2cPort].I2CTimeout) != ERROR)
		{
			return I2CPortStatus[i2cPort] = I2C_PORT_CONFIGURED;
		}
		else
		{
			return I2CPortStatus[i2cPort] = I2C_ERROR_CONFIG_OPERATION;
		}
	}
	else
	{
		return I2CPortStatus[i2cPort] = I2C_UNREACHABLE_BUS;
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
		if(i2c_SendRestart(i2cPort) != ERROR)
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
		opstatus = i2c_WriteData(i2cPort, deviceAddr, reg, dataBuff, count);

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
		opstatus = i2c_ReadData(i2cPort, deviceAddr, reg, dataBuff, count);

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
void DoOnI2CEventWrite(UINT8 i2cPort, UINT8 *dataBuffer)
//*****************************************************************************
//
//*****************************************************************************
{


}


