// PX2EU_CanvasStageSimu.hpp

#ifndef PX2EU_CANVASSTAGESIMU_HPP
#define PX2EU_CANVASSTAGESIMU_HPP

#include "PX2EditorPre.hpp"
#include "PX2Canvas.hpp"
#include "PX2UISizeExtendControl.hpp"

namespace PX2
{

	class PX2_EDITOR_ITEM EU_CanvasStageSimu : public Canvas
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_STREAM(EU_CanvasStageSimu);

	public:
		EU_CanvasStageSimu();
		virtual ~EU_CanvasStageSimu();

		virtual void SetActivate(bool act);

		virtual void OnLeftDown(const APoint &sceenPos, const APoint &logicPos);
		virtual void OnLeftUp(const APoint &sceenPos, const APoint &logicPos);
		virtual void OnLeftDClick(const APoint &sceenPos, const APoint &logicPos);
		virtual void OnMiddleDown(const APoint &sceenPos, const APoint &logicPos);
		virtual void OnMiddleUp(const APoint &sceenPos, const APoint &logicPos);
		virtual void OnMouseWheel(const APoint &sceenPos, const APoint &logicPos, float delta);
		virtual void OnRightDown(const APoint &sceenPos, const APoint &logicPos);
		virtual void OnRightUp(const APoint &sceenPos, const APoint &logicPos);
		virtual void OnMotion(const APoint &sceenPos, const APoint &logicPos);

	protected:
		virtual void UpdateWorldData(double applicationTime, 
			double elapsedTime);
	};

	PX2_REGISTER_STREAM(EU_CanvasStageSimu);
	typedef Pointer0<EU_CanvasStageSimu> EU_CanvasStageSimuPtr;

}

#endif