// PX2N_DlgSetCurveVal.hpp

#ifndef PX2N_DLGSETCURVEVAL_HPP
#define PX2N_DLGSETCURVEVAL_HPP

#include "PX2N_Pre.hpp"

namespace NA
{

	class DlgSetCurveVal : public wxDialog
	{
	public:
		DlgSetCurveVal(wxWindow *parent);

		void SetLabel(std::string str);
		void SetVal(float val);
		float GetVal();

		void OnButton(wxCommandEvent& event);

	protected:
		wxStaticText *mLabel;
		wxTextCtrl *mVal;
		wxButton *mOK;
		wxButton *mCancel;

		DECLARE_EVENT_TABLE();
	};

}

#endif