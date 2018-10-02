// PX2EU_StatusBar.hpp

#ifndef PX2EU_STATUSBAR_HPP
#define PX2EU_STATUSBAR_HPP

#include "PX2EditorPre.hpp"
#include "PX2UIFrame.hpp"
#include "PX2UIFText.hpp"

namespace PX2
{

	class PX2_EDITOR_ITEM EU_StatusBar : public UIFrame
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_STREAM(EU_StatusBar);

	public:
		EU_StatusBar();
		virtual ~EU_StatusBar();

	protected:
		virtual void UpdateWorldData(double applicationTime,
			double elapsedTime);
		void _UpdateCursorPos();

		UIFTextPtr mCursorPosText;
	};

	PX2_REGISTER_STREAM(EU_StatusBar);
	typedef Pointer0<EU_StatusBar> EU_StatusBarPtr;

}

#endif