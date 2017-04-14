// PX2UIVLCMemObj.hpp

#ifndef PX2UIVLCMEMOBJ_HPP
#define PX2UIVLCMEMOBJ_HPP

#include "PX2UIFrame.hpp"
#include "PX2VLC.hpp"
#include "PX2VLCMem.hpp"
#include "PX2ScopedCS.hpp"

#if defined PX2_USE_VLC

namespace PX2
{

	class PX2_ENGINE_ITEM VLCMemObj : public VLCMem
	{
	public:
		VLCMemObj();
		virtual ~VLCMemObj();

		virtual void OnFormatSetup();
		virtual void OnFrameReady(const std::vector<char>* frameBuf);
		virtual void OnFrameCleanUp();

		void SetTextureUpdated(bool updated);
		bool IsTextureUpdated() const;
		Texture2D *GetTex2D();

	protected:
		Texture2DPtr mTex2D;
		Mutex mMutex;
		bool mIsTextureUpdated;
	};
	typedef Pointer0<VLCMemObj> VLCMemObjPtr;

}

#endif

#endif