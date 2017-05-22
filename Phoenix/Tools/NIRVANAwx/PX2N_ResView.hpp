// PX2N_ResView.hpp

#ifndef PX2N_RESVIEW_HPP
#define PX2N_RESVIEW_HPP

#include "PX2N_Pre.hpp"
#include "PX2N_GeneralWindow.hpp"
#include "PX2N_RenderView.hpp"
#include "PX2N_ResSplitPanel.hpp"
#include "PX2RenderWindow.hpp"
#include "PX2wxAui.hpp"

namespace NA
{

	class ResView : public wxWindow
	{
		DECLARE_DYNAMIC_CLASS(ResView)

	public:
		ResView(wxWindow *parent);
		virtual ~ResView();

	protected:
		DECLARE_EVENT_TABLE()
		ResView();

		PX2wxAuiToolBar *mResTreeBar;
		wxSplitterWindow *mSplitter;

		ResSplitPanel *mSplitPanel;
		wxTextCtrl *mTextCtrl;

		void Splitter1OnIdle(wxIdleEvent&)
		{
			mSplitter->SetSashPosition(120);
			mSplitter->Disconnect(wxEVT_IDLE, wxIdleEventHandler(ResView::Splitter1OnIdle), NULL, this);
		}
	};

}

#endif