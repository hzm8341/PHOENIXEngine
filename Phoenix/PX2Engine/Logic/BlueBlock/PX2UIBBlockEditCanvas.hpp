// PX2UIBBlockEditCanvas.hpp

#ifndef PX2UIBBLOCKEDITCANVAS_HPP
#define PX2UIBBLOCKEDITCANVAS_HPP

#include "PX2BBlockPre.hpp"
#include "PX2Canvas.hpp"
#include "PX2Singleton_NeedNew.hpp"
#include "PX2UIFrame.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM UIBBlockEditCanvas : public Canvas
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(UIBBlockEditCanvas);

	public:
		UIBBlockEditCanvas();
		virtual ~UIBBlockEditCanvas();

		UIFrame *GetPlaygroundBlocks();
		const Sizef &GetPlaygourndSize();

		// callbacks - general use for editor
	public:
		virtual void OnMotion(const PickInputData &data);
		virtual void OnLeftUp(const PickInputData &data);
		virtual void OnMiddleUp(const PickInputData &data);
		virtual void OnRightUp(const PickInputData &data);

	protected:
		virtual void UpdateWorldData(double applicationTime, double elapsedTime);
		virtual void OnSizeChanged();
		void _InitUpdateCamera();
		void _UpdateCameraScale(float &moveScale, int &recoverType);
		bool _CheckCamPos();
		APoint _CalPickPos(const APoint &worldPos);

		Sizef mPlaygourndSize;
		float mHeightOverWidth;
		UIFramePtr mEditPlayground;
		UIFramePtr mEditPlaygroundBlocks;
		bool mIsInitUpdateCamera;
		float mCamDragMaxDistance;
		float mMoveScale;
		int mScaleRecoverType;
		bool mIsDoScaleRecover;
	};

	PX2_REGISTER_STREAM(UIBBlockEditCanvas);
	typedef Pointer0<UIBBlockEditCanvas> BUIBlockEditCanvasPtr;

}

#endif