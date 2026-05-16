/*
 * physical_I2c.c
 *
 *  Created on: 2 may 2026
 *      Author: MAX PC
 *
 *      for NXP MKL82Z128 VLK7 variant 80 pins device [Table 1 of KL82P121M72SF0.pdf]
 */

#include "C:\Users\MAX PC\Documents\repositories\CodePool\Common\MCU\global_def.h"
#include "C:\Users\MAX PC\Documents\repositories\CodePool\Drivers\CommsLogicalDrivers\I2C\c\MCU\KL82Z128\physical_i2c.h"
#include "MKL82Z7.h"

//I2c physical driver events
OnWrite 		OnEvent_I2CWrite;
OnRead 			OnEvent_I2CRead;
OnError 		OnEvent_I2CError;

//pointer to describe the num of i2c ports and its pinout alternatives, [section 11.3.1, KL82P121M72SF0RM.pdf]
UINT8 portsAndPinoutAlt[2][I2C_PINOUT_ALTERNATIVE_POSITIONS];

TI2CMCUFeatures i2cPhysicalDriverFeatures;
TI2cPhysicalConfigHandler PhysicalDriverConfigHandler; //config handler for i2c module

//*****************************************************************************
UINT8 I2C0_Config_PinoutLocation(TI2CPinoutLocation pinoutLocation)
//*****************************************************************************
// MCU dependant function: I2C config pinout location
//*****************************************************************************
{
	//section

	//configuring i2c signals pinout
	switch(pinoutLocation)
	{
		default:
		case pinoutLocation_Alt2:
			//enable clock gate for i2c0 selected pinout port
			SIM->SCGC5 |= 0x00000400;

			//setup the corresponding selected pins for i2c0 signals
	    /* PORTB0  I2C0_SCL*/
			PORTB->PCR[0] |= 0x00000200;
	    /* PORTB1  I2C0_SDA*/
			PORTB->PCR[1] |= 0x00000200;

		return OK;
		break;

		case pinoutLocation_Alt7:
			//enable clock gate for i2c0 selected pinout port
			SIM->SCGC5 |= 0x00001000;

			//setup the corresponding selected pins for i2c0 signals
	    /* PORTD2  I2C0_SCL*/
			PORTD->PCR[2] |= 0x00000700;
	    /* PORTD3  I2C0_SDA*/
			PORTD->PCR[3] |= 0x00000700;

		return OK;
		break;
	}
	return ERROR;
}

//*****************************************************************************
UINT8 I2C1_Config_PinoutLocation(TI2CPinoutLocation pinoutLocation)
//*****************************************************************************
// MCU dependant function: I2C config pinout location
//*****************************************************************************
{
	//configuring i2c signals pinout
	switch(pinoutLocation)
	{
		default:
		case pinoutLocation_Alt2:
			//enable clock gate for i2c1 selected pinout port
			SIM->SCGC5 |= 0x00000800;

			//setup the corresponding selected pins for i2c1 signals
	    /* PORTC10  I2C1_SCL*/
			PORTC->PCR[10] |= 0x00000200;
	    /* PORTC11  I2C1_SDA*/
			PORTC->PCR[11] |= 0x00000200;
		return OK;
		break;

		case pinoutLocation_Alt6 :
			//enable clock gate for i2c1 selected pinout port
			SIM->SCGC5 |= 0x00002000;

			//setup the corresponding selected pins for i2c1 signals
	    /* PORTE0  I2C1_SCL*/
			PORTE->PCR[0] |= 0x00000600;
	    /* PORTE1  I2C1_SDA*/
			PORTE->PCR[1] |= 0x00000600;

		return OK;
		break;
	}

	return ERROR;
}

//*****************************************************************************
UINT8 I2C_Config_port(TI2cPhysicalConfigHandler *I2C_Config_Handler)
//*****************************************************************************
// MCU dependant function: I2C config port
//*****************************************************************************
{
	//configuring peripheral i2c
	switch(I2C_Config_Handler->portNumber)
	{
		case 0:
			//enable clock gate for i2c port 0 mcu peripheral [section 13.2.7, KL82P121M72SF0RM.pdf]
			SIM->SCGC4 |= 0x00000040;

			//[section 49.3.1, KL82P121M72SF0RM.pdf]
			I2C0->C1 |= 0b01100000;

			//[section 49.4.6, KL82P121M72SF0RM.pdf]
			I2C0->C2 |= 0b00000000;

			//set the pinout location
			I2C0_Config_PinoutLocation(I2C_Config_Handler->pinoutLocation);
		break;

		case 1:
			//enable clock gate for i2c port 1 mcu peripheral [section 13.2.7, KL82P121M72SF0RM.pdf]
			SIM->SCGC4 |= 0x00000080;

			//[section 49.3.1, KL82P121M72SF0RM.pdf]
			I2C1->C1 |= 0b01100000;

			//[section 49.4.6, KL82P121M72SF0RM.pdf]
			I2C1->C2 |= 0b00000000;

			//set the pinout location
			I2C1_Config_PinoutLocation(I2C_Config_Handler->pinoutLocation);
			break;

		default:
			//if port greater than 1 is trying to be confifgured, drivers raise an error
		return ERROR;
		break;
	}

	return OK;
}

//*****************************************************************************
UINT8 I2C_Config_Clk(TI2cPhysicalConfigHandler *I2C_Config_Handler)
//*****************************************************************************
// MCU dependant function: I2C config clk speed
//*****************************************************************************
{
	switch(I2C_Config_Handler->portNumber)
	{
		case 0:
			break;

		case 1:
			break;

		default:
			return ERROR;
			break;
	}
	return OK;
}

//*****************************************************************************
UINT8 I2C_Config_Timeout(UINT8 timeout)
//*****************************************************************************
// MCU dependant function: I2C config clk speed
//*****************************************************************************
{
	//TODO
	return OK;
}

//*****************************************************************************
void SaveI2CPhysicalDriverConfig(TI2cPhysicalConfigHandler *I2C_Config_Handler)
//*****************************************************************************
//
//*****************************************************************************
{
	PhysicalDriverConfigHandler.portNumber = I2C_Config_Handler->portNumber;
	PhysicalDriverConfigHandler.busSpeed = I2C_Config_Handler->busSpeed;
	PhysicalDriverConfigHandler.I2CTimeout = I2C_Config_Handler->I2CTimeout;
	PhysicalDriverConfigHandler.slave10AddressBitsOn = I2C_Config_Handler->slave10AddressBitsOn;

	//wiring events to callbacks from logical driver
	OnEvent_I2CWrite = I2C_Config_Handler->callbackWriteI2c;
	OnEvent_I2CRead = I2C_Config_Handler->callbackReadI2c;
	OnEvent_I2CError = I2C_Config_Handler->callbackErrorI2c;
}

//*****************************************************************************
// Physical driver exposed external functions implementation
//*****************************************************************************

//*****************************************************************************
TI2CMCUFeatures *I2C_AskPeripheralFeatures(void)
//*****************************************************************************
// MCU i2c peripheral features
//*****************************************************************************
{
	UINT8 j=0;

	//physical how many I2C ports the physical driver manages according to I2C HW
	i2cPhysicalDriverFeatures.numOfPhysicalPorts = 2;

	//define I2C pinout posible locations and fill the other ones with none alternative
	i2cPhysicalDriverFeatures.pinoutAltsPerPort = portsAndPinoutAlt;

	portsAndPinoutAlt[0][0] = pinoutLocation_Alt2;
	portsAndPinoutAlt[0][1] = pinoutLocation_Alt7;
	for(j=2; j<I2C_PINOUT_ALTERNATIVE_POSITIONS; j++)
	{
		portsAndPinoutAlt[0][j] = pinoutLocation_none;
	}

	portsAndPinoutAlt[1][0]= pinoutLocation_Alt2;
	portsAndPinoutAlt[1][1]= pinoutLocation_Alt6;
	for(j=2; j<I2C_PINOUT_ALTERNATIVE_POSITIONS; j++)
	{
		portsAndPinoutAlt[1][j] = pinoutLocation_none;
	}

	//device has master mode feature
	i2cPhysicalDriverFeatures.masterModeFeature = TRUE;

	//device has 10bits slave address feature
	i2cPhysicalDriverFeatures.slave10AddressBitFeature = TRUE;

	//device has DMA I2C transfers feature
	i2cPhysicalDriverFeatures.DMAI2CTransfersfeature = TRUE;

	return &i2cPhysicalDriverFeatures;
}

//*****************************************************************************
UINT8 I2C_Config(TI2cPhysicalConfigHandler *I2C_Config_Handler)
//*****************************************************************************
//
//*****************************************************************************
{
	//config port
	if( I2C_Config_port(I2C_Config_Handler) == ERROR)
	{
		return ERROR;
	}

	//config CLK
	if( I2C_Config_Clk(I2C_Config_Handler) == ERROR)
	{
		return ERROR;
	}
	else

	//config timeout
	if( I2C_Config_Timeout(I2C_Config_Handler->I2CTimeout) == ERROR)
	{
		return ERROR;
	}

	//saving current i2c config
	SaveI2CPhysicalDriverConfig(I2C_Config_Handler);

	return OK;
}

//*****************************************************************************
UINT8 I2C_Start(UINT8 i2cPort)
//*****************************************************************************
//
//*****************************************************************************
{
	//

	//test
	UINT8 dataBuff[10];
	UINT8 i=0;

	for(i=0; i<10; i++)
	{
		dataBuff[i] = 0xAA;
	}

	if(OnEvent_I2CWrite) OnEvent_I2CWrite(0, dataBuff, 10);
	if(OnEvent_I2CRead) OnEvent_I2CRead(0, dataBuff, 10);
	if(OnEvent_I2CError) OnEvent_I2CError(0, 0xaa);

	return OK;
}

//*****************************************************************************
UINT8 I2C_SendRestart(UINT8 i2cPort)
//*****************************************************************************
//
//*****************************************************************************
{
	//TODO
	return OK;
}

//*****************************************************************************
UINT8 I2C_WriteData(UINT8 i2cPort, UINT8 addr, UINT8 reg, UINT8 *dataBuff, UINT8 Count)
//*****************************************************************************
//
//*****************************************************************************
{
	//TODO
	return OK;
}

//*****************************************************************************
UINT8 I2C_ReadData(UINT8 i2cPort, UINT8 addr, UINT8 reg, UINT8 *dataBuff, UINT8 Count)
//*****************************************************************************
//
//*****************************************************************************
{
	//TODO
	return OK;
}
