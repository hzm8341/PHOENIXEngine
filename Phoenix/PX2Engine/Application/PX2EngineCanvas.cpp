// PX2EngineCanvas.cpp

#include "PX2EngineCanvas.hpp"
#include "PX2ProjectEvent.hpp"
#include "PX2Project.hpp"
#include "PX2GraphicsRoot.hpp"
#include "PX2UIFPicBox.hpp"
#include "PX2ProjectEvent.hpp"
#include "PX2ProjectEventController.hpp"
#include "PX2Application.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Canvas, EngineCanvas);
PX2_IMPLEMENT_STREAM(EngineCanvas);
PX2_IMPLEMENT_FACTORY(EngineCanvas);
PX2_IMPLEMENT_DEFAULT_NAMES(Canvas, EngineCanvas);

//----------------------------------------------------------------------------
EngineCanvas::EngineCanvas()
{
	CreateUICameraNode();

	SetClearFlag(true, true, true);
	SetClearColor(Float4::MakeColor(0, 0, 0, 255));

	EngineSceneCanvas *sceneCanvas = new0 EngineSceneCanvas();
	AttachChild(sceneCanvas);
	mEngineSceneCanvas = sceneCanvas;

	sceneCanvas->AttachController(new0 ProjectEventController());
	sceneCanvas->SetName("ProjectSceneCanvas");
	sceneCanvas->EnableAnchorLayout(true);
	sceneCanvas->SetAnchorHor(0.0f, 1.0f);
	sceneCanvas->SetAnchorVer(0.0f, 1.0f);
	sceneCanvas->SetClearFlag(true, true, true);
	sceneCanvas->SetClearColor(Float4::MakeColor(153, 217, 234, 255));
	sceneCanvas->SetRenderNodeUpdate(true);

	EngineUICanvas *uiCanvas = new0 EngineUICanvas();
	AttachChild(uiCanvas);
	mEngineUICanvas = uiCanvas;
	uiCanvas->SetUpdatePriority(10);
	uiCanvas->LocalTransform.SetTranslateY(-10.0f);
	uiCanvas->AttachController(new0 ProjectEventController());
	uiCanvas->SetName("ProjectUICanvas");
	uiCanvas->EnableAnchorLayout(true);
	uiCanvas->SetAnchorHor(0.0f, 1.0f);
	uiCanvas->SetAnchorVer(0.0f, 1.0f);
	uiCanvas->SetClearFlag(false, true, true);
	uiCanvas->SetRenderNodeUpdate(true);

	UIFramePtr frame = new0 UIFrame();
	AttachChild(frame);
	UIPicBox *backPic = frame->CreateAddBackgroundPicBox(true);
	backPic->SetAlpha(0.4f);
	frame->SetAnchorHor(0.0f, 1.0f);
	frame->SetAnchorVer(1.0f, 1.0f);
	frame->SetSize(0.0f, 24.0f);
	frame->SetPivot(0.5f, 1.0f);
	mInfoFrame = frame;
	mInfoFrame->LocalTransform.SetTranslateY(-50.0f);

	UIFTextPtr infoText = new0 UIFText();
	frame->AttachChild(infoText);
	infoText->SetAnchorHor(0.0f, 1.0f);
	infoText->SetAnchorVer(0.0f, 1.0f);
	infoText->SetPivot(0.5f, 0.5f);
	infoText->GetText()->SetText("FPS:0");
	infoText->GetText()->SetFontWidthHeight(16, 16);
	infoText->GetText()->SetAligns(TEXTALIGN_LEFT | TEXTALIGN_VCENTER);
	mInfoText = infoText;

	mFPS = 0;
	mFPSUpdate = 0;
	mFPSUpdateTime = 0.0f;

	SetName("EngineCanvas");

	EnableAnchorLayout(true);
	SetSize(400.0f, 400.0f);
	SetAnchorHor(0.5f, 0.5f);
	SetAnchorVer(0.5f, 0.5f);
	EnableScreenRectLayout(false);

	ComeInEventWorld();
}
//----------------------------------------------------------------------------
EngineCanvas::~EngineCanvas()
{
}
//----------------------------------------------------------------------------
void EngineCanvas::OnEvent(Event *event)
{
	if (ProjectES::IsEqual(event, ProjectES::NewProject) || 
		ProjectES::IsEqual(event, ProjectES::LoadedProject))
	{
		const Sizef &projSize = PX2_PROJ.GetSize();
		_CalSize(projSize);
	}
}
//----------------------------------------------------------------------------
void EngineCanvas::_CalSize(const Sizef &projSize)
{
	SizeNode *parent = DynamicCast<SizeNode>(GetParent());
	if (!parent) return;

	const Sizef &parentSize = parent->GetSize();

	float parentHeightOverWidth = parentSize.Height / parentSize.Width;
	float projHeightOverWidth = projSize.Height / projSize.Width;

	float useWidth = projSize.Width;
	float useHeight = projSize.Height;

	if (parentHeightOverWidth > projHeightOverWidth)
	{
		useWidth = projSize.Width;
		useHeight = useWidth * parentHeightOverWidth;
	}
	else
	{
		useHeight = projSize.Height;
		useWidth = useHeight / parentHeightOverWidth;
	}

	SetSize(useWidth, useHeight);
}
//----------------------------------------------------------------------------
void EngineCanvas::UpdateLayout(Movable *parent)
{
	bool isLayoutChanged = mIsLayoutChanged;
	Canvas::UpdateLayout(parent);
	if (isLayoutChanged)
	{
		Project *proj = Project::GetSingletonPtr();
		if (proj)
		{
			const Sizef &projSize = proj->GetSize();
			_CalSize(projSize);
		}
	}
}
//----------------------------------------------------------------------------
void EngineCanvas::UpdateWorldData(double applicationTime,
	double elapsedTime)
{
	Canvas::UpdateWorldData(applicationTime, elapsedTime);

	SizeNode *parent = DynamicCast<SizeNode>(GetParent());
	if (!parent) return;
	SetScreenRect(parent->GetScreenRect());

	bool isShowInfo = PX2_APP.IsShowInfo();
	mInfoFrame->Show(isShowInfo);
	if (!isShowInfo)
		return;

	mFPSUpdate++;
	mFPSUpdateTime += (float)elapsedTime;

	if (mFPSUpdateTime > 0.1f)
	{
		mFPS = (int)((float)mFPSUpdate / (float)mFPSUpdateTime);
		mFPSUpdate = 0;
		mFPSUpdateTime = 0.0f;
	}

	Renderer *renderer = Renderer::GetDefaultRenderer();
	int numPerFrame = renderer->GetNumDrawPrimitivePerFrame();
	std::string infoStr = std::string("FPS:" + StringHelp::IntToString(mFPS) +
		" DrNum:" + StringHelp::IntToString(numPerFrame));
	mInfoText->GetText()->SetText(infoStr);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// EngineCanvas
//----------------------------------------------------------------------------
EngineCanvas::EngineCanvas(LoadConstructor value) :
Canvas(value)
{
	mFPS = 0;
	mFPSUpdate = 0;
	mFPSUpdateTime = 0.0f;
}
//----------------------------------------------------------------------------
void EngineCanvas::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Canvas::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(EngineCanvas, source);
}
//----------------------------------------------------------------------------
void EngineCanvas::Link(InStream& source)
{
	Canvas::Link(source);
}
//----------------------------------------------------------------------------
void EngineCanvas::PostLink()
{
	Canvas::PostLink();
}
//----------------------------------------------------------------------------
bool EngineCanvas::Register(OutStream& target) const
{
	if (Canvas::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EngineCanvas::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Canvas::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(EngineCanvas, target);
}
//----------------------------------------------------------------------------
int EngineCanvas::GetStreamingSize(Stream &stream) const
{
	int size = Canvas::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------