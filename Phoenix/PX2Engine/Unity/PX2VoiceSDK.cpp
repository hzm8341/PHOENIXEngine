// PX2VoiceSDK.cpp

#include "PX2VoiceSDK.hpp"
#include "PX2Log.hpp"
#include "PX2VoiceEventType.hpp"
#if defined (__ANDROID__)
#include "AppPlayJNI.hpp"
#endif
using namespace PX2;

//----------------------------------------------------------------------------
VoiceSDK::VoiceSDK() :
mIsAutoSpeakEnabled(false),
mIsAutoTTSSpeakEnabled(true)
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
void VoiceSDK::OnSpeakStart()
{
	Event *ent = PX2_CREATEEVENTEX(VoiceSDKSpace, SpeakStart);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void VoiceSDK::OnSpeakPause()
{
	Event *ent = PX2_CREATEEVENTEX(VoiceSDKSpace, SpeakPause);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void VoiceSDK::OnSpeakCancel()
{
	Event *ent = PX2_CREATEEVENTEX(VoiceSDKSpace, SpeakCancel);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void VoiceSDK::OnSpeakFinish()
{
	Event *ent = PX2_CREATEEVENTEX(VoiceSDKSpace, SpeakFinish);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void VoiceSDK::OnSpeakText(std::string &txt)
{
	Event *ent = PX2_CREATEEVENTEX(VoiceSDKSpace, SpeakText);
	ent->SetDataStr0(txt);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void VoiceSDK::OnVoiceRecordStart()
{
	Event *ent = PX2_CREATEEVENTEX(VoiceSDKSpace, RecordStart);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void VoiceSDK::OnVoiceRecordEnd()
{
	Event *ent = PX2_CREATEEVENTEX(VoiceSDKSpace, RecordEnd);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void VoiceSDK::OnVoiceRecognizeResults(const std::string &strRet,
	const std::string &strJSON)
{
	VoiceData vData;
	vData.StrRet = strRet;
	vData.StrJSON = strJSON;
	Event *ent = PX2_CREATEEVENTEX(VoiceSDKSpace, RecognizeResults);
	ent->SetDataStr0(strRet);
	ent->SetDataStr1(strJSON);
	ent->SetData<VoiceData>(vData);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void VoiceSDK::EnableAutoSpeak(bool isAutoSpeakEnable)
{
	mIsAutoSpeakEnabled = isAutoSpeakEnable;
	
#ifdef __ANDROID__
	VoiceEnableAutoSpeak(isAutoSpeakEnable);
#endif
}
//----------------------------------------------------------------------------
bool VoiceSDK::IsAutoSpeakEnabled() const
{
	return mIsAutoSpeakEnabled;
}
//----------------------------------------------------------------------------
void VoiceSDK::EnableAutoSpeakTTS(bool isAutoSpeakTTSEnable)
{
	mIsAutoTTSSpeakEnabled = isAutoSpeakTTSEnable;

#ifdef __ANDROID__
	VoiceEnableAutoSpeakTTS(isAutoSpeakTTSEnable);
#endif
}
//----------------------------------------------------------------------------
bool VoiceSDK::IsAutoSpeakTTSEnabled() const
{
	return mIsAutoTTSSpeakEnabled;
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