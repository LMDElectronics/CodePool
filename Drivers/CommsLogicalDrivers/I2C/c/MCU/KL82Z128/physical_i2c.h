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
typedef void (*OnWrite)(UINT8 port, UINT8 *dataBuffer, UINT8 count);
typedef void (*OnRead)(UINT8 port, UINT8 *dataBuffer, UINT8 count);
typedef void (*OnError)(UINT8 port, UINT8 error);

/**
 * @ config struct for Logical slave bus I2C driver
 */
typedef struct
{
	UINT8 	portNumber;						/**<Physical i2c bus number >*/
	UINT16	busSpeed;							/**<Physical i2c bus speed >*/
	UINT8		masterModeOn;					/**<Physical i2c master mode or slave mode>*/
	UINT8		slave10AddressBitsOn;	/**<Physical i2c bits used for slave address>*/
	UINT16	I2CTimeout;						/**<Physical i2c timout to wait for response from slave>*/
	UINT8		pinoutLocation;				/**<Physical i2c location for i2c pinout ios (for mcu supporting multiple peripheral pinouts)> */

	OnWrite	callbackWriteI2c;
	OnRead 	callbackReadI2c;
	OnError callbackErrorI2c;

}TI2cPhysicalConfigHandler;

/**
 * @ Enums for multiple i2c0 pinout location [section 11.3.1, KL82P121M72SF0RM.pdf]
 */
typedef enum
{
	pinoutLocation_Alt1,
	pinoutLocation_Alt2,
	pinoutLocation_Alt3,
	pinoutLocation_Alt4,
	pinoutLocation_Alt5,
	pinoutLocation_Alt6,
	pinoutLocation_Alt7

}TI2CPinoutLocation;

/**
 * @ Enums for physical i2c driver features
 */
typedef enum
{
	tfi2c_multimaster,
	tfi2c_masterAndSlave,
	tfi2c_10bitAdresses,
	tfi2c_lowPowerMode,
	tfi2c_DMASupport,
	tfi2c_MultiplePinoutLocation,
	//...
	feature31

}TI2CPeripheralFeatures;

TI2CPeripheralFeatures I2C_AskPeripheralFeatures(void);
UINT8 I2C_Config(TI2cPhysicalConfigHandler *I2C_Config_Handler);
UINT8 I2C_Start(UINT8 i2cPort);
UINT8 I2C_Stop(UINT8 i2cPort);
UINT8 I2C_SendRestart(UINT8 i2cPort);

UINT8 I2C_WriteData(UINT8 i2cPort, UINT8 addr, UINT8 reg, UINT8 *dataBuff, UINT8 Count);
UINT8 I2C_ReadData(UINT8 i2cPort, UINT8 addr, UINT8 reg, UINT8 *dataBuff, UINT8 Count );

#endif /* PHYSICAL_I2C_H_ */
