// PX2N_ResGridView.cpp

#include "PX2N_ResGridView.hpp"
#include "PX2EU_Manager.hpp"
#include "PX2N_Frame.hpp"
#include "PX2EU_ResGridFrame.hpp"
#include "PX2N_Man.hpp"
using namespace NA;

IMPLEMENT_DYNAMIC_CLASS(ResGridView, wxWindow)
BEGIN_EVENT_TABLE(ResGridView, wxWindow)
END_EVENT_TABLE()
//----------------------------------------------------------------------------
ResGridView::ResGridView()
{
}
//----------------------------------------------------------------------------
ResGridView::ResGridView(wxWindow *parent) :
wxWindow(parent, wxID_ANY)
{
	SetBackgroundColour(Float3TowxColour(PX2EU_MAN.GetEditParams()
		->GetCurTheme()->Color_Page_Background));
	SetForegroundColour(Float3TowxColour(PX2EU_MAN.GetEditParams()
		->GetCurTheme()->Color_Page_Foreground));

	wxBoxSizer* bSizer54;
	bSizer54 = new wxBoxSizer(wxVERTICAL);

	RenderWindow *rw = new0 RenderWindow();
	rw->SetName("ResGridRenderWindow");
	PX2_GR.AddRenderWindow("ResGridRenderWindow", rw);

	Canvas *canvas = new0 Canvas();
	canvas->SetName("ResGridCanvas");
	rw->SetMainCanvas(canvas);
	canvas->SetClearFlag(true, true, true);
	canvas->SetClearColor(Float4::MakeColor(51, 51, 51, 51));
	canvas->CreateUICameraNode();

	float toolBarHeight = 28.0f;

	UIFrame *toolBarFrame = new0 UIFrame();
	canvas->AttachChild(toolBarFrame);
	toolBarFrame->SetAnchorHor(0.0f, 1.0f);
	toolBarFrame->SetAnchorVer(1.0f, 1.0f);
	toolBarFrame->SetSize(0.0f, 1.0f);
	toolBarFrame->SetPivot(0.5f, 1.0f);
	UIPicBox *picBox = toolBarFrame->CreateAddBackgroundPicBox(true);
	picBox->SetColor(Float3::MakeColor(101, 101, 101));
	toolBarFrame->SetHeight(toolBarHeight);

	UIButton *butOpenIn = UIButton::New("ButOpenIn");
	toolBarFrame->AttachChild(butOpenIn);
	butOpenIn->SetSize(toolBarHeight - 4, toolBarHeight - 4);
	butOpenIn->SetPivot(0.0, 0.5);
	butOpenIn->SetAnchorHor(0.0, 0.0);
	butOpenIn->SetAnchorVer(0.5, 0.5);
	butOpenIn->SetStateColor(UIButtonBase::BS_NORMAL, Float3::WHITE);
	butOpenIn->SetStateColor(UIButtonBase::BS_HOVERED, Float3::WHITE);
	butOpenIn->SetStateColor(UIButtonBase::BS_PRESSED, Float3::WHITE);
	butOpenIn->SetStateBrightness(UIButtonBase::BS_NORMAL, 1.0f);
	butOpenIn->SetStateBrightness(UIButtonBase::BS_HOVERED, 0.9f);
	butOpenIn->SetStateBrightness(UIButtonBase::BS_PRESSED, 0.7f);
	butOpenIn->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexture("DataNIRVANAwx/images/icons/res/openin.png");
	butOpenIn->SetScriptHandler("n_ResButCallback");

	UIButton *butOpenOut = UIButton::New("ButOpenOut");
	toolBarFrame->AttachChild(butOpenOut);
	butOpenOut->SetSize(toolBarHeight - 4, toolBarHeight - 4);
	butOpenOut->SetPivot(0.0, 0.5);
	butOpenOut->SetAnchorParamHor(toolBarHeight, toolBarHeight);
	butOpenOut->SetAnchorHor(0.0, 0.0);
	butOpenOut->SetAnchorVer(0.5, 0.5);
	butOpenOut->SetStateColor(UIButtonBase::BS_NORMAL, Float3::WHITE);
	butOpenOut->SetStateColor(UIButtonBase::BS_HOVERED, Float3::WHITE);
	butOpenOut->SetStateColor(UIButtonBase::BS_PRESSED, Float3::WHITE);
	butOpenOut->SetStateBrightness(UIButtonBase::BS_NORMAL, 1.0f);
	butOpenOut->SetStateBrightness(UIButtonBase::BS_HOVERED, 0.9f);
	butOpenOut->SetStateBrightness(UIButtonBase::BS_PRESSED, 0.7f);
	butOpenOut->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexture("DataNIRVANAwx/images/icons/res/openout.png");
	butOpenOut->SetScriptHandler("n_ResButCallback");

	UIButton *butCopyPath = UIButton::New("ButCopyPath");
	toolBarFrame->AttachChild(butCopyPath);
	butCopyPath->SetSize(toolBarHeight - 4, toolBarHeight - 4);
	butCopyPath->SetPivot(0.0, 0.5);
	butCopyPath->SetAnchorParamHor(toolBarHeight*2.0f, toolBarHeight*2.0f);
	butCopyPath->SetAnchorHor(0.0, 0.0);
	butCopyPath->SetAnchorVer(0.5, 0.5);
	butCopyPath->SetStateColor(UIButtonBase::BS_NORMAL, Float3::WHITE);
	butCopyPath->SetStateColor(UIButtonBase::BS_HOVERED, Float3::WHITE);
	butCopyPath->SetStateColor(UIButtonBase::BS_PRESSED, Float3::WHITE);
	butCopyPath->SetStateBrightness(UIButtonBase::BS_NORMAL, 1.0f);
	butCopyPath->SetStateBrightness(UIButtonBase::BS_HOVERED, 0.9f);
	butCopyPath->SetStateBrightness(UIButtonBase::BS_PRESSED, 0.7f);
	butCopyPath->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexture("DataNIRVANAwx/images/icons/res/copypath.png");
	butCopyPath->SetScriptHandler("n_ResButCallback");

	UIButton *butUp = UIButton::New("ButUp");
	toolBarFrame->AttachChild(butUp);
	butUp->SetSize(toolBarHeight - 4, toolBarHeight - 4);
	butUp->SetPivot(1.0, 0.5);
	butUp->SetAnchorParamHor(-toolBarHeight, -toolBarHeight);
	butUp->SetAnchorHor(1.0, 1.0);
	butUp->SetAnchorVer(0.5, 0.5);
	butUp->SetStateColor(UIButtonBase::BS_NORMAL, Float3::WHITE);
	butUp->SetStateColor(UIButtonBase::BS_HOVERED, Float3::WHITE);
	butUp->SetStateColor(UIButtonBase::BS_PRESSED, Float3::WHITE);
	butUp->SetStateBrightness(UIButtonBase::BS_NORMAL, 1.0f);
	butUp->SetStateBrightness(UIButtonBase::BS_HOVERED, 0.9f);
	butUp->SetStateBrightness(UIButtonBase::BS_PRESSED, 0.7f);
	butUp->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexture("DataNIRVANAwx/images/icons/res/up.png");
	butUp->SetScriptHandler("n_ResButCallback");

	UIButton *butDown = UIButton::New("ButDown");
	toolBarFrame->AttachChild(butDown);
	butDown->SetSize(toolBarHeight - 4, toolBarHeight - 4);
		butDown->SetPivot(1.0, 0.5);
	butDown->SetAnchorHor(1.0, 1.0);
	butDown->SetAnchorVer(0.5, 0.5);
	butDown->SetStateColor(UIButtonBase::BS_NORMAL, Float3::WHITE);
	butDown->SetStateColor(UIButtonBase::BS_HOVERED, Float3::WHITE);
	butDown->SetStateColor(UIButtonBase::BS_PRESSED, Float3::WHITE);
	butDown->SetStateBrightness(UIButtonBase::BS_NORMAL, 1.0f);
	butDown->SetStateBrightness(UIButtonBase::BS_HOVERED, 0.9f);
	butDown->SetStateBrightness(UIButtonBase::BS_PRESSED, 0.7f);
	butDown->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexture("DataNIRVANAwx/images/icons/res/down.png");
	butDown->SetScriptHandler("n_ResButCallback");

	Canvas *canvasGridFrame = new0 Canvas();
	canvasGridFrame->SetName("ResGridFrameCanvas");
	canvas->AttachChild(canvasGridFrame);
	canvasGridFrame->LocalTransform.SetTranslateY(-1.0f);
	canvasGridFrame->SetAnchorHor(0.0f, 1.0f);
	canvasGridFrame->SetAnchorVer(0.0f, 1.0f);
	canvasGridFrame->SetClearFlag(true, true, true);
	canvasGridFrame->SetClearColor(Float4::MakeColor(51, 51, 51, 51));
	canvasGridFrame->CreateUICameraNode();
	canvasGridFrame->SetAnchorParamVer(0.0f, -toolBarHeight);

	EU_ResGridFrame *resGrid = new0 EU_ResGridFrame();
	canvasGridFrame->AttachChild(resGrid);
	resGrid->SetAnchorHor(0.0f, 1.0f);
	resGrid->SetAnchorVer(0.0f, 1.0f);
	resGrid->SetAnchorParamVer(10.0, 10.0f);

	RenderView *renderView = new RenderView(rw, this);
	rw->SetName("ResGridView");
	Renderer *renderer = PX2_APP.CreateRenderer("ResGridView",
		renderView->GetHandle(), 0, 0, 100, 100, 0);
	rw->SetRenderer(renderer);
	rw->SetScreenSize(Sizef((float)100, (float)100));

	wxBoxSizer* bSizer57;
	bSizer57 = new wxBoxSizer(wxVERTICAL);
	bSizer57->Add(renderView, 1, wxEXPAND | wxTOP, 0);
	bSizer54->Add(bSizer57, 1, wxEXPAND, 0);

	this->SetSizer(bSizer54);
	this->Layout();
}
//----------------------------------------------------------------------------
ResGridView::~ResGridView()
{
}
//----------------------------------------------------------------------------