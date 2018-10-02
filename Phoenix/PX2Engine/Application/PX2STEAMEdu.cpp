// PX2STEAMEdu.cpp

#include "PX2STEAMEdu.hpp"
#include "PX2FileIO.hpp"
#include "PX2ResourceManager.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
STEAMEduManager::STEAMEduManager()
{

}
//----------------------------------------------------------------------------
STEAMEduManager::~STEAMEduManager()
{

}
//----------------------------------------------------------------------------
void STEAMEduManager::Initlize()
{
	ServerSocket socket(8389);
	HTTPServerParams *param = new0 HTTPServerParams();
	param->SetMaxQueued(50);
	param->SetMaxThreads(1);

	mHttpServer = new0 HTTPServer(new0 STEAMEduHandlerFactory(), socket, param);
	mHttpServer->Start();
}
//----------------------------------------------------------------------------
void STEAMEduManager::Terminate()
{
	mHttpServer->Stop();
	mHttpServer = 0;
}
//----------------------------------------------------------------------------
void STEAMEduManager::Update()
{

}
//----------------------------------------------------------------------------
void STEAMEduManager::OpenArduino(const std::string &filename)
{
#if defined _WIN32 || defined (WIN32)
	std::string cmdStr = "arduino " + filename;
	WinExec(cmdStr.c_str(), SW_SHOW);
#endif
}
//----------------------------------------------------------------------------