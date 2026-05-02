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
 * @ Physical driver I2C events
 */
typedef void (*OnWrite)(I2CReturnData);
typedef void (*OnRead)(I2CReturnData);
typedef void (*OnError)(I2CReturnData);

void Set_OnPhysical_I2C_Write_Callback(OnWrite function);
void Set_OnPhysical_I2C_Read_Callback(OnRead function);
void Set_OnPhysical_I2C_Error_Callback(OnRead function);

UINT8 I2C_Config(TI2cConfigHandler *I2C_Config_Handler);
UINT8 I2C_Start(UINT8 i2cPort);
UINT8 I2C_Stop(UINT8 i2cPort);
UINT8 I2C_SendRestart(UINT8 i2cPort);

UINT8 I2C_WriteData(UINT8 i2cPort, UINT8 addr, UINT8 reg, UINT8 *dataBuff, UINT8 Count);
UINT8 I2C_ReadData(UINT8 i2cPort, UINT8 addr, UINT8 reg, UINT8 *dataBuff, UINT8 Count );

#endif /* PHYSICAL_I2C_H_ */
