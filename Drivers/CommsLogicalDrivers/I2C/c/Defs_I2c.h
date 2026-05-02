#ifndef DRIVERDEFS_I2C_H_
#define DRIVERDEFS_I2C_H_

#include "C:\Users\MAX PC\Documents\repositories\CodePool\Common\MCU\typedef.h"

/**
 * @ I2C returned data from physical driver events
 */
typedef struct
{
	UINT8 i2cPort;
	UINT8 *dataBuffer;
	UINT8 error;

}I2CReturnData;

/**
 * @ I2C events
 */
typedef void (*OnWrite)(I2CReturnData);
typedef void (*OnRead)(I2CReturnData);
typedef void (*OnError)(I2CReturnData);

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
	UINT32				I2CTimeout;	/**<Physical i2c timout to wait for response from slave>*/

	//callbacks from physical I2C driver
	OnWrite OnI2CWrite;
	OnRead	OnI2CRead;
	OnError OnI2CError;

}TI2cConfigHandler;


#endif
