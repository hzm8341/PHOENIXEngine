// PX2EU_ResGridFrame.hpp

#ifndef PX2EU_RESGRIDFRAME_HPP
#define PX2EU_RESGRIDFRAME_HPP

#include "PX2EditorPre.hpp"
#include "PX2UIGridFrame.hpp"

namespace PX2
{

	class PX2_EDITOR_ITEM EU_ResGridFrame : public UIGridFrame
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_STREAM(EU_ResGridFrame);
		PX2_NEW(EU_ResGridFrame);

	public:
		EU_ResGridFrame();
		virtual ~EU_ResGridFrame();

		void OnEvent(Event *event);

	protected:
		void RefreshItems(const std::string &path, int flag);
		void _RefreshGridItems();

		std::string mSelectPath;
	};

	PX2_REGISTER_STREAM(EU_ResGridFrame);
	typedef Pointer0<EU_ResGridFrame> EU_GridFramePtr;

}

#endif