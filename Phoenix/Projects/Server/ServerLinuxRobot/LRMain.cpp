// LRMain.cpp

#include "PX2Net.hpp"
#include "PX2Core.hpp"
#include "PX2Mathematics.hpp"
#include "PX2Application.hpp"
#include "PX2Log.hpp"
#include "LRServer.hpp"
#include "PX2ServerInfoManager.hpp"
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
			std::cout << "please input your test commond :\n";
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

int main()
{
	Application *app = new Application();
	isShutdownServer = false;

	if (app->Initlize())
	{
		Logger *logger = Logger::GetSingletonPtr();
		logger->CloseLogger();

#if defined(_WIN32) || defined(WIN32) || defined(__LINUX__)
		logger->AddFileHandler("log_server.txt", LT_INFO | LT_ERROR | LT_USER);
#endif
		logger->AddOutputWindowHandler(LT_INFO | LT_ERROR | LT_USER);
		logger->AddConsoleHandler(LT_INFO | LT_ERROR | LT_USER);
		logger->SetLogFileInfo(false);
		logger->StartLogger();

		PX2_SVRINFOMAN.LoadServerInfo(LR_DATA + "net/config.xml");
		const ServerInfo *serverLRInfo = PX2_SVRINFOMAN.GetServerInfoByName("server_lr");
		if (!serverLRInfo) return false;

		int numMaxConnect = serverLRInfo->NumMaxConnect;
		LRServerPtr lrServer = new0 LRServer(Server::ST_POLL, serverLRInfo->Port,
			numMaxConnect, 10);
		if (!lrServer->Start())
			return false;

		std::string writeablePath = PX2_RM.GetWriteablePath();
		std::string slrPath = writeablePath + "slr/";
		if (!PX2_RM.IsFileFloderExist(slrPath))
		{
			PX2_RM.CreateFloder(writeablePath, "slr/");
		}

		std::string projName = "Block";
		std::string projectPath = "Data/" + projName + "/" + projName + ".px2proj";
		app->LoadProject(projectPath);

		PX2_LOG_INFO("ServerLinuxRobot Server Start OK!");

		ThreadPtr inputThread = new0 Thread();
		inputThread->Start(InputThreadProc);

		while (!isShutdownServer)
		{
			app->Update();
			lrServer->Run();

			if (sIsHasInput)
			{
				int ret = lrServer->OnProcessString(-1, sCmdString);
				if (0 == ret)
				{
					ScopedCS cs(&sServerMutex);
					sIsHasInput = false;
				}
				if (1 == ret)
				{
					sIsDoQuit = true;
					isShutdownServer = true;

					PX2_LOG_INFO("Quit");
				}
			}

			System::SleepSeconds(0.03f);
		}

		if (lrServer)
			lrServer->Shutdown();

		System::SleepSeconds(1.0f);

		lrServer = 0;
		inputThread = 0;

		PX2_LOG_INFO("ServerLinuxRobot Server shutdowning...");

		app->Terminate();
	}

	delete(app);

	return 0;
}