// PX2EngineNetCmdProcess.cpp

#include "PX2EngineNetCmdProcess.hpp"
#include "PX2EngineCanvas.hpp"
#include "PX2StringHelp.hpp"
#include "PX2Project.hpp"
#include "PX2Application.hpp"
#include "PX2EngineNetDefine.hpp"
#include "PX2Application.hpp"
using namespace PX2;

EngineNetCmdProcess::EngineNetCmdProcess()
{

}
//----------------------------------------------------------------------------
EngineNetCmdProcess::~EngineNetCmdProcess()
{

}
//----------------------------------------------------------------------------
std::string fromIP;
int fromPort = 0;
//----------------------------------------------------------------------------
void _HardCameraCallback(int width, int height, const char* buf, int size)
{
	std::string content;
	content += "cameraview_";
	content += StringHelp::IntToString(width) + "_";
	content += StringHelp::IntToString(height) + "_";
	content += std::string(buf, size);

	SocketAddress sktAdr(fromIP, (int16_t)fromPort);
	PX2_APP.GetEngineUDPServerClient()->GetSocket().SendTo(content.c_str(), 
		content.length(), sktAdr);
}
//----------------------------------------------------------------------------
void EngineNetCmdProcess::OnCmd(const std::string &fromip, 
	const std::string &cmdStr,
	const std::string &paramStr0, const std::string &paramStr1)
{
	PX2_UNUSED(paramStr1);

	if (CMD_PushProject == cmdStr)
	{
		std::string ipStr = "ftp://" + fromip + "/";
		PX2_RM.SetResourceUpdateAddr(ipStr);

		Project *proj = Project::GetSingletonPtr();
		if (proj)
		{
			PX2_APP.CloseProject();
		}

		std::string projName = paramStr0;
		if (!projName.empty())
		{
			std::string pathDir = "Data/";
			pathDir += projName;

			PX2_APP.LoadProject(projName);
			PX2_APP.Play(Application::PT_PLAY);
		}
	}
	else if (CMD_LoadProject == cmdStr)
	{
		std::string projName = paramStr0;
		if (!projName.empty())
		{
			PX2_APP.CloseProject();
			PX2_APP.LoadProject(projName);
			PX2_APP.Play(Application::PT_PLAY);
		}
	}
	else if (CMD_CloseProject == cmdStr)
	{
		PX2_APP.CloseProject();
	}
	else if ("getcameraview" == cmdStr)
	{
		fromIP = fromip;
		fromPort = EngineUDPPortClient;

		PX2_HARDCAMERA.OpenCamera(1);
		PX2_HARDCAMERA.AddHardCameraCallback(_HardCameraCallback);
	}
}
//----------------------------------------------------------------------------