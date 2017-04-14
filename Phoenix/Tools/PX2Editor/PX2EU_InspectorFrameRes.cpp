// PX2EU_InspectorFrameRes.cpp

#include "PX2EU_InspectorFrameRes.hpp"
#include "PX2UISkinManager.hpp"
#include "PX2UISizeExtendControl.hpp"
#include "PX2EditorEventType.hpp"
#include "PX2SelectResData.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2Edit.hpp"
#include "PX2Creater.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIFrame, EU_InspectorFrameRes);
PX2_IMPLEMENT_STREAM(EU_InspectorFrameRes);
PX2_IMPLEMENT_FACTORY(EU_InspectorFrameRes);

//----------------------------------------------------------------------------
EU_InspectorFrameRes::EU_InspectorFrameRes()
{
	float showHeight = 250.0f;

	mPropertyGridRes = new0 EU_PropertyGridRes();
	AttachChild(mPropertyGridRes);

	mPropertyGridRes->SetAnchorHor(0.0f, 1.0f);
	mPropertyGridRes->SetAnchorVer(0.0f, 1.0f);

	mPropertyGridRes->SetAnchorParamHor(0.0f, 0.0f);
	mPropertyGridRes->SetAnchorParamVer(showHeight, 0.0f);

	mShowFrame = new0 UIFrame();
	AttachChild(mShowFrame);
	mShowFrame->SetAnchorHor(0.0f, 1.0f);
	mShowFrame->SetAnchorVer(0.0f, 0.0f);
	mShowFrame->SetSize(0.0f, showHeight);
	mShowFrame->SetPivot(0.5f, 0.0f);

	// show picBox
	mShowCanvas = new0 Canvas();
	mShowCanvas->CreateUICameraNode();
	mShowFrame->AttachChild(mShowCanvas);
	mShowCanvas->SetAnchorHor(0.0f, 1.0f);
	mShowCanvas->SetAnchorVer(0.0f, 1.0f);
	mShowCanvas->GetUICameraNode()->GetCamera()->SetClearFlag(true, true, true);
	mShowCanvas->GetUICameraNode()->GetCamera()->SetClearColor(
		Float4::MakeColor(80, 80, 80, 255));

	mShowPicBox = new0 UIFPicBox();
	mShowCanvas->AttachChild(mShowPicBox);
	mShowPicBox->SetAnchorHor(0.0f, 1.0f);
	mShowPicBox->SetAnchorVer(0.0f, 1.0f);

	mSizeExtendControl_ShowPicBox = new0 UISizeExtendControl();
	mShowPicBox->AttachController(mSizeExtendControl_ShowPicBox);
	mSizeExtendControl_ShowPicBox->ResetPlay();
	mShowCanvas->Show(false);

	// show model
	mCanvasModel = new0 Canvas();
	mCanvasModel->CreateUICameraNode();
	mShowFrame->AttachChild(mCanvasModel);
	mCanvasModel->SetClearFlag(false, true, true);
	mCanvasModel->SetAnchorHor(0.0f, 1.0f);
	mCanvasModel->SetAnchorVer(0.0f, 1.0f);
	mCanvasModel->Show(false);

	mCanvasModelNode = new0 Node();
	mCanvasModel->AttachChild(mCanvasModelNode);
	mRotCtrl = new0 InterpCurveRotateController();
	mCanvasModelNode->AttachController(mRotCtrl);
	mRotCtrl->mValues.Reset();
	mRotCtrl->mValues.AddPoint(0.0f, Float3(0.0f, 0.0f, 0.0f));
	mRotCtrl->mValues.AddPoint(5.0f, Float3(0.0f, 0.0f, Mathf::TWO_PI));
	mRotCtrl->Repeat = Controller::RT_WRAP;
	mRotCtrl->MaxTime = 5.0f;
	mRotCtrl->ResetPlay();

	mCameraNodeModel = PX2_CREATER.CreateNode_Camera();
	mCanvasModel->AttachChild(mCameraNodeModel);
	mCameraNodeModel->LocalTransform.SetTranslate(0.0f, -5.0f, 2.5f);
	mCameraNodeModel->LookAt(APoint(0.0f, 0.0f, 0.0f));

	Camera *camera = mCameraNodeModel->GetCamera();
	camera->SetClearColor(Float4::MakeColor(100, 100, 100, 255));
	camera->SetClearFlag(true, true, true);

	mCanvasModel->AddCamera(camera);

	ComeInEventWorld();
}
//----------------------------------------------------------------------------
EU_InspectorFrameRes::~EU_InspectorFrameRes()
{
	GoOutEventWorld();
}
//----------------------------------------------------------------------------
void EU_InspectorFrameRes::OnEvent(Event *event)
{
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::SelectRes))
	{
		const SelectResData &selectResData = PX2_EDIT.GetSelectedResource();

		const std::string &resPathName = selectResData.ResPathname;

		std::string outPath;
		std::string outBaseName;
		std::string outExtention;
		
		StringHelp::SplitFullFilename(resPathName, outPath, outBaseName, 
			outExtention);

		if ("png" == outExtention || "PNG" == outExtention)
		{
			Texture2D *tex2D = DynamicCast<Texture2D>(
				PX2_RM.BlockLoad(resPathName));
			if (tex2D)
			{
				float texWidth = (float)tex2D->GetWidth();
				float texHeight = (float)tex2D->GetHeight();

				mShowPicBox->GetUIPicBox()->SetTexture(tex2D);

				mSizeExtendControl_ShowPicBox->SetWidthOverHeightPercent(
					texWidth / texHeight);
				mSizeExtendControl_ShowPicBox->SetOriginHeight(texHeight);

				mShowCanvas->Show(true);
				mShowPicBox->Show(true);
				mCanvasModel->Show(false);
			}
		}
		else if (!outExtention.empty())
		{
			mShowCanvas->Show(false);
			mShowPicBox->Show(false);
			mCanvasModel->Show(true);

			MovablePtr mov = DynamicCast<Movable>(PX2_RM.BlockLoadCopy(resPathName));
			if (mov)
			{
				mCanvasModelNode->DetachAllChildren();
				mCanvasModelNode->AttachChild(mov);

				mov->ResetPlay();
				mCanvasModelNode->Update(Time::GetTimeInSeconds(), 0.0f);

				float radius = mov->WorldBound.GetRadius();
				AVector dir(0.0f, -5.0f, 3.0f);
				dir.Normalize();
				APoint pos = APoint::ORIGIN + radius*6.0f * dir;
				mCameraNodeModel->LocalTransform.SetTranslate(pos);
				mCameraNodeModel->LookAt(APoint(0.0f, 0.0f, 0.0f));
			}
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EU_InspectorFrameRes::EU_InspectorFrameRes(LoadConstructor value) :
UIFrame(value)
{
}
//----------------------------------------------------------------------------
void EU_InspectorFrameRes::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIFrame::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(EU_InspectorFrameRes, source);
}
//----------------------------------------------------------------------------
void EU_InspectorFrameRes::Link(InStream& source)
{
	UIFrame::Link(source);
}
//----------------------------------------------------------------------------
void EU_InspectorFrameRes::PostLink()
{
	UIFrame::PostLink();
}
//----------------------------------------------------------------------------
bool EU_InspectorFrameRes::Register(OutStream& target) const
{
	if (UIFrame::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EU_InspectorFrameRes::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIFrame::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(EU_InspectorFrameRes, target);
}
//----------------------------------------------------------------------------
int EU_InspectorFrameRes::GetStreamingSize(Stream &stream) const
{
	int size = UIFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------