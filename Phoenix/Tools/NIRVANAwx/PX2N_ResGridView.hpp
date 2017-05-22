// PX2N_ResGridView.hpp

#ifndef PX2N_RESGRIDVIEW_HPP
#define PX2N_RESGRIDVIEW_HPP

#include "PX2N_Pre.hpp"

namespace NA
{

	class PX2wxAuiToolBar;

	class ResGridView : public wxWindow
	{
		DECLARE_DYNAMIC_CLASS(ProjView)

	public:
		ResGridView(wxWindow *parent);
		virtual ~ResGridView();

	protected:
		DECLARE_EVENT_TABLE()

		ResGridView();

		PX2wxAuiToolBar *mProjTreeBar;
	};
}

#endif