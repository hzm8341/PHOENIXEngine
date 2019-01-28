// PX2BBlock.hpp

#ifndef PX2BBLOCK_HPP
#define PX2BBLOCK_HPP

#include "PX2BBlockPre.hpp"
#include "PX2LogicPre.hpp"
#include "PX2UIFrame.hpp"
#include "PX2LBlock.hpp"
#include "PX2UIFText.hpp"
#include "PX2BBlockConnector.hpp"
#include "PX2UIEditBox.hpp"
#include "PX2UIComboBox.hpp"

namespace PX2
{

	class BBlockConnector;

	class PX2_ENGINE_ITEM ConnectUIObj
	{
	public:
		ConnectUIObj();
		~ConnectUIObj();

		UIFTextPtr mNameText;
	};
	typedef Pointer0<ConnectUIObj> ConnectUIObjPtr;

	class PX2_ENGINE_ITEM BBlock : public UIFrame
	{
		PX2_DECLARE_RTTI;
		PX2_NEW(BBlock);
		PX2_DECLARE_STREAM(BBlock);

	public:
		BBlock();
		virtual ~BBlock();

		enum BlockState 
		{
			BS_NORMAL,
			BS_PRESSED,
			BS_MAX_STEATE
		};
		void SetState(BlockState state);
		BlockState GetState() const;

		bool IsAttachedToBlockConnector();
		bool IsCanBeDragingDetached();

		virtual void OnPivotChanged();

		enum EditState
		{
			ES_INIT,
			ES_PRE_EDITOR,
			ES_EDITOR
		};
		void SetEditState(EditState state);
		EditState GetEditState() const;

		void SetDraging(bool draging);

		BBlock *CopyAll(EditState editState);

		void SetLBlock(LBlock *block);
		void ResetBlock();
		LBlock *GetLBlock();
		float GetBlockHeightWithNext();

		void OnSelect(bool select);

		void SetPickingOffset(const Float2 &offset);
		const Float2 &GetPickingOffset() const;

		enum ShapeType
		{
			ST_EVENT,
			ST_FUN,
			ST_FUN_OUTPUT,
			ST_FUN_OPERATOR,
			ST_PARAM,
			ST_IF,
			ST_IFELSE,
			ST_WHILE,
			ST_PROGRAM,
			ST_PROGRAMSTART,
			ST_PROGRAMFIXUPDATE,
			ST_COROUTINE,
			BST_MAX_TYPE
		};
		void SetShapeType(ShapeType st);
		ShapeType GetShapeType() const;

		void SetBoardColor(const Float4 &color);
		const Float4 &GetBoardColor() const;

		void SetBoardBrightness(float brightness);

		UIFPicBoxPtr mBackPic0;
		UIFPicBoxPtr mBackPic1;
		UIFPicBoxPtr mBackPic2;
		UIFPicBoxPtr mBackPic3;
		UIFPicBoxPtr mBackPicBoxVer;

		BBlockConnector *GetLastNextConnector();
		BBlockConnector *GetBlockConnectorByName(const std::string &name);
		BBlockConnector *GetCloestConnector(BBlock *block);

		std::vector<Pointer0<BBlockConnector> > &GetConnectors();

		UICheckButton *GetCheckButtonUseThisPointer();

		void SetDoReset();

		virtual void OnEvent(Event *ent);

	public_internal:
		void _ReGenLayOut();
		static void _SetFont(UIText *text);

	protected:
		virtual void UpdateWorldData(double applicationTime, double elapsedTime);
		static bool _IsTypeCanAdd(BBlock *block, BBlockConnector *connector);
		void _Init();
		void _GenLayout();
		void _GenBlockFun(float &outWidth, float &outHeight, bool isOutPut);
		void _GenBlockFunOperator(float &outWidth, float &outHeight);
		void _GenBlockParam(float &outWidth, float &outHeight);
		void _GenBlockCtrl(float &outWidth, float &outHeight, 
			const std::string &paramCnt, std::vector<std::string> &cnts);

		TriMesh *_GenTriMesh(const std::vector<Vector2f> &pos,
			const std::vector<int> tangles, bool isShadow);
		void _DetachConnector(const std::string &name);
		void _AddConnector(BBlockConnector *cnt);

		virtual void OnSizeNodeNotPicked(const CanvasInputData &inputData);
		virtual void OnWidgetPicked(const CanvasInputData &inputData);
		void _UICallback(UIFrame *frame, UICallType type);
		void _UpdateParamWidth();
		static BBlock *_CopyBlock(BBlock *block, EditState editState);

		bool mIsDoSetTexture;
		float mHeightInOutAdjust;

		BlockState mState;
		bool mIsPressedMoved;
		bool mIsSelected;

		Float4 mBoardColor;

		LBlockPtr mBlock;
		EditState mEditState;
		Float2 mPickingOffset;

		std::vector<Pointer0<BBlockConnector> > mConnectors;

		bool mIsNeedReGenBlock;

		ShapeType mShapeType;

		UIFTextPtr mBlockTextName;
		UIEditBoxPtr mParamEditBox;
		UIComboBoxPtr mParamComboBox;
		UIFPicBoxPtr mPic_Type;

		UICheckButtonPtr mCheck_UseThisPointer;
		bool mIsNeedReSet;

		bool mIsNeedUpdateWidth;
	};

#include "PX2BBlock.inl"
	PX2_REGISTER_STREAM(BBlock);
	typedef Pointer0<BBlock> BBlockPtr;

}

#endif