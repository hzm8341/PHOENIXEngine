// PX2N_TextView.cpp

#include "PX2N_TextView.hpp"
#include "PX2EU_Manager.hpp"
#include "PX2N_Frame.hpp"
#include "PX2EditorEventType.hpp"
#include "PX2ProjectEvent.hpp"
#include "PX2LogicES.hpp"
using namespace NA;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(NA::TextView, wxWindow)
BEGIN_EVENT_TABLE(TextView, wxWindow)
END_EVENT_TABLE()
//----------------------------------------------------------------------------
TextView::TextView()
{
}
//----------------------------------------------------------------------------
TextView::TextView(wxWindow *parent) :
wxWindow(parent, wxID_ANY),
mTextCtrl(0)
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

	N_Frame::MainFrame->AddTool(mProjTreeBar, "DataNIRVANAwx/images/icons/text/save.png", "n_Text_Save", "Save", 0);

	mProjTreeBar->Realize();

	bSizer55->Add(mProjTreeBar, 0, wxEXPAND | wxBOTTOM, 0);

	bSizer54->Add(bSizer55, 0, wxEXPAND, 0);

	mTextCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
		wxTE_MULTILINE | wxTE_PROCESS_TAB);

	wxBoxSizer* bSizer57;
	bSizer57 = new wxBoxSizer(wxVERTICAL);
	bSizer57->Add(mTextCtrl, 1, wxEXPAND | wxTOP, 0);
	bSizer54->Add(bSizer57, 1, wxEXPAND, 0);

	this->SetSizer(bSizer54);
	this->Layout();

	PX2_EW.ComeIn(this);
}
//----------------------------------------------------------------------------
TextView::~TextView()
{
}
//----------------------------------------------------------------------------
wxTextCtrl *TextView::GetTextCtrl()
{
	return mTextCtrl;
}
//-----------------------------------------------------------------------------
void TextView::OnEvent(Event *ent)
{
	if (EditorEventSpace::IsEqual(ent, EditorEventSpace::OpenContentRes))
	{
		std::string path = ent->GetData<std::string>();

		std::string outPath;
		std::string outBaseName;
		std::string outExtention;
		StringHelp::SplitFullFilename(path, outPath, outBaseName, outExtention);
		std::string filename = outBaseName + "." + outExtention;

		if ("lua" == outExtention || "xml" == outExtention ||
			"bat" == outExtention || "pkg" == outExtention ||
			"txt" == outExtention || "fx" == outExtention ||
			"px2proj" == outExtention)
		{
			mTextCtrl->LoadFile(path);
		}
	}
	else if (ProjectES::IsEqual(ent, ProjectES::SavedProject))
	{
		mTextCtrl->SaveFile();
	}
	else if (EditorEventSpace::IsEqual(ent, EditorEventSpace::SaveText))
	{
		mTextCtrl->SaveFile();
	}
	else if (LogicES::IsEqual(ent, LogicES::RefreshGeneratedScript))
	{
		mTextCtrl->Clear();
		const std::string &generatedScript = PX2_LOGICM.GetCurGeneratedScript();
		mTextCtrl->SetValue(generatedScript);
	}
}
//----------------------------------------------------------------------------