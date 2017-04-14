// PX2UIRound.hpp

#ifndef PX2UIROUND_HPP
#define PX2UIROUND_HPP

#include "PX2UIFrame.hpp"
#include "PX2UIFPicBox.hpp"
#include "PX2UIButton.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM UIRound : public UIFrame
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_FUNCTION;
		PX2_NEW(UIRound);
		PX2_DECLARE_STREAM(UIRound);

	public:
		UIRound();
		virtual ~UIRound();

		UIFPicBox *GetBack();
		UIButton *GetButton();

		void SetDragable(bool dragable);
		bool IsDragable() const;

		virtual void OnPressed();
		virtual void OnReleased();
		virtual void OnReleasedNotPick();
		virtual void OnDrag(const Vector2f &dir, float percent,
			const APoint &pickWorldPos);
		
		const Vector2f &GetDraggingDir() const;
		float GetDraggingPercent() const;
		const Vector2f &GetDraggedDir() const;
		float GetDraggedPercent() const;

		// none 0
		// top 1; bottom 2; left 3; right 4;
		int GetDragingDirSimple() const;

		const APoint &GetCurPickWorldPos() const;

		virtual void SetRangeAcceptFrame(UIFrame *frame);

		virtual void PreCanvasPick(const CanvasInputData &inputData, Canvas *canvas);
		virtual void OnSizeNodePicked(const CanvasInputData &inputData);

	protected:
		void _UIButCallback(UIFrame *frame, UICallType type);

		bool mIsDragable;

		UIFPicBoxPtr mBack;
		UIButtonPtr mBut;
		bool mIsPressed;
		Vector2f mDraggingDir;
		float mDraggingPercent;
		Vector2f mDraggedDir;
		float mDraggedPercent;
		APoint mCurPickWorldPos;
	};

#include "PX2UIRound.inl"
	PX2_REGISTER_STREAM(UIRound);
	typedef Pointer0<UIRound> UIRoundPtr;

}

#endif