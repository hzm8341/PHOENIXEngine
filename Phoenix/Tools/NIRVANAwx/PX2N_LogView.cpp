// PX2N_LogView.cpp

#include "PX2N_LogView.hpp"
#include "PX2N_Define.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2Log.hpp"
#include "PX2wxAui.hpp"
#include "PX2Edit.hpp"
#include "PX2N_Define.hpp"
#include "PX2EU_Manager.hpp"
#include "PX2EventWorld.hpp"
#include "PX2EditorEventType.hpp"
#include "PX2N_Frame.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2Edit.hpp"
using namespace NA;
using namespace PX2;

#define ID_LOGPANEL_CLEAR (wxID_HIGHEST+8001)
#define ID_LOGPANEL_COMMOND (wxID_HIGHEST+8002)

BEGIN_EVENT_TABLE(LogView, wxWindow)
EVT_TOOL(ID_LOGPANEL_CLEAR, LogView::OnClear)
EVT_TEXT_ENTER(ID_LOGPANEL_COMMOND, LogView::OnTextEnter)
END_EVENT_TABLE()

//-----------------------------------------------------------------------------
LogView::LogView(wxWindow *parent) :
wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER),
mToolBar(0),
mToolbarClearID(0)
{
	SetBackgroundColour(Float3TowxColour(PX2EU_MAN.GetEditParams()->GetCurTheme()->Color_Page_Background));
	SetForegroundColour(Float3TowxColour(PX2EU_MAN.GetEditParams()->GetCurTheme()->Color_Page_Foreground));

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer(wxVERTICAL);

	// tool bar
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer(wxVERTICAL);

	mToolBar = new PX2wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_HORIZONTAL);
	mToolBar->SetArtProvider(new PX2wxAuiToolBarArt(1));

	mToolbarClearID = PX2_EDIT_GETID;
	mToolBar->AddTool(mToolbarClearID, "",
		wxBitmap("DataNIRVANAwx/images/icons/console/clear.png", wxBITMAP_TYPE_PNG), "Clear",
		wxITEM_NORMAL);

	Connect(mToolbarClearID, wxEVT_COMMAND_TOOL_CLICKED,
		wxCommandEventHandler(LogView::OnClear));


	mToolBar->Realize();

	bSizer10->Add(mToolBar, 1, wxEXPAND, 0);

	bSizer9->Add(bSizer10, 0, wxEXPAND | wxALIGN_CENTER_HORIZONTAL, 0);

	// commond text
	wxBoxSizer* bSizer60;
	bSizer60 = new wxBoxSizer(wxVERTICAL);

	mCommondTextCtrl = new wxTextCtrl(this, ID_LOGPANEL_COMMOND, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	bSizer60->Add(mCommondTextCtrl, 1, wxEXPAND | wxTOP | wxBOTTOM, 0);

	mCommondTextCtrl->SetBackgroundColour(Float3TowxColour(PX2EU_MAN.GetEditParams()->GetCurTheme()->Color_Page_Background));
	mCommondTextCtrl->SetForegroundColour(Float3TowxColour(PX2EU_MAN.GetEditParams()->GetCurTheme()->Color_Page_Foreground));

	bSizer9->Add(bSizer60, 0, wxEXPAND, 0);

	// log text
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer(wxVERTICAL);

	mTextCtrl = new LogTextCtrl(this);
	bSizer11->Add(mTextCtrl, 1, wxALL | wxEXPAND, 0);

	bSizer9->Add(bSizer11, 1, wxEXPAND, 0);

	SetSizer(bSizer9);
	Layout();

	SetBackgroundColour(wxColour(255, 255, 255));
}
//-----------------------------------------------------------------------------
LogView::~LogView()
{
}
//-----------------------------------------------------------------------------
void LogView::OnClear(wxCommandEvent& event)
{
	PX2_UNUSED(event);

	mTextCtrl->Clear();
}
//-----------------------------------------------------------------------------
void LogView::OnTextEnter(wxCommandEvent& event)
{
	if (event.GetEventObject() == mCommondTextCtrl)
	{
		std::string commondStr = mCommondTextCtrl->GetValue().ToStdString();

		PX2_SC_LUA->CallString(commondStr.c_str());

		mTextCtrl->SetDefaultStyle(wxTextAttr(*wxBLUE, wxColour(240, 240, 240)));
		mTextCtrl->AppendText(commondStr + "\n");
	}
}
//-----------------------------------------------------------------------------
LogTextCtrl *LogView::GetLogTextCtrl() const
{
	return mTextCtrl;
}
//-----------------------------------------------------------------------------