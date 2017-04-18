// PX2UIVlc.cpp

#include "PX2UIVlc.hpp"
#include "PX2Renderer.hpp"
#include "PX2Log.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIFrame, UIVlc);
PX2_IMPLEMENT_STREAM(UIVlc);
PX2_IMPLEMENT_FACTORY(UIVlc);

//----------------------------------------------------------------------------
UIVlc::UIVlc()
{
	mFPicBox = new0 UIFPicBox();
	AttachChild(mFPicBox);
	mFPicBox->LocalTransform.SetTranslateY(-1.0f);
	mFPicBox->SetAnchorHor(0.0f, 1.0f);
	mFPicBox->SetAnchorVer(0.0f, 1.0f);
	mFPicBox->GetUIPicBox()->SetTexture("Data/engine/white.png");

	mFPicBoxRight = new0 UIFPicBox();
	AttachChild(mFPicBoxRight);
	mFPicBoxRight->LocalTransform.SetTranslateY(-1.0f);
	mFPicBoxRight->GetUIPicBox()->SetTexture("Data/engine/white.png");
	mFPicBoxRight->Show(false);

#if defined PX2_USE_VLC
	mVLC = new0 VLC();
	mVLCMemObj = new0 VLCMemObj();
	mVLC->SetMem(mVLCMemObj);
#endif

	mMode = UIVlc::M_NORMAL;

	SetWidget(true);

	SetName("UIVlc");
}
//----------------------------------------------------------------------------
UIVlc::~UIVlc()
{
	mFPicBox->GetUIPicBox()->SetTexture(0);
	mFPicBoxRight->GetUIPicBox()->SetTexture(0);

#if defined PX2_USE_VLC
	mVLC = 0;
	mVLCMemObj = 0;
#endif
}
//----------------------------------------------------------------------------
void UIVlc::SetMode(Mode m)
{
	mMode = m;
	_UpdateOnMode(mMode);
}
//----------------------------------------------------------------------------
void UIVlc::StartVLC(const std::string &filename)
{
	PX2_UNUSED(filename);

#if defined PX2_USE_VLC
	if (mVLC)
	{
		mVLC->Start(filename);
	}
#endif
}
//----------------------------------------------------------------------------
void UIVlc::StopVLC()
{
#if defined PX2_USE_VLC
	if (mVLC)
	{
		mVLC->Stop();
	}
#endif
}
//----------------------------------------------------------------------------
UIVlc::Mode UIVlc::GetMode() const
{
	return mMode;
}
//----------------------------------------------------------------------------
void UIVlc::OnSizeChanged()
{
	UIFrame::OnSizeChanged();
}
//----------------------------------------------------------------------------
void UIVlc::_UpdateOnMode(Mode m)
{
	if (M_NORMAL == m)
	{
		mFPicBox->Show(true);
		mFPicBox->SetAnchorHor(0.0f, 1.0f);
		mFPicBox->SetAnchorVer(0.0f, 1.0f);
		mFPicBoxRight->Show(false);
	}
	else if (M_VR == m)
	{
		mFPicBox->Show(true);
		mFPicBox->SetAnchorHor(0.0f, 0.5f);
		mFPicBox->SetAnchorVer(0.0f, 1.0f);

		mFPicBoxRight->Show(true);
		mFPicBoxRight->SetAnchorHor(0.5f, 1.0f);
		mFPicBoxRight->SetAnchorVer(0.0f, 1.0f);
	}
}
//----------------------------------------------------------------------------
void UIVlc::UpdateWorldData(double applicationTime,
	double elapsedTime)
{
	UIFrame::UpdateWorldData(applicationTime, elapsedTime);

#if defined PX2_USE_VLC
	if (mVLCMemObj && mVLCMemObj->IsTextureUpdated())
	{
		Texture2D *tex2D = mVLCMemObj->GetTex2D();
		if (tex2D)
		{
			mFPicBox->GetUIPicBox()->SetTexture(tex2D);
			if (M_VR == mMode)
				mFPicBoxRight->GetUIPicBox()->SetTexture(tex2D);
			else
				mFPicBoxRight->GetUIPicBox()->SetTexture(0);

			Renderer::UpdateAll(tex2D, 0);
		}

		mVLCMemObj->SetTextureUpdated(false);
	}
#endif
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
UIVlc::UIVlc(LoadConstructor value) :
UIFrame(value)
{
}
//----------------------------------------------------------------------------
void UIVlc::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIFrame::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(UIVlc, source);
}
//----------------------------------------------------------------------------
void UIVlc::Link(InStream& source)
{
	UIFrame::Link(source);
}
//----------------------------------------------------------------------------
void UIVlc::PostLink()
{
	UIFrame::PostLink();
}
//----------------------------------------------------------------------------
bool UIVlc::Register(OutStream& target) const
{
	if (UIFrame::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void UIVlc::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIFrame::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(UIVlc, target);
}
//----------------------------------------------------------------------------
int UIVlc::GetStreamingSize(Stream &stream) const
{
	int size = UIFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------