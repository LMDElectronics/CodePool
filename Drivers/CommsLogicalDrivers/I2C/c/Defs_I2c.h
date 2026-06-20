#ifndef DRIVERDEFS_I2C_H_
#define DRIVERDEFS_I2C_H_

#include "C:\Users\MAX PC\Documents\repositories\CodePool\Common\MCU\typedef.h"

/**
 * @ I2C clock speed selection
 */
enum
{
	I2C_CLK_100_KHZ,
	I2C_CLK_400_KHZ,
	I2C_CLK_1_MHZ,
	I2C_CLK_3M4_MHZ,
	I2C_CLK_5_MHZ
};

/**
 * @ Enums for multiple i2c pinout location
 */
typedef enum
{
	pinoutLocation_none,
	pinoutLocation_Alt1,
	pinoutLocation_Alt2,
	pinoutLocation_Alt3,
	pinoutLocation_Alt4,
	pinoutLocation_Alt5,
	pinoutLocation_Alt6,
	pinoutLocation_Alt7

}TI2CPinoutLocation;

#define I2C_PINOUT_ALTERNATIVE_POSITIONS 16

/**
 * @ struct for i2c physical driver features
 */
typedef struct
{
	UINT8 numOfPhysicalPorts;
	UINT8 (*pinoutAltsPerPort)[I2C_PINOUT_ALTERNATIVE_POSITIONS]; //enables up to 16 pinout alternatives
	UINT8 masterModeFeature;
	UINT8 slave10AddressBitFeature;
	UINT8 DMAI2CTransfersfeature;

}TI2CMCUFeatures;

typedef enum
{
	SendStart,
	SendStop,
	SendRestart,
	DoNothing

}TI2COperation;

#endif
