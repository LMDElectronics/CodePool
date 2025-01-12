// MsgBuilderTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//*****************************************************************************
// TODO list:
//   -encapsulate Ping message class test into a class 
//   -finish test for the rest of the messages
//*****************************************************************************

#include <iostream>
#include <Windows.h>
#include "..\MsgBuilder\MsgBuilder\MsgBuilder.h"

#define CONSOLE_COLOR_GREEN 10
#define CONSOLE_DEFAULT_COLOR 7
#define CONSOLE_COLOR_WHITE 15
#define CONSOLE_COLOR_RED 12
#define CONSOLE_COLOR_BLUE 11
#define CONSOLE_COLOR_YELLOW 14

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

uint8_t serializedData[MSG_PING_PAYLOAD_BYTES];
uint16_t nodeOrigin = 1;
uint16_t nodeDestination = 2;
uint16_t sendingTime = 3;
uint16_t pingData = 0xaaaa;

TMsgPing* msg = new TMsgPing(nodeOrigin, nodeDestination, sendingTime, pingData);
TMsgPing* msgDeserialized;

uint32_t classFieldsToTest = msg->GetMessageFields();

bool CheckData(void)
{
	bool retVal = true;	
	uint32_t messageFieldsToTest = classFieldsToTest;

	if (msg != NULL)
	{
		if (nodeOrigin != msg->GetSourceNode()) retVal = false; messageFieldsToTest--;
		if (nodeDestination != msg->GetDestinationNode()) retVal = false; messageFieldsToTest--;
		if (sendingTime != msg->GetSendTime()) retVal = false; messageFieldsToTest--;
		if (pingData != msg->GetPingData()) retVal = false; messageFieldsToTest--;
		
		//used to check as a remainder if all class member variables has been tested
		if (messageFieldsToTest != 0)
		{
			retVal = false;
		}
	}
	else
	{
		retVal = false;
	}

	return retVal;
}

void PrintConsole_OK(void)
{
	SetConsoleTextAttribute(hConsole, CONSOLE_COLOR_WHITE);
	printf("[");
	SetConsoleTextAttribute(hConsole, CONSOLE_COLOR_GREEN);
	printf("OK");
	SetConsoleTextAttribute(hConsole, CONSOLE_COLOR_WHITE);
	printf("]");
	SetConsoleTextAttribute(hConsole, CONSOLE_DEFAULT_COLOR);
}

void PrintConsole_FAIL(void)
{
	SetConsoleTextAttribute(hConsole, CONSOLE_COLOR_WHITE);
	printf("[");
	SetConsoleTextAttribute(hConsole, CONSOLE_COLOR_RED);
	printf("FAIL");
	SetConsoleTextAttribute(hConsole, CONSOLE_COLOR_WHITE);
	printf("]");
	SetConsoleTextAttribute(hConsole, CONSOLE_DEFAULT_COLOR);
}

void PrintConsoleTextWithColor(const char* text, uint16_t color=CONSOLE_DEFAULT_COLOR)
{
	SetConsoleTextAttribute(hConsole, color);
	printf(text);
	SetConsoleTextAttribute(hConsole, CONSOLE_DEFAULT_COLOR);
}

bool CheckSerialization(void)
{
	bool retVal = true;

	uint8_t index = 0;

	uint16_t nodeOriginSerialized = 0;
	uint16_t nodeDestinationSerialized = 0;
	uint16_t nodeSendTimeSerialized = 0;
	uint16_t nodePingDataSerialized = 0;
	uint32_t messageFieldsToTest = classFieldsToTest;

	if (serializedData != NULL)
	{
		nodeOriginSerialized = serializedData[index++];
		nodeOriginSerialized <<= 8;
		nodeOriginSerialized |= serializedData[index++];
		if (nodeOriginSerialized != msg->GetSourceNode()) return false; messageFieldsToTest--;

		nodeDestinationSerialized = serializedData[index++];
		nodeDestinationSerialized <<= 8;
		nodeDestinationSerialized |= serializedData[index++];
		if (nodeDestinationSerialized != msg->GetDestinationNode()) return false; messageFieldsToTest--;

		nodeSendTimeSerialized = serializedData[index++];
		nodeSendTimeSerialized <<= 8;
		nodeSendTimeSerialized |= serializedData[index++];
		if (nodeSendTimeSerialized != msg->GetSendTime()) return false; messageFieldsToTest--;

		nodePingDataSerialized = serializedData[index++];
		nodePingDataSerialized <<= 8;
		nodePingDataSerialized |= serializedData[index++];
		if (nodePingDataSerialized != msg->GetPingData()) return false; messageFieldsToTest--;

		//used to check as a remainder if all class member variables has been tested
		if (messageFieldsToTest != 0)
		{
			retVal = false;
		}
	}
	else
	{
		retVal = false;
	}	

	return retVal;
}

bool CheckDeserialization(void)
{
	bool retVal = true;

	uint8_t index = 0;
	uint32_t messageFieldsToTest = classFieldsToTest;

	if (serializedData != NULL)
	{
		if (msgDeserialized->GetSourceNode() != msg->GetSourceNode()) return false; messageFieldsToTest--;
		if (msgDeserialized->GetDestinationNode() != msg->GetDestinationNode()) return false; messageFieldsToTest--;
		if (msgDeserialized->GetSendTime() != msg->GetSendTime()) return false; messageFieldsToTest--;
		if (msgDeserialized->GetPingData() != msg->GetPingData()) return false; messageFieldsToTest--;

		//used to check as a remainder if all class member variables has been tested
		if (messageFieldsToTest != 0)
		{
			retVal = false;
		}
	}
	else
	{
		retVal = false;
	}

	return retVal;
}

int main()
{	
	PrintConsoleTextWithColor("********************************** \n", CONSOLE_COLOR_WHITE);
	PrintConsoleTextWithColor("--- Running MsgBuilderTest ---     \n", CONSOLE_COLOR_YELLOW);
	PrintConsoleTextWithColor("********************************** \n", CONSOLE_COLOR_WHITE);

	PrintConsoleTextWithColor("--- Testing Ping message class --- \n", CONSOLE_COLOR_WHITE);

	printf("Checking Data...");
	if (CheckData())
	{
		PrintConsole_OK();
	}
	else
	{
		PrintConsole_FAIL();
		return 1;
	}
	printf("\n");
	
	printf("Testing msg serialization...");	
	msg->Serialize(serializedData);
	if (CheckSerialization())
	{
		PrintConsole_OK();
	}
	else
	{
		PrintConsole_FAIL();
		return 1;
	}
	printf("\n");

	printf("Testing msg deserialization...");
	msgDeserialized = msg->Deserialize(serializedData);
	if (CheckDeserialization())
	{
		PrintConsole_OK();
	}
	else
	{
		PrintConsole_FAIL();
		return 1;
	}
	printf("\n");

	delete msg;
	delete msgDeserialized;

	PrintConsoleTextWithColor("--- Testing Finished --- \n", CONSOLE_COLOR_WHITE);

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window t o see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
