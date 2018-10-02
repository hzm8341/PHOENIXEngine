// PX2BBlockConnector.hpp

#ifndef PX2BBLOCKCONNECTOR_HPP
#define PX2BBLOCKCONNECTOR_HPP

#include "PX2BBlockPre.hpp"
#include "PX2LogicPre.hpp"
#include "PX2UIFrame.hpp"
#include "PX2UIFPicBox.hpp"
#include "PX2LParam.hpp"
#include "PX2LBlock.hpp"
#include "PX2UIFText.hpp"

namespace PX2
{

	class BBlock;

	class PX2_ENGINE_ITEM BBlockConnector : public UIFrame
	{
		PX2_DECLARE_RTTI;
		PX2_NEW(BBlockConnector);
		PX2_DECLARE_STREAM(BBlockConnector);

	public:
		enum ConnectorType
		{
			CT_PARAM,
			CT_BLOCK,
			CT_NEXT,
			CT_MAX_TYPE
		};

		BBlockConnector(LParam *lParam, ConnectorType type = CT_PARAM);
		virtual ~BBlockConnector();

		ConnectorType GetConnectorType() const;
		int GetNumChildUIBlock();

		UIFText *GetNameText();
		UIFrame *GetConnectRectFrame();

		void ShowHitPicBox(bool show);
		UIFPicBox *GetHitPicBox();

		BBlock *GetCurBlock();

		virtual int AttachChild(Movable* child);
		virtual int DetachChild(Movable* child);

		LParam *GetLParam();

	public_internal:
		float GetBlockAllWidth();
		float GetBlockAllHeight(int *numChildBlocks=0);

	protected:
		BBlockConnector();

		UIFPicBoxPtr mHitPicBox;
		UIFPicBoxPtr mBackPic;
		UIFTextPtr mNameText;
		ConnectorType mConnectorType;
		UIFramePtr mConnectRectFrame;
		LParamPtr mLParam;
	};

	PX2_REGISTER_STREAM(BBlockConnector);
	typedef Pointer0<BBlockConnector> BBlockConnectorPtr;

}

#endif