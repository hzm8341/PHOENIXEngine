// PX2EU_CanvasTimeLineEdit.cpp

#include "PX2EU_CanvasTimeLineEdit.hpp"
#include "PX2EU_Manager.hpp"
#include "PX2Edit.hpp"
#include "PX2EditTimeLineEdit.hpp"
#include "PX2Renderer.hpp"
#include "PX2Picker.hpp"
#include "PX2Canvas.hpp"
#include "PX2EditorEventType.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2GraphicsEventType.hpp"
#include "PX2Application.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIFrame, EU_CanvasTimeLineEdit);
PX2_IMPLEMENT_STREAM(EU_CanvasTimeLineEdit);
PX2_IMPLEMENT_FACTORY(EU_CanvasTimeLineEdit);

//----------------------------------------------------------------------------
EU_CanvasTimeLineEdit::EU_CanvasTimeLineEdit():
mMoveMode(MM_PAN),
mIsInitUpdated(false),
mLeftWidth(120.0f),
mPixelOverCamIn(1.0f),
mPixelOverCamOut(1.0f),
mUPerGrid(0.0f),
mVPerGrid(0.0f),
mXStart(0.0f),
mXEnd(0.0f),
mZStart(0.0f),
mZEnd(0.0f),
mIsLeftDown(false),
mIsMiddleDown(false)
{
	mCanvasGrid = new0 Canvas();
	mCanvasGrid->CreateUICameraNode();
	AttachChild(mCanvasGrid);
	mCanvasGrid->SetClearFlag(false, true, true);
	mCanvasGrid->SetClearColor(Float4::MakeColor(200, 200, 200, 255));
	mCanvasGrid->SetAnchorHor(0.0f, 1.0f);
	mCanvasGrid->SetAnchorParamHor(mLeftWidth, 0.0f);
	mCanvasGrid->SetAnchorVer(0.0f, 1.0f);
	mCanvasGrid->RemoveAllCameras();

	mCanvasNode = new0 Node();
	mCanvasGrid->SetRenderNode(mCanvasNode);
	mCanvasGrid->SetRenderNodeUpdate(true);

	mCanvasOverCamera = new0 Camera(false);
	mCanvasOverCamera->SetFrame(APoint(0.0f, -2000.0f, 0.0f),
		AVector::UNIT_Y, AVector::UNIT_Z, AVector::UNIT_X);
	mCanvasOverCamera->SetClearFlag(true, true, true);
	mCanvasOverCamera->SetClearColor(Float4::MakeColor(200, 200, 200, 255));
	mCanvasGrid->SetOverCamera(mCanvasOverCamera);

	mCanvasOverCameraNode = new0 CameraNode(mCanvasOverCamera);
	mCanvasNode->AttachChild(mCanvasOverCameraNode);

	Node *gridRoot = PX2_EDIT.GetTimeLineEdit()
		->GetCurEditNode_GridRoot();
	mCanvasNode->AttachChild(gridRoot);

	float rWidth = 2.0f*mCanvasGrid->GetSize().Width;
	float scaleX = rWidth / 15.0f;
	float scaleZ = scaleX * (1.0f);
	PX2_EDIT.GetTimeLineEdit()->SetCtrlsScale(Float2(scaleX, scaleZ));

	UIFrame *uiFrame = PX2_EDIT.GetTimeLineEdit()->GetCurveEditNode_UIGroup();
	AttachChild(uiFrame);
	UIPicBox *picBox = uiFrame->CreateAddBackgroundPicBox();
	picBox->SetColor(Float3::MakeColor(220, 220, 220));
	uiFrame->SetAnchorHor(0.0f, 0.0f);
	uiFrame->SetAnchorParamHor(mLeftWidth / 2.0f, 0.0f);
	uiFrame->SetAnchorVer(0.0f, 1.0f);
	uiFrame->SetSize(mLeftWidth, 0.0f);

	ComeInEventWorld();
}
//----------------------------------------------------------------------------
EU_CanvasTimeLineEdit::~EU_CanvasTimeLineEdit()
{
	GoOutEventWorld();
}
//----------------------------------------------------------------------------
void EU_CanvasTimeLineEdit::FitViewHorizontally()
{
	Camera *camera = mCanvasOverCamera;

	float inMin = Mathf::MAX_REAL;
	float inMax = -Mathf::MAX_REAL;
	PX2_EDIT.GetTimeLineEdit()->GetInRange(inMin, inMax);

	float inLength = inMax - inMin;
	bool inLenghtZero = false;
	if (inLength == 0.0f)
	{
		inLength = 10.0f;
		inLenghtZero = true;
	}

	float dMin = 0.0f;
	float dMax = 0.0f;
	float uMin = 0.0f;
	float uMax = 0.0f;
	float rMin = 0.0f;
	float rMax = 0.0f;
	camera->GetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);
	rMax = inLength / 2.0f * 1.5f;
	rMin = -rMax;
	camera->SetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);

	APoint pos = camera->GetPosition();

	if (inLenghtZero)
	{
		pos.X() = inMin;
	}
	else
	{
		pos.X() = inMin + inLength / 2.0f;
	}

	mCanvasOverCameraNode->LocalTransform.SetTranslate(pos);
	mCanvasOverCameraNode->Update(Time::GetTimeInSeconds(), 0.0f);

	_RefreshGrid(true);
}
//----------------------------------------------------------------------------
void EU_CanvasTimeLineEdit::FitViewVertically()
{
	float outMin = Mathf::MAX_REAL;
	float outMax = -Mathf::MAX_REAL;
	PX2_EDIT.GetTimeLineEdit()->GetOutRange(outMin, outMax);

	float outLength = outMax - outMin;
	bool outLenghtZero = false;
	if (outLength == 0.0f)
	{
		outLength = 10.0f;
		outLenghtZero = true;
	}

	float dMin = 0.0f;
	float dMax = 0.0f;
	float uMin = 0.0f;
	float uMax = 0.0f;
	float rMin = 0.0f;
	float rMax = 0.0f;
	mCanvasOverCamera->GetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);
	uMax = outLength / 2.0f * 1.5f;
	uMin = -uMax;
	mCanvasOverCamera->SetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);

	APoint pos = mCanvasOverCamera->GetPosition();

	if (outLenghtZero)
		pos.Z() = outMin;
	else
		pos.Z() = outMin + outLength / 2.0f;

	mCanvasOverCameraNode->LocalTransform.SetTranslate(pos);
	mCanvasOverCameraNode->Update(Time::GetTimeInSeconds(), 0.0f);

	_RefreshGrid(true);
}
//----------------------------------------------------------------------------
void EU_CanvasTimeLineEdit::FitViewToAll()
{
	FitViewHorizontally();
	FitViewVertically();
}
//----------------------------------------------------------------------------
void EU_CanvasTimeLineEdit::FitViewToSelected()
{
	CurveCtrl *ctrl = PX2_EDIT.GetTimeLineEdit()->GetSelectedCurveCtrl();
	if (!ctrl) return;

	float inMin = Mathf::MAX_REAL;
	float inMax = -Mathf::MAX_REAL;
	PX2_EDIT.GetTimeLineEdit()->GetInRange(inMin, inMax);

	float outMin = Mathf::MAX_REAL;
	float outMax = -Mathf::MAX_REAL;
	PX2_EDIT.GetTimeLineEdit()->GetOutRange(outMin, outMax);

	float inLength = inMax - inMin;
	float outLength = outMax - outMin;

	if (inLength == 0.0f)
	{
		inLength = 10.0f;
	}
	if (outLength == 0.0f)
	{
		outLength = 10.0f;
	}

	float dMin = 0.0f;
	float dMax = 0.0f;
	float uMin = 0.0f;
	float uMax = 0.0f;
	float rMin = 0.0f;
	float rMax = 0.0f;
	mCanvasOverCamera->GetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);
	rMax = inLength / 2.0f * 1.5f;
	rMin = -rMax;
	uMax = outLength / 2.0f * 1.5f;
	uMin = -uMax;
	mCanvasOverCamera->SetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);

	APoint camPos = mCanvasOverCamera->GetPosition();
	APoint ctrPos = ctrl->GetOutVal();
	camPos.X() = ctrPos.X();
	camPos.Z() = ctrPos.Z();
	mCanvasOverCameraNode->LocalTransform.SetTranslate(camPos);
	mCanvasOverCameraNode->Update(Time::GetTimeInSeconds(), 0.0f);

	_RefreshGrid(true);
}
//----------------------------------------------------------------------------
void EU_CanvasTimeLineEdit::ZoomCamera(float xDetal, float zDetal)
{
	Camera *camera = mCanvasOverCamera;

	float dMin = 0.0f;
	float dMax = 0.0f;
	float uMin = 0.0f;
	float uMax = 0.0f;
	float rMin = 0.0f;
	float rMax = 0.0f;
	camera->GetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);
	float uMaxTemp = uMax;
	float rMaxTemp = rMax;

	if (xDetal > 0.0f)
	{
		rMaxTemp *= xDetal;
	}
	else
	{
		rMaxTemp /= -xDetal;
	}

	if (zDetal > 0.0f)
	{
		uMaxTemp *= zDetal;
	}
	else
	{
		uMaxTemp /= -zDetal;
	}

	if (uMaxTemp > 0.0f)
	{
		uMax = uMaxTemp;
	}
	if (rMaxTemp > 0.0f)
	{
		rMax = rMaxTemp;
	}

	uMin = -uMax;
	rMin = -rMax;
	camera->SetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);

	_RefreshGrid(true);
}
//----------------------------------------------------------------------------
void EU_CanvasTimeLineEdit::ZoomCameraTo(float xMax, float zMax)
{
	if (xMax <= 0.0f || zMax <= 0.0f) return;

	Camera *camera = mCanvasOverCamera;

	float dMin = 0.0f;
	float dMax = 0.0f;
	float uMin = 0.0f;
	float uMax = 0.0f;
	float rMin = 0.0f;
	float rMax = 0.0f;
	camera->GetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);

	rMax = xMax;
	rMin = -rMax;
	uMax = zMax;
	uMin = -uMax;
	camera->SetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);

	_RefreshGrid(true);
}
//----------------------------------------------------------------------------
void EU_CanvasTimeLineEdit::OnEvent(Event *ent)
{
	if (EditorEventSpace::IsEqual(ent, EditorEventSpace::TimeLine_FitHor))
	{
		FitViewHorizontally();
	}
	else if (EditorEventSpace::IsEqual(ent, EditorEventSpace::TimeLine_FitVer))
	{
		FitViewVertically();
	}
	else if (EditorEventSpace::IsEqual(ent, EditorEventSpace::TimeLine_FitAll))
	{
		FitViewToAll();
	}
	else if (EditorEventSpace::IsEqual(ent, EditorEventSpace::TimeLine_Fit_Selected))
	{
		FitViewToSelected();
	}
	else if (EditorEventSpace::IsEqual(ent, EditorEventSpace::TimeLine_Pan))
	{
		mMoveMode = MM_PAN;
	}
	else if (EditorEventSpace::IsEqual(ent, EditorEventSpace::TimeLine_Zoom))
	{
		mMoveMode = MM_ZOOM;
	}
	else if (EditorEventSpace::IsEqual(ent, EditorEventSpace::TimeLine_CurveMode))
	{
		InterpCurveMode icmMode = (InterpCurveMode)ent->GetData<int>();

		CurveCtrl *ctrl = PX2_EDIT.GetTimeLineEdit()->GetSelectedCurveCtrl();
		if (ctrl)
		{
			ctrl->SetInterpCurveMode(icmMode);
		}
	}
	else if (GraphicsES::IsEqual(ent, GraphicsES::RemoveObject))
	{
	}
}
//----------------------------------------------------------------------------
float _GetTimeLineGridSpacing(int gridNum)
{
	if (gridNum & 0x01) // Odd numbers
	{
		return Mathf::Pow(10.f, 0.5f*((float)(gridNum - 1)) + 1.f);
	}
	else // Even numbers
	{
		return 0.5f * Mathf::Pow(10.f, 0.5f*((float)(gridNum)) + 1.f);
	}
}
//----------------------------------------------------------------------------
void EU_CanvasTimeLineEdit::UpdateWorldData(double applicationTime, 
	double elapsedTime)
{
	UIFrame::UpdateWorldData(applicationTime, elapsedTime);

	if (!mIsInitUpdated)
	{
		_RefreshGrid(true);

		mIsInitUpdated = true;
	}
}
//----------------------------------------------------------------------------
void EU_CanvasTimeLineEdit::_RefreshGrid(bool doScale)
{
	if (!mCanvasGrid) return;
	if (!mCanvasOverCamera) return;

	Polysegment *gird = PX2_EDIT.GetTimeLineEdit()->GetGridPoly();

	int width = (int)mCanvasGrid->GetSize().Width;
	int height = (int)mCanvasGrid->GetSize().Height;

	if (width <= 0 || height <= 0) return;

	Camera *camera = mCanvasOverCamera;
	APoint pos = camera->GetPosition();
	float dMin = 0.0f;
	float dMax = 0.0f;
	float uMin = 0.0f;
	float uMax = 0.0f;
	float rMin = 0.0f;
	float rMax = 0.0f;
	camera->GetFrustum(dMin, dMax, uMin, uMax, rMin, rMax);
	if (0.0f == rMax || 0.0f == uMax || 0.0f == dMax) return;

	float inLength = rMax - rMin;
	float outLength = uMax - uMin;
	inLength = Mathf::FAbs(inLength);
	outLength = Mathf::FAbs(outLength);

	mPixelOverCamIn = width / inLength;
	mPixelOverCamOut = height / outLength;

	int minPixelsPerInGrid = 35;
	int minPixelsPerOutGrid = 25;
	float minGridSpacing = 0.001f;

	int gridNum = 0;
	float inGridSpacing = minGridSpacing;
	while (inGridSpacing*mPixelOverCamIn < minPixelsPerInGrid)
	{
		inGridSpacing = minGridSpacing * _GetTimeLineGridSpacing(gridNum);
		gridNum++;
	}
	mUPerGrid = inGridSpacing;

	gridNum = 0;
	float outGridSpacing = minGridSpacing;
	while (outGridSpacing*mPixelOverCamOut < minPixelsPerOutGrid)
	{
		outGridSpacing = minGridSpacing * _GetTimeLineGridSpacing(gridNum);
		gridNum++;
	}
	mVPerGrid = outGridSpacing;

	mXStart = pos.X() + rMin;
	mXEnd = pos.X() + rMax;
	mZStart = pos.Z() + uMin;
	mZEnd = pos.Z() + uMax;

	Float3 gray(0.62f, 0.62f, 0.62f);
	int segNum = 0;
	mFontStrs.clear();
	int iTemp = 4;
	int zTemp = 4;

	VertexBufferAccessor vba(gird);
	float zPosTemp = 0.0f;
	while (zPosTemp < mZEnd)
	{
		zPosTemp += mVPerGrid;

		vba.Position<Float3>(2 * segNum) = Float3(mXStart, 1.0f, zPosTemp);
		vba.Color<Float3>(0, 2 * segNum) = gray;
		vba.Position<Float3>(2 * segNum + 1) = Float3(mXEnd, 1.0f, zPosTemp);
		vba.Color<Float3>(0, 2 * segNum + 1) = gray;

		Vector2f scrv = mCanvasOverCamera->WorldPos3DTo2D(GetWorldRect(), 
			APoint(0.0f, 0.0f, zPosTemp));
		FontStr fs;
		fs.x = iTemp + (int)mLeftWidth;
		fs.y = height - (int)scrv.Y();
		fs.str = StringHelp::FloatToString(zPosTemp);
		mFontStrs.push_back(fs);

		segNum++;
	}
	zPosTemp = 0.0f;
	while (zPosTemp > mZStart)
	{
		zPosTemp -= mVPerGrid;

		vba.Position<Float3>(2 * segNum) = Float3(mXStart, 1.0f, zPosTemp);
		vba.Color<Float3>(0, 2 * segNum) = gray;
		vba.Position<Float3>(2 * segNum + 1) = Float3(mXEnd, 1.0f, zPosTemp);
		vba.Color<Float3>(0, 2 * segNum + 1) = gray;

		Vector2f scrv = mCanvasOverCamera->WorldPos3DTo2D(GetWorldRect(), 
			APoint(0.0f, 0.0f, zPosTemp));
		FontStr fs;
		fs.x = iTemp + (int)mLeftWidth;
		fs.y = height - (int)scrv.Y();
		fs.str = StringHelp::FloatToString(zPosTemp);
		mFontStrs.push_back(fs);

		segNum++;
	}
	float xPosTemp = 0.0f;
	while (xPosTemp < mXEnd)
	{
		xPosTemp += mUPerGrid;

		vba.Position<Float3>(2 * segNum) = Float3(xPosTemp, 1.0f, mZStart);
		vba.Color<Float3>(0, 2 * segNum) = gray;
		vba.Position<Float3>(2 * segNum + 1) = Float3(xPosTemp, 1.0f, mZEnd);
		vba.Color<Float3>(0, 2 * segNum + 1) = gray;

		Vector2f scrv = mCanvasOverCamera->WorldPos3DTo2D(GetWorldRect(),
			APoint(0.0f, 0.0f, zPosTemp));
		FontStr fs;
		fs.x = (int)scrv.X() + iTemp;
		fs.y = height - zTemp;
		fs.str = StringHelp::FloatToString(xPosTemp);
		mFontStrs.push_back(fs);

		segNum++;
	}
	xPosTemp = 0.0f;
	while (xPosTemp > mXStart)
	{
		xPosTemp -= mUPerGrid;

		vba.Position<Float3>(2 * segNum) = Float3(xPosTemp, 1.0f, mZStart);
		vba.Color<Float3>(0, 2 * segNum) = gray;
		vba.Position<Float3>(2 * segNum + 1) = Float3(xPosTemp, 1.0f, mZEnd);
		vba.Color<Float3>(0, 2 * segNum + 1) = gray;

		Vector2f scrv = mCanvasOverCamera->WorldPos3DTo2D(GetWorldRect(), 
			APoint(0.0f, 0.0f, zPosTemp));
		FontStr fs;
		fs.x = (int)scrv.X() + iTemp;
		fs.y = height - zTemp;
		fs.str = StringHelp::FloatToString(xPosTemp);
		mFontStrs.push_back(fs);

		segNum++;
	}

	Float3 zeroLineColorRed = Float3::MakeColor(150, 28, 36);
	Float3 zeroLineColorBlue = Float3::MakeColor(63, 72, 175);

	vba.Position<Float3>(2 * segNum) = Float3(mXStart, 1.0f, 0.0f);
	vba.Color<Float3>(0, 2 * segNum) = zeroLineColorRed;
	vba.Position<Float3>(2 * segNum + 1) = Float3(mXEnd, 1.0f, 0.0f);
	vba.Color<Float3>(0, 2 * segNum + 1) = zeroLineColorRed;
	segNum++;
	vba.Position<Float3>(2 * segNum) = Float3(0.0f, 1.0f, mZStart);
	vba.Color<Float3>(0, 2 * segNum) = zeroLineColorBlue;
	vba.Position<Float3>(2 * segNum + 1) = Float3(0.0f, 1.0f, mZEnd);
	vba.Color<Float3>(0, 2 * segNum + 1) = zeroLineColorBlue;
	segNum++;

	Vector2f scrv = mCanvasOverCamera->WorldPos3DTo2D(GetWorldRect(), APoint(0.0f, 0.0f,
		zPosTemp));
	FontStr fs;
	fs.x = iTemp + (int)mLeftWidth;
	fs.y = height - (int)scrv.Y();
	fs.str = "0.0";
	mFontStrs.push_back(fs);

	FontStr fs1;
	fs1.x = (int)scrv.X() + iTemp;
	fs1.y = height - zTemp;
	fs1.str = "0.0";
	mFontStrs.push_back(fs1);

	gird->SetNumSegments(segNum);

	gird->UpdateModelSpace(Renderable::GU_MODEL_BOUND_ONLY);

	Renderer::UpdateAll(gird->GetVertexBuffer());

	if (doScale)
	{
		float rWidth = 2.0f * rMax;
		float scaleX = rWidth / 15.0f;

		float uHeight = 2.0f * uMax;
		float scaleZ = uHeight / (((float)mCanvasGrid->GetSize().Height / (float)mCanvasGrid->GetSize().Width)*15.0f);
		PX2_EDIT.GetTimeLineEdit()->SetCtrlsScale(Float2(scaleX, scaleZ));
	}
}
//----------------------------------------------------------------------------
void EU_CanvasTimeLineEdit::_TrySelectCurveCtrlPoint(float posSizePercentWidth,
	float posSizePercentHeight)
{
	if (!mCanvasGrid) return;
	if (!mCanvasOverCamera) return;

	APoint origin;
	AVector direction;
	mCanvasOverCamera->GetPickRay(posSizePercentWidth, posSizePercentHeight,
		origin, direction);

	Node *gridNode = PX2_EDIT.GetTimeLineEdit()->GetCurveEditNode_Grid();

	Picker picker;
	picker.Execute(gridNode, origin, direction, 0.0f, Mathf::MAX_REAL);

	if ((int)(picker.Records.size()) > 0)
	{
		Movable *mov = picker.GetClosestNonnegative().Intersected;

		CurveCtrl *ctrl = PX2_EDIT.GetTimeLineEdit()->TrySelectCurve(mov);

		if (ctrl)
		{
			//UnToggleAllInterps();
			//EnableInterps(true);
			//ToggleInterp(ctrl->GetInterpCurveMode());

			PX2_EDIT.GetTimeLineEdit()->SetSelectedCurveCtrl(ctrl);
		}
		else
		{
			PX2_EDIT.GetTimeLineEdit()->SetSelectedCurveCtrl(0);
		}
	}
	else
	{
		PX2_EDIT.GetTimeLineEdit()->SetSelectedCurveCtrl(0);
	}
}
//----------------------------------------------------------------------------
void EU_CanvasTimeLineEdit::OnSizeChanged()
{
	FitViewToAll();

	Camera *camera = mCanvasOverCamera;
	if (camera)
	{
		float helfWidth = mCanvasGrid->GetSize().Width / 2.0f;
		float helfHeight = mCanvasGrid->GetSize().Height / 2.0f;
		camera->SetFrustum(0.1f, 2000.0f + 1000.0f,
			-helfHeight, helfHeight, -helfWidth, helfWidth);
	}

	_RefreshGrid(true);
}
//----------------------------------------------------------------------------
void EU_CanvasTimeLineEdit::OnSizeNodePicked(const CanvasInputData &inputData)
{
	const APoint &worldPos = inputData.LogicPos;
	Float2 wPos(worldPos.X(), worldPos.Z());

	const Rectf &canvasWorldRect = mCanvasGrid->GetWorldRect();
	if (!canvasWorldRect.IsInsize(wPos))
	{
		// left

		if (CanvasInputData::MT_RIGHT == inputData.TheMouseTag)
		{
			CreateEditMenu(worldPos);
		}
	}
	else
	{

		float posSizePercentWdith = (wPos[0] - canvasWorldRect.Left) /
			canvasWorldRect.Width();
		float posSizePercentHeight = (wPos[1] - canvasWorldRect.Bottom) /
			canvasWorldRect.Height();

		if (UIPT_PRESSED == inputData.PickType)
		{
			if (CanvasInputData::MT_LEFT == inputData.TheMouseTag)
			{
				mIsLeftDown = true;
				_TrySelectCurveCtrlPoint(posSizePercentWdith, posSizePercentHeight);
			}
			else if (CanvasInputData::MT_MIDDLE == inputData.TheMouseTag)
			{
				mIsMiddleDown = true;
			}
		}
		else if (UIPT_RELEASED == inputData.PickType)
		{
			mIsLeftDown = false;
			mIsMiddleDown = false;
		}
		else if (UIPT_DOUBLE_PRESSED == inputData.PickType)
		{
			mIsLeftDown = false;
			mIsMiddleDown = false;

			bool isCtrlDown = PX2_EDIT.IsCtrlDown;
			PX2_UNUSED(isCtrlDown);

			UICurveGroup *uiCurveGroup = PX2_EDIT.GetTimeLineEdit()->GetSelectedUICurveGroup();
			if (!uiCurveGroup) return;

			APoint camPos = mCanvasOverCamera->GetPosition();
			Vector2f camScreenPos = mCanvasOverCamera->WorldPos3DTo2D(canvasWorldRect, camPos);
			float xDissCam = worldPos.X() - camScreenPos.X();
			float zDissCam = worldPos.Z() - camScreenPos.Y();
			float xDissCamReal = xDissCam / mPixelOverCamIn;
			float zDissCamReal = zDissCam / mPixelOverCamOut;
			APoint pointPos = camPos + AVector(xDissCamReal, 0.0f, zDissCamReal);
			pointPos.Y() = 0.0f;

			CurveGroup *curveGroup = uiCurveGroup->GetCurveGroup();
			curveGroup->AddPoint(pointPos);
		}
		else if (UIPT_WHELLED == inputData.PickType)
		{
			float val = 1.2f * Mathf::Sign(inputData.Wheel);
			ZoomCamera(val, val);
		}
		else if (UIPT_MOVED == inputData.PickType)
		{
			AVector diff = inputData.MoveDelta;
			if (AVector::ZERO == diff) return;

			float movedX = -diff.X() / mPixelOverCamIn;
			float movedZ = -diff.Z() / mPixelOverCamOut;

			bool isCtrlDown = PX2_EDIT.IsCtrlDown;
			CurveCtrl *selectedCtrl = PX2_EDIT.GetTimeLineEdit()
				->GetSelectedCurveCtrl();

			if (isCtrlDown && selectedCtrl && mIsLeftDown)
			{
				Camera *camera = mCanvasOverCamera;

				const APoint &outVal = selectedCtrl->GetOutVal();
				Vector2f posInViewPort = mCanvasOverCamera->WorldPos3DTo2D(canvasWorldRect, outVal);

				float xDiss = worldPos.X() - posInViewPort.X();
				float zDiss = worldPos.Z() - posInViewPort.Y();
				float xDissReal = xDiss / mPixelOverCamIn;
				float zDissReal = zDiss / mPixelOverCamOut;

				AVector arrive = AVector(-xDissReal, 0.0f, -zDissReal);
				arrive.Normalize();
				AVector leave = AVector(xDissReal, 0.0f, zDissReal);
				leave.Normalize();

				if (CurveCtrl::SM_ARRIVE == selectedCtrl->GetSelectMode())
				{
					if (xDiss < 0.0f)
					{
						selectedCtrl->SetArriveTangent(arrive);

						InterpCurveMode mode = selectedCtrl->GetInterpCurveMode();
						if (ICM_CURVE_AUTO == mode || ICM_CURVE_AUTOCLAMPED == mode)
						{
							selectedCtrl->SetInterpCurveMode(ICM_CURVE_USER);
							//UnToggleAllInterps();
							//ToggleInterp(ICM_CURVE_USER);
						}
					}
				}
				else if (CurveCtrl::SM_LEAVE == selectedCtrl->GetSelectMode())
				{
					if (xDiss > 0.0f)
					{
						selectedCtrl->SetLeaveTangent(leave);

						InterpCurveMode mode = selectedCtrl->GetInterpCurveMode();
						if (ICM_CURVE_AUTO == mode || ICM_CURVE_AUTOCLAMPED == mode)
						{
							selectedCtrl->SetInterpCurveMode(ICM_CURVE_USER);
							//UnToggleAllInterps();
							//ToggleInterp(ICM_CURVE_USER);
						}
					}
				}
				else if (CurveCtrl::SM_CENTER == selectedCtrl->GetSelectMode())
				{
					APoint camPos = camera->GetPosition();
					Vector2f posInViewPort = mCanvasOverCamera->WorldPos3DTo2D(canvasWorldRect, camPos);
					float xDissCam = worldPos.X() - posInViewPort.X();
					float zDissCam = worldPos.Z() - posInViewPort.Y();
					float xDissCamReal = xDissCam / mPixelOverCamIn;
					float zDissCamReal = zDissCam / mPixelOverCamOut;
					APoint pointPos = camPos + AVector(xDissCamReal, 0.0f, zDissCamReal);
					pointPos.Y() = 0.0f;

					selectedCtrl->SetInVal(pointPos.X()); // ctrl may changed

					selectedCtrl = PX2_EDIT.GetTimeLineEdit()->GetSelectedCurveCtrl(); // ctrl may changed, can it again
					if (selectedCtrl) selectedCtrl->SetOutVal(pointPos);
				}
			}

			if (MM_PAN == mMoveMode)
			{
				if (mCanvasGrid && mIsMiddleDown)
				{
					APoint pos = mCanvasOverCameraNode->LocalTransform.GetTranslate();
					pos += AVector(movedX, 0.0f, movedZ);
					mCanvasOverCameraNode->LocalTransform.SetTranslate(pos);
					mCanvasOverCameraNode->Update(Time::GetTimeInSeconds(), 0.0f);

					_RefreshGrid(false);
				}
			}
			else if (MM_ZOOM == mMoveMode)
			{
			}
		}
	}
}
//----------------------------------------------------------------------------
void EU_CanvasTimeLineEdit::OnSizeNodeNotPicked(const CanvasInputData &inputData)
{
	PX2_UNUSED(inputData);

	mIsLeftDown = false;
	mIsMiddleDown = false;
}
//----------------------------------------------------------------------------
void EU_CanvasTimeLineEdit::CreateEditMenu(const APoint &pos)
{
	PX2_APP.Menu_Edit_Begin("Stage", "TimeLineEdit");

	PX2_APP.Menu_Edit_AddItem("Stage", "TimeLineEdit", "Delete",
		PX2_LM_EDITOR.V("n_Delete"), "n_TimeLine_Delete()");
	PX2_APP.Menu_Edit_AddItem("Stage", "TimeLineEdit", "DeleteAll",
		PX2_LM_EDITOR.V("n_DeleteAll"), "n_TimeLine_DeleteAll()");

	PX2_APP.Menu_Edit_EndPopUp("Stage", pos);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EU_CanvasTimeLineEdit::EU_CanvasTimeLineEdit(LoadConstructor value) :
UIFrame(value),
mIsInitUpdated(false),
mLeftWidth(200.0f),
mPixelOverCamIn(1.0f),
mPixelOverCamOut(1.0f),
mUPerGrid(0.0f),
mVPerGrid(0.0f),
mXStart(0.0f),
mXEnd(0.0f),
mZStart(0.0f),
mZEnd(0.0f)
{
}
//----------------------------------------------------------------------------
void EU_CanvasTimeLineEdit::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIFrame::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(EU_CanvasTimeLineEdit, source);
}
//----------------------------------------------------------------------------
void EU_CanvasTimeLineEdit::Link(InStream& source)
{
	UIFrame::Link(source);
}
//----------------------------------------------------------------------------
void EU_CanvasTimeLineEdit::PostLink()
{
	UIFrame::PostLink();
}
//----------------------------------------------------------------------------
bool EU_CanvasTimeLineEdit::Register(OutStream& target) const
{
	if (UIFrame::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EU_CanvasTimeLineEdit::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIFrame::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(EU_CanvasTimeLineEdit, target);
}
//----------------------------------------------------------------------------
int EU_CanvasTimeLineEdit::GetStreamingSize(Stream &stream) const
{
	int size = UIFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------