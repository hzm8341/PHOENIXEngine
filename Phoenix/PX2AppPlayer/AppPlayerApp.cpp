// AppPlayerApp.cpp

#include "AppPlayerApp.hpp"
#include "PX2Renderer.hpp"
#include "PX2Application.hpp"
#include "PX2ScriptManager.hpp"
using namespace PX2;

PX2_IMPLEMENT_APPLICATION(AppPlayerApp)
//----------------------------------------------------------------------------
AppPlayerApp::AppPlayerApp ()
{

}
//----------------------------------------------------------------------------
AppPlayerApp::~AppPlayerApp ()
{
	// 所有内存释放,必须在析构函数之前释放
}
//----------------------------------------------------------------------------
bool AppPlayerApp::Initlize()
{
	if (App::Initlize())
	{
		std::string projectName = PX2_APP.GetBoostProjectName();

		if (!mCmdProjectName.empty())
			projectName = mCmdProjectName;

		PX2_LOG_INFO("BoostProject Name %s", projectName.c_str());

		if (!projectName.empty())
		{
			std::string projectPath = "Data/" + projectName + "/" + projectName
				+ ".px2proj";

			// Load Project
			PX2_APP.LoadProject(projectPath);
		}

		PX2_APP.Play(Application::PT_PLAY);

		std::string titleProj = GetTitleProj(projectName);
		SetTitle(titleProj);

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
int main(int numArguments, char* arguments[]){	AppBase::msAppInitlizeFun();

	int exitCode = AppBase::msEntry(numArguments, arguments);

	AppBase::msAppTernamateFun();

	return exitCode;
}
//----------------------------------------------------------------------------