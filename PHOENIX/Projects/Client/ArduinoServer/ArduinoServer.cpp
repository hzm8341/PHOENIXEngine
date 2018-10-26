// LRMain.cpp

#include "PX2Net.hpp"
#include "PX2Core.hpp"
#include "PX2Mathematics.hpp"
#include "PX2Application.hpp"
#include "PX2Log.hpp"
using namespace PX2;

int main()
{
	Application *app = new Application();

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

		while (!app->IsQuit())
		{
			app->Update();

		}
		app->Terminate();
	}

	delete(app);

	return 0;
}