// PX2AppBoostInfo.hpp

#ifndef PX2APPBOOSTINFO_HPP
#define PX2APPBOOSTINFO_HPP

#include "PX2CorePre.hpp"
#include "PX2Size.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM AppBoostInfo
	{
	public:
		AppBoostInfo();
		~AppBoostInfo();

		enum PlayLogicMode
		{
			PLM_SIMPLE,
			PLM_LOGIC,
			PLM_MAX_MODE
		};

		// general
		std::string ProjectName;
		std::vector<std::string> Plugins;

		// app
		Sizef BoostSize;
		PlayLogicMode ThePlayLogicMode;
		bool IsShowInfo;

		// server
		int Port;
		int NumMaxConnection;
	};

}

#endif