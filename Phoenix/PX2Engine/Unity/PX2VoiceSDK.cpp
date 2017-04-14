// PX2VoiceSDK.cpp

#include "PX2VoiceSDK.hpp"
#include "PX2Log.hpp"
#include "PX2VoiceEventType.hpp"
#if defined (__ANDROID__)
#include "AppPlayJNI.hpp"
#endif
using namespace PX2;


//----------------------------------------------------------------------------
VoiceSDK::VoiceSDK()
{
}
//----------------------------------------------------------------------------
VoiceSDK::~VoiceSDK()
{
}
//----------------------------------------------------------------------------
void VoiceSDK::SetVoiceSDK(const std::string &thirdname)
{
	mVoiceSDK = thirdname;
}
//----------------------------------------------------------------------------
const std::string &VoiceSDK::GetVoiceSDK() const
{
	return mVoiceSDK;
}
//----------------------------------------------------------------------------
void VoiceSDK::StartVoiceListening()
{
#ifdef __ANDROID__
	VoiceStartVoiceListening();
#endif
}
//----------------------------------------------------------------------------
void VoiceSDK::EndVoiceListening()
{
#ifdef __ANDROID__
	VoiceEndVoiceListening();
#endif
}
//----------------------------------------------------------------------------
void VoiceSDK::OnVoiceRecognizeResults(const std::string &strRet,
	const std::string &strJSON)
{
	VoiceData vData;
	vData.StrRet = strRet;
	vData.StrJSON = strJSON;

	Event *ent = VoiceSDKSpace::CreateEventX(VoiceSDKSpace::Results);
	ent->SetData<VoiceData>(vData);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void VoiceSDK::Speak(const std::string &text)
{
	PX2_UNUSED(text);

#ifdef __ANDROID__
	VoiceSpeak(text.c_str());
#endif
}
//----------------------------------------------------------------------------