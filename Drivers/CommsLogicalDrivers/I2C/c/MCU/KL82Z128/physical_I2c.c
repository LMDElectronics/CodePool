/*
 * physical_I2c.c
 *
 *  Created on: 2 may 2026
 *      Author: MAX PC
 */

#include "C:\Users\MAX PC\Documents\repositories\CodePool\Common\MCU\global_def.h"
#include "C:\Users\MAX PC\Documents\repositories\CodePool\Drivers\CommsLogicalDrivers\I2C\c\MCU\KL82Z128\physical_i2c.h"

OnWrite OnEvent_I2CWrite;
OnRead OnEvent_I2CRead;
OnError OnEvent_I2CError;

TI2cPhysicalConfigHandler PhysicalDriverConfigHandler;

//*****************************************************************************
UINT8 I2C_Config_Port(UINT8 i2cPort)
//*****************************************************************************
// MCU dependant function: I2C config port
//*****************************************************************************
{
	//TODO
	return OK;
}

//*****************************************************************************
UINT8 I2C_Config_Clk(UINT8 clkSpeed)
//*****************************************************************************
// MCU dependant function: I2C config clk speed
//*****************************************************************************
{
	//TODO
	return OK;
}

//*****************************************************************************
void SaveI2CPhysicalDriverConfig(TI2cPhysicalConfigHandler *I2C_Config_Handler)
//*****************************************************************************
//
//*****************************************************************************
{
	PhysicalDriverConfigHandler.PortNumber = I2C_Config_Handler->PortNumber;
	PhysicalDriverConfigHandler.busSpeed = I2C_Config_Handler->busSpeed;
	PhysicalDriverConfigHandler.I2CTimeout = I2C_Config_Handler->I2CTimeout;
}

void Set_OnPhysical_I2C_Write_Callback(OnWrite function)
{
	OnEvent_I2CWrite = function;
}

void Set_OnPhysical_I2C_Read_Callback(OnRead function)
{
	OnEvent_I2CRead = function;
}

void Set_OnPhysical_I2C_Error_Callback(OnError function)
{
	OnEvent_I2CError = function;
}

//*****************************************************************************
// Physical driver external functions implementation
//*****************************************************************************

//*****************************************************************************
UINT8 I2C_Start(UINT8 i2cPort)
//*****************************************************************************
//
//*****************************************************************************
{
	UINT8 dataBuff[10];
	UINT8 i=0;

	for(i=0; i<10; i++)
	{
		dataBuff[i] = 0xAA;
	}

	//test
	if(OnEvent_I2CWrite) OnEvent_I2CWrite(0, dataBuff, 10);

	return OK;
}

//*****************************************************************************
UINT8 I2C_Config(TI2cPhysicalConfigHandler *I2C_Config_Handler)
//*****************************************************************************
// MCU dependant function: I2C config port
//*****************************************************************************
{
	//config port
	if( I2C_Config_Port(I2C_Config_Handler->PortNumber) == ERROR)
	{
		return ERROR;
	}

	//config CLK
	if( I2C_Config_Clk(I2C_Config_Handler->busSpeed) == ERROR)
	{
		return ERROR;
	}
	else

	//config timeout
	if( I2C_Config_Port(I2C_Config_Handler->I2CTimeout) == ERROR)
	{
		return ERROR;
	}

	//saving current i2c config
	SaveI2CPhysicalDriverConfig(I2C_Config_Handler);

	return OK;
}

//*****************************************************************************
UINT8 I2C_SendRestart(UINT8 i2cPort)
//*****************************************************************************
//
//*****************************************************************************
{
	//TODO
	return OK;
}

//*****************************************************************************
UINT8 I2C_WriteData(UINT8 i2cPort, UINT8 addr, UINT8 reg, UINT8 *dataBuff, UINT8 Count)
//*****************************************************************************
//
//*****************************************************************************
{
	//TODO
	return OK;
}

//*****************************************************************************
UINT8 I2C_ReadData(UINT8 i2cPort, UINT8 addr, UINT8 reg, UINT8 *dataBuff, UINT8 Count)
//*****************************************************************************
//
//*****************************************************************************
{
	//TODO
	return OK;
}
