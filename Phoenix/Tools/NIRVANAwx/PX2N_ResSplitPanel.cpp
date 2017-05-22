// PX2N_ResSplitPanel.cpp

#include "PX2N_ResSplitPanel.hpp"
#include "PX2N_ResTree.hpp"
#include "PX2N_RenderView.hpp"
#include "PX2GraphicsRoot.hpp"
#include "PX2EU_ResGridFrame.hpp"
#include "PX2N_Frame.hpp"
#include "PX2N_ResGridView.hpp"
using namespace NA;
using namespace PX2;

IMPLEMENT_DYNAMIC_CLASS(ResSplitPanel, wxPanel)
BEGIN_EVENT_TABLE(ResSplitPanel, wxPanel)
END_EVENT_TABLE()
//----------------------------------------------------------------------------
ResSplitPanel::ResSplitPanel(wxWindow* parent, bool useSplit, wxWindowID id,
	const wxPoint& pos, const wxSize& size, long style) 
	: wxPanel(parent, id, pos, size, style)
{
	wxBoxSizer* sizer;
	sizer = new wxBoxSizer(wxHORIZONTAL);

	if (useSplit)
	{
		mSplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_NOBORDER);
		mSplitter->Connect(wxEVT_IDLE, wxIdleEventHandler(ResSplitPanel::mSplitterOnIdle), NULL, this);
		mSplitter->SetMinimumPaneSize(200);
		mSplitter->SetSashGravity(0.2f);

		mLeftPanel = new wxPanel(mSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

		wxBoxSizer* leftSizer;
		leftSizer = new wxBoxSizer(wxHORIZONTAL);

		ResTree *resTree = new ResTree(mLeftPanel, true);
		leftSizer->Add(resTree, 1, wxEXPAND, 0);

		mLeftPanel->SetSizer(leftSizer);
		mLeftPanel->Layout();
		leftSizer->Fit(mLeftPanel);

		mRightPanel = new wxPanel(mSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

		ResGridView *gridView = new ResGridView(mRightPanel);
		wxBoxSizer* rightSizer;
		rightSizer = new wxBoxSizer(wxVERTICAL);
		rightSizer->Add(gridView, 1, wxEXPAND, 0);

		mRightPanel->SetSizer(rightSizer);
		mRightPanel->Layout();
		rightSizer->Fit(mRightPanel);

		mSplitter->SplitHorizontally(mLeftPanel, mRightPanel, 220);
		sizer->Add(mSplitter, 1, wxEXPAND, 0);

		if (mSplitter)
			mSplitter->UpdateSize();
	}
	else
	{
		ResTree *resTree = new ResTree(this, false);
		sizer->Add(resTree, 1, wxEXPAND, 0);
	}

	SetSizer(sizer);
	Layout();
}
//----------------------------------------------------------------------------
ResSplitPanel::~ResSplitPanel()
{
}
//----------------------------------------------------------------------------
ResSplitPanel::ResSplitPanel()
{
}
//----------------------------------------------------------------------------
