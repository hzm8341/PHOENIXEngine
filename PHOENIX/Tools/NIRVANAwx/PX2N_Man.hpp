// PX2N_Man.hpp

#ifndef PX2N_MAN_HPP
#define PX2N_MAN_HPP

#include "PX2EditorPre.hpp"
#include "PX2Singleton_NeedNew.hpp"
#include "PX2wxAui.hpp"
#include "PX2EffectableController.hpp"
#include "PX2Effectable.hpp"
using namespace NA;

namespace PX2
{

	class NirMan : public wxEvtHandler, public PX2::Singleton<NirMan>
	{
		DECLARE_EVENT_TABLE()

	public:
		NirMan();
		virtual ~NirMan();

		bool Initlize();
		bool Ternamate();

		// menu
	public:
		void SetCurMenu(wxMenu *menu);
		wxMenu *GetCurMenu();

		wxMenu *AddSubMenu(wxMenu *menu, const std::string &title);
		wxMenuItem *AddMenuItem(wxMenu *menu, const std::string &title,
			const std::string &script, const std::string &scriptParam);
		void AddSeparater(wxMenu *menu);

		void RefreshEffectableControllerModules(wxMenu *menu,
			EffectableController *eftCtrl);
		void CreateEffectableControllerModule(const std::string &typeStr);

	protected:
		wxMenu *mCurMenu;

		// toolbar
	public:
		void SetCurToolBar(PX2wxAuiToolBar *toolBar);
		PX2wxAuiToolBar *GetCurToolBar();

		void AddTool(const std::string &icon, std::string &script, const std::string &helpStr = "", int type = 0);
		void AddToolChoose(const std::string &script,
			const std::string &choose0,
			const std::string &choose1 = "",
			const std::string &choose2 = "",
			const std::string &choose3 = "",
			const std::string &choose4 = "");
		void AddToolSeparater();
		void AddToolStretch();

	protected:
		PX2wxAuiToolBar *mCurToolBar;

		// messagebox
	public:
		int MessageBox(const std::string &caption, const std::string &content, int type = 0);
	};

}

#endif