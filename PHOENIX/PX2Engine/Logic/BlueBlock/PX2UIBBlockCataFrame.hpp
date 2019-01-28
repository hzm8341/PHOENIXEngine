// PX2UIBBlockCataFrame.hpp

#ifndef PX2UIBBLOCKCATAFRAME_HPP
#define PX2UIBBLOCKCATAFRAME_HPP

#include "PX2BBlockPre.hpp"
#include "PX2UIFrame.hpp"
#include "PX2UIButton.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM UIBBlockCataFrame : public UIFrame
	{
		PX2_DECLARE_RTTI;
		PX2_NEW(UIBBlockCataFrame);
		PX2_DECLARE_STREAM(UIBBlockCataFrame);

	public:
		UIBBlockCataFrame();
		virtual ~UIBBlockCataFrame();

		enum CataType
		{
			CT_NORMAL,
			CT_VER,
			CT_VER_BOTTOM,
			CT_MAX_TYPE
		};
		void SetCataType(CataType cataType);
		CataType GetCataType() const;

		void CreateCataButs();

		virtual void OnEvent(Event *ent);

		void _UICataButCallback(UIFrame *frame, UICallType type);

	protected:
		void _RefreshCata(bool isArduino);
		std::vector<UIButtonPtr> mUIButtons;

		CataType mCataType;
	};

	PX2_REGISTER_STREAM(UIBBlockCataFrame);
	typedef Pointer0<UIBBlockCataFrame> UIBBlockCataFramePtr;

}

#endif