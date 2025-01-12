// MsgBuilder.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "MsgBuilder.h"

#ifdef MSGBUILDER_EXPORTS
#pragma message("MSGBUILDER_EXPORTS está definido")
#else
#pragma message("MSGBUILDER_EXPORTS NO está definido")
#endif

// This is an example of an exported variable
MSGBUILDER_API int nMsgBuilder=0;

// This is an example of an exported function.
MSGBUILDER_API int fnMsgBuilder(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CMsgBuilder::CMsgBuilder()
{
    return;
}

//*****************************************************************************
// TMessage class implementation
//*****************************************************************************
TMessage::TMessage()
{
	numberOfMsgFields = TMESSAGE_CLASS_FIELDS;
}

uint32_t TMessage::GetFields()
{
	return numberOfMsgFields;
}

uint16_t TMessage::GetDestinationNode()
{
	return nodeDestination;
}

uint16_t TMessage::GetSourceNode()
{
	return nodeSource;
}

uint16_t TMessage::GetSendTime()
{
	return sendTime;
}

//*****************************************************************************
// TMsgPing class implementation
//*****************************************************************************
TMsgPing::TMsgPing(uint16_t org, uint16_t dest, uint16_t sendT,uint16_t pingData)
{	
	this->numberOfMsgFields = this->GetFields() + TPING_CLASS_FIELDS;

	nodeSource = org;
	nodeDestination = dest;
	sendTime = sendT;
	_data = pingData;
}

TMsgPing::TMsgPing()
{
	nodeSource = 0;
	nodeDestination = 0;
	sendTime = 0;
}

uint16_t TMsgPing::GetPingData(void)
{
	return _data;
}

uint32_t TMsgPing::GetMessageFields(void)
{
	return this->numberOfMsgFields;
}

MSGBUILDER_API TMsgPing* TMsgPing::Deserialize(uint8_t* serializedData)
{
	//Deserializing from data received
	nodeSource = serializedData[0];
	nodeSource <<= 8;
	nodeSource |= serializedData[1];

	nodeDestination = serializedData[2];
	nodeDestination <<= 8;
	nodeDestination |= serializedData[3];

	sendTime = serializedData[4];
	sendTime <<= 8;
	sendTime |= serializedData[5];

	_data = serializedData[6];
	_data <<= 8;
	_data |= serializedData[7];

	return new TMsgPing(nodeSource, nodeDestination, sendTime, _data);
}

MSGBUILDER_API void TMsgPing::Serialize(uint8_t* dataBuffer)
{
	uint16_t index = 0;

	dataBuffer[index++] = (uint8_t)((nodeSource & 0xFF00) >> 8);
	dataBuffer[index++] = (uint8_t)((nodeSource & 0x00FF) );

	dataBuffer[index++] = (uint8_t)((nodeDestination & 0xFF00) >> 8);
	dataBuffer[index++] = (uint8_t)((nodeDestination & 0x00FF));

	dataBuffer[index++] = (uint8_t)((sendTime & 0xFF00) >> 8);
	dataBuffer[index++] = (uint8_t)((sendTime & 0x00FF));

	dataBuffer[index++] = (uint8_t)((_data & 0xFF00) >> 8);
	dataBuffer[index++] = (uint8_t)((_data & 0x00FF));
}