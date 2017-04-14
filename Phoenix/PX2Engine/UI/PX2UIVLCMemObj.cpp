// PX2UIVLCMemObj.cpp

#include "PX2UIVLCMemObj.hpp"
#include "PX2Log.hpp"
using namespace PX2;

#if defined PX2_USE_VLC

//----------------------------------------------------------------------------
VLCMemObj::VLCMemObj() :
mTex2D(0),
mIsTextureUpdated(true)
{
}
//----------------------------------------------------------------------------
VLCMemObj::~VLCMemObj()
{
}
//----------------------------------------------------------------------------
void VLCMemObj::OnFormatSetup()
{
	if (mMediaWidth > 0 && mMediaHeight > 0)
	{
		mTex2D = new0 Texture2D(Texture::TF_A8R8G8B8, mMediaWidth, mMediaHeight, 1);
	}
	else
	{
		mTex2D = 0;
	}
}
//----------------------------------------------------------------------------
void VLCMemObj::OnFrameReady(const std::vector<char>* frameBuf)
{
	if (mMediaWidth > 0 && mMediaHeight > 0)
	{
		const std::vector<char> &fromBufs = *frameBuf;
		int width = mTex2D->GetWidth();
		int height = mTex2D->GetHeight();
		char* pDest = mTex2D->GetData(0);

		int offsetSrc = 0;
		int offsetDst = 0;

		for (int row = 0; row < width; ++row)
		{
			for (int col = 0; col < height; ++col)
			{
#if defined (__ANDROID__)
				pDest[offsetDst] = fromBufs[offsetSrc + 2];
				pDest[offsetDst + 1] = fromBufs[offsetSrc + 1];
				pDest[offsetDst + 2] = fromBufs[offsetSrc + 0];
				pDest[offsetDst + 3] = fromBufs[offsetSrc + 3];
#else
				pDest[offsetDst] = fromBufs[offsetSrc + 0];			// b
				pDest[offsetDst + 1] = fromBufs[offsetSrc + 1];		// g 
				pDest[offsetDst + 2] = fromBufs[offsetSrc + 2];		// r
				pDest[offsetDst + 3] = fromBufs[offsetSrc + 3];
#endif

				offsetSrc += 4;
				offsetDst += 4;
			}
		}
	}

	ScopedCS cs(&mMutex);
	{
		mIsTextureUpdated = true;
	}
}
//----------------------------------------------------------------------------
void VLCMemObj::OnFrameCleanUp()
{
}
//----------------------------------------------------------------------------
void VLCMemObj::SetTextureUpdated(bool updated)
{
	ScopedCS cs(&mMutex);
	mIsTextureUpdated = updated;
}
//----------------------------------------------------------------------------
bool VLCMemObj::IsTextureUpdated() const
{
	return mIsTextureUpdated;
}
//----------------------------------------------------------------------------
Texture2D *VLCMemObj::GetTex2D()
{
	return mTex2D;
}
//----------------------------------------------------------------------------

#endif