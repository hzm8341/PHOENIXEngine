// PX2N_MakingWindow.hpp

#ifndef PX2N_MAKINGWINDOW_HPP
#define PX2N_MAKINGWINDOW_HPP

#include "PX2EditorPre.hpp"
#include "PX2Object.hpp"
#include "PX2N_Pre.hpp"
#include "PX2EventHandler.hpp"

namespace NA
{

	class MakingWindow : public wxScrolled<wxWindow>, public PX2::EventHandler
	{
	public:
		MakingWindow(wxWindow *parent);
		~MakingWindow();

		void OnSize(wxSizeEvent& e);

		void SetObject(PX2::Object *object);

		virtual void OnEvent(PX2::Event *ent);

	protected:
		DECLARE_EVENT_TABLE()
		void ChangeToWindow(const std::string &str, int userData = 0);

		PX2::ObjectPtr mObject;
		std::string mCurWinStr;
		wxWindow *mCurWindow;
		wxSize mCurWindowOriginSize;
	};

}

#endif