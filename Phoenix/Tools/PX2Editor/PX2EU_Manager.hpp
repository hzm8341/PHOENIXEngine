// PX2EU_Manager.hpp

#ifndef PX2EU_MANAGER_HPP
#define PX2EU_MANAGER_HPP

#include "PX2EditorPre.hpp"
#include "PX2Singleton_NeedNew.hpp"
#include "PX2UIMenu.hpp"
#include "PX2UIAuiFrame.hpp"
#include "PX2RenderWindow.hpp"
#include "PX2EventHandler.hpp"
#include "PX2Project.hpp"
#include "PX2Application.hpp"
#include "PX2EditParams.hpp"

namespace PX2
{

	class Canvas;
	class UIFrame;
	class UIMenu;
	class UICheckButton;
	class UIComboBox;
	
	class PX2_EDITOR_ITEM EU_Manager : public Singleton<EU_Manager>, public Visitor, public EventHandler
	{
	public:
		EU_Manager();
		virtual ~EU_Manager();

		bool Initlize(const std::string &tag);
		bool Initlize1(const std::string &tag);
		bool Terminate();
		const std::string &GetEditorTag() const;

		EditParams *GetEditParams();

		// windows
		void CreateUIWindowMain();
		RenderWindow *GetUIWindowMain();
		UIFrame *CreateMainFrame(Canvas *canvas, UIAuiFrame *&outAuiFrame);

		UIFrame *GetFrame_Main();

		// frames
		UIAuiBlockFrame *CreateFrame_Center();
		UIAuiBlockFrame *CreateFrame_Project(UIAuiBlockFrame *beforeCenterFrame, UIAuiBlockFrame *&outCenter);
		UIAuiBlockFrame *CreateFrame_Property(UIAuiBlockFrame *beforeCenterFrame, UIAuiBlockFrame *&outCenter);
		UIAuiBlockFrame *CreateFrame_Resource(UIAuiBlockFrame *beforeCenterFrame, UIAuiBlockFrame *&outCenter);

		// toolbar
		void CreateFrame_ToolBar();

		// status
		void CreateFrame_StatusBar();

		UIAuiBlockFrame *CreateUIAuiBlockFrame(UIAuiBlockFrame *parent,
			UILayoutPosType pos, const Sizef &size = Sizef(300.0f, 300.0f));

		UIAuiBlockFrame *CreateUIAuiBlockFrame2(UIAuiBlockFrame *parent,
			UILayoutPosType pos, UIAuiBlockFrame *&outCenter, 
			const Sizef &size = Sizef(300.0f, 300.0f));

		// welcome frame 
		void SetWelcomeFrame(UIFrame *frame);
		UIFrame *GetWelcomeFrame();

		void SetLogicCanvas(Canvas *logicCanvas);
		Canvas *GetLogicCanvas();

		// UserLeaveUp
		void ShowWindowUserLeaveUp(bool show);
		bool IsWindowUserLeaveUpShow() const;

		// InspectorView
		void SetInspectorView(int val);

		// ProjectTree
		void SetProjectTreeLevel(int level);

		virtual void Visit(Object *obj, int info);
		virtual void OnEvent(Event *event);

	protected:
		UICheckButton *CreateCheckBut(const std::string &name, const std::string &text);

		std::string mEditorUITag;
		Pointer0<UIFrame> mFrame_Main;
		UIAuiFramePtr mFrame_Content;
		UIFramePtr mFrame_ToolBar;
		Pointer0<UIFrame> mFrame_StatusBar;
		RenderWindowPtr mUserLeaveUpWindow;
		UIFramePtr mWelcomeFrame;
		CanvasPtr mLogicCanvas;
		EditParamsPtr mEditParams;

		// commonds
	public:
		void NewProject();
		void OpenProject();
		void SaveProject();
		void CloseProject();
		void NewScene();
		void OpenScene();
		void SaveScene();
		void SaveSceneAs();
		void CloseScene();
		void Exit();
		void Import();
		void Export();

		// tip
	public:
		void PlayTip(const std::string &title, const std::string &content);

		// menus
	public:
		enum EditMenuType
		{
			EMT_PROJTREE,
			EMT_SCENE,
			EMT_UI,
			EMT_BP,
			EMT_MAX_TYPE
		};
		void CreateEditMenu(const std::string &whereStr, const APoint &pos, EditMenuType menuType);
		EditMenuType GetEidtMenuType();

	protected:
		void AddAppItem(const std::string &whereStr, Application::MenuItem *itemParent, Application::MenuItem *item);

		EditMenuType mEditMenuType;

		// tool bar
	public:
		void AddTool(const std::string &whereStr, const std::string &icon, std::string &script, const std::string &helpStr = "", int type = 0);
		void AddToolChoose(const std::string &whereStr, const std::string &script,
			const std::string &choose0,
			const std::string &choose1 = "",
			const std::string &choose2 = "",
			const std::string &choose3 = "",
			const std::string &choose4 = "");
		void AddToolSeparater(const std::string &whereStr);
		void AddToolStretch(const std::string &whereStr);
	};

#define PX2EU_MAN EU_Manager::GetSingleton()

}

#endif