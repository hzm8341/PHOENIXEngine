// PX2HardCamera.cpp

#include "PX2HardCamera.hpp"
#include "PX2StringTokenizer.hpp"
#include "PX2Log.hpp"

#if defined(__ANDROID__)
#include "AppPlayJNI.hpp"
#endif

using namespace PX2;

//----------------------------------------------------------------------------
HardCamera::HardCamera() :
mIsCameraOpened(false)
{
}
//----------------------------------------------------------------------------
HardCamera::~HardCamera()
{
}
//----------------------------------------------------------------------------
bool HardCamera::IsCameraOpened() const
{
	return mIsCameraOpened;
}
//----------------------------------------------------------------------------
void HardCamera::OpenCamera(int type)
{
#if defined(__ANDROID__)
	CameraOpenStream(type);
#endif

	mIsCameraOpened = true;
}
//----------------------------------------------------------------------------
void HardCamera::CloseCamera()
{
#if defined(__ANDROID__)
	CameraCloseStream();
#endif

	mIsCameraOpened = false;
}
//----------------------------------------------------------------------------
void HardCamera::OnSetCameraFrame(int width, int height, const char *data,
	int size)
{
	PX2_LOG_INFO("SetCameraFrame %d", size);
}
//----------------------------------------------------------------------------
bool HardCamera::AddHardCameraCallback(HardCameraCallback callback)
{
	if (IsHasHardCameraCallback(callback))
		return false;

	mCallbacks.push_back(callback);

	return false;
}
//----------------------------------------------------------------------------
bool HardCamera::IsHasHardCameraCallback(HardCameraCallback callback) const
{
	for (int i = 0; i < (int)mCallbacks.size(); i++)
	{
		if (callback == mCallbacks[i])
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void HardCamera::ClearHardCameraCallbacks()
{
	mCallbacks.clear();
}
//----------------------------------------------------------------------------