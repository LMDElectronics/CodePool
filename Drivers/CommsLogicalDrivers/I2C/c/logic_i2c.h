#ifndef LOGIC_I2C_DRV
#define LOGIC_I2C_DRV

#include "typedef.h"

//Low level functions to be implemented in physical driver
extern UINT8 ll_i2c_start(void);
extern UINT8 ll_i2c_stop(void);
extern UINT8 ll_i2c_write(UINT8 data);
extern UINT8 ll_i2c_read(UINT8 *data, UINT8 ack);
extern UINT8 ll_i2c_bus_busy(void);

typedef enum
{
	I2C_OK = 0,
	I2C_ERROR_TIMEOUT,
	I2C_ERROR_NACK,
	I2C_ERROR_BUS

}TI2C_Status;

/**
 * @ I2C clock speed selection
 */
typedef enum
{
	I2C_CLK_100_KHZ,
	I2C_CLK_400_KHZ,
	I2C_CLK_1_MHZ,
	I2C_CLK_3M4_MHZ,
	I2C_CLK_5_MHZ

}TI2C_ClkSpeed;

/**
 * @ config struct for Logical slave bus I2C driver
 */
typedef struct
{
	UINT8 				PortNumber;	/**<Physical i2c bus number >*/
	TI2C_ClkSpeed	busSpeed;	/**<Physical i2c bus speed >*/
	UINT8					I2CTimeout;	/**<Physical i2c timout to wait for response from slave>*/

}TLogicI2cConfig;

/**
 * @brief Configure physical I2c bus
 * @param[in] TLogicI2cConfig, config handler to be set up in I2C bus
 * @return TI2C_Status
 */
//*****************************************************************************
TI2C_Status Logical_I2C_Config(TLogicI2cConfig *Logical_I2C_Config_Handler);
//*****************************************************************************

/**
 * @brief Starts the I2C bus
 * @return TI2C_Status
 */
//*****************************************************************************
TI2C_Status Logical_I2C_Start(void);
//*****************************************************************************

/**
 * @brief Stops the I2C bus
 * @return TI2C_Status
 */
//*****************************************************************************
TI2C_Status Logical_I2C_Stop(void);
//*****************************************************************************

/**
 * @brief Send restart condition
 * @return TI2C_Status
 */
//*****************************************************************************
TI2C_Status Logical_I2C_Restart(void);
//*****************************************************************************
#endif

