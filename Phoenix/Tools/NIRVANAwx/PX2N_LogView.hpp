// PX2N_LogView.hpp

#ifndef PX2N_LOGVIEW_HPP
#define PX2N_LOGVIEW_HPP

#include "PX2N_Pre.hpp"
#include "PX2N_LogTextCtrl.hpp"
#include "PX2EventHandler.hpp"

namespace NA
{

	class PX2wxAuiToolBar;

	class LogView : public wxWindow
	{
	public:
		LogView(wxWindow *parent);
		~LogView();

		void OnClear(wxCommandEvent& event);
		void OnTextEnter(wxCommandEvent& event);

		LogTextCtrl *GetLogTextCtrl() const;

	protected:
		DECLARE_EVENT_TABLE()

		PX2wxAuiToolBar *mToolBar;
		wxTextCtrl *mCommondTextCtrl;
		LogTextCtrl *mTextCtrl;
		int mToolbarClearID;
	};

}

#endif