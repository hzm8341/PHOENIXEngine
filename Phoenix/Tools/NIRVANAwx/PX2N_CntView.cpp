// PX2N_CntView.cpp

#include "PX2N_CntView.hpp"
#include "PX2N_Frame.hpp"
#include "PX2EU_Manager.hpp"
#include "PX2Edit.hpp"
#include "PX2Application.hpp"
#include "PX2EngineNetDefine.hpp"
#include "PX2EngineNetEvent.hpp"
#include "PX2StringTokenizer.hpp"
using namespace NA;
using namespace PX2;

#define ID_CONNECTPANEL_TOGGLESERVER (wxID_HIGHEST+8101)
#define ID_CONNECTPANEL_CONNECT (wxID_HIGHEST+8102)
#define ID_CONNECTPANEL_SEND (wxID_HIGHEST+8103)
#define ID_CONNECTPANEL_SYNALL (wxID_HIGHEST+8104)
#define ID_CONNECTPANEL_SYN (wxID_HIGHEST+8105)
#define ID_CONNECTPANEL_UDREFRESH (wxID_HIGHEST+8106)
#define ID_TEXT_CTRL (wxID_HIGHEST+8111)
#define ID_LIST_CTRL (wxID_HIGHEST+8120)

BEGIN_EVENT_TABLE(ConnectView, wxWindow)
EVT_TOOL(ID_CONNECTPANEL_TOGGLESERVER, ConnectView::OnToggleServer)
EVT_TOOL(ID_CONNECTPANEL_CONNECT, ConnectView::OnConnector)
EVT_TOOL(ID_CONNECTPANEL_SEND, ConnectView::OnSend)
EVT_TOOL(ID_CONNECTPANEL_SYN, ConnectView::OnSyn)
EVT_TOOL(ID_CONNECTPANEL_SYNALL, ConnectView::OnSynAll)
EVT_LIST_ITEM_SELECTED(ID_LIST_CTRL, ConnectView::OnSelected)
EVT_TOOL(ID_CONNECTPANEL_UDREFRESH, ConnectView::OnUDPRefresh)
EVT_TEXT_ENTER(ID_TEXT_CTRL, ConnectView::OnTextEnter)
END_EVENT_TABLE()

//----------------------------------------------------------------------------
ConnectView *ConnectView::msConnectView = 0;
//----------------------------------------------------------------------------
ConnectView::ConnectView(wxWindow *parent) :
wxWindow(parent, wxID_ANY),
mListCtrl(0),
mSelectListIndex(-1)
{
	msConnectView = this;

	SetBackgroundColour(Float3TowxColour(
		PX2EU_MAN.GetEditParams()->GetCurTheme()->Color_Page_Background));
	SetForegroundColour(Float3TowxColour(
		PX2EU_MAN.GetEditParams()->GetCurTheme()->Color_Page_Foreground));

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer(wxVERTICAL);

	// tool bar
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer(wxVERTICAL);

	mToolBar = new PX2wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_HORIZONTAL);
	mToolBar->SetArtProvider(new PX2wxAuiToolBarArt(1));

	mToolBar->AddTool(ID_CONNECTPANEL_TOGGLESERVER, wxBitmap("DataNIRVANAwx/images/icons/connect/start.png", wxBITMAP_TYPE_PNG),
		wxBitmap("DataNIRVANAwx/images/icons/connect/stop.png", wxBITMAP_TYPE_PNG), true);
	mToolBar->AddSeparator();

	mToolBar->AddTool(ID_CONNECTPANEL_CONNECT, wxBitmap("DataNIRVANAwx/images/icons/connect/connect.png", wxBITMAP_TYPE_PNG),
		wxBitmap("DataNIRVANAwx/images/icons/connect/stop.png", wxBITMAP_TYPE_PNG), false);

	mToolBar->AddTool(ID_CONNECTPANEL_SEND, "",
		wxBitmap("DataNIRVANAwx/images/icons/connect/send.png", wxBITMAP_TYPE_PNG),
		"SendMsg", wxITEM_NORMAL);

	mToolBar->AddStretchSpacer();
	mToolBar->AddTool(ID_CONNECTPANEL_SYN, "",
		wxBitmap("DataNIRVANAwx/images/icons/connect/synchronize.png", wxBITMAP_TYPE_PNG),
		"Syn", wxITEM_NORMAL);
	mToolBar->AddTool(ID_CONNECTPANEL_SYNALL, "",
		wxBitmap("DataNIRVANAwx/images/icons/connect/synchronizeall.png", wxBITMAP_TYPE_PNG),
		"SynAll", wxITEM_NORMAL);

	mToolBar->Realize();

	bSizer10->Add(mToolBar, 1, wxEXPAND, 0);

	bSizer9->Add(bSizer10, 0, wxEXPAND | wxALIGN_CENTER_HORIZONTAL, 0);

	// commond text
	wxBoxSizer* bSizer60;
	bSizer60 = new wxBoxSizer(wxVERTICAL);

	mCommondTextCtrl = new wxTextCtrl(this, ID_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	bSizer60->Add(mCommondTextCtrl, 1, wxEXPAND | wxTOP | wxBOTTOM, 0);

	mCommondTextCtrl->SetBackgroundColour(Float3TowxColour(PX2EU_MAN.GetEditParams()->GetCurTheme()->Color_Page_Background));
	mCommondTextCtrl->SetForegroundColour(Float3TowxColour(PX2EU_MAN.GetEditParams()->GetCurTheme()->Color_Page_Foreground));

	bSizer9->Add(bSizer60, 0, wxEXPAND, 0);

	// list
	mListCtrl = new wxListCtrl(this, ID_LIST_CTRL, wxDefaultPosition, wxDefaultSize,
		wxLC_REPORT);

	wxListItem itemCol;
	itemCol.SetText(PX2_LM_EDITOR.GetValue("n_Name"));
	itemCol.SetAlign(wxLIST_FORMAT_LEFT);
	mListCtrl->InsertColumn(0, itemCol);

	itemCol.SetText(PX2_LM_EDITOR.GetValue("n_IP"));
	itemCol.SetAlign(wxLIST_FORMAT_LEFT);
	mListCtrl->InsertColumn(1, itemCol);

	itemCol.SetText(PX2_LM_EDITOR.GetValue("n_State"));
	itemCol.SetAlign(wxLIST_FORMAT_LEFT);
	mListCtrl->InsertColumn(2, itemCol);

	itemCol.SetText(PX2_LM_EDITOR.GetValue("n_Property"));
	itemCol.SetAlign(wxLIST_FORMAT_LEFT);
	mListCtrl->InsertColumn(3, itemCol);

	mListCtrl->SetColumnWidth(0, 100);
	mListCtrl->SetColumnWidth(1, 150);

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer(wxVERTICAL);

	bSizer11->Add(mListCtrl, 1, wxALL | wxEXPAND, 0);

	bSizer9->Add(bSizer11, 1, wxEXPAND, 0);

	// last
	this->SetSizer(bSizer9);
	this->Layout();

	PX2_EW.ComeIn(this);
}
//----------------------------------------------------------------------------
ConnectView::~ConnectView()
{
	EventWorld *ew = EventWorld::GetSingletonPtr();
	if (ew)
		ew->GoOut(this);
}
//----------------------------------------------------------------------------
void ConnectView::OnToggleServer(wxCommandEvent& event)
{
	EngineServer *es = PX2_APP.GetEngineServer();
	if (es)
	{
		if (!es->IsStarted())
			es->Start();
		else
			es->Shutdown();
	}
}
//----------------------------------------------------------------------------
void ConnectView::OnConnector(wxCommandEvent& event)
{
	UDPServer *udpServer = PX2_APP.GetEngineUDPServerEditor();
	if (udpServer)
	{
		UDPNetInfo *info = PX2_APP.GetUDPNetInfo(mSelectListIndex);
		if (info)
		{
			SocketAddress skAddr(info->IP, EngineUDPPortClient);
			std::string buf = CMD_EngineUDPConnectMeStr;
			udpServer->GetSocket().SendTo(buf.c_str(), (int)buf.length(),
				skAddr);
		}
	}
}
//----------------------------------------------------------------------------
void ConnectView::OnSend(wxCommandEvent& event)
{
	UDPServer *udpServer = PX2_APP.GetEngineUDPServerEditor();
	if (udpServer)
	{
		UDPNetInfo *info = PX2_APP.GetUDPNetInfo(mSelectListIndex);
		if (info)
		{
			SocketAddress skAddr(info->IP, EngineUDPPortClient);
			std::string buf = mCommondTextCtrl->GetValue();
			udpServer->GetSocket().SendTo(buf.c_str(), (int)buf.length(),
				skAddr);
		}
	}
}
//----------------------------------------------------------------------------
void ConnectView::OnSyn(wxCommandEvent& event)
{
	Project *proj = Project::GetSingletonPtr();
	if (!proj)
		return;
	const std::string &projName = proj->GetName();
	PX2_APP.SaveProject();

	UDPServer *udpServer = PX2_APP.GetEngineUDPServerEditor();
	if (udpServer)
	{
		UDPNetInfo *info = PX2_APP.GetUDPNetInfo(mSelectListIndex);
		if (info)
		{
			SocketAddress skAddr(info->IP, EngineUDPPortClient);

			std::string strBuf = CMD_PushProject + " " + projName;
			udpServer->GetSocket().SendTo(strBuf.c_str(), (int)strBuf.length(),
				skAddr);
		}
	}
}
//----------------------------------------------------------------------------
void ConnectView::OnSynAll(wxCommandEvent& event)
{
	Project *proj = Project::GetSingletonPtr();
	if (!proj)
		return;
	const std::string &projName = proj->GetName();
	PX2_APP.SaveProject();

	UDPServer *udpServer = PX2_APP.GetEngineUDPServerEditor();
	if (udpServer)
	{
		int numUDPNetInfo = PX2_APP.GetNumUDPNetInfo();
		for (int i = 0; i < numUDPNetInfo; i++)
		{
			UDPNetInfo *info = PX2_APP.GetUDPNetInfo(i);
			SocketAddress skAddr(info->IP, EngineUDPPortClient);

			std::string strBuf = CMD_PushProject + " " + projName;
			udpServer->GetSocket().SendTo(strBuf.c_str(), (int)strBuf.length(),
				skAddr);
		}
	}
}
//----------------------------------------------------------------------------
void ConnectView::OnSelected(wxListEvent& event)
{
	if (mListCtrl->GetWindowStyle() & wxLC_REPORT)
	{
		mSelectListIndex = event.m_itemIndex;
	}
}
//----------------------------------------------------------------------------
void ConnectView::OnUDPRefresh(wxCommandEvent& event)
{
	PX2_APP.ClearUDPNetInfo();
}
//----------------------------------------------------------------------------
void ConnectView::OnTextEnter(wxCommandEvent& event)
{
	OnSend(event);
}
//----------------------------------------------------------------------------
void ConnectView::_RefreshAddresses()
{
	if (mListCtrl)
	{
		mListCtrl->DeleteAllItems();

		int numUDPNetInfos = PX2_APP.GetNumUDPNetInfo();
		for (int i = 0; i < numUDPNetInfos; i++)
		{
			UDPNetInfo *info = PX2_APP.GetUDPNetInfo(i);

			int index = mListCtrl->InsertItem(i, info->Name);
			mListCtrl->SetItem(index, 1, info->IP);
		}
	}
}
//----------------------------------------------------------------------------
void ConnectView::OnEvent(Event *event)
{
	if (EngineNetES::IsEqual(event, EngineNetES::EngineClientUDPInfoChanged))
	{
		_RefreshAddresses();
	}
}
//----------------------------------------------------------------------------