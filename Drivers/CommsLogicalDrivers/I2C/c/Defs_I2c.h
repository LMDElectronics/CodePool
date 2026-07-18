#ifndef DRIVERDEFS_I2C_H_
#define DRIVERDEFS_I2C_H_

#include "C:\Users\MAX PC\Documents\repositories\CodePool\Common\MCU\typedef.h"

//max number of i2c independent ports to be controlled
#define MAX_DEF_PORTS 8

#define I2C_LAST_TRANSACTION_OK 						0
#define I2C_LAST_TRANSACTION_ERROR_TIMEOUT 	1
#define I2C_LAST_TRANSACTION_ERROR_ACK 			2
#define I2C_LAST_TRANSACTION_NACK			 			3
#define I2C_LAST_TRANSACTION_ERROR_UNKNOWN 	99

typedef enum
{
	I2C_PORT_NOT_INITIALIZED,
	I2C_PORT_INITIALIZED,
	I2C_PORT_CONFIGURED,
	I2C_PORT_STOP,

	I2C_ERROR_INIT_OPERATION,
	I2C_ERROR_CONFIG_OPERATION,
	I2C_ERROR_STOP_OPERATION,
	I2C_ERROR_RESTART_OPERATION,
	I2C_ERROR_WRITE_DATA_OPERATION,

	I2C_WRITE_OPERATION_OK,
	I2C_READ_OPERATION_OK,
	I2C_ERROR_TIMEOUT,
	I2C_ERROR_ACK,
	I2C_ERROR_NACK,
	I2C_ERROR_UNKNOWN,

	I2C_UNREACHABLE_BUS
}TI2C_Status;

typedef struct
{
	UINT8 port;
	UINT8 *dataBuff;
	UINT8 count;
	UINT8 error;

}I2CLogicalReturnData;

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

#endif
