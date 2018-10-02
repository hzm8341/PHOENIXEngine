// PX2N_Frame_TimeLine.cpp

#include "PX2N_Frame.hpp"
#include "PX2N_DlgSetCurveVal.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2N_Man.hpp"
#include "PX2Edit.hpp"
using namespace NA;
using namespace PX2;

//----------------------------------------------------------------------------
void N_Frame::TimeLine_SelectCtrl_InValue()
{
	CurveCtrl *ctrl = PX2_EDIT.GetTimeLineEdit()->GetSelectedCurveCtrl();
	if (!ctrl) return;

	DlgSetCurveVal dlg(mTimeLineView);
	dlg.SetVal(ctrl->GetInVal());
	dlg.SetTitle(PX2_LM_EDITOR.GetValue("n_SetInValue"));
	dlg.SetLabel(PX2_LM_EDITOR.GetValue("n_NewInValue"));
	if (dlg.ShowModal() == wxID_OK)
	{
		float val = dlg.GetVal();
		ctrl->SetInVal(val);
	}
}
//----------------------------------------------------------------------------
void N_Frame::TimeLine_SelectCtrl_OutValue()
{
	CurveCtrl *ctrl = PX2_EDIT.GetTimeLineEdit()->GetSelectedCurveCtrl();
	if (!ctrl) return;

	DlgSetCurveVal dlg(mTimeLineView);
	dlg.SetVal(ctrl->GetOutVal().Z());
	dlg.SetTitle(PX2_LM_EDITOR.GetValue("n_SetOutValue"));
	dlg.SetLabel(PX2_LM_EDITOR.GetValue("n_NewOutValue"));
	if (dlg.ShowModal() == wxID_OK)
	{
		float val = dlg.GetVal();

		APoint outVal = ctrl->GetOutVal();
		outVal.Z() = val;
		ctrl->SetOutVal(outVal);
	}
}
//----------------------------------------------------------------------------