// PX2N_Frame_Menu.cpp

#include "PX2N_Frame.hpp"
#include "PX2Edit.hpp"
using namespace NA;
using namespace PX2;

//----------------------------------------------------------------------------
void N_Frame::AddTool(wxAuiToolBar *toolBar, const std::string &icon,
	const std::string &script, const std::string &helpStr, int type)
{
	int id = PX2_EDIT_GETID;

	wxItemKind itemKind = wxITEM_NORMAL;
	if (0 == type) itemKind = wxITEM_NORMAL;
	else if (1 == type) itemKind = wxITEM_CHECK;
	else if (2 == type) itemKind = wxITEM_RADIO;

	toolBar->AddTool(id, "", wxBitmap(icon, wxBITMAP_TYPE_PNG), helpStr,
		itemKind);

	Connect(id, wxEVT_COMMAND_TOOL_CLICKED,
		wxCommandEventHandler(N_Frame::OnCommondItem));

	toolBar->Realize();

	mIDScripts[id] = script;
}
//----------------------------------------------------------------------------
void N_Frame::AddToolChoose(wxAuiToolBar *toolBar,
	const std::string &script,
	const std::string &choose0,
	const std::string &choose1,
	const std::string &choose2,
	const std::string &choose3,
	const std::string &choose4)
{
	int id = PX2_EDIT_GETID;

	wxChoice* choice = new wxChoice(toolBar, id);
	if (!choose0.empty()) choice->AppendString(choose0);
	if (!choose1.empty()) choice->AppendString(choose1);
	if (!choose2.empty()) choice->AppendString(choose2);
	if (!choose3.empty()) choice->AppendString(choose3);
	if (!choose4.empty()) choice->AppendString(choose4);
	toolBar->AddControl(choice);
	choice->Select(0);

	Connect(id, wxEVT_COMMAND_CHOICE_SELECTED,
		wxCommandEventHandler(N_Frame::OnChooseItem));

	mIDScripts[id] = script;
}
//----------------------------------------------------------------------------
void N_Frame::AddToolSeparater(wxAuiToolBar *toolBar)
{
	toolBar->AddSeparator();
}
//----------------------------------------------------------------------------
void N_Frame::AddToolStretch(wxAuiToolBar *toolBar)
{
	toolBar->AddStretchSpacer();
}
//----------------------------------------------------------------------------