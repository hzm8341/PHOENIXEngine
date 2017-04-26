// PX2UIVlc.hpp

#ifndef PX2UIVLC_HPP
#define PX2UIVLC_HPP

#include "PX2UIFrame.hpp"
#include "PX2UIFPicBox.hpp"
#include "PX2VLC.hpp"
#include "PX2VLCMem.hpp"
#include "PX2UIVLCMemObj.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM UIVlc : public UIFrame
	{
		PX2_DECLARE_RTTI;
		PX2_NEW(UIVlc);
		PX2_DECLARE_STREAM(UIVlc);

	public:
		UIVlc();
		virtual ~UIVlc();

		enum Mode
		{
			M_NORMAL,
			M_VR,
			M_MAX_TYPE
		};
		void SetMode(Mode m);
		Mode GetMode() const;

		void StartVLC(const std::string &filename);
		void StopVLC();

#if defined PX2_USE_VLC
		VLC *GetVLC();
#endif

		virtual void OnSizeChanged();

	protected:
		void _UpdateOnMode(Mode m);
		virtual void UpdateWorldData(double applicationTime,
			double elapsedTime);

#if defined PX2_USE_VLC
		VLCPtr mVLC;
		VLCMemObjPtr mVLCMemObj;
#endif
		Mode mMode;
		UIFPicBoxPtr mFPicBox;
		UIFPicBoxPtr mFPicBoxRight;
		Texture2DPtr mTex2D;
	};

#include "PX2UIVlc.inl"
	PX2_REGISTER_STREAM(UIVlc);
	typedef Pointer0<UIVlc> UIVLCPtr;

}

#endif