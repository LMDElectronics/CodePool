#ifndef LOGIC_I2C_DRV
#define LOGIC_I2C_DRV

#include "C:\Users\MAX PC\Documents\repositories\CodePool\Drivers\CommsLogicalDrivers\I2C\c\Defs_i2c.h"

//Low level functions to be implemented in physical driver
/*extern UINT8 I2C_Config(TI2cConfigHandler *i2cConfigHandler);
extern UINT8 I2C_Init(UINT8 i2cPort);
extern UINT8 I2C_Stop(UINT8 i2cPort);

extern UINT8 I2C_WriteData(UINT8 i2cPort, UINT8 addr, UINT8 reg, UINT8 *dataBuff, UINT8 Count);
extern UINT8 I2C_ReadData(UINT8 i2cPort, UINT8 addr, UINT8 reg, UINT8 *dataBuff, UINT8 Count);

extern UINT8 I2C_SendRestart(UINT8 i2cPort);
extern UINT8 I2C_BusyCheck(UINT8 i2cPort);*/

//max number of i2c independent ports to be controlled
#define MAX_DEF_PORTS 8

#define I2C_LAST_TRANSACTION_OK 						0
#define I2C_LAST_TRANSACTION_ERROR_TIMEOUT 	1
#define I2C_LAST_TRANSACTION_ERROR_ACK 			2
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
	I2C_ERROR_UNKNOWN,

	I2C_UNREACHABLE_BUS
}TI2C_Status;

/**
 * @brief Configure physical I2c bus
 * @param[in] TLogicI2cConfig, config handler to be set up in I2C bus
 * @return TI2C_Status
 */
//*****************************************************************************
TI2C_Status Logical_I2C_Config(TI2cConfigHandler *I2C_Config_Handler);
//*****************************************************************************

/**
 * @brief Starts the I2C bus
 * @return TI2C_Status
 */
//*****************************************************************************
TI2C_Status Logical_I2C_Start(UINT8 i2cPort);
//*****************************************************************************

/**
 * @brief Stops the I2C bus
 * @return TI2C_Status
 */
//*****************************************************************************
TI2C_Status Logical_I2C_Stop(UINT8 i2cPort);
//*****************************************************************************

/**
 * @brief Send restart condition
 * @return TI2C_Status
 */
//*****************************************************************************
TI2C_Status Logical_I2C_Restart(UINT8 i2cPort);
//*****************************************************************************

/**
 * @brief write byte
 * @param[in] i2cPort: 		I2C Port number to send the data
 * @param[in] deviceAddr: I2C device address
 * @param[in] reg:				I2C device register to start writing data
 * @param[in] dataBuff:		I2C duffer containing the bytes to write
 * @param[in] count:			I2C number of bytes from dataBuff to write
 * @return TI2C_Status
 */
//*****************************************************************************
TI2C_Status Logical_I2C_WriteData(UINT8 i2cPort, UINT8 deviceAddr, UINT8 reg, UINT8 *dataBuff, UINT8 count);

/**
 * @brief write byte
 * @param[in] i2cPort: 		I2C Port number from which read the data
 * @param[in] deviceAddr: I2C device address
 * @param[in] reg:				I2C device register to start read data
 * @param[in] dataBuff:		I2C buffer to store the bytes read
 * @param[in] count:			I2C number of bytes to read
 * @return TI2C_Status
 */
//*****************************************************************************
TI2C_Status Logical_I2C_ReadData(UINT8 i2cPort, UINT8 deviceAddr, UINT8 reg, UINT8 *dataBuff, UINT8 count);

#endif

