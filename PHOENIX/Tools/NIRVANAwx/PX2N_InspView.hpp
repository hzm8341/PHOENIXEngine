// PX2N_InspView.hpp

#ifndef PX2N_INSPVIEW_HPP
#define PX2N_INSPVIEW_HPP

#include "PX2N_Pre.hpp"
#include "PX2EventHandler.hpp"
#include "PX2wxAui.hpp"
#include "PX2Object.hpp"

namespace NA
{

	class ObjectInspector;

	class InspView : public wxWindow, public PX2::EventHandler
	{
	public:
		InspView(wxWindow *parent);
		~InspView();

		virtual void OnEvent(PX2::Event *event);
		void ChangeShowWindow(int windowType);

	protected:
		DECLARE_EVENT_TABLE()

		void _SetObject(PX2::Object *object);
		void _ChangeToWindow(std::string strTag, int userData = 0);

		PX2::ObjectPtr mObject;
		std::string mStrTag;
		wxBoxSizer *mCurSizer;
		PX2wxAuiToolBar *mInspTreeBar;
		ObjectInspector *mCurWindow;
	};

}

#endif