// PX2N_CntView.hpp

#ifndef PX2N_CNTVIEW_HPP
#define PX2N_CNTVIEW_HPP

#include "PX2N_Pre.hpp"
#include "PX2EventHandler.hpp"
#include "PX2wxAui.hpp"
#include "PX2Object.hpp"
#include "PX2UDPServer.hpp"

namespace NA
{

	class ConnectView : public wxWindow, public PX2::EventHandler
	{
	public:
		ConnectView(wxWindow *parent);
		virtual ~ConnectView();

		static ConnectView *msConnectView;

		void OnToggleServer(wxCommandEvent& event);
		void OnConnector(wxCommandEvent& event);
		void OnSend(wxCommandEvent& event);
		void OnSyn(wxCommandEvent& event);
		void OnSynAll(wxCommandEvent& event);
		void OnSelected(wxListEvent& event);
		void OnUDPRefresh(wxCommandEvent& event);
		void OnTextEnter(wxCommandEvent& event);

		virtual void OnEvent(PX2::Event *event);

	protected:
		DECLARE_EVENT_TABLE()
		void _RefreshAddresses();

		PX2wxAuiToolBar *mToolBar;
		wxTextCtrl *mCommondTextCtrl;
		wxListCtrl *mListCtrl;
		int mSelectListIndex;
	};

}

#endif