// PX2N_InspView.cpp

#include "PX2N_InspView.hpp"
#include "PX2N_Define.hpp"
#include "PX2N_ObjectInspector.hpp"
#include "PX2Selection.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2EditEventType.hpp"
#include "PX2Edit.hpp"
#include "PX2EU_Manager.hpp"
#include "PX2GraphicsEventType.hpp"
#include "PX2N_Frame.hpp"
#include "PX2ProjectEvent.hpp"
#include "PX2EditorEventType.hpp"
using namespace NA;
using namespace PX2;

BEGIN_EVENT_TABLE(InspView, wxWindow)
END_EVENT_TABLE()

//----------------------------------------------------------------------------
InspView::InspView(wxWindow *parent) :
wxWindow(parent, wxID_ANY),
mCurWindow(0)
{
	wxBoxSizer* bSizer54;
	bSizer54 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer55;
	bSizer55 = new wxBoxSizer(wxVERTICAL);

	mInspTreeBar = new PX2wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_HORIZONTAL);
	mInspTreeBar->SetArtProvider(new PX2wxAuiToolBarArt(1));

	N_Frame::MainFrame->AddTool(mInspTreeBar, "DataNIRVANAwx/images/icons/inspector/property.png", "n_InspView_Property");
	N_Frame::MainFrame->AddTool(mInspTreeBar, "DataNIRVANAwx/images/icons/inspector/make.png", "n_InspView_Make");

	mInspTreeBar->Realize();

	bSizer55->Add(mInspTreeBar, 0, wxEXPAND | wxBOTTOM, 0);

	bSizer54->Add(bSizer55, 0, wxEXPAND, 0);

	mCurSizer = new wxBoxSizer(wxVERTICAL);
	mCurWindow = new ObjectInspector(this);
	mCurSizer->Add(mCurWindow, 1, wxEXPAND | wxTOP, 0);

	bSizer54->Add(mCurSizer, 1, wxEXPAND, 0);

	this->SetSizer(bSizer54);
	this->Layout();

	PX2_EW.ComeIn(this);

	SetBackgroundColour(Float3TowxColour(PX2EU_MAN.GetEditParams()->GetCurTheme()->Color_Page_Background));
	SetForegroundColour(Float3TowxColour(PX2EU_MAN.GetEditParams()->GetCurTheme()->Color_Page_Foreground));
}
//----------------------------------------------------------------------------
InspView::~InspView()
{
	if (mCurWindow)
	{
		delete mCurWindow;
		mCurWindow = 0;
	}
}
//----------------------------------------------------------------------------
void InspView::OnEvent(PX2::Event *ent)
{
	if (EditES::IsEqual(ent, EditES::AddSelect))
	{
		Object *obj = ent->GetData<Object*>();
		_SetObject(obj);
	}
	else if (EditES::IsEqual(ent, EditES::RemoveAllSelects))
	{
		_SetObject(0);
	}
	else if (ProjectES::IsEqual(ent, ProjectES::CloseProject))
	{
		_SetObject(0);
	}
	else if (EditorEventSpace::IsEqual(ent, EditorEventSpace::SetInspectorView))
	{
		int viewType = ent->GetData<int>();
		ChangeShowWindow(viewType);
	}
}
//----------------------------------------------------------------------------
void InspView::_SetObject(PX2::Object *obj)
{
	if (mObject == obj && obj)
		return;

	mObject = obj;

	if (mObject)
		_ChangeToWindow("Object");
	else
		_ChangeToWindow("");
}
//----------------------------------------------------------------------------
void InspView::_ChangeToWindow(std::string str, int userData)
{
	PX2_UNUSED(userData);

	if (mCurWindow)
	{
		mCurWindow->Show(false);
	}

	mStrTag = str;

	if ("Object" == str)
	{
		mCurWindow->SetObject(mObject);
		mCurWindow->Show(true);
	}
	else
	{
		mCurWindow->SetObject(0);
		mCurWindow->Show(false);
	}
}
//----------------------------------------------------------------------------
void InspView::ChangeShowWindow(int windowType)
{
	mCurWindow->ChangeShowWindow(windowType);
}
//----------------------------------------------------------------------------