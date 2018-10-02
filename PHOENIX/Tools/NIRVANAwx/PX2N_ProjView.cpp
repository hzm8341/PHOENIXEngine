// PX2N_RenderView.cpp

#include "PX2N_ProjView.hpp"
#include "PX2N_ProjTree.hpp"
#include "PX2N_Define.hpp"
#include "PX2Project.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2Edit.hpp"
#include "PX2EU_Manager.hpp"
#include "PX2wxAui.hpp"
#include "PX2N_Frame.hpp"
using namespace NA;

IMPLEMENT_DYNAMIC_CLASS(NA::ProjView, wxWindow)
BEGIN_EVENT_TABLE(ProjView, wxWindow)
END_EVENT_TABLE()
//----------------------------------------------------------------------------
ProjView::ProjView()
{
}
//----------------------------------------------------------------------------
ProjView::ProjView(wxWindow *parent) :
wxWindow(parent, wxID_ANY),
mProjTree(0)
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

	N_Frame::MainFrame->AddTool(mProjTreeBar, "DataNIRVANAwx/images/icons/project/children.png", "n_Project_Children", "Children", 2);
	N_Frame::MainFrame->AddTool(mProjTreeBar, "DataNIRVANAwx/images/icons/project/control.png", "n_Project_Control", "Control", 2);
	N_Frame::MainFrame->AddTool(mProjTreeBar, "DataNIRVANAwx/images/icons/project/material.png", "n_Project_Material", "Material", 2);
	N_Frame::MainFrame->AddTool(mProjTreeBar, "DataNIRVANAwx/images/icons/project/detail.png", "n_Project_Detail", "Detail", 2);

	mProjTreeBar->Realize();

	bSizer55->Add(mProjTreeBar, 0, wxEXPAND | wxBOTTOM, 0);

	bSizer54->Add(bSizer55, 0, wxEXPAND, 0);

	wxBoxSizer* bSizer56;
	bSizer56 = new wxBoxSizer(wxVERTICAL);

	mTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	bSizer56->Add(mTextCtrl, 0, wxEXPAND, 0);

	bSizer54->Add(bSizer56, 0, wxEXPAND, 0);

	wxBoxSizer* bSizer57;
	bSizer57 = new wxBoxSizer(wxVERTICAL);

	mProjTree = new ProjTree(this);
	bSizer57->Add(mProjTree, 1, wxEXPAND | wxTOP, 0);

	bSizer54->Add(bSizer57, 1, wxEXPAND, 0);

	this->SetSizer(bSizer54);
	this->Layout();
}
//----------------------------------------------------------------------------
ProjView::~ProjView()
{
}
//----------------------------------------------------------------------------
ProjTree *ProjView::GetProjTree()
{
	return mProjTree;
}
//----------------------------------------------------------------------------