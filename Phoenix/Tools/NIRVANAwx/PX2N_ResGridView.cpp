// PX2N_ResGridView.cpp

#include "PX2N_ResGridView.hpp"
#include "PX2EU_Manager.hpp"
#include "PX2N_Frame.hpp"
#include "PX2EU_ResGridFrame.hpp"
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
	SetBackgroundColour(Float3TowxColour(PX2EU_MAN.GetEditParams()->GetCurTheme()->Color_Page_Background));
	SetForegroundColour(Float3TowxColour(PX2EU_MAN.GetEditParams()->GetCurTheme()->Color_Page_Foreground));

	wxBoxSizer* bSizer54;
	bSizer54 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer55;
	bSizer55 = new wxBoxSizer(wxVERTICAL);

	mProjTreeBar = new PX2wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_HORIZONTAL);
	mProjTreeBar->SetArtProvider(new PX2wxAuiToolBarArt(1));
	N_Frame::MainFrame->AddTool(mProjTreeBar, "DataNIRVANAwx/images/icons/res/openin.png", "n_ResView_OpenIn", "OpenIn", 0);
	N_Frame::MainFrame->AddTool(mProjTreeBar, "DataNIRVANAwx/images/icons/res/openout.png", "n_ResView_OpenOut", "OpenOut", 0);
	N_Frame::MainFrame->AddToolStretch(mProjTreeBar);
	N_Frame::MainFrame->AddTool(mProjTreeBar, "DataNIRVANAwx/images/icons/res/up.png", "n_ResView_Up", "Up", 0);
	N_Frame::MainFrame->AddTool(mProjTreeBar, "DataNIRVANAwx/images/icons/res/down.png", "n_ResView_Down", "Down", 0);

	mProjTreeBar->Realize();

	bSizer55->Add(mProjTreeBar, 0, wxEXPAND | wxBOTTOM, 0);

	bSizer54->Add(bSizer55, 0, wxEXPAND, 0);

	RenderWindow *rw = new0 RenderWindow();
	rw->SetName("ResGridRenderWindow");
	PX2_GR.AddRenderWindow("ResGridRenderWindow", rw);

	Canvas *canvas = new0 Canvas();
	canvas->SetName("ResGridCanvas");
	rw->SetMainCanvas(canvas);
	canvas->SetClearFlag(true, true, true);
	canvas->SetClearColor(Float4::MakeColor(51, 51, 51, 51));
	canvas->CreateUICameraNode();

	EU_ResGridFrame *resGrid = new0 EU_ResGridFrame();
	canvas->AttachChild(resGrid);
	resGrid->SetAnchorHor(0.0f, 1.0f);
	resGrid->SetAnchorVer(0.0f, 1.0f);

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