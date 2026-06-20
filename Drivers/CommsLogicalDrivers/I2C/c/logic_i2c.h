#ifndef LOGIC_I2C_DRV
#define LOGIC_I2C_DRV

#include "C:\Users\MAX PC\Documents\repositories\CodePool\Drivers\CommsLogicalDrivers\I2C\c\Defs_I2c.h"

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

typedef struct
{
	UINT8 port;
	UINT8 *dataBuff;
	UINT8 count;
	UINT8 error;

}I2CLogicalReturnData;

/**
 * @ I2C Logical Bus events
 */
typedef void (*OnWriteI2C)(I2CLogicalReturnData);
typedef void (*OnReadI2C)(I2CLogicalReturnData);
typedef void (*OnErrorI2C)(I2CLogicalReturnData);
typedef void (*OnFeaturesRecv)(TI2CMCUFeatures);

/**
 * @ config struct for Logical slave bus I2C driver
 */
typedef struct
{
	UINT8		portNumber;							/**<Logic i2c bus number >*/
	UINT16	busSpeed;								/**<Logic i2c bus speed >*/
	UINT8		slave10AddressBitsOn; 	/**<Logic i2c bits used for slave address>*/
	UINT16	I2CTimeout;							/**<Logic i2c timout to wait for response from slave>*/
	UINT8		mastermode;							/**<Logic i2c port mode>*/
	UINT8		pinoutLocation;					/**<Logic i2c location for i2c pinout ios (for mcu supporting multiple peripheral pinouts)> */
	UINT8 	useDMA;									/**<Logic i2c use DMA>*/
	UINT8 	useInterrupts;					/**<Logic i2c use interrupts>*/

	OnWriteI2C			WriteI2C_Callback;
	OnReadI2C				ReadI2C_Callback;
	OnErrorI2C			ErrorI2C_Callback;

}TI2cLogicConfigHandler;

/**
 * @brief Ask for I2C driver features
 * @return TI2CMCUFeatures features data
 */
//*****************************************************************************
TI2CMCUFeatures *Logical_I2C_Features(void);
//*****************************************************************************

/**
 * @brief Configure I2c bus
 * @param[in] TLogicI2cConfig, config handler to be set up in I2C bus
 * @return TI2C_Status
 */
//*****************************************************************************
TI2C_Status Logical_I2C_Config(TI2cLogicConfigHandler *I2C_Config_Handler);
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
 * @param[in] dataBuff:		I2C duffer containing the bytes to write
 * @param[in] count:			I2C number of bytes from dataBuff to write
 * @return TI2C_Status
 */
//*****************************************************************************
TI2C_Status Logical_I2C_WriteData(UINT8 i2cPort, UINT8 deviceAddr, UINT8 *dataBuff, UINT32 count, TI2COperation StartOperation, TI2COperation EndOperation);
//*****************************************************************************

/**
 * @brief write byte
 * @param[in] i2cPort: 				I2C Port number from which read the data
 * @param[in] deviceAddr: 		I2C device address
 * @param[in] dataBuff:				I2C buffer to store the bytes read
 * @param[in] count:					I2C number of bytes to read
 * @param[in] StartOperation:	I2C operation to perfom before data transfer in the bus [start, stop, restart, nothing]
 * @param[in] StartOperation:	I2C operation to perfom after data transfer in the bus [start, stop, restart, nothing]
 * @return TI2C_Status
v */
//*****************************************************************************
TI2C_Status Logical_I2C_ReadData(UINT8 i2cPort, UINT8 deviceAddr,UINT8 *dataBuff, UINT32 count);
//*****************************************************************************

#endif

