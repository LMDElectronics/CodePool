// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the MSGBUILDER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// MSGBUILDER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MSGBUILDER_EXPORTS
#define MSGBUILDER_API __declspec(dllexport)
#else
#define MSGBUILDER_API __declspec(dllimport)
#endif

//TODO export the MsgBuilder functions of the TMessage anf TMsgPing

#include <cstdint>

extern MSGBUILDER_API int nMsgBuilder;
extern MSGBUILDER_API

//exported functions
//MSGBUILDER_API int fnMsgBuilder(void);

#define TMESSAGE_CLASS_FIELDS 3
#define TPING_CLASS_FIELDS 1

#define MSG_PING_PAYLOAD_BYTES 2*4 //8 bytes 

//*****************************************************************************
// TMessage parent class declaration
//*****************************************************************************
class MSGBUILDER_API TMessage
{
	private:
		//private class variable to hold the number of fields (variables) that class containsa
		uint32_t numberOfMsgFields;

	protected:
		uint16_t nodeSource;
		uint16_t nodeDestination;
		uint16_t sendTime;

		uint32_t GetFields(void);

	public:
		TMessage();		

		uint16_t GetSourceNode();
		uint16_t GetDestinationNode();
		uint16_t GetSendTime();

		//pure virtual function, need to be overriden in the child classes
		virtual TMessage* Deserialize(uint8_t* serializedData) = 0;
		virtual void Serialize(uint8_t* dataBuffer) = 0;
};

//*****************************************************************************
// TMsgPing child class declaration
//*****************************************************************************
class MSGBUILDER_API TMsgPing : public TMessage
{
	private:
		uint32_t numberOfMsgFields;
		uint16_t _data;

	public:		
		TMsgPing(uint16_t org, uint16_t dest, uint16_t sendT, uint16_t pingData);
		TMsgPing();

		uint16_t GetPingData(void);		
		uint32_t GetMessageFields(void);

		//overriding parent pure virtual classes
		TMsgPing* Deserialize(uint8_t* serializedData) override;
		void Serialize(uint8_t* dataBuffer) override;
};

class MSGBUILDER_API CMsgBuilder {
public:
	CMsgBuilder(void);
	// TODO: add your methods here.
};
