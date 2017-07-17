// PX2EngineClientConnector.cpp

#include "PX2EngineClientConnector.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2EngineNetCmdProcess.hpp"
#include "PX2StringTokenizer.hpp"
#include "PX2EngineNetEvent.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2EngineCanvas.hpp"
#include "PX2Log.hpp"
#include "PX2HostEntry.hpp"
#include "PX2DNS.hpp"
#include "PX2Application.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
EngineClientConnector::EngineClientConnector():
ClientConnector(10),
mIsAutoConnect(false),
mAutoConnectTime(5.0f),
mAutoConnectTiming(0.0f),
mIsServerConnected(false),
mAutoConnectIP("127.0.0.1"),
mAutoConnectPort(EngineServerPort),
mHeartTiming(0.0f),
mIsBroadcastInfo(true),
mBroadcastTiming(0.0f)
{
	RegisterHandler(EngineServerMsgID,
		(ServerMsgHandleFunc)&EngineClientConnector::OnStringMsg);
}
//----------------------------------------------------------------------------
EngineClientConnector::~EngineClientConnector()
{
}
//----------------------------------------------------------------------------
int EngineClientConnector::Update(float elapsedSeconds)
{
	if (!IsEnable())
		return -1;

	int ret = ClientConnector::Update(elapsedSeconds);

	if (!mIsServerConnected)
	{
		if (CONNSTATE_CONNECTED == GetConnectState())
		{
			mAutoConnectIP = mConnectToAddr.GetHost().ToString();
			mAutoConnectPort = (int)mConnectToAddr.GetPort();

			OnConnectedToServer();
			mIsServerConnected = true;
		}
		else
		{
			if (mIsBroadcastInfo)
			{
				mBroadcastTiming += elapsedSeconds;
				if (mBroadcastTiming > EngineUDPSendInfoTime)
				{
					BroadcastInfoToLocalNet(EngineUDPPortClient);
					BroadcastInfoToLocalNet(EngineUDPPortServerEditor);

					mBroadcastTiming = 0.0f;
				}
			}
		}
	}
	else
	{
		mHeartTiming += elapsedSeconds;
		if (mHeartTiming >= EngineClientHeartTime)
		{
			_SendHeart();
			mHeartTiming = 0.0f;
		}

		if (CONNSTATE_CONNECTED != GetConnectState())
		{
			OnDisConnectedToServer();
			mIsServerConnected = false;
		}
	}

	if (!mIsServerConnected && mIsAutoConnect)
	{
		mAutoConnectTiming += elapsedSeconds;

		if (mAutoConnectTiming > mAutoConnectTime)
		{
			ConnectNB(mAutoConnectIP, mAutoConnectPort);

			mAutoConnectTiming = 0.0f;
		}
	}

	return ret;
}
//----------------------------------------------------------------------------
void EngineClientConnector::SetAutoConnect(bool autoCnt)
{
	mIsAutoConnect = autoCnt;
}
//----------------------------------------------------------------------------
bool EngineClientConnector::IsAutoConnect() const
{
	return mIsAutoConnect;
}
//----------------------------------------------------------------------------
void EngineClientConnector::SetAutoConnectTime(float seconds)
{
	mAutoConnectTime = seconds;
}
//----------------------------------------------------------------------------
float EngineClientConnector::GetAutoConnectTime() const
{
	return mAutoConnectTime;
}
//----------------------------------------------------------------------------
void EngineClientConnector::SetAutoConnectIP(const std::string &ipStr)
{
	mAutoConnectIP = ipStr;
}
//----------------------------------------------------------------------------
void EngineClientConnector::SetAutoConnectPort(int port)
{
	mAutoConnectPort = port;
}
//----------------------------------------------------------------------------
const std::string &EngineClientConnector::GetAutoConnectIP() const
{
	return mAutoConnectIP;
}
//----------------------------------------------------------------------------
int EngineClientConnector::GetAutoConnectPort() const
{
	return mAutoConnectPort;
}
//----------------------------------------------------------------------------
bool EngineClientConnector::IsConnected() const
{
	return mIsServerConnected;
}
//----------------------------------------------------------------------------
void EngineClientConnector::OnConnectedToServer()
{
	for (int i = 0; i < (int)mOnConnectCallbacks.size(); i++)
	{
		const std::string &strCallBack = mOnConnectCallbacks[i];
		if (!strCallBack.empty())
		{
			PX2_SC_LUA->CallFunction(strCallBack, this);
		}
	}

	Event *ent = PX2_CREATEEVENTEX(EngineNetES, OnEngineClientConnected);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EngineClientConnector::OnDisConnectedToServer()
{
	for (int i = 0; i < (int)mOnDisconnectCallbacks.size(); i++)
	{
		const std::string &strCallBack = mOnDisconnectCallbacks[i];
		if (!strCallBack.empty())
		{
			PX2_SC_LUA->CallFunction(strCallBack, this);
		}
	}

	Event *ent = PX2_CREATEEVENTEX(EngineNetES, OnEngineClientDisConnected);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EngineClientConnector::SendString(const std::string &str)
{
	if (!str.empty())
	{
		SendMsgToServerBuffer(EngineServerMsgID, str.c_str(),
			(int)str.length());
	}
}
//----------------------------------------------------------------------------
void EngineClientConnector::SendPushProject()
{
	SendString(CMD_PushProject);
}
//----------------------------------------------------------------------------
bool EngineClientConnector::IsHasOnConnectCallback(
	const std::string &strCallback) const
{
	for (int i = 0; i < (int)mOnConnectCallbacks.size(); i++)
	{
		const std::string &ck = mOnConnectCallbacks[i];
		if (ck == strCallback)
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EngineClientConnector::AddOnConnectCallback(const std::string &callback)
{
	if (IsHasOnConnectCallback(callback))
		return;

	mOnConnectCallbacks.push_back(callback);
}
//----------------------------------------------------------------------------
void EngineClientConnector::RemoveOnConnectCallback(const std::string &callback)
{
	auto it = std::find(mOnConnectCallbacks.begin(), mOnConnectCallbacks.end(),
		callback);
	if (it != mOnConnectCallbacks.end())
	{
		mOnConnectCallbacks.erase(it);
	}
}
//----------------------------------------------------------------------------
bool EngineClientConnector::IsHasOnDisConnectCallback(const std::string &strCallback) const
{
	for (int i = 0; i < (int)mOnDisconnectCallbacks.size(); i++)
	{
		const std::string &ck = mOnDisconnectCallbacks[i];
		if (ck == strCallback)
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EngineClientConnector::AddOnDisconnectCallback(const std::string &callback)
{
	if (IsHasOnDisConnectCallback(callback))
		return;

	mOnDisconnectCallbacks.push_back(callback);
}
//----------------------------------------------------------------------------
void EngineClientConnector::RemoveOnDisconnectCallback(const std::string &callback)
{
	auto it = std::find(mOnDisconnectCallbacks.begin(), mOnDisconnectCallbacks.end(),
		callback);
	if (it != mOnDisconnectCallbacks.end())
	{
		mOnDisconnectCallbacks.erase(it);
	}
}
//----------------------------------------------------------------------------
bool EngineClientConnector::IsHasOnRecvCallback(const std::string &strCallback) const
{
	for (int i = 0; i < (int)mOnRecvCallbacks.size(); i++)
	{
		const std::string &ck = mOnRecvCallbacks[i];
		if (ck == strCallback)
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EngineClientConnector::AddOnRecvCallback(const std::string &callback)
{
	if (IsHasOnRecvCallback(callback))
		return;

	mOnRecvCallbacks.push_back(callback);
}
//----------------------------------------------------------------------------
void EngineClientConnector::RemoveOnRecvCallback(const std::string &callback)
{
	auto it = std::find(mOnRecvCallbacks.begin(), mOnRecvCallbacks.end(),
		callback);
	if (it != mOnRecvCallbacks.end())
	{
		mOnRecvCallbacks.erase(it);
	}
}
//----------------------------------------------------------------------------
int EngineClientConnector::OnStringMsg(const void *pbuffer, int buflen)
{
	std::string strBuf((const char*)pbuffer, buflen);

	for (int i = 0; i < (int)mOnRecvCallbacks.size(); i++)
	{
		const std::string &strCallBack = mOnRecvCallbacks[i];
		if (!strCallBack.empty())
		{
			PX2_SC_LUA->CallFunction(strCallBack, this, strBuf);
		}
	}

	EngineCanvas *engineCanvas = EngineCanvas::GetSingletonPtr();
	UIList *list = engineCanvas->GetEngineInfoList();
	list->AddItem("EngineClientConnector OnStringMsg:" + strBuf);
	PX2_LOG_INFO("EngineClientConnector OnStringMsg: %s", strBuf.c_str());

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

	EngineNetCmdProcess::OnCmd(mAutoConnectIP, cmdStr, paramStr0, paramStr1);

	return 0;
}
//----------------------------------------------------------------------------
void EngineClientConnector::_SendHeart()
{
	if (IsConnected())
	{
		SendString("heart");
	}
}
//----------------------------------------------------------------------------
void EngineClientConnector::SetBroadcastInfo(bool broadcast)
{
	mIsBroadcastInfo = broadcast;
}
//----------------------------------------------------------------------------
bool EngineClientConnector::IsBroadcastInfo() const
{
	return mIsBroadcastInfo;
}
//----------------------------------------------------------------------------
void EngineClientConnector::BroadcastInfoToLocalNet(int port)
{
	SocketAddress sktAddr("255.255.255.255", EngineUDPPortClient);
	std::string name = PX2_APP.GetHostName();
	std::string bufStr = CMD_EngineUDPInfoTag + " " + name;

	UDPServer *udpServer = PX2_APP.GetEngineUDPServerClient();
	if (udpServer)
	{
		DatagramSocket &udpSocket = udpServer->GetSocket();
		udpSocket.SetBroadcast(true);
		udpSocket.SendTo(bufStr.c_str(), bufStr.length(), sktAddr);
		udpSocket.SetBroadcast(false);
	}
}
//----------------------------------------------------------------------------