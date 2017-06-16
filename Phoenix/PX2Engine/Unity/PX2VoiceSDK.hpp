// PX2VoiceSDK.hpp

#ifndef PX2VOICESDK_HPP
#define PX2VOICESDK_HPP

#include "PX2CorePre.hpp"
#include "PX2Singleton.hpp"
#include "PX2Singleton_NeedNew.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM VoiceSDK : public Singleton<VoiceSDK>
	{
	public:
		VoiceSDK();
		virtual ~VoiceSDK();

		void SetVoiceSDK(const std::string &thirdname);
		const std::string &GetVoiceSDK() const;

		void StartVoiceListening();
		void EndVoiceListening();

		void OnSpeakStart();
		void OnSpeakPause();
		void OnSpeakCancel();
		void OnSpeakFinish();

		void OnVoiceRecordStart();
		void OnVoiceRecordEnd();
		void OnVoiceRecognizeResults(const std::string &strRet, 
			const std::string &strJSON);

		void Speak(const std::string &text);

	private:
		std::string mVoiceSDK;
	};

#define PX2_VOICESDK VoiceSDK::GetSingleton()

}

#endif