/*
 * physical_i2c.h
 *
 *  Created on: 2 may 2026
 *      Author: MAX PC
 */

#ifndef PHYSICAL_I2C_H_
#define PHYSICAL_I2C_H_

#include "C:\Users\MAX PC\Documents\repositories\CodePool\Drivers\CommsLogicalDrivers\I2C\c\Defs_i2c.h"

/**
 * @ config struct for Logical slave bus I2C driver
 */
typedef struct
{
	UINT8 				PortNumber;	/**<Physical i2c bus number >*/
	UINT16				busSpeed;	/**<Physical i2c bus speed >*/
	UINT32				I2CTimeout;	/**<Physical i2c timout to wait for response from slave>*/

}TI2cPhysicalConfigHandler;

/**
 * @ I2C returned data from physical driver events
 */
typedef struct
{
	UINT8 i2cPort;
	UINT8 *dataBuffer;
	UINT8 count;
	UINT8 error;

}I2CPhyReturnData;

/**
 * @ I2C events
 */
typedef void (*OnWrite)(UINT8 Port, UINT8 *dataBuffer, UINT8 count);
typedef void (*OnRead)(UINT8 Port, UINT8 *dataBuffer, UINT8 count);
typedef void (*OnError)(UINT8 Port, UINT8 error);

/**
 * @ I2C funtions to setup the upper layer callback
 */
void Set_OnPhysical_I2C_Write_Callback(OnWrite function);
void Set_OnPhysical_I2C_Read_Callback(OnRead function);
void Set_OnPhysical_I2C_Error_Callback(OnError function);

UINT8 I2C_Config(TI2cPhysicalConfigHandler *I2C_Config_Handler);
UINT8 I2C_Start(UINT8 i2cPort);
UINT8 I2C_Stop(UINT8 i2cPort);
UINT8 I2C_SendRestart(UINT8 i2cPort);

UINT8 I2C_WriteData(UINT8 i2cPort, UINT8 addr, UINT8 reg, UINT8 *dataBuff, UINT8 Count);
UINT8 I2C_ReadData(UINT8 i2cPort, UINT8 addr, UINT8 reg, UINT8 *dataBuff, UINT8 Count );

#endif /* PHYSICAL_I2C_H_ */
