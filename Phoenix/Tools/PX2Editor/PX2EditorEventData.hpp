// PX2EditorEventData.hpp

#ifndef PX2EDITOREVENTDATA_HPP
#define PX2EDITOREVENTDATA_HPP

#include "PX2EditorPre.hpp"

namespace PX2
{

	class PX2_EDITOR_ITEM AddToolBarData
	{
	public:
		AddToolBarData();
		~AddToolBarData();

		enum Type
		{
			T_TOOL,
			T_CHOOSE,
			T_SPEARATER,
			T_STRETCH,
			T_MAXTYPE
		};

		Type TheType;
		std::string Where;
		std::string Icon;
		std::string Script;
		std::string HelpStr;
		int DataType;
		std::vector<std::string> Chooses;
	};
	
}

#endif