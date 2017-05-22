// PX2N_ResSplitPanel.hpp

#ifndef PX2N_RESSPLITPANEL_HPP
#define PX2N_RESSPLITPANEL_HPP

#include "PX2N_Pre.hpp"

namespace NA
{

	class ResSplitPanel : public wxPanel
	{
		DECLARE_DYNAMIC_CLASS(ResSplitPanel)

	public:
		ResSplitPanel(wxWindow* parent, bool useSplit, wxWindowID id = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxSize(500, 300), long style = wxTAB_TRAVERSAL);
		~ResSplitPanel();

		void mSplitterOnIdle(wxIdleEvent&)
		{
			//mSplitter->SetSashPosition(150);
			mSplitter->Disconnect(wxEVT_IDLE,
				wxIdleEventHandler(ResSplitPanel::mSplitterOnIdle), NULL, this);
		}

	protected:
		DECLARE_EVENT_TABLE()
		ResSplitPanel();

		wxSplitterWindow* mSplitter;
		wxPanel* mLeftPanel;
		wxPanel* mRightPanel;
	};

}

#endif