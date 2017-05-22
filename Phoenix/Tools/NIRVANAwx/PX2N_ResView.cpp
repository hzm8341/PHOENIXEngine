// PX2N_RenderView.cpp

#include "PX2N_ResView.hpp"
#include "PX2N_ResSplitPanel.hpp"
#include "PX2N_ResTree.hpp"
#include "PX2N_Define.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2Edit.hpp"
#include "PX2EU_Manager.hpp"
#include "PX2N_Frame.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2N_Frame.hpp"
using namespace NA;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(NA::ResView, wxWindow)
BEGIN_EVENT_TABLE(ResView, wxWindow)
END_EVENT_TABLE()
//----------------------------------------------------------------------------
ResView::ResView()
{
}
//----------------------------------------------------------------------------
ResView::ResView(wxWindow *parent) :
wxWindow(parent, -1)
{
	SetBackgroundColour(Float3TowxColour(PX2EU_MAN.GetEditParams()->GetCurTheme()->Color_Page_Background));
	SetForegroundColour(Float3TowxColour(PX2EU_MAN.GetEditParams()->GetCurTheme()->Color_Page_Foreground));

	wxBoxSizer* bSizer54;
	bSizer54 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer55;
	bSizer55 = new wxBoxSizer(wxVERTICAL);

	mResTreeBar = new PX2wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_HORIZONTAL);
	mResTreeBar->SetArtProvider(new PX2wxAuiToolBarArt(1));

	N_Frame::MainFrame->AddTool(mResTreeBar, "DataNIRVANAwx/images/icons/res/refresh.png", "n_ResView_Refresh");
	N_Frame::MainFrame->AddTool(mResTreeBar, "DataNIRVANAwx/images/icons/res/clear.png", "n_ResView_Clear");
	N_Frame::MainFrame->AddToolSeparater(mResTreeBar);

	mResTreeBar->Realize();

	bSizer55->Add(mResTreeBar, 0, wxEXPAND | wxBOTTOM, 0);

	bSizer54->Add(bSizer55, 0, wxEXPAND, 0);

	wxBoxSizer* bSizer56;
	bSizer56 = new wxBoxSizer(wxVERTICAL);

	mTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	bSizer56->Add(mTextCtrl, 0, wxEXPAND, 0);

	bSizer54->Add(bSizer56, 0, wxEXPAND, 0);

	wxBoxSizer* bSizer57;
	bSizer57 = new wxBoxSizer(wxVERTICAL);

	mSplitPanel = new ResSplitPanel(this, true);
	bSizer57->Add(mSplitPanel, 1, wxEXPAND | wxTOP, 0);

	bSizer54->Add(bSizer57, 1, wxEXPAND, 0);

	this->SetSizer(bSizer54);
	this->Layout();
}
//----------------------------------------------------------------------------
ResView::~ResView()
{
}
//----------------------------------------------------------------------------