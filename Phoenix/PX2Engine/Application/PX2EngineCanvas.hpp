// PX2EngineUI.hpp

#ifndef PX2ENGINECANVAS_HPP
#define PX2ENGINECANVAS_HPP

#include "PX2Singleton_NeedNew.hpp"
#include "PX2EngineSceneCanvas.hpp"
#include "PX2EngineUICanvas.hpp"
#include "PX2UIFrame.hpp"
#include "PX2UIFText.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM EngineCanvas : public Canvas,
		public Singleton<EngineCanvas>
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(EngineCanvas);

	public:
		EngineCanvas();
		virtual ~EngineCanvas();
		
		virtual void OnEvent(Event *event);

	protected:
		virtual void UpdateLayout(Movable *parent);
		virtual void UpdateWorldData(double applicationTime,
			double elapsedTime);
		void _CalSize(const Sizef &projSize);

		EngineSceneCanvasPtr mEngineSceneCanvas;
		EngineUICanvasPtr mEngineUICanvas;

		UIFramePtr mInfoFrame;
		UIFTextPtr mInfoText;

		int mFPS;
		int mFPSUpdate;
		float mFPSUpdateTime;
	};
	PX2_REGISTER_STREAM(EngineCanvas);
	typedef Pointer0<EngineCanvas> EngineCanvasPtr;

}

#endif