// PX2EngineServer.hpp

#ifndef PX2ENGINESERVER_HPP
#define PX2ENGINESERVER_HPP

#include "PX2CorePre.hpp"
#include "PX2NetServer.hpp"
#include "PX2Singleton_NeedNew.hpp"
#include "PX2EngineNetDefine.hpp"

namespace PX2
{

	class _ConnectObj
	{
	public:
		_ConnectObj();
		~_ConnectObj();

		unsigned int ClientID;
		float HeartTiming;
	};
	typedef Pointer0<_ConnectObj> _ConnectObjPtr;

	class PX2_ENGINE_ITEM EngineServer : public Server, public Singleton < EngineServer >
	{
	public:
		EngineServer(PX2::Server::ServerType serverType, int port);
		virtual ~EngineServer();

		virtual void Run(float elapsedTime);

		void SendString(int clientid, const std::string &str);
		void BroadCastString(const std::string &str);
		void BroadCastPushProject(const std::string &projName);

	protected:
		virtual int OnConnect(unsigned int clientid);
		virtual int OnDisconnect(unsigned int clientid);
		int OnString(unsigned int clientid, const void *pbuffer, int buflen);

	protected:
		std::map<unsigned int, _ConnectObjPtr> mConnections;
	};
	typedef Pointer0<EngineServer> EngineServerPtr;

}

#endif