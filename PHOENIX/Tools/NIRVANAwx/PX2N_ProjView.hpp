// PX2N_ProjView.hpp

#ifndef PX2N_PROJVIEW_HPP
#define PX2N_PROJVIEW_HPP

#include "PX2N_Pre.hpp"
#include "PX2N_ProjTree.hpp"
#include "PX2EditParams.hpp"
using namespace PX2;

namespace NA
{

	class PX2wxAuiToolBar;

	class ProjView : public wxWindow
	{
		DECLARE_DYNAMIC_CLASS(ProjView)

	public:
		ProjView(wxWindow *parent);
		virtual ~ProjView();

		ProjTree *GetProjTree();

	protected:
		DECLARE_EVENT_TABLE()

		ProjView();

		PX2wxAuiToolBar *mProjTreeBar;
		ProjTree *mProjTree;
		wxTextCtrl *mTextCtrl;
	};

}

#endif