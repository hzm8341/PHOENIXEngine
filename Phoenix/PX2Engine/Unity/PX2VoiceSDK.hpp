// PX2VoiceSDK.hpp

#ifndef PX2VOICESDK_HPP
#define PX2VOICESDK_HPP

#include "PX2CorePre.hpp"
#include "PX2Singleton.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM VoiceSDK
	{
		PX2_SINGLETION(VoiceSDK);

	public:
		void SetVoiceSDK(const std::string &thirdname);
		const std::string &GetVoiceSDK() const;

		void StartVoiceListening();
		void EndVoiceListening();

		void OnVoiceRecognizeResults(const std::string &strRet, 
			const std::string &strJSON);

		void Speak(const std::string &text);

	private:
		std::string mVoiceSDK;
	};

#define PX2_VOICESDK VoiceSDK::GetSingleton()

}

#endif