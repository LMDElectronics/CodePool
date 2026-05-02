#include "C:\Users\MAX PC\Documents\repositories\CodePool\Common\MCU\global_def.h"
#include "logic_i2c.h"
#include "physical_i2c.h"

TI2C_Status I2CPortStatus[MAX_DEF_PORTS];

//*****************************************************************************
// Event Callbacks
//*****************************************************************************

//*****************************************************************************
void DoOnI2CEventWrite(I2CReturnData data)
//*****************************************************************************
//
//*****************************************************************************
{
	int i=0;

	i=0;
}

//*****************************************************************************
//void DoOnI2CEventRead(I2CReturnData data)
//*****************************************************************************
//
//*****************************************************************************
//{


//}

//*****************************************************************************
//void DoOnI2CEventError(I2CReturnData data)
//*****************************************************************************
//
//*****************************************************************************
//{


//}



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
TI2C_Status Logical_I2C_Config(TI2cConfigHandler *I2C_Config_Handler)
//*****************************************************************************
//
//*****************************************************************************
{

	//wiring callbacks
	I2C_Config_Handler->OnI2CWrite = DoOnI2CEventWrite;

	if(I2C_Config_Handler->PortNumber <= MAX_DEF_PORTS)
	{
		//Configuring the port
		if( I2C_Config(	I2C_Config_Handler) != ERROR)
		{
			return I2CPortStatus[I2C_Config_Handler->PortNumber] = I2C_PORT_CONFIGURED;
		}
		else
		{
			return I2CPortStatus[I2C_Config_Handler->PortNumber] = I2C_ERROR_CONFIG_OPERATION;
		}
	}
	else
	{
		return I2CPortStatus[I2C_Config_Handler->PortNumber] = I2C_UNREACHABLE_BUS;
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


