// PX2UIBBlockEditCanvas.cpp

#include "PX2UIBBlockEditCanvas.hpp"
#include "PX2GraphicsRoot.hpp"
#include "PX2InputEventData.hpp"
#include "PX2EngineCanvas.hpp"
#include "PX2BBManager.hpp"
#include "PX2LogicES.hpp"
#include "PX2LogicManager.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Canvas, UIBBlockEditCanvas);
PX2_IMPLEMENT_STREAM(UIBBlockEditCanvas);
PX2_IMPLEMENT_FACTORY(UIBBlockEditCanvas);
PX2_IMPLEMENT_DEFAULT_NAMES(Canvas, UIBBlockEditCanvas);

//----------------------------------------------------------------------------
UIBBlockEditCanvas::UIBBlockEditCanvas() :
mIsInitUpdateCamera(true),
mMoveScale(1.0f),
mScaleRecoverType(0),
mIsDoScaleRecover(false)
{
	SetName("UIBBlockEditCanvas");

	CreateUICameraNode();
	EnableUICameraAutoAdjust(false);

	SetClearFlag(true, true, true);
	SetClearColor(Float4::MakeColor(50, 50, 50, 50));

	SetChildPickOnlyInSizeRange(false);
	SetChildNotPickRecursion(false);

	mPlaygourndSize.Width = 1024.0f;
	mPlaygourndSize.Height = 1024.0f * mHeightOverWidth;
	mHeightOverWidth = 3.0f;
	mEditPlayground = new0 UIFrame();
	AttachChild(mEditPlayground);
	mEditPlayground->SetAnchorHor(0.0f, 1.0f);
	mEditPlayground->SetSize(mPlaygourndSize);

	UIPicBox *picBox = mEditPlayground->CreateAddBackgroundPicBox();
	picBox->SetTexture("Data/BlueBlock/images/background.png");
	picBox->SetUVRepeat(Float2(4.0f, 4.0f*mHeightOverWidth));
	picBox->SetBrightness(0.8f);

	mEditPlaygroundBlocks = new0 UIFrame();
	mEditPlayground->AttachChild(mEditPlaygroundBlocks);
	mEditPlaygroundBlocks->LocalTransform.SetTranslateY(-1.0f);
	mEditPlaygroundBlocks->SetAnchorHor(0.0f, 1.0f);
	mEditPlaygroundBlocks->SetAnchorVer(0.0f, 1.0f);

	mCamDragMaxDistance = 200.0f;

	ComeInEventWorld();
	SetChildNotPickRecursion(false);
}
//----------------------------------------------------------------------------
UIBBlockEditCanvas::~UIBBlockEditCanvas()
{
}
//----------------------------------------------------------------------------
UIFrame *UIBBlockEditCanvas::GetPlaygroundBlocks()
{
	return mEditPlaygroundBlocks;
}
//----------------------------------------------------------------------------
const Sizef &UIBBlockEditCanvas::GetPlaygourndSize()
{
	return mPlaygourndSize;
}
//----------------------------------------------------------------------------
void UIBBlockEditCanvas::OnSizeChanged()
{
	Canvas::OnSizeChanged();

	mPlaygourndSize.Width = GetWidth();
	mPlaygourndSize.Height = mPlaygourndSize.Width * mHeightOverWidth;
	mEditPlayground->SetSize(mPlaygourndSize);

	_InitUpdateCamera();
}
//----------------------------------------------------------------------------
void UIBBlockEditCanvas::_InitUpdateCamera()
{
	float helfWidth = mSize.Width / 2.0f;
	float helfHeight = mSize.Height / 2.0f;
	GetUICameraNode()->GetCamera()->SetFrustum(0.1f, Mathf::FAbs(msUICameraY) + 100.0f,
		-helfHeight, helfHeight, -helfWidth, helfWidth);

	float playUp = mPlaygourndSize.Height * 0.5f;

	GetUICameraNode()->LocalTransform.SetTranslateXZ(0.0f, 
		playUp - helfHeight);

	mIsInitUpdateCamera = false;
}
//----------------------------------------------------------------------------
void UIBBlockEditCanvas::OnMotion(const PickInputData &data)
{
	Canvas::OnMotion(data);

	EngineUICanvas *euc = EngineUICanvas::GetSingletonPtr();
	Movable *topestMov = euc->GetTopestMovable();
	if (topestMov) return;

	if (mIsPressed)
	{
		mIsDoScaleRecover = false;

		BBlock *pressingUIBlock = PX2_BBM.GetEditorPressingBBlock();
		BBlock *dragingUIBlock = PX2_BBM.GetDragingBBlock();
		if (!pressingUIBlock && !dragingUIBlock)
		{
			_UpdateCameraScale(mMoveScale, mScaleRecoverType);

			APoint beforePos = GetUICameraNode()->LocalTransform.GetTranslate();
			APoint pos = beforePos;
			const AVector &moveDelta = mMoveDelta;
			pos.Z() -= moveDelta.Z() * mMoveScale;
			GetUICameraNode()->LocalTransform.SetTranslate(pos);
		}
	}
}
//----------------------------------------------------------------------------
void UIBBlockEditCanvas::UpdateWorldData(double applicationTime, 
	double elapsedTime)
{
	Canvas::UpdateWorldData(applicationTime, elapsedTime);

	if (mIsDoScaleRecover)
	{
		APoint pos = GetUICameraNode()->LocalTransform.GetTranslate();

		float scale = 0.0f;
		int recoverType = 0;
		_UpdateCameraScale(scale, recoverType);
		if (scale > 0.7f)
			scale = 0.7f;

		float dragSpeed = 4000.0f * (1.0f - scale) * (1.0f - scale);

		if (1 == recoverType)
		{
			pos.Z() += dragSpeed * (float)elapsedTime;
		}
		else if (2 == recoverType)
		{
			pos.Z() -= dragSpeed * (float)elapsedTime;
		}
		else
		{
			mIsDoScaleRecover = false;
		}

		GetUICameraNode()->LocalTransform.SetTranslate(pos);
	}
}
//----------------------------------------------------------------------------
void UIBBlockEditCanvas::OnLeftUp(const PickInputData &data)
{
	Canvas::OnLeftUp(data);

	if (mMoveScale < 1.0f)
	{
		mMoveScale = 1.0f;
		mIsDoScaleRecover = true;
	}
}
//----------------------------------------------------------------------------
void UIBBlockEditCanvas::OnMiddleUp(const PickInputData &data)
{
	Canvas::OnMiddleUp(data);

	if (mMoveScale < 1.0f)
	{
		mMoveScale = 1.0f;
		mIsDoScaleRecover = true;
	}
}
//----------------------------------------------------------------------------
void UIBBlockEditCanvas::OnRightUp(const PickInputData &data)
{
	Canvas::OnRightUp(data);

	if (mMoveScale < 1.0f)
	{
		mMoveScale = 1.0f;
		mIsDoScaleRecover = true;
	}
}
//----------------------------------------------------------------------------
void UIBBlockEditCanvas::_UpdateCameraScale(float &moveScale,
	int &recoverType)
{
	float rMin = 0.0f;
	float rMax = 0.0f;
	float uMin = 0.0f;
	float uMax = 0.0f;
	float dMin = 0.0f;
	float dMax = 0.0f;
	GetUICameraNode()->GetCamera()->GetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);
	APoint camPos = GetUICameraNode()->LocalTransform.GetTranslate();
	float camDown = camPos.Z() - uMax;
	float camUp = camPos.Z() + uMax;

	float playgroundDown = -mPlaygourndSize.Height * 0.5f;
	float playgroundUp = mPlaygourndSize.Height * 0.5f;

	if (camDown >= playgroundDown && camUp <= playgroundUp)
	{
		moveScale = 1.0f;
		recoverType = 0;
	}
	else if (camDown < playgroundDown)
	{
		float dist = playgroundDown - camDown;
		float leftDist = mCamDragMaxDistance - dist;
		if (leftDist < 0.01f)
			leftDist = 0.01f;
		moveScale = leftDist / mCamDragMaxDistance;
		recoverType = 1;
	}
	else if (camUp > playgroundUp)
	{
		float dist = camUp - playgroundUp;
		float leftDist = mCamDragMaxDistance - dist;
		if (leftDist < 0.01f)
			leftDist = 0.01f;
		moveScale = leftDist / mCamDragMaxDistance;
		recoverType = 2;
	}
}
//----------------------------------------------------------------------------
bool UIBBlockEditCanvas::_CheckCamPos()
{
	float rMin = 0.0f;
	float rMax = 0.0f;
	float uMin = 0.0f;
	float uMax = 0.0f;
	float dMin = 0.0f;
	float dMax = 0.0f;
	GetUICameraNode()->GetCamera()->GetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);
	APoint camPos = GetUICameraNode()->LocalTransform.GetTranslate();
	float canvasLeft = camPos.X() - rMax;
	float canvasRight = camPos.X() + rMax;
	float canvasDown = camPos.Z() - uMax;
	float canvasUp = camPos.Z() + uMax;

	float playLeft = -mPlaygourndSize.Width * 0.5f;
	float playRight = mPlaygourndSize.Width * 0.5f;
	float playDown = -mPlaygourndSize.Height * 0.5f;
	float playUp = mPlaygourndSize.Height * 0.5f;

	if (canvasLeft + mCamDragMaxDistance >= playLeft &&
		canvasRight - mCamDragMaxDistance <= playRight &&
		canvasDown + mCamDragMaxDistance >= playDown &&
		canvasUp - mCamDragMaxDistance <= playUp)
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
APoint UIBBlockEditCanvas::_CalPickPos(const APoint &worldPos)
{
	float rMin = 0.0f;
	float rMax = 0.0f;
	float uMin = 0.0f;
	float uMax = 0.0f;
	float dMin = 0.0f;
	float dMax = 0.0f;
	GetUICameraNode()->GetCamera()->GetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);
	float camWidth = rMax - rMin;
	float camHeight = uMax - uMin;
	PX2_UNUSED(camWidth);
	PX2_UNUSED(camHeight);

	const Sizef &size = GetSize();
	float xPercent = worldPos.X() / size.Width;
	float zPercent = worldPos.Z() / size.Height;
	float distX = (xPercent - 0.5f) * rMax * 2.0f;
	float distZ = (zPercent - 0.5f) * uMax * 2.0f;
	const APoint &camPos = GetUICameraNode()->WorldTransform.GetTranslate();
	APoint pickPos = APoint(camPos.X() + distX, worldPos.Y(), camPos.Z() + distZ);

	return pickPos;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// UIBBlockEditCanvas
//----------------------------------------------------------------------------
UIBBlockEditCanvas::UIBBlockEditCanvas(LoadConstructor value) :
Canvas(value)
{
}
//----------------------------------------------------------------------------
void UIBBlockEditCanvas::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Canvas::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(UIBBlockEditCanvas, source);
}
//----------------------------------------------------------------------------
void UIBBlockEditCanvas::Link(InStream& source)
{
	Canvas::Link(source);
}
//----------------------------------------------------------------------------
void UIBBlockEditCanvas::PostLink()
{
	Canvas::PostLink();
}
//----------------------------------------------------------------------------
bool UIBBlockEditCanvas::Register(OutStream& target) const
{
	if (Canvas::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void UIBBlockEditCanvas::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Canvas::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(UIBBlockEditCanvas, target);
}
//----------------------------------------------------------------------------
int UIBBlockEditCanvas::GetStreamingSize(Stream &stream) const
{
	int size = Canvas::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------