// SCA_Manage.cpp

#include "SCA_Manager.hpp"
#include "PX2ProjectEvent.hpp"
#include "CSA_HandlerFactory.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
SCA_Man::SCA_Man()
{
}
//----------------------------------------------------------------------------
SCA_Man::~SCA_Man()
{
}
//----------------------------------------------------------------------------
void SCA_Man::Initlize()
{
	PX2_EW.ComeIn(this);

	ServerSocket socket(8387);
	HTTPServerParamsPtr pParams = new0 HTTPServerParams();
	pParams->SetMaxQueued(50);
	pParams->SetMaxThreads(4);
	mHttpServer = new0 HTTPServer(new0 HandlerFactory(), socket, pParams);
	mHttpServer->Start();
}
//----------------------------------------------------------------------------
void SCA_Man::Terminate()
{
	mHttpServer->Stop();
	mHttpServer = 0;

	PX2_EW.GoOut(this);
}
//----------------------------------------------------------------------------
void SCA_Man::Update()
{
}
//----------------------------------------------------------------------------
void SCA_Man::_Play()
{
	mIsPlaying = true;
}
//----------------------------------------------------------------------------
void SCA_Man::_Stop()
{
	mIsPlaying = false;
}
//----------------------------------------------------------------------------
void SCA_Man::OnEvent(Event *event)
{
	if (ProjectES::IsEqual(event, ProjectES::Play))
	{
		_Play();
	}
	else if (ProjectES::IsEqual(event, ProjectES::Stop))
	{
		_Stop();
	}

	PX2_UNUSED(event);
}
//----------------------------------------------------------------------------