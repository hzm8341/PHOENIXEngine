// LRServer.hpp

#ifndef LRSERVER_HPP
#define LRSERVER_HPP

#include "LRPre.hpp"
#include "PX2NetServer.hpp"
#include "PX2SmartPointer.hpp"
#include "PX2Singleton_NeedNew.hpp"
#include "PX2GPIO.hpp"
#include "PX2Serial.hpp"

namespace PX2
{

	class LRServer : public Server, public Singleton < LRServer >
	{
	public:
		LRServer(PX2::Server::ServerType serverType, int port,
			int numMaxConnects, int numMaxMsgHandlers);
		virtual ~LRServer();

		void SendString(unsigned int clientid, const std::string &str);

		int OnProcessString(int clientid, const std::string &cmdStr);

	protected:
		virtual int OnConnect(unsigned int clientid);
		virtual int OnDisconnect(unsigned int clientid);
		int OnString(unsigned int clientid, const void *pbuffer, int buflen);

	protected:
		unsigned int GetNextUID();
		void _PlayMusic(bool play);
		void _SetMove(const std::string &leftRight, const std::string &goBack);
		void _SetSpeed(const std::string &leftRight, const std::string &speedVal);
		void _LogGPIOVal(int pin);
		void _RefreshRobot(int clientID);
		
		unsigned int mNextUID;
		GPIO mGPIOLeft0;
		GPIO mGPIOLeft1;
		GPIO mGPIOLeftSpeed;
		GPIO mGPIORight0;
		GPIO mGPIORight1;
		GPIO mGPIORightSpeed;
		Serial mSerial;
	};

#define  LR_SERVER LRServer::GetSingleton()
	typedef Pointer0<LRServer> LRServerPtr;

}

#endif