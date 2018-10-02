// PX2BProject.cpp

#include "PX2BProject.hpp"
#include "PX2BBlockSprite.hpp"
#include "PX2StringHelp.hpp"
#include "PX2Scene.hpp"
#include "PX2Creater.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Object, BProject);
PX2_IMPLEMENT_STREAM(BProject);
PX2_IMPLEMENT_FACTORY(BProject);

//----------------------------------------------------------------------------
BProject::BProject()
{
	mContentFrame = new0 UIFrame();
	mContentFrame->SetName("ContentFrame");
	mContentFrame->SetAnchorHor(0.0f, 1.0f);
	mContentFrame->SetAnchorVer(0.0f, 1.0f);

	mSmallFrame = UIFrame::New("SmallFrame");
	mSmallFrame->SetAnchorHor(0.0f, 1.0f);
	mSmallFrame->SetAnchorVer(0.0f, 1.0f);
	mSmallFrame->SetPivot(0.5f, 0.5f);

	mSmallCanvas = new0 Canvas();
	mSmallFrame->AttachChild(mSmallCanvas);
	mSmallCanvas->SetAnchorHor(0.0f, 1.0f);
	mSmallCanvas->SetAnchorVer(0.0f, 1.0f);
	mSmallCanvas->CreateUICameraNode();
	mSmallCanvas->SetClearFlag(true, true, true);
	mSmallCanvas->SetClearColor(Float4::MakeColor(0, 162, 232, 255));
	mSmallCanvas->GetUICameraNode()->GetCamera()->SetClearFlag(false, false, false);

	mScene = new0 Scene();

	mCameraNode = mScene->GetMainCameraNode();
	mCameraPlayCtrl = new0 CameraPlayController();
	mCameraNode->AttachController(mCameraPlayCtrl);
	mCameraPlayCtrl->ResetPlay();
	mCameraPlayCtrl->SetCameraNode(mCameraNode);
}
//----------------------------------------------------------------------------
BProject::~BProject()
{
}
//----------------------------------------------------------------------------
void BProject::CreateTemplate(TemplateType tt)
{
	// ui
	BBlockSprite *spriteRound = BBlockSprite::New(BBlockSprite::ST_ROUND);
	mContentFrame->AttachChild(spriteRound);
	spriteRound->SetName("Round");
	spriteRound->SetHorLayOutType(BBlockSprite::HLOT_LEFT);
	spriteRound->SetLayoutParamHor(200.0);
	spriteRound->SetVerLayoutType(BBlockSprite::VLOT_BOTTOM);
	spriteRound->SetLayoutParamVer(200.0);
	spriteRound->SetLookImage("Data/PhoenixCode/images/ui/stage/roundout.png");
	spriteRound->SetLookImage1("Data/PhoenixCode/images/ui/stage/circlebut.png");

	float posXStart = -150.0f;
	float posZStart = 150.0f;

	BBlockSprite *spriteSkill0 = BBlockSprite::New(BBlockSprite::ST_BUTTON);
	mContentFrame->AttachChild(spriteSkill0);
	spriteSkill0->SetHorLayOutType(BBlockSprite::HLOT_RIGHT);
	spriteSkill0->SetLayoutParamHor(posXStart);
	spriteSkill0->SetVerLayoutType(BBlockSprite::VLOT_BOTTOM);
	spriteSkill0->SetLayoutParamVer(posZStart);
	spriteSkill0->SetLookImage("Data/PhoenixCode/images/ui/stage/circlebut.png");
	spriteSkill0->SetLookImage1("Data/PhoenixCode/images/ui/stage/circlebutpress.png");
	spriteSkill0->SetSize(140, 140);
	spriteSkill0->setColor(237, 28, 36);
	float length = 200.0;
	float degree = 0.0;
	
	for (int i = 0; i < 3; i++)
	{
		float radVal = degree * Mathf::DEG_TO_RAD;

		float offX = Mathf::Cos(radVal);
		float offY = Mathf::Sin(radVal);

		float posX = posXStart - offX * length;
		float posY = posZStart + offY * length;

		BBlockSprite *spriteSkill = BBlockSprite::New(BBlockSprite::ST_BUTTON);
		mContentFrame->AttachChild(spriteSkill);
		std::string name = std::string("Skill") + StringHelp::IntToString(i);
		spriteSkill->SetName(name);
		spriteSkill->SetHorLayOutType(BBlockSprite::HLOT_RIGHT);
		spriteSkill->SetVerLayoutType(BBlockSprite::VLOT_BOTTOM);
		spriteSkill->SetLayoutParamHor(posX);
		spriteSkill->SetLayoutParamVer(posY);
		spriteSkill->SetSize(106, 106);
		spriteSkill->SetLookImage("Data/PhoenixCode/images/ui/stage/circlebut.png");
		spriteSkill->SetLookImage1("Data/PhoenixCode/images/ui/stage/circlebutpress.png");
		degree = degree + 45.0f;

		if (0 == i)
		{
			spriteSkill->setColor(255, 242, 0);
		}
		else if (1 == i)
		{
			spriteSkill->setColor(0, 162, 232);
		}
		else if (2 == i)
		{
			spriteSkill->setColor(34, 177, 76);
		}
	}

	BBlockSprite *spBloodPic = BBlockSprite::New(BBlockSprite::ST_PICBOX);
	mContentFrame->AttachChild(spBloodPic);
	spBloodPic->SetName("HeartPic");
	spBloodPic->LocalTransform.SetTranslateY(-1.0f);
	spBloodPic->SetLookImage("Data/PhoenixCode/images/sample/phoenixframe/heart.png");
	spBloodPic->SetAnchorHor(0.0f, 0.0f);
	spBloodPic->setAnchorParamHor(100.0f, 100.0f);
	spBloodPic->SetAnchorVer(1.0f, 1.0f);
	spBloodPic->SetAnchorParamVer(-60.0f, -60.0f);
	spBloodPic->SetSize(80.0f, 80.0f);

	BBlockSprite *progress = BBlockSprite::New(BBlockSprite::ST_PROGRESS);
	mContentFrame->AttachChild(progress);
	progress->SetLookImage("Data/BlueBlock/images/sprite/progressback.png", true);
	progress->SetLookImage1("Data/BlueBlock/images/sprite/progress.png", true);
	progress->LocalTransform.SetTranslateY(-1.0f);
	progress->SetAnchorHor(0.0f, 0.0f);
	progress->setAnchorParamHor(280.0f, 280.0f);
	progress->SetAnchorVer(1.0f, 1.0f);
	progress->SetAnchorParamVer(-60.0f, -60.0f);
	progress->setValue(0.5f);
	progress->setColor(255, 0, 0);

	// scene

}
//----------------------------------------------------------------------------
UIFrame *BProject::GetContentFrame()
{
	return mContentFrame;
}
//----------------------------------------------------------------------------
Scene *BProject::GetScene()
{
	return mScene;
}
//----------------------------------------------------------------------------
CameraNode *BProject::GetCameraNode()
{
	return mCameraNode;
}
//----------------------------------------------------------------------------
CameraPlayController *BProject::GetCameraPlayController()
{
	return mCameraPlayCtrl;
}
//----------------------------------------------------------------------------
UIFrame *BProject::GetSmallFrame()
{
	return mSmallFrame;
}
//----------------------------------------------------------------------------
Canvas *BProject::GetSmallCanvas()
{
	return mSmallCanvas;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
BProject::BProject(LoadConstructor value) :
Object(value)
{
}
//----------------------------------------------------------------------------
void BProject::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Object::Load(source);
	PX2_VERSION_LOAD(source);

	source.ReadString(DateStr);
	source.ReadString(Desc);
	source.ReadPointer(mContentFrame);
	source.ReadPointer(mScene);
	source.ReadPointer(mCameraNode);
	source.ReadPointer(mCameraPlayCtrl);

	source.ReadPointer(mSmallFrame);
	source.ReadPointer(mSmallCanvas);

	PX2_END_DEBUG_STREAM_LOAD(BProject, source);
}
//----------------------------------------------------------------------------
void BProject::Link(InStream& source)
{
	Object::Link(source);

	source.ResolveLink(mContentFrame);
	source.ResolveLink(mCameraNode);
	source.ResolveLink(mCameraPlayCtrl);

	source.ResolveLink(mScene);

	source.ResolveLink(mSmallFrame);
	source.ResolveLink(mSmallCanvas);
}
//----------------------------------------------------------------------------
void BProject::PostLink()
{
	Object::PostLink();

	if (mContentFrame)
	{
		mContentFrame->PostLink();
	}

	if (mScene)
	{
		mScene->PostLink();
	}

	if (mCameraNode)
	{
		mCameraNode->PostLink();
	}

	if (mCameraPlayCtrl)
	{
		mCameraPlayCtrl->PostLink();
	}

	if (mSmallFrame)
	{
		mSmallFrame->PostLink();
	}

	if (mSmallCanvas)
	{
		mSmallCanvas->PostLink();
	}

	ComeInEventWorld();
}
//----------------------------------------------------------------------------
bool BProject::Register(OutStream& target) const
{
	if (Object::Register(target))
	{
		target.Register(mContentFrame);
		target.Register(mScene);
		target.Register(mCameraNode);
		target.Register(mCameraPlayCtrl);
		target.Register(mSmallFrame);
		target.Register(mSmallCanvas);

		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void BProject::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Object::Save(target);
	PX2_VERSION_SAVE(target);

	target.WriteString(DateStr);
	target.WriteString(Desc);
	target.WritePointer(mContentFrame);
	target.WritePointer(mScene);
	target.WritePointer(mCameraNode);
	target.WritePointer(mCameraPlayCtrl);

	target.WritePointer(mSmallFrame);
	target.WritePointer(mSmallCanvas);

	PX2_END_DEBUG_STREAM_SAVE(BProject, target);
}
//----------------------------------------------------------------------------
int BProject::GetStreamingSize(Stream &stream) const
{
	int size = Object::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	size += PX2_STRINGSIZE(DateStr);
	size += PX2_STRINGSIZE(Desc);
	size += PX2_POINTERSIZE(mContentFrame);
	size += PX2_POINTERSIZE(mScene);
	size += PX2_POINTERSIZE(mCameraNode);
	size += PX2_POINTERSIZE(mCameraPlayCtrl);

	size += PX2_POINTERSIZE(mSmallFrame);
	size += PX2_POINTERSIZE(mSmallCanvas);

	return size;
}
//----------------------------------------------------------------------------