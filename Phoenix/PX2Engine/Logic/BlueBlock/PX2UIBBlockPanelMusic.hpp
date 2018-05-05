// PX2UIBBlockPanelMusic.hpp

#ifndef PX2UIBBLOCKPANELMUSIC_HPP
#define PX2UIBBLOCKPANELMUSIC_HPP

#include "PX2BBlockPre.hpp"
#include "PX2UIFrame.hpp"
#include "PX2UIButton.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM UIBBlockPanelMusic : public UIFrame
	{
		PX2_DECLARE_RTTI;
		PX2_NEW(UIBBlockPanelMusic);
		PX2_DECLARE_STREAM(UIBBlockPanelMusic);

	public:
		UIBBlockPanelMusic();
		virtual ~UIBBlockPanelMusic();

	protected:
		void _UIButCallback(UIFrame *frame, UICallType type);

		UIButtonPtr mButCreateParam;
	};

	PX2_REGISTER_STREAM(UIBBlockPanelMusic);
	typedef Pointer0<UIBBlockPanelMusic> UIBBlockPanelMusicPtr;

}

#endif