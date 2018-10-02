// PX2BBlockEvents.hpp

#ifndef PX2BBLOCKEVENTS_HPP
#define PX2BBLOCKEVENTS_HPP

#include "PX2EventSystem.hpp"
#include "PX2BBlockPre.hpp"

namespace PX2
{

	PX2_DECLARE_EVENT_BEGIN(PX2_ENGINE_ITEM BBlockES)
	PX2_EVENT(ShowCreateVaiableFrame)
	PX2_EVENT(RefreshBlockCata)
	PX2_EVENT(CopyedBlock)
	PX2_EVENT(SetDragingBBlock)
	PX2_EVENT(SetSelectBBlockEditor)
	PX2_EVENT(ShowBlockCata)
	PX2_EVENT(RefreshParamObject)
	PX2_EVENT(CreateVariable)
	PX2_EVENT(DeleteVariable)
	PX2_EVENT(SelectSprite)
	PX2_EVENT(Run)
	PX2_EVENT(ShowStage)
	PX2_EVENT(ShowCodeView)
	PX2_EVENT(NewingProject)
	PX2_EVENT(OpenProject)
	PX2_EVENT(CloseProject)
	PX2_EVENT(PlayCamOK)
	PX2_DECLARE_EVENT_END(BBlockES)

	class BBlock;

	struct PX2_ENGINE_ITEM CopyedBlockData
	{
		CopyedBlockData();
		~CopyedBlockData();

		BBlock *From;
		BBlock *TheBlock;
	};

}

#endif