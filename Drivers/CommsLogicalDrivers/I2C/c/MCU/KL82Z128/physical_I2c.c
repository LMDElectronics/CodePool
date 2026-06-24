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

#define NOT_BUSY 			0;
#define BUSY					1;

//I2c physical driver events
OnWrite 		OnEvent_I2CWrite;
OnRead 			OnEvent_I2CRead;
OnError 		OnEvent_I2CError;

//pointer to describe the num of i2c ports and its pinout alternatives, [section 11.3.1, KL82P121M72SF0RM.pdf]
UINT8 portsAndPinoutAlt[2][I2C_PINOUT_ALTERNATIVE_POSITIONS];

TI2CMCUFeatures i2cPhysicalDriverFeatures;
TI2cPhysicalConfigHandler PhysicalDriverConfigHandler; //config handler for i2c module

//*****************************************************************************
UINT8 I2C_Config_Clock_Gate(UINT8 portNumber)
//*****************************************************************************
// Configure the I2c peripheral clock gate
//*****************************************************************************
{
	switch(portNumber)
	{
	case 0:
		SIM->SCGC4 |= 0x00000040;
		return OK;

	case 1:
		SIM->SCGC4 |= 0x00000080;
		return OK;

	default:
		return ERROR;
	}
}

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

			//setup the corresponding selected pins for i2c0 signals, and ODE for open drain output
	    /* PORTB0  I2C0_SCL*/
			PORTB->PCR[0] |= 0x00000220;
	    /* PORTB1  I2C0_SDA*/
			PORTB->PCR[1] |= 0x00000220;
		return OK;

		case pinoutLocation_Alt7:
			//enable clock gate for i2c0 selected pinout port
			SIM->SCGC5 |= 0x00001000;

			//setup the corresponding selected pins for i2c0 signals, and ODE for open drain output
	    /* PORTD2  I2C0_SCL*/
			PORTD->PCR[2] |= 0x00000720;
	    /* PORTD3  I2C0_SDA*/
			PORTD->PCR[3] |= 0x00000720;
			return OK;
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

			//setup the corresponding selected pins for i2c1 signals, and ODE for open drain output
	    /* PORTC10  I2C1_SCL*/
			PORTC->PCR[10] |= 0x00000220;
	    /* PORTC11  I2C1_SDA*/
			PORTC->PCR[11] |= 0x00000220;
			return OK;

		case pinoutLocation_Alt6 :
			//enable clock gate for i2c1 selected pinout port
			SIM->SCGC5 |= 0x00002000;

			//setup the corresponding selected pins for i2c1 signals, and ODE for open drain output
	    /* PORTE0  I2C1_SCL*/
			PORTE->PCR[0] |= 0x00000620;
	    /* PORTE1  I2C1_SDA*/
			PORTE->PCR[1] |= 0x00000620;
			return OK;
	}

	return ERROR;
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
	PhysicalDriverConfigHandler.masterModeOn = I2C_Config_Handler->masterModeOn;
	PhysicalDriverConfigHandler.useDMA = I2C_Config_Handler->useDMA;
	PhysicalDriverConfigHandler.useInterrupts = I2C_Config_Handler->useInterrupts;

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
UINT8 I2C_Start(UINT8 i2cPort)
//*****************************************************************************
// TODO
//*****************************************************************************
{
	I2C_Type *port;

	switch(i2cPort)
	{
		case 0:
			port = ((I2C_Type *)I2C0_BASE);
			break;

		case 1:
			port = ((I2C_Type *)I2C1_BASE);
			break;

		default: return ERROR;
	}

	port->C1 |= 0x80;

	return OK;
}

//*****************************************************************************
UINT8 I2C_Stop(UINT8 i2cPort)
//*****************************************************************************
// TODO
//*****************************************************************************
{
	I2C_Type *port = 0;

	switch(i2cPort)
	{
		case 0:
			port = ((I2C_Type *)I2C0_BASE);
			break;

		case 1:
			port = ((I2C_Type *)I2C1_BASE);
			break;

		default: return ERROR;
	}

	port->C1 &= 0x7F;

	return OK;
}

//*****************************************************************************
UINT8 I2C_Config(TI2cPhysicalConfigHandler *I2C_Config_Handler)
//*****************************************************************************
// Config I2C peripheral
//*****************************************************************************
{
	I2C_Type *port = 0;

	//configuring pinout
	switch(I2C_Config_Handler->portNumber)
	{
		case 0:
				port = ((I2C_Type *)I2C0_BASE);

				//config pinout location
				if(I2C0_Config_PinoutLocation(I2C_Config_Handler->pinoutLocation) == ERROR)
				{
					return ERROR;
				}
				break;

		case 1:
			port = ((I2C_Type *)I2C1_BASE);

			//config pinout location
			if(I2C1_Config_PinoutLocation(I2C_Config_Handler->pinoutLocation) == ERROR)
			{
				return ERROR;
			}
			break;

		default:
			return ERROR;
	}

	//Config clock gate for peripheral [section 13.2.7, KL82P121M72SF0RM.pdf]
	if(I2C_Config_Clock_Gate(I2C_Config_Handler->portNumber) == ERROR)
	{
		return ERROR;
	}

	//config interrupts
	if(I2C_Config_Handler->useInterrupts)
	{
		port->C1 |= 0x40;
	}
	else
	{
		port->C1 &= 0xBF;
	}

	//config i2c slave address bits
	if(I2C_Config_Handler->slave10AddressBitsOn)
	{
		port->C2 |= 0x40;
	}
	else
	{
		port->C2 &= 0xBF;
	}

	//config i2c using DMA //TODO
	if(I2C_Config_Handler->useDMA)
	{
		port->C1 |= 0x01;
	}
	else
	{
		port->C1 &= 0xFE;
	}

	//config bus speed //TODO
	//I2c uses Bus clock, Max 24Mhz [section 5.7, KL82P121M72SF0RM.pdf]
	port->F = 0x4F; //preescaling for 1Mhz

	//config bus timeouts						//TODO

	//saving current i2c config
	SaveI2CPhysicalDriverConfig(I2C_Config_Handler);

	return OK;
}

//*****************************************************************************
UINT8 I2C_ClearInterrupts(UINT8 i2cPort)
//*****************************************************************************
// TODO
//*****************************************************************************
{
	I2C_Type *port = 0;

	switch(i2cPort)
	{
		case 0:
			port = ((I2C_Type *)I2C0_BASE);
			break;

		case 1:
			port = ((I2C_Type *)I2C1_BASE);
			break;

		default: return ERROR;
	}

	port->S |= 0x02;

	return OK;
}

//*****************************************************************************
UINT8 I2C_SendStart(UINT8 i2cPort)
//*****************************************************************************
// TODO
//*****************************************************************************
{
	I2C_Type *port = 0;

	switch(i2cPort)
	{
		case 0:
			port = ((I2C_Type *)I2C0_BASE);
			break;

		case 1:
			port = ((I2C_Type *)I2C1_BASE);
			break;

		default: return ERROR;
	}

	port->C1 |= 0x30;

	return OK;
}

//*****************************************************************************
UINT8 I2C_SendStop(UINT8 i2cPort)
//*****************************************************************************
// TODO
//*****************************************************************************
{
	I2C_Type *port = 0;

	switch(i2cPort)
	{
		case 0:
			port = ((I2C_Type *)I2C0_BASE);
			break;

		case 1:
			port = ((I2C_Type *)I2C1_BASE);
			break;

		default: return ERROR;
	}

	port->C1 &= 0xDF;
	port->C1 &= 0xEF;

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
UINT8 I2C_CheckBusBusy(UINT8 i2cPort)
//*****************************************************************************
// Busy: 			1
// Not Busy: 	0
//*****************************************************************************
{
	I2C_Type *port = 0;

	switch(i2cPort)
	{
		case 0:
			port = ((I2C_Type *)I2C0_BASE);
			break;

		case 1:
			port = ((I2C_Type *)I2C1_BASE);
			break;

		default:
			return ERROR;
	}

	if((port->S & 0x02) != 0x02)
	{
		return BUSY;
	}
	else
	{
		return NOT_BUSY;
	}
}

//*****************************************************************************
UINT8 I2C_WriteByteBlocking(UINT8 i2cPort, UINT8 byte)
//*****************************************************************************
// returns the ack byte
//*****************************************************************************
{
	I2C_Type *port = 0;

	switch(i2cPort)
	{
		case 0:
			port = ((I2C_Type *)I2C0_BASE);
			break;

		case 1:
			port = ((I2C_Type *)I2C1_BASE);
			break;

		default:
			return ERROR;
	}

	port->D = byte;
	while(I2C_CheckBusBusy(i2cPort));
	I2C_ClearInterrupts(i2cPort);

	return (port->C1 & 0x01); //ACK bit return
}

//*****************************************************************************
UINT8 I2C_ReadByteBlocking(UINT8 i2cPort, UINT8 ack)
//*****************************************************************************
// read a bute from i2c slave
// ack: ack value 0 or 1 to drive into the line when reading from i2c slave
//*****************************************************************************
{
	I2C_Type *port = 0;
	UINT8 data=0;

	switch(i2cPort)
	{
		case 0:
			port = ((I2C_Type *)I2C0_BASE);
			break;

		case 1:
			port = ((I2C_Type *)I2C1_BASE);
			break;

		default:
			return ERROR;
	}

	//drives a 0 or 1 as ack
	if(ack)
	{
		port->C1 &= 0xF7; //ACK
	}
	else
	{
		port->C1 |= 0x08; //NACK
	}

	//Rx mode
	port->C1 &= 0xEF;

	//dummy read
	data = port->D;

	I2C_CheckBusBusy(i2cPort);
	I2C_ClearInterrupts(i2cPort);

	return port->D;
}

//*****************************************************************************
UINT8 I2C_WriteData(UINT8 i2cPort, UINT8 addr, UINT8 *dataBuff, UINT32 Count, TI2COperation StartOperation, TI2COperation EndOperation)
//*****************************************************************************
// TODO
//*****************************************************************************
{
	UINT32 i=0;

	//set the i2c start operation for this transfer
	switch(StartOperation)
	{
		case SendStart:
			I2C_SendStart(i2cPort);
			break;

		case SendStop:
			I2C_SendStop(i2cPort);
			break;

		case SendRestart:
			I2C_SendRestart(i2cPort);
			break;

		case DoNothing:
		default:
			break;
	}

	//send device address
	I2C_WriteByteBlocking(i2cPort, addr);

	//send data
	for(i=0; i < Count; i++)
	{
		I2C_WriteByteBlocking(i2cPort, dataBuff[i]);
	}

	//set the i2c end operation for this transfer
	switch(EndOperation)
	{
		case SendStart:
			I2C_SendStart(i2cPort);
			break;

		case SendStop:
			I2C_SendStop(i2cPort);
			break;

		case SendRestart:
			I2C_SendRestart(i2cPort);
			break;

		case DoNothing:
		default:
			break;
	}

	return OK;
}

//*****************************************************************************
UINT8 I2C_ReadData(UINT8 i2cPort, UINT8 addr, UINT8 *dataBuff, UINT32 Count, TI2COperation StartOperation, TI2COperation EndOperation)
//*****************************************************************************
//
//*****************************************************************************
{
	UINT32 i=0;

	//set the i2c start operation for this transfer
	switch(StartOperation)
	{
		case SendStart:
			I2C_SendStart(i2cPort);
			break;

		case SendStop:
			I2C_SendStop(i2cPort);
			break;

		case SendRestart:
			I2C_SendRestart(i2cPort);
			break;

		case DoNothing:
		default:
			break;
	}

	//send device address
	I2C_WriteByteBlocking(i2cPort, addr | 0x01);

	for(i=0; i < Count; i++)
	{
		if(i == Count - 1)
		{
			dataBuff[i] = I2C_ReadByteBlocking(i2cPort, 0);
		}
		else
		{
			dataBuff[i] = I2C_ReadByteBlocking(i2cPort, 1);
		}
	}

	//set the i2c end operation for this transfer
	switch(EndOperation)
	{
		case SendStart:
			I2C_SendStart(i2cPort);
			break;

		case SendStop:
			I2C_SendStop(i2cPort);
			break;

		case SendRestart:
			I2C_SendRestart(i2cPort);
			break;

		case DoNothing:
		default:
			break;
	}

	return OK;
}
