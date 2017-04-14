// PX2GeneralServer.cpp

#include "PX2GeneralServer.hpp"
#include "PX2Log.hpp"
#include "PX2StringTokenizer.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
GeneralServerCallData::GeneralServerCallData() :
TheCallType(GSCT_MAX_TYPE),
ClientID(0)
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
GeneralServer::GeneralServer(Server::ServerType serverType, int port,
	int numMaxConnects, int numMaxMsgHandlers) :
	Server(serverType, port, numMaxConnects, numMaxMsgHandlers)
{
	RegisterHandler(GeneralServerMsgID, (Server::MsgHandleFunc)&GeneralServer::OnString);
}
//----------------------------------------------------------------------------
GeneralServer::~GeneralServer()
{
}
//----------------------------------------------------------------------------
int GeneralServer::OnConnect(unsigned int clientid)
{
	PX2_LOG_INFO("client: %d connected", clientid);

	ClientContext *context = GetClientContext(clientid);
	if (context)
	{
		SocketAddress addr = context->TheSocket.GetImpl()->GetPeerAddress();
		std::string ip = addr.ToString();

		GeneralServerCallData data;
		data.TheCallType = GSCT_ON_CONNECT;
		data.ClientID = clientid;
		data.strData = ip;

		for (int i = 0; i < (int)mCallbacks.size(); i++)
		{	
			mCallbacks[i](data);
		}
	}

	return 0;
}
//----------------------------------------------------------------------------
int GeneralServer::OnDisconnect(unsigned int clientid)
{
	PX2_LOG_INFO("client: %d disconnected", clientid);

	GeneralServerCallData data;
	data.TheCallType = GSCT_ON_DISCONNECT;
	data.ClientID = clientid;

	for (int i = 0; i < (int)mCallbacks.size(); i++)
	{
		mCallbacks[i](data);
	}

	return 0;
}
//----------------------------------------------------------------------------
int GeneralServer::OnString(unsigned int clientid, const void *pbuffer, int buflen)
{
	std::string strBuf((const char*)pbuffer, buflen);

	GeneralServerCallData data;
	data.TheCallType = GSCT_ON_RECVEDMSG;
	data.ClientID = clientid;
	data.strData = strBuf;

	for (int i = 0; i < (int)mCallbacks.size(); i++)
	{
		mCallbacks[i](data);
	}

	return 0;
}
//----------------------------------------------------------------------------
void GeneralServer::SendString(int clientid, const std::string &str)
{
	if (!str.empty() && clientid > 0)
	{
		SendMsgToClientBuffer(clientid, GeneralServerMsgID, str.c_str(),
			str.length());
	}
}
//----------------------------------------------------------------------------
void GeneralServer::AddCallback(GeneralServerCallback callBack)
{
	mCallbacks.push_back(callBack);
}
//----------------------------------------------------------------------------