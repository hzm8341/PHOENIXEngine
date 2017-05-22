// PX2N_LogTextCtrl.hpp

#ifndef PX2N_LOGTEXTCTRL_HPP
#define PX2N_LOGTEXTCTRL_HPP

#include "PX2N_Pre.hpp"
#include "PX2EventHandler.hpp"
#include "PX2Log.hpp"

namespace NA
{

	class LogTextCtrl : public wxTextCtrl, public PX2::LogHandler
	{
	public:
		LogTextCtrl(wxWindow *parent);
		virtual ~LogTextCtrl();

		virtual void Handle(const PX2::LogBuffer *logBuffer,
			const char *timeStamp);

	protected:
		DECLARE_EVENT_TABLE()
	};

}

#endif