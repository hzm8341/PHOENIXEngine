// PX2SPMain.cpp

#include "PX2Net.hpp"
#include "PX2Core.hpp"
#include "PX2Mathematics.hpp"
#include "PX2Application.hpp"
#include "PX2Log.hpp"
#include "PX2ServerInfoManager.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2StringTokenizer.hpp"
using namespace PX2;

Mutex sServerMutex;
bool isShutdownServer = false;

static std::string sCmdString;
static std::vector<std::string> sCmdParams;
static bool sIsHasInput = false;
static bool sIsDoQuit = false;
//----------------------------------------------------------------------------
void InputThreadProc(void* data)
{
	PX2_UNUSED(data);

	while (!sIsDoQuit)
	{
		if (!sIsHasInput)
		{
			std::cout << "please input your commond:\n";
			char buffer[256];
			std::cin.getline(buffer, 256);
			std::string cmdbuf(buffer);
			sCmdString = cmdbuf;
			sCmdParams.resize(0);

			ScopedCS cs(&sServerMutex);
			sIsHasInput = true;
		}
	}
}
//----------------------------------------------------------------------------
int _ProcessInputString(const std::string &buf)
{
	int ret = 0;
	std::string cmd;
	StringTokenizer tokenizer(buf, " ");
	int count = tokenizer.Count();
	if (count > 0)
	{
		cmd = tokenizer[0];

		if ("quit" == cmd && count == 1)
		{
			ret = 1;
		}
	}

	return ret;
}
//----------------------------------------------------------------------------
int main(int numArguments, char* arguments[])
{
	std::string cmdProjectName;
	if (numArguments > 1)
	{
		cmdProjectName = std::string(arguments[1]);
	}

	Application *app = new Application();
	app->SetBoostMode(Application::BM_SERVER);
	isShutdownServer = false;

	if (app->Initlize())
	{
		Logger *logger = Logger::GetSingletonPtr();
		logger->CloseLogger();

#if defined(_WIN32) || defined(WIN32) || defined(__LINUX__)
		logger->AddFileHandler("log_serverplayer.txt", LT_INFO | LT_ERROR | LT_USER);
#endif
		logger->AddOutputWindowHandler(LT_INFO | LT_ERROR | LT_USER);
		logger->AddConsoleHandler(LT_INFO | LT_ERROR | LT_USER);
		logger->SetLogFileInfo(false);
		logger->StartLogger();

		AppBoostInfo boostInfo = app->GetBoostServerInfo();
		std::string projName = boostInfo.ProjectName;
		if (!cmdProjectName.empty())
			projName = cmdProjectName;
		int port = boostInfo.Port;
		int numMaxConnection = boostInfo.NumMaxConnection;

		GeneralServer *gs = PX2_APP.CreateGeneralServer(port, numMaxConnection, 10);
		if (!gs->Start())
		{
			PX2_LOG_ERROR("GeneralServer start failed!");
			isShutdownServer = true;
		}

		std::string projectPath = "Data/" + projName + "/" + projName + ".px2proj";
		app->LoadProject(projectPath);
		app->Play(Application::PT_PLAY);

		PX2_LOG_INFO("ServerPlayer Start OK, Pojrect:%s", projName.c_str());

		ThreadPtr inputThread = new0 Thread();
		inputThread->Start(InputThreadProc);

		while (!isShutdownServer)
		{
			app->Update();

			if (sIsHasInput)
			{
				int ret = _ProcessInputString(sCmdString);
				if (0 == ret)
				{
					ScopedCS cs(&sServerMutex);
					sIsHasInput = false;
				}
				if (1 == ret)
				{
					sIsDoQuit = true;
					isShutdownServer = true;

					PX2_LOG_INFO("quit...");
				}
			}

			System::SleepSeconds(0.03f);
		}

		if (gs)
			gs->Shutdown();

		System::SleepSeconds(1.0f);

		inputThread = 0;

		PX2_LOG_INFO("ServerPlayer shutdown");

		app->Terminate();
	}

	delete(app);

	return 0;
}
//----------------------------------------------------------------------------