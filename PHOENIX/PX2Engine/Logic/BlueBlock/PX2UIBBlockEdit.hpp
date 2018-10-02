// PX2UIBBlockEdit.hpp

#ifndef PX2UIBBLOCKSEDIT_HPP
#define PX2UIBBLOCKSEDIT_HPP

#include "PX2BBlockPre.hpp"
#include "PX2UIBBlockPanels.hpp"
#include "PX2BBlock.hpp"
#include "PX2UIBBlockEditToolFrame.hpp"
#include "PX2RUStateManager.hpp"
#include "PX2LFile.hpp"
#include "PX2UIBBlockEditCanvas.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM UIBBlockEdit : public UIFrame
	{
		PX2_DECLARE_RTTI;
		PX2_NEW(UIBBlockEdit);
		PX2_DECLARE_STREAM(UIBBlockEdit);

	public:
		UIBBlockEdit();
		virtual ~UIBBlockEdit();

		virtual void OnEvent(Event *ent);

	protected:
		BBlockConnector *_GetPickingConnector(BBlock *block);
		bool _IsOverRecycle(BBlock *block);
		virtual void OnSizeNodePicked(const CanvasInputData &inputData);

		void _UpdateUIDraing(const CanvasInputData &inputData);
		Float2 _GetDragingPos(const CanvasInputData &inputData);
		void _ShowOnClickUIBlock(bool show);
		void _RefreshFile(LFile *lFile);
		void _RefreshBlock(Node *parentNode, LBlock *lBlock);

		CanvasInputData mCurInputData;

		BUIBlockEditCanvasPtr mEditPlaygroundCanvas;

		TransStateObj mStartDragTransStateObj;
		Movable *mStartDragParent;
	};

	PX2_REGISTER_STREAM(UIBBlockEdit);
	typedef Pointer0<UIBBlockEdit> BUIBlockEditPtr;

}

#endif
