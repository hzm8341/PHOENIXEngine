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

		virtual void OnLeftDown(const PickInputData &data);
		virtual void OnLeftUp(const PickInputData &data);
		virtual void OnLeftDClick(const PickInputData &data);
		virtual void OnMiddleDown(const PickInputData &data);
		virtual void OnMiddleUp(const PickInputData &data);
		virtual void OnMouseWheel(const PickInputData &data);
		virtual void OnRightDown(const PickInputData &data);
		virtual void OnRightUp(const PickInputData &data);
		virtual void OnMotion(const PickInputData &data);

	protected:
		virtual void UpdateWorldData(double applicationTime, 
			double elapsedTime);
	};

	PX2_REGISTER_STREAM(EU_CanvasStageSimu);
	typedef Pointer0<EU_CanvasStageSimu> EU_CanvasStageSimuPtr;

}

#endif