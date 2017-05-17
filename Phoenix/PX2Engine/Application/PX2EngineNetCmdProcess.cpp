// PX2EngineNetCmdProcess.cpp

#include "PX2EngineNetCmdProcess.hpp"
#include "PX2EngineCanvas.hpp"
#include "PX2StringHelp.hpp"
#include "PX2Project.hpp"
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
void EngineNetCmdProcess::OnCmd(const std::string &cmdStr,
	const std::string &paramStr0, const std::string &paramStr1)
{
	if ("pushproject" == cmdStr)
	{
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
	else if ("loadproject" == cmdStr)
	{
		std::string projName = paramStr0;
		if (!projName.empty())
		{
			PX2_APP.CloseProject();
			PX2_APP.LoadProject(projName);
			PX2_APP.Play(Application::PT_PLAY);
		}
	}
	else if ("closeproject" == cmdStr)
	{
		PX2_APP.CloseProject();
	}
}
//----------------------------------------------------------------------------