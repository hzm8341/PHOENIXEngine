// PX2N_App.cpp

#include "PX2N_App.hpp"
#include "PX2N_Frame.hpp"
#include "PX2N_GeneralFrame.hpp"
#include "PX2EU_Manager.hpp"
#include "PX2EditEventData.hpp"
#include "PX2Edit.hpp"
#include "PX2EditEventType.hpp"
#include "PX2RenderWindow.hpp"
#include "PX2EditEventType.hpp"
#include "PX2Application.hpp"
#include "PX2EditorEventType.hpp"
#include "PX2Application.hpp"
#include "PX2N_Man.hpp"
using namespace PX2;
using namespace NA;

//-----------------------------------------------------------------------------
IMPLEMENT_APP(NA::N_App)
//-----------------------------------------------------------------------------
N_App::N_App()
{
}
//-----------------------------------------------------------------------------
N_App::~N_App()
{
}
//-----------------------------------------------------------------------------
bool N_App::OnInit()
{
	Application *app = new Application();
	PX2_UNUSED(app);

	PX2_APP.Initlize();
	PX2_EW.ComeIn(this);

	std::vector<std::string> plugins;
	plugins.push_back("BluePrint");
	PX2_APP.LoadPlugins(plugins);

	PX2_APP.Play(Application::PT_NONE);

	NirMan *nirMan = new0 NirMan();
	nirMan->Initlize();

	wxLog::SetLogLevel(0);
	wxImage::AddHandler(new wxBMPHandler());
	wxImage::AddHandler(new wxPNGHandler());
	wxImage::AddHandler(new wxGIFHandler());
	wxFileSystem::AddHandler(new wxArchiveFSHandler());
	wxXmlResource::Get()->InitAllHandlers();
	wxXmlResource::Get()->Load(wxT("DataNIRVANAwx/wxfbp/*.xrc"));	

	N_Frame *frame = CreateMainFrame();
	frame->Maximize();

#ifdef __WXMSW__
	frame->SetIcon(wxICON(aIcon));
#else
	frame->SetIcon(wxICON(aIcon));
#endif // __WXMSW__

	Edit *edit = new0 Edit();
	edit->Initlize("wx");

	frame->InitlizeAUI();

	edit->Initlize1("wx");

	frame->InitMainFrameItems();

	frame->Show(true);

	return true;
}
//-----------------------------------------------------------------------------
int N_App::OnExit()
{
	wxApp::OnExit();

	return 0;
}
//-----------------------------------------------------------------------------
void N_App::CleanUp()
{
	wxApp::CleanUp();

	PX2_EW.Shutdown(true);

	PX2EU_MAN.Terminate();

	std::vector<std::string> plugins;
	plugins.push_back("BluePrint");
	PX2_APP.ClosePlugins(plugins);

	NirMan *nirMan = NirMan::GetSingletonPtr();
	if (nirMan)
	{
		nirMan->Ternamate();
		delete0(nirMan);
		NirMan::Set(0);
	}

	PX2_EW.Shutdown(true);

	Edit *edit = Edit::GetSingletonPtr();
	if (edit)
	{
		edit->Terminate();

		delete0(edit);
		Edit::Set(0);
	}

	PX2_EW.GoOut(this);
	PX2_APP.Terminate();

	Application *app = Application::GetSingletonPtr();
	delete app;
	Application::Set(0);
}
//-----------------------------------------------------------------------------
void N_App::OnEvent(Event *event)
{
	if (EditorEventSpace::IsEqual(event, EditorEventSpace::N_PlayInWindow))
	{
		SimuApp(ST_APP);
		SimuApp(ST_SERVER);
	}
}
//-----------------------------------------------------------------------------
N_Frame *N_App::CreateMainFrame()
{
	int displayWidth, displayHeight;
	wxDisplaySize(&displayWidth, &displayHeight);

	std::string title = "NIRVANAwx";

	std::string renderTag = Renderer::GetRenderTag();
	title += renderTag;

#if defined(_WIN64) || defined(WIN64)
	title += "64";
#endif

#ifdef _DEBUG
	title += "D";
#endif

	N_Frame *mainFrame = new N_Frame(0, 0, wxDEFAULT_FRAME_STYLE);
	mainFrame->SetName("Main");
	mainFrame->Show(false);
	SetTopWindow(mainFrame);
	mainFrame->SetTitle(title);
	mainFrame->Center();

	return mainFrame;
}
//-----------------------------------------------------------------------------
void N_App::SimuApp(SimuType st)
{
	Project *proj = Project::GetSingletonPtr();
	if (!proj) return;

	const std::string &projName = proj->GetName();
	std::string renderTag = Renderer::GetRenderTag();
	if ("Dx9" == renderTag)
		renderTag = "";

	std::string exeName = "AppPlayer";
	if (ST_APP == st)
		exeName = "AppPlayer" + renderTag;
	else if (ST_SERVER == st)
		exeName = "ServerPlayer" + renderTag;

	std::string strCfg =
		std::string(" ") + "proj" + std::string("=") + projName;

	std::string appName;

#if defined(_WIN32) || defined(WIN32)

#ifdef _DEBUG
#if defined(_WIN64) || defined(WIN64)
	appName = exeName + "64D.exe" + std::string(" ") + strCfg;
#else
	appName = exeName + "D.exe" + std::string(" ") + strCfg;
#endif

#else

#if defined(_WIN64) || defined(WIN64)
	appName = exeName + "64.exe" + std::string(" ") + strCfg;
#else
	appName = exeName + ".exe" + std::string(" ") + strCfg;
#endif

#endif

	WinExec(appName.c_str(), SW_SHOW);

#endif
}
//-----------------------------------------------------------------------------