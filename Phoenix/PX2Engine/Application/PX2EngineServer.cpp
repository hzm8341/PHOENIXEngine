// PX2EngineServer.hpp

#include "PX2EngineServer.hpp"
#include "PX2EngineCanvas.hpp"
#include "PX2StringHelp.hpp"
#include "PX2StringTokenizer.hpp"
#include "PX2Application.hpp"
#include "PX2Dir.hpp"
#include "PX2EngineNetCmdProcess.hpp"
#include "PX2EngineNetEvent.hpp"
#include "PX2Log.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
_ConnectObj::_ConnectObj()
{
	ClientID = 0;
	HeartTiming = 0.0f;
}
//----------------------------------------------------------------------------
_ConnectObj::~_ConnectObj()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
EngineServer::EngineServer(Server::ServerType serverType, int port) :
	Server(serverType, port, 10, 10)
{
	RegisterHandler(EngineServerMsgID, (Server::MsgHandleFunc)
		&EngineServer::OnString);
}
//----------------------------------------------------------------------------
EngineServer::~EngineServer()
{
}
//----------------------------------------------------------------------------
void EngineServer::Run(float elapsedTime)
{
	Server::Run(elapsedTime);

	auto it = mConnections.begin();
	for (; it != mConnections.end();)
	{
		_ConnectObj *obj = it->second;
		obj->HeartTiming += elapsedTime;

		if (obj->HeartTiming > EngineServerHeartTime)
		{
			obj->HeartTiming = 0.0f;

			int clientID = (int)it->first;
			DisconnectClient(it->first);
			it = mConnections.erase(it);

			PX2_LOG_INFO("Heart disconnect client %d", clientID);
		}
		else
		{
			it++;
		}
	}
}
//----------------------------------------------------------------------------
void EngineServer::SendString(int clientid, const std::string &str)
{
	if (!str.empty() && clientid > 0)
	{
		SendMsgToClientBuffer(clientid, EngineServerMsgID, str.c_str(),
			str.length());
	}
}
//----------------------------------------------------------------------------
void EngineServer::BroadCastString(const std::string &str)
{
	auto it = mConnections.begin();
	for (; it != mConnections.end(); it++)
	{
		unsigned int clientID = it->first;
		SendString(clientID, str);
	}
}
//----------------------------------------------------------------------------
void EngineServer::BroadCastPushProject(const std::string &projName)
{
	auto it = mConnections.begin();
	for (; it != mConnections.end(); it++)
	{
		unsigned int clientID = it->first;
		SendString(clientID, "pushproject " + projName);
	}
}
//----------------------------------------------------------------------------
int EngineServer::OnConnect(unsigned int clientid)
{
	_ConnectObj *cntObj = new0 _ConnectObj();
	cntObj->ClientID = clientid;
	mConnections[clientid] = cntObj;

	Event *ent = PX2_CREATEEVENTEX(EngineNetES, OnEngineServerBeConnected);
	ent->SetDataStr0(StringHelp::IntToString((int)clientid));
	PX2_EW.BroadcastingLocalEvent(ent);

	return 0;
}
//----------------------------------------------------------------------------
int EngineServer::OnDisconnect(unsigned int clientid)
{
	mConnections.erase(clientid);

	Event *ent = PX2_CREATEEVENTEX(EngineNetES, OnEngineServerBeDisConnected);
	ent->SetDataStr0(StringHelp::IntToString((int)clientid));
	PX2_EW.BroadcastingLocalEvent(ent);

	return 0;
}
//----------------------------------------------------------------------------
int EngineServer::OnString(unsigned int clientid, const void *pbuffer,
	int buflen)
{
	std::string strBuf((const char*)pbuffer, buflen);

	EngineCanvas *engineCanvas = EngineCanvas::GetSingletonPtr();
	if (engineCanvas)
	{
		UIList *list = engineCanvas->GetEngineInfoList();
		list->AddItem("OnString clientid:" + StringHelp::IntToString(clientid) +
			" " + "Str:" + strBuf);
	}

	StringTokenizer stk(strBuf, " ");
	int numTok = stk.Count();
	
	std::string cmdStr;
	std::string paramStr0;
	std::string paramStr1;
	if (numTok >= 1)
		cmdStr = stk[0];
	if (numTok >= 2)
		paramStr0 = stk[1];
	if (numTok >= 3)
		paramStr1 = stk[2];

	if ("heart" == cmdStr)
	{
		mConnections[clientid]->HeartTiming = 0.0f;
	}

	EngineNetCmdProcess::OnCmd(cmdStr, paramStr0, paramStr1);

	return 0;
}
//----------------------------------------------------------------------------