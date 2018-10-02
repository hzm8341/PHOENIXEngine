// PX2UIBBlockEditToolFrame.hpp

#ifndef PX2UIBBLOCKEDITTOOLFRAME_HPP
#define PX2UIBBLOCKEDITTOOLFRAME_HPP

#include "PX2BBlockPre.hpp"
#include "PX2UIFrame.hpp"
#include "PX2UIFText.hpp"
#include "PX2UIButton.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM UIBBlockEditToolFrame: public UIFrame
	{
		PX2_DECLARE_RTTI;
		PX2_NEW(UIBBlockEditToolFrame);
		PX2_DECLARE_STREAM(UIBBlockEditToolFrame);

	public:
		UIBBlockEditToolFrame();
		virtual ~UIBBlockEditToolFrame();

		virtual void OnEvent(Event *ent);

		UIButton *GetButtonRecycle();

		enum ShowType
		{
			ST_NORMAL,
			ST_RECYCLE,
			ST_RECYCLEDISABLE,
			ST_MAX_TYPE
		};
		void SetShowType(ShowType st);
		ShowType GetShowType() const;

	protected:
		void _UIButCallback(UIFrame *frame, UICallType type);

		UIButtonPtr mButCode;
		UIButtonPtr mButClone;
		UIButtonPtr mButUnDo;
		UIButtonPtr mButReDo;
		UIButtonPtr mButRecycle;

		ShowType mShowType;
	};

	PX2_REGISTER_STREAM(UIBBlockEditToolFrame);
	typedef Pointer0<UIBBlockEditToolFrame> BUIProgramToolFramePtr;

}

#endif