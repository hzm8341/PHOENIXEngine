// PX2ApplicationUDPNetInfo.cpp

#include "PX2Application.hpp"
#include "PX2EngineNetEvent.hpp"
#include "PX2ApplicationUDPNetInfo.hpp"
#include "PX2EngineNetCmdProcess.hpp"
#include "PX2DNS.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
void UDPNetInfo::UDPServerRecvCallback(SocketAddress &address,
	const std::string &buf)
{
	StringTokenizer stk(buf, " ");

	std::string cmd;
	std::string param0;
	std::string param1;

	if (stk.Count() > 0)
		cmd = stk[0];
	if (stk.Count() > 1)
		param0 = stk[1];
	if (stk.Count() > 2)
		param1 = stk[2];

	std::string ip = address.GetHost().ToString();

	if (CMD_EngineUDPInfoTag == cmd)
	{
		std::string paramName = param0;

		std::string myName = PX2_APP.GetHostName();
		if (paramName != myName || PX2_APP.IsInEditor())
		{
			UDPNetInfo *info = PX2_APP.GetUDPNetInfo(ip);
			if (!info)
			{
				PX2_APP.AddUDPNetInfo(ip, paramName);
			}
			else
			{
				info->UpdateTiming = 0.0f;
			}
		}
	}
	else if (CMD_EngineUDPConnectMeStr == cmd)
	{
		EngineClientConnector *cnt = PX2_APP.GetEngineClientConnector();
		if (cnt && cnt->IsEnable())
		{
			PX2_LOG_INFO("Connect to %s:%d", ip.c_str(), EngineServerPort);

			cnt->Disconnect();
			cnt->SetAutoConnectIP(ip);
			cnt->SetAutoConnectPort(EngineServerPort);
			cnt->SetAutoConnect(true);
			cnt->ConnectNB(ip, EngineServerPort);
		}
	}
	else
	{
		EngineNetCmdProcess::OnCmd(ip, cmd, param0, param1);
	}
}
//----------------------------------------------------------------------------
UDPNetInfo::UDPNetInfo()
{
	ClientID = 0;
	IsConnected = false;
}
//----------------------------------------------------------------------------
UDPNetInfo::~UDPNetInfo()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
UDPNetInfo *Application::GetUDPNetInfo(const std::string &ip)
{
	for (int i = 0; i < (int)mUDPNetInfos.size(); i++)
	{
		if (ip == mUDPNetInfos[i]->IP)
			return mUDPNetInfos[i];
	}

	return 0;
}
//----------------------------------------------------------------------------
bool Application::AddUDPNetInfo(const std::string &ip, const std::string &name)
{
	UDPNetInfo *info = GetUDPNetInfo(ip);
	if (info)
		return false;

	info = new0 UDPNetInfo();
	info->IP = ip;
	info->Name = name;

	mUDPNetInfos.push_back(info);

	Event *ent = EngineNetES::CreateEventX(
		EngineNetES::EngineClientUDPInfoChanged);
	PX2_EW.BroadcastingLocalEvent(ent);

	return true;
}
//----------------------------------------------------------------------------
int Application::GetNumUDPNetInfo() const
{
	return (int)mUDPNetInfos.size();
}
//----------------------------------------------------------------------------
UDPNetInfo *Application::GetUDPNetInfo(int i)
{
	if (0<=i && i<(int)mUDPNetInfos.size())
		return mUDPNetInfos[i];

	return 0;
}
//----------------------------------------------------------------------------
void Application::ClearUDPNetInfo()
{
	mUDPNetInfos.clear();

	Event *ent = EngineNetES::CreateEventX(
		EngineNetES::EngineClientUDPInfoChanged);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void Application::_UpdateUDPNetInfos(float elapsedTime)
{
	bool isInfoChanged = false;
	
	auto it = mUDPNetInfos.begin();
	for (; it != mUDPNetInfos.end();)
	{
		UDPNetInfo *info = *it;

		info->UpdateTiming += elapsedTime;
		if (info->UpdateTiming >= EngineUDPSendInfoTime*2.2f &&
			!info->IsConnected)
		{
			it = mUDPNetInfos.erase(it);

			isInfoChanged = true;
		}
		else
		{
			it++;
		}
	}

	if (isInfoChanged)
	{
		Event *ent = EngineNetES::CreateEventX(
			EngineNetES::EngineClientUDPInfoChanged);
		PX2_EW.BroadcastingLocalEvent(ent);
	}
}
//----------------------------------------------------------------------------