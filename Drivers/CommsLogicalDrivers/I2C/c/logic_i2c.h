#ifndef LOGIC_I2C_DRV
#define LOGIC_I2C_DRV

#include "C:\Users\MAX PC\Documents\repositories\CodePool\Drivers\CommsLogicalDrivers\I2C\c\Defs_I2c.h"

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
	UINT32  i2cBaseClock;						/**<clock freq from which the i2c bus is running (Hz)>*/
	UINT8		busSpeed;								/**<Logic target i2c bus speed to be set>*/
	UINT8		slave10AddressBitsOn; 	/**<Logic i2c bits used for slave address flag>*/
	UINT16	I2CTimeout;							/**<Logic i2c timout to wait for response from slave>*/
	UINT8		mastermode;							/**<Logic i2c port mode flag>*/
	UINT8		pinoutLocation;					/**<Logic i2c location for i2c pinout ios (for mcu supporting multiple peripheral pinouts)> */
	UINT8 	useDMA;									/**<Logic i2c use DMA flag>*/
	UINT8 	useInterrupts;					/**<Logic i2c use interrupts flag>*/

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
TI2C_Status Logical_I2C_WriteData(UINT8 i2cPort, UINT8 deviceAddr, UINT8 *dataBuff, UINT32 count);
//*****************************************************************************

/**
 * @brief write byte
 * @param[in] i2cPort: 				I2C Port number from which read the data
 * @param[in] deviceAddr: 		I2C device address
 * @param[in] dataBuff:				I2C buffer to store the bytes read
 * @param[in] count:					I2C number of bytes to read
 * @return TI2C_Status
v */
//*****************************************************************************
TI2C_Status Logical_I2C_ReadData(UINT8 i2cPort, UINT8 deviceAddr,UINT8 *dataBuff, UINT32 count);
//*****************************************************************************

#endif

