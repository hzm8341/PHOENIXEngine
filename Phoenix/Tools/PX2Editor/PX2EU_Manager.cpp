// PX2EU_Manager.cpp

#include "PX2EU_Manager.hpp"
#include "PX2Application.hpp"
#include "PX2GraphicsRoot.hpp"
#include "PX2Canvas.hpp"
#include "PX2UIMenu.hpp"
#include "PX2UIAuiBlockFrame.hpp"
#include "PX2UITabFrame.hpp"
#include "PX2UICheckButton.hpp"
#include "PX2EU_ProjectFrame.hpp"
#include "PX2EU_ResFrame.hpp"
#include "PX2EU_InspectorFrame.hpp"
#include "PX2EU_ConsoleFrame.hpp"
#include "PX2EU_CreateFrame.hpp"
#include "PX2EU_StageFrame.hpp"
#include "PX2EU_TimeLineFrame.hpp"
#include "PX2EU_SimuFrame.hpp"
#include "PX2EU_ResGridItem.hpp"
#include "PX2EU_Manager.hpp"
#include "PX2EU_StatusBar.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2EditEventType.hpp"
#include "PX2EditEventData.hpp"
#include "PX2RenderWindow.hpp"
#include "PX2GraphicsRoot.hpp"
#include "PX2EditorEventType.hpp"
#include "PX2ProjectEvent.hpp"
#include "PX2Project.hpp"
#include "PX2SelectionManager.hpp"
#include "PX2Log.hpp"
#include "PX2UISkinManager.hpp"
#include "PX2UIWebFrame.hpp"
#include "PX2EditorEventData.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
EU_Manager::EU_Manager()
{
}
//----------------------------------------------------------------------------
EU_Manager::~EU_Manager()
{
}
//----------------------------------------------------------------------------
bool EU_Manager::Initlize(const std::string &tag)
{
	mEditorUITag = tag;

	PX2_EW.ComeIn(this);

	PX2_SC_LUA->SetUserTypePointer("PX2EU_MAN", "EU_Manager", this);

	mEditParams = new0 EditParams();
	bool loaded = mEditParams->Load("DataNIRVANAwx/config/config.xml");
	mEditParams->SetCurTheme(mEditParams->GetCurThemeTypeStr());

	if ("2" == tag)
	{
		PX2_SC_LUA->CallFileFunction("DataNIRVANA2/scripts/start.lua", "naPreStart");
		PX2_SC_LUA->CallFileFunction("DataNIRVANA2/scripts/start.lua", "naStart");
	}
	else if ("wx" == tag)
	{
		PX2_SC_LUA->CallFileFunction("DataNIRVANAwx/scripts/start.lua", "naPreStart");
	}

	return true;
}
//----------------------------------------------------------------------------
bool EU_Manager::Initlize1(const std::string &tag)
{
	if ("wx" == tag)
	{
		PX2_SC_LUA->CallFileFunction("DataNIRVANAwx/scripts/start.lua", "naStart");
	}

	return true;
}
//----------------------------------------------------------------------------
bool EU_Manager::Terminate()
{
	if (mEditParams)
		mEditParams->Save("DataNIRVANAwx/config/config.xml");
	mEditParams = 0;

	PX2_EW.GoOut(this);

	EU_ResGridItem::sLastSelectItemBut = 0;

	mFrame_Main = 0;
	mFrame_ToolBar = 0;
	mFrame_StatusBar = 0;
	mLogicCanvas = 0;

	return true;
}
//----------------------------------------------------------------------------
const std::string &EU_Manager::GetEditorTag() const
{
	return mEditorUITag;
}
//----------------------------------------------------------------------------
EditParams *EU_Manager::GetEditParams()
{
	return mEditParams;
}
//----------------------------------------------------------------------------
void EU_Manager::NewProject()
{
	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::N_NewProject);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EU_Manager::OpenProject()
{
	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::N_OpenProject);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EU_Manager::SaveProject()
{
	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::N_SaveProject);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EU_Manager::CloseProject()
{
	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::N_CloseProject);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EU_Manager::NewScene()
{
	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::N_NewScene);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EU_Manager::OpenScene()
{
	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::N_OpenScene);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EU_Manager::SaveScene()
{
	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::N_SaveScene);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EU_Manager::SaveSceneAs()
{
	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::N_SaveSceneAs);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EU_Manager::CloseScene()
{
	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::N_CloseScene);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EU_Manager::Exit()
{
	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::N_Exit);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EU_Manager::Import()
{
	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::N_Import);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EU_Manager::Export()
{
	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::N_Export);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EU_Manager::PlayTip(const std::string &title, const std::string &content)
{
	EED_Tip tipData;
	tipData.Title = title;
	tipData.Content = content;

	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::N_PlayTip);
	ent->SetData(tipData);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EU_Manager::CreateEditMenu(const std::string &whereStr, const APoint &pos, EditMenuType menuType)
{
	mEditMenuType = menuType;

	Object *obj = PX2_SELECTM_E->GetFirstObject();
	Controlledable *selectControlledable = DynamicCast<Controlledable>(obj);
	Movable *selectedMovable = DynamicCast<Movable>(obj);
	EffectableController *selectEffectableCtrl = DynamicCast<EffectableController>(obj);
	EffectModule *selectEffectModule = DynamicCast<EffectModule>(obj);
	Node *selectedNode = DynamicCast<Node>(obj);
	Controller *ctrl = DynamicCast<Controller>(obj);
	InterpCurveController *interpCurveCtrl = DynamicCast<InterpCurveController>(obj);

	PX2_APP.Menu_Edit_Begin(whereStr, "Edit");

	if (selectedMovable || selectEffectableCtrl)
	{
		PX2_APP.Menu_Edit_AddSubItem(whereStr, "Edit", "Create", PX2_LM_EDITOR.V("n_Create"));
	}
	
	if (selectedNode)
	{
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreate", "Node", PX2_LM_EDITOR.V("n_Node"), "n_Create_Node");

		PX2_APP.Menu_Edit_AddSubItem(whereStr, "EditCreate", "Geometry", PX2_LM_EDITOR.V("n_Geometry"));
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateGeometry", "Plane", PX2_LM_EDITOR.V("n_Plane"), "n_Create_Geometry_Plane");
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateGeometry", "Box", PX2_LM_EDITOR.V("n_Box"), "n_Create_Geometry_Box");
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateGeometry", "Sphere", PX2_LM_EDITOR.V("n_Sphere"), "n_Create_Geometry_Sphere");

		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreate", "CameraNode", PX2_LM_EDITOR.V("n_Camera"), "n_Create_Camera");

		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreate", "Terrain", PX2_LM_EDITOR.V("n_Terrain"), "n_Create_Terrain");

		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreate", "SkyBox", PX2_LM_EDITOR.V("n_SkyBox"), "n_Create_SkyBox");

		PX2_APP.Menu_Edit_AddSubItem(whereStr, "EditCreate", "Effect", PX2_LM_EDITOR.V("n_Effect"));
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateEffect", "Billboard", PX2_LM_EDITOR.V("n_Billboard"), "n_Create_Billboard");
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateEffect", "Particle", PX2_LM_EDITOR.V("n_Particle"), "n_Create_Particle");
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateEffect", "Beam", PX2_LM_EDITOR.V("n_Beam"), "n_Create_Beam");
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateEffect", "Ribbon", PX2_LM_EDITOR.V("n_Ribbon"), "n_Create_Ribbon");
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateEffect", "Sound", PX2_LM_EDITOR.V("n_Sound"), "n_Create_Sound");

		PX2_APP.Menu_Edit_AddSubItem(whereStr, "EditCreate", "UI", PX2_LM_EDITOR.V("n_UI"));
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateUI", "UIFrame", PX2_LM_EDITOR.V("n_UIFrame"), "n_Create_UIFrame");
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateUI", "UIFPicBox", PX2_LM_EDITOR.V("n_UIFPicBox"), "n_Create_UIFPicBox");
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateUI", "UIFText", PX2_LM_EDITOR.V("n_UIFText"), "n_Create_UIFPicBox");
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateUI", "UIButton", PX2_LM_EDITOR.V("n_UIButton"), "n_Create_UIButton");
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateUI", "UICheckBox", PX2_LM_EDITOR.V("n_UICheckButton"), "n_Create_UICheckButton");
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateUI", "UIComboBox", PX2_LM_EDITOR.V("n_UIComboBox"), "n_Create_UIComboBox");
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateUI", "UIEditBox", PX2_LM_EDITOR.V("n_UIEditBox"), "n_Create_UIEditBox");

		PX2_APP.Menu_Edit_AddItemSeparater(whereStr, "EditCreateUI");
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateUI", "UIPicBox", PX2_LM_EDITOR.V("n_UIPicBox"), "n_Create_UIPicBox");
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateUI", "UIText", PX2_LM_EDITOR.V("n_UIText"), "n_Create_UIText");

		PX2_APP.Menu_Edit_AddItemSeparater(whereStr, "Edit");
		PX2_APP.Menu_Edit_AddItem(whereStr, "Edit", "ImportSelected", PX2_LM_EDITOR.V("n_ImportSelectedRes"), "n_ImportSelectRes");
		PX2_APP.Menu_Edit_AddItem(whereStr, "Edit", "Import", PX2_LM_EDITOR.V("n_Import"), "n_Import");
	}

	if (obj)
	{
		if (selectedMovable)
			PX2_APP.Menu_Edit_AddItemSeparater(whereStr, "Edit");

		PX2_APP.Menu_Edit_AddItem(whereStr, "Edit", "ExportSelected", PX2_LM_EDITOR.V("n_Export"), "n_Export");
	}

	if (selectedMovable)
	{
		PX2_APP.Menu_Edit_AddItemSeparater(whereStr, "EditCreate");
		PX2_APP.Menu_Edit_AddSubItem(whereStr, "EditCreate", "Controller", PX2_LM_EDITOR.V("n_Controller"));
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateController", "ColorController", PX2_LM_EDITOR.V("n_ColorController"), "n_Create_Controller_ColorController");
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateController", "BrightnessController", PX2_LM_EDITOR.V("n_BrightnessController"), "n_Create_Controller_BrightnessController");
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateController", "AlphaController", PX2_LM_EDITOR.V("n_AlphaController"), "n_Create_Controller_AlphaController");
		PX2_APP.Menu_Edit_AddItemSeparater(whereStr, "EditCreateController");
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateController", "UniformScaleController", PX2_LM_EDITOR.V("n_UniformScaleController"), "n_Create_Controller_UniformScaleController");
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateController", "ScaleController", PX2_LM_EDITOR.V("n_ScaleController"), "n_Create_Controller_ScaleController");
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateController", "RotateController", PX2_LM_EDITOR.V("n_RotateController"), "n_Create_Controller_RotateController");
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateController", "TranslateController", PX2_LM_EDITOR.V("n_TranslateController"), "n_Create_Controller_TranslateController");
	}

	if (selectEffectableCtrl)
	{
		Effectable *ea = DynamicCast<Effectable>(selectEffectableCtrl->GetControlledable());

		const std::vector<std::string> &namesEA = ea->GetAllModuleNames_EA();
		const std::vector<std::string> &namesEO = ea->GetAllModuleNames_EO();

		PX2_APP.Menu_Edit_AddSubItem(whereStr, "EditCreate", "EffectMoudle", PX2_LM_EDITOR.V("n_EffectMoudle"));

		for (int i = 0; i < (int)namesEA.size(); i++)
		{
			std::string createStr = "n_CreateEffectableControllerModule";
			PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateEffectMoudle", namesEA[i], namesEA[i], createStr, namesEA[i]);
		}

		PX2_APP.Menu_Edit_AddItemSeparater(whereStr, "EditCreateEffectMoudle");

		for (int i = 0; i < (int)namesEO.size(); i++)
		{
			std::string createStr = "n_CreateEffectableControllerModule";
			PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreateEffectMoudle", namesEO[i], namesEO[i], createStr, namesEO[i]);
		}
	}

	if (selectControlledable)
	{
		PX2_APP.Menu_Edit_AddItemSeparater(whereStr, "EditCreate");
		PX2_APP.Menu_Edit_AddItem(whereStr, "EditCreate", "CreateScriptController", 
			PX2_LM_EDITOR.V("n_CreateScriptControllerFromRes"), "n_CreateScriptControllerFromRes");
	}

	if (selectedMovable || ctrl || selectEffectableCtrl || selectEffectModule)
	{
		if (selectedMovable || selectEffectableCtrl)
			PX2_APP.Menu_Edit_AddItemSeparater(whereStr, "Edit");

		PX2_APP.Menu_Edit_AddItem(whereStr, "Edit", "Copy", PX2_LM_EDITOR.V("n_Copy"), "n_Copy");
		PX2_APP.Menu_Edit_AddItem(whereStr, "Edit", "Paste", PX2_LM_EDITOR.V("n_Paste"), "n_Paste");
		PX2_APP.Menu_Edit_AddItem(whereStr, "Edit", "Delete", PX2_LM_EDITOR.V("n_Delete"), "n_DeleteSelection");
	}

	if (selectedMovable || interpCurveCtrl || selectEffectableCtrl)
	{
		PX2_APP.Menu_Edit_AddItemSeparater(whereStr, "Edit");
		PX2_APP.Menu_Edit_AddItem(whereStr, "Edit", "ResetPlay", PX2_LM_EDITOR.V("n_ResetPlay"), "n_AnimResetPlay");
		PX2_APP.Menu_Edit_AddItem(whereStr, "Edit", "Play", PX2_LM_EDITOR.V("n_Play"), "n_AnimPlayStop");
		PX2_APP.Menu_Edit_AddItem(whereStr, "Edit", "Pause", PX2_LM_EDITOR.V("n_Pause"), "n_AnimStop");
		PX2_APP.Menu_Edit_AddItem(whereStr, "Edit", "Reset", PX2_LM_EDITOR.V("n_Reset"), "n_AnimReset");
	}

	if (selectedMovable)
	{
		PX2_APP.Menu_Edit_AddItemSeparater(whereStr, "Edit");
		PX2_APP.Menu_Edit_AddItem(whereStr, "Edit", "FindInProjectTree", PX2_LM_EDITOR.V("n_FindInProjectTree"), "n_FindInProjectTree");
		PX2_APP.Menu_Edit_AddItem(whereStr, "Edit", "FindInResTree", PX2_LM_EDITOR.V("n_FindInResTree"), "n_FindInResTree");
	}

	if (interpCurveCtrl || selectEffectModule)
	{
		PX2_APP.Menu_Edit_AddItemSeparater(whereStr, "Edit");
		PX2_APP.Menu_Edit_AddItem(whereStr, "Edit", "MakeCurve", PX2_LM_EDITOR.V("n_MakeCurve"), "n_MakeCurve");
	}

	if (obj)
	{
		PX2_APP.Menu_Edit_AddItemSeparater(whereStr, "Edit");
		Application::MenuItem *menuItem = PX2_APP.GetMenuItem();
		AddAppItem(whereStr, 0, menuItem);
		PX2_APP.Menu_Edit_EndPopUp(whereStr, pos);
	}
}
//----------------------------------------------------------------------------
void EU_Manager::AddAppItem(const std::string &whereStr, Application::MenuItem *itemParent,
	Application::MenuItem *item)
{
	const std::string &allName = item->AllName;
	const std::string &itemName = item->Name;
	const std::string &script = item->Script;
	Application::MenuItem::Type type = item->TheType;

	if (!itemParent)
	{
		PX2_APP.Menu_Edit_AddSubItem(whereStr, "Edit", allName, itemName);
	}
	else
	{
		std::string parAllName = "Edit" + itemParent->AllName;

		if (type == Application::MenuItem::T_SUB)
		{
			PX2_APP.Menu_Edit_AddSubItem(whereStr, parAllName, itemName, itemName);
		}
		else if (type == Application::MenuItem::T_ITEM)
		{
			PX2_APP.Menu_Edit_AddItem(whereStr, parAllName, itemName, itemName, script);
		}
	}

	for (int i = 0; i < (int)item->Items.size(); i++)
	{
		AddAppItem(whereStr, item, item->Items[i]);
	}
}
//----------------------------------------------------------------------------
EU_Manager::EditMenuType EU_Manager::GetEidtMenuType()
{
	return mEditMenuType;
}
//----------------------------------------------------------------------------
void EU_Manager::AddTool(const std::string &whereStr, const std::string &icon,
	std::string &script, const std::string &helpStr, int type)
{
	AddToolBarData data;
	data.Where = whereStr;
	data.TheType = AddToolBarData::T_TOOL;
	data.Icon = icon;
	data.Script = script;
	data.HelpStr = helpStr;
	data.DataType = type;

	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::N_AddTool);
	ent->SetData(data);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EU_Manager::AddToolChoose(const std::string &whereStr, 
	const std::string &script,
	const std::string &choose0,
	const std::string &choose1,
	const std::string &choose2,
	const std::string &choose3,
	const std::string &choose4)
{
	AddToolBarData data;
	data.Where = whereStr;
	data.TheType = AddToolBarData::T_CHOOSE;
	data.Script = script;
	data.Chooses.push_back(choose0);
	data.Chooses.push_back(choose1);
	data.Chooses.push_back(choose2);
	data.Chooses.push_back(choose3);
	data.Chooses.push_back(choose4);

	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::N_AddTool);
	ent->SetData(data);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EU_Manager::AddToolSeparater(const std::string &whereStr)
{
	AddToolBarData data;
	data.Where = whereStr;
	data.TheType = AddToolBarData::T_SPEARATER;

	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::N_AddTool);
	ent->SetData(data);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EU_Manager::AddToolStretch(const std::string &whereStr)
{
	AddToolBarData data;
	data.Where = whereStr;
	data.TheType = AddToolBarData::T_STRETCH;

	Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::N_AddTool);
	ent->SetData(data);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EU_Manager::CreateUIWindowMain()
{
	RenderWindow *rw = PX2_GR.GetMainWindow();
	Canvas *canvasMain = rw->GetMainCanvas();

	UIAuiFrame *uiAuiFrame = 0;
	mFrame_Main = CreateMainFrame(canvasMain, uiAuiFrame);
	mFrame_Content = uiAuiFrame;
	mFrame_Content->SetAnchorParamVer(Float2(PX2_UISM.Size_StatusBar, -PX2_UISM.Size_MainToolBar));
	UIAuiManager::GetSingleton().AddAuiFrame(rw, mFrame_Content);

	// tool bar
	CreateFrame_ToolBar();

	// status bar
	CreateFrame_StatusBar();

	// center
	UIAuiBlockFrame *centerFrame = CreateFrame_Center();
	UIAuiBlockFrame *outCenter = 0;
	UIAuiBlockFrame *projectFrame = CreateFrame_Project(centerFrame, outCenter);

	UIAuiBlockFrame *projOut = 0;
	UIAuiBlockFrame *resFrame = CreateFrame_Resource(projectFrame, projOut);
	PX2_UNUSED(resFrame);

	UIAuiBlockFrame *propertyFrame = CreateFrame_Property(outCenter, outCenter);
	PX2_UNUSED(propertyFrame);
}
//----------------------------------------------------------------------------
UIFrame *EU_Manager::CreateMainFrame(Canvas *canvas,
	UIAuiFrame *&outAuiFrame)
{
	UIFrame *frame = new0 UIFrame();
	frame->SetName("CanvasContentFrame");
	canvas->AttachChild(frame);
	frame->SetAnchorHor(Float2(0.0f, 1.0f));
	frame->SetAnchorVer(Float2(0.0f, 1.0f));
	frame->SetSize(500.0f, 300.0f);
	frame->SetPivot(0.5f, 0.5f);

	UIAuiFrame *auiFrame = new0 UIAuiFrame();
	frame->AttachChild(auiFrame);
	auiFrame->SetAnchorHor(0.0f, 1.0f);
	auiFrame->SetAnchorVer(0.0f, 1.0f);
	outAuiFrame = auiFrame;

	return frame;
}
//----------------------------------------------------------------------------
UIFrame *EU_Manager::GetFrame_Main()
{
	return mFrame_Main;
}
//----------------------------------------------------------------------------
void _TableCallback(UIFrame *frame, UICallType type)
{
	PX2_UNUSED(frame);
	PX2_UNUSED(type);
}
//----------------------------------------------------------------------------
UIAuiBlockFrame *EU_Manager::CreateFrame_Center()
{
	UIAuiBlockFrame *blockFrame = CreateUIAuiBlockFrame(
		mFrame_Content->AuiBlockDefault, UILPT_CENTER);

	UITabFrame *tabFrame = DynamicCast<UITabFrame>(
		blockFrame->GetObjectByName("UITabFrame_" + blockFrame->GetName()));

	UIFrame *frameWelcome = new0 UIFrame();
	frameWelcome->SetName("WelcomeFrame");
	tabFrame->AddTab("Welcome", PX2_LM_EDITOR.GetValue("Welcome"), frameWelcome);
	frameWelcome->SetAnchorHor(0.0, 1.0f);
	frameWelcome->SetAnchorVer(0.0, 1.0);
	SetWelcomeFrame(frameWelcome);

	EU_StageFrame *stageFrame = new0 EU_StageFrame();
	tabFrame->AddTab("Stage", PX2_LM_EDITOR.GetValue("Stage"), stageFrame);
	stageFrame->SetAnchorHor(0.0f, 1.0f);
	stageFrame->SetAnchorVer(0.0f, 1.0f);
	stageFrame->LocalTransform.SetTranslateY(-5.0f);

	EU_SimuFrame *simuFrame = new0 EU_SimuFrame();
	tabFrame->AddTab("Simulation", PX2_LM_EDITOR.GetValue("Simulation"), simuFrame);
	simuFrame->SetAnchorHor(0.0f, 1.0f);
	simuFrame->SetAnchorVer(0.0f, 1.0f);
	simuFrame->LocalTransform.SetTranslateY(-5.0f);

	tabFrame->AddUICallback(_TableCallback);

	tabFrame->SetActiveTab("Welcome");

	return blockFrame;
}
//----------------------------------------------------------------------------
UIAuiBlockFrame *EU_Manager::CreateFrame_Project(
	UIAuiBlockFrame *beforeCenterFrame,
	UIAuiBlockFrame *&outCenter)
{
	UIAuiBlockFrame *blockFrame = CreateUIAuiBlockFrame2(
		beforeCenterFrame, UILPT_LEFT, outCenter, Sizef(400.0f, 500.0f));

	UITabFrame *tabFrame = DynamicCast<UITabFrame>(
		blockFrame->GetObjectByName("UITabFrame_" + blockFrame->GetName()));

	tabFrame->SetAnchorHor(0.0f, 1.0f);
	tabFrame->SetAnchorVer(0.0f, 1.0f);

	EU_ProjectFrame *frameProj = new0 EU_ProjectFrame();
	tabFrame->AddTab("Project", PX2_LM_EDITOR.GetValue("Project"), frameProj);
	frameProj->SetAnchorHor(0.0f, 1.0f);
	frameProj->SetAnchorVer(0.0f, 1.0f);

	EU_CreateFrame *frameCreate = new0 EU_CreateFrame();
	tabFrame->AddTab("Create", PX2_LM_EDITOR.GetValue("Create"), frameCreate);
	frameCreate->SetAnchorHor(0.0f, 1.0f);
	frameCreate->SetAnchorVer(0.0f, 1.0f);

	tabFrame->SetActiveTab("Project");

	return blockFrame;
}
//----------------------------------------------------------------------------
UIAuiBlockFrame *EU_Manager::CreateFrame_Property(
	UIAuiBlockFrame *beforeCenterFrame,
	UIAuiBlockFrame *&outCenter)
{
	UIAuiBlockFrame *blockFrame = CreateUIAuiBlockFrame2(
		beforeCenterFrame, UILPT_RIGHT, outCenter, Sizef(400.0f, 500.0f));

	UITabFrame *tabFrame = DynamicCast<UITabFrame>(
		blockFrame->GetObjectByName("UITabFrame_" + blockFrame->GetName()));

	EU_InspectorFrame *frame = new0 EU_InspectorFrame();
	tabFrame->AddTab("Property", PX2_LM_EDITOR.GetValue("Property"), frame);
	frame->SetAnchorHor(0.0f, 1.0f);
	frame->SetAnchorVer(0.0f, 1.0f);

	tabFrame->SetActiveTab("Property");

	return blockFrame;
}
//----------------------------------------------------------------------------
UIAuiBlockFrame *EU_Manager::CreateFrame_Resource(
	UIAuiBlockFrame *beforeCenterFrame, UIAuiBlockFrame *&outCenter)
{
	UIAuiBlockFrame *blockFrame = CreateUIAuiBlockFrame2(
		beforeCenterFrame, UILPT_BOTTOM, outCenter, Sizef(400.0f, 500.0f));

	UITabFrame *tabFrame = DynamicCast<UITabFrame>(
		blockFrame->GetObjectByName("UITabFrame_" + blockFrame->GetName()));

	EU_ResFrame *frame1 = new0 EU_ResFrame();
	tabFrame->AddTab("Resource", PX2_LM_EDITOR.GetValue("Resource"), frame1);
	frame1->SetAnchorHor(0.0f, 1.0f);
	frame1->SetAnchorVer(0.0f, 1.0f);

	EU_ConcoleFrame *frame = new0 EU_ConcoleFrame();
	tabFrame->AddTab("Console", PX2_LM_EDITOR.GetValue("Console"), frame);
	frame->SetAnchorHor(0.0f, 1.0f);
	frame->SetAnchorVer(0.0f, 1.0f);

	EU_TimeLineFrame *frameTimeLine = new0 EU_TimeLineFrame();
	tabFrame->AddTab("TimeLine", PX2_LM_EDITOR.GetValue("TimeLine"), frameTimeLine);
	frameTimeLine->SetAnchorHor(0.0f, 1.0f);
	frameTimeLine->SetAnchorVer(0.0f, 1.0f);

	tabFrame->SetActiveTab("Resource");

	return blockFrame;
}
//----------------------------------------------------------------------------
void _LevelUpCallback (UIFrame *frame, UICallType type)
{
	UIButton *but = DynamicCast<UIButton>(frame);
	if (but)
	{
		if (UICT_RELEASED == type)
		{
			PX2EU_MAN.ShowWindowUserLeaveUp(true);
		}
	}
}
//----------------------------------------------------------------------------
void EU_Manager::CreateFrame_ToolBar()
{
	mFrame_ToolBar = new0 UIFrame();
	mFrame_Main->AttachChild(mFrame_ToolBar);
	mFrame_ToolBar->SetName("ToolBar");

	UIPicBox *picBox = mFrame_ToolBar->CreateAddBackgroundPicBox();
	picBox->SetColor(PX2_UISM.Color_MainToolBar);

	mFrame_ToolBar->SetSize(0.0f, PX2_UISM.Size_MainToolBar);

	mFrame_ToolBar->SetAnchorHor(Float2(0.0f, 1.0f));
	mFrame_ToolBar->SetAnchorVer(Float2(1.0f, 1.0f));
	mFrame_ToolBar->SetPivot(0.5f, 1.0f);

	// buts
	Sizef butSize = Sizef(PX2_UISM.Size_ToolBarBut*2.0f, PX2_UISM.Size_ToolBarBut);
	float butSpace = 2.0f;
	Sizef spliterSize = Sizef(4.0f,
		PX2_UISM.Size_ToolBar - 2);

	float addButPos = 0.0f;

	// edit type
	addButPos = butSize.Width / 2.0f;
	UICheckButton *butSimu = CreateCheckBut("ButSimu", PX2_LM_EDITOR.GetValue("Simu"));
	mFrame_ToolBar->AttachChild(butSimu);
	butSimu->SetAnchorHor(0.0f, 0.0f);
	butSimu->SetAnchorVer(0.5f, 0.5f);
	butSimu->SetAnchorParamHor(addButPos, 0.0f);
	butSimu->SetSize(butSize);
	butSimu->AddVisitor(this);
	butSimu->Enable(false);

	addButPos += butSpace + butSize.Width;
	UICheckButton *butPlay = CreateCheckBut("ButPlay", PX2_LM_EDITOR.GetValue("Ply"));
	mFrame_ToolBar->AttachChild(butPlay);
	butPlay->LocalTransform.SetTranslateY(-1.0f);
	butPlay->SetAnchorHor(0.0f, 0.0f);
	butPlay->SetAnchorVer(0.5f, 0.5f);
	butPlay->SetAnchorParamHor(addButPos, 0.0f);
	butPlay->SetSize(butSize);
	butPlay->AddVisitor(this);
	butPlay->Enable(false);

	addButPos += butSpace + butSize.Width;
	UIButton *butPlayInWindow = new0 UIButton();
	mFrame_ToolBar->AttachChild(butPlayInWindow);
	butPlayInWindow->LocalTransform.SetTranslateY(-1.0f);
	butPlayInWindow->SetAnchorHor(0.0f, 0.0f);
	butPlayInWindow->SetAnchorVer(0.5f, 0.5f);
	butPlayInWindow->SetAnchorParamHor(addButPos, 0.0f);
	butPlayInWindow->SetSize(butSize);
	butPlayInWindow->SetName("ButPlayInWindow");
	butPlayInWindow->AddVisitor(this);
	butPlayInWindow->CreateAddText(PX2_LM_EDITOR.GetValue("PlyW"));
	butPlayInWindow->GetText()->SetFontColor(PX2_UISM.Color_ContentFont);
	butPlayInWindow->GetText()->SetFontScale(PX2_UISM.Size_PropertyFontScale);
	butPlayInWindow->Enable(false);

	float minusButPos = 0.0f;

	minusButPos += -(butSpace + butSize.Width *0.5f);
	UIButton *butLogin = new0 UIButton();
	mFrame_ToolBar->AttachChild(butLogin);
	butLogin->LocalTransform.SetTranslateY(-1.0f);
	butLogin->SetSize(butSize);
	butLogin->SetAnchorHor(1.0f, 1.0f);
	butLogin->SetAnchorParamHor(minusButPos, minusButPos);
	butLogin->SetAnchorVer(0.5f, 0.5f);
	UIFText *text = butLogin->CreateAddText(PX2_LM_EDITOR.GetValue("Login"));
	text->GetText()->SetFontColor(Float3::WHITE);
	text->GetText()->SetDrawStyle(FD_SHADOW);

	minusButPos += -butSize.Width *0.5f;

	minusButPos += -(butSpace + butSize.Width*1.25f);
	UIButton *butLevelUp = new0 UIButton();
	mFrame_ToolBar->AttachChild(butLevelUp);
	butLevelUp->LocalTransform.SetTranslateY(-1.0f);
	butLevelUp->SetSize(Sizef(butSize.Width*2.5f, butSize.Height));
	butLevelUp->SetAnchorHor(1.0f, 1.0f);
	butLevelUp->SetAnchorParamHor(minusButPos, minusButPos);
	butLevelUp->SetAnchorVer(0.5f, 0.5f);
	butLevelUp->SetStateColor(UIButtonBase::BS_NORMAL, Float3::MakeColor(239, 228, 176));
	butLevelUp->SetStateColor(UIButtonBase::BS_HOVERED, Float3::MakeColor(239, 228, 176));
	butLevelUp->SetStateColor(UIButtonBase::BS_PRESSED, Float3::MakeColor(239, 228, 176));
	butLevelUp->SetStateBrightness(UIButtonBase::BS_NORMAL, 0.8f);
	butLevelUp->SetStateBrightness(UIButtonBase::BS_HOVERED,1.0f);
	butLevelUp->SetStateBrightness(UIButtonBase::BS_PRESSED, 1.2f);
	butLevelUp->AddUICallback(_LevelUpCallback);
	text = butLevelUp->CreateAddText(PX2_LM_EDITOR.GetValue("UserLevelUp"));
	text->GetText()->SetFontColor(Float3::WHITE);
	text->GetText()->SetDrawStyle(FD_SHADOW);
}
//----------------------------------------------------------------------------
UICheckButton *EU_Manager::CreateCheckBut(const std::string &name,
	const std::string &text)
{
	UICheckButton *butCheck = new0 UICheckButton();
	butCheck->LocalTransform.SetTranslateY(-1.0f);
	butCheck->SetName(name);
	butCheck->AddVisitor(this);
	butCheck->CreateAddText(text);
	butCheck->GetText()->SetDrawStyle(FD_SHADOW);
	butCheck->GetText()->SetFontColor(PX2_UISM.Color_ContentFont);
	//butCheck->GetText()->SetFontScale(PX2_UISM.Size_PropertyFontScale);

	butCheck->SetButType(UIButtonBase::BT_COLOR);

	UIPicBox *picNormal = butCheck->GetPicBoxAtState(UIButton::BS_NORMAL);
	picNormal->SetTexture("Data/engine/white.png");
	picNormal->SetPicBoxType(UIPicBox::PBT_NORMAL);

	butCheck->Check(false, false);

	return butCheck;
}
//----------------------------------------------------------------------------
void EU_Manager::CreateFrame_StatusBar()
{
	mFrame_StatusBar = new0 EU_StatusBar();
	mFrame_Main->AttachChild(mFrame_StatusBar);
	mFrame_StatusBar->SetName("StatusBar");	
}
//----------------------------------------------------------------------------
void _RenderWindowButCallback (UIFrame *frame, UICallType type)
{
	UIButton *but = DynamicCast<UIButton>(frame);
	if (but)
	{
		const std::string &name = frame->GetName();

		if (UICT_RELEASED == type)
		{
			if ("Max" == name)
			{
				RenderWindow *rw = but->GetUserData<RenderWindow*>("window");
				if (rw)
				{
					rw->MaxSize(!rw->IsMaxSize());
				}
			}
			else if ("Close" == name)
			{
				RenderWindow *rw = but->GetUserData<RenderWindow*>("window");
				if (rw)
				{
					rw->Show(false);
				}
			}
		}
	}
}
//----------------------------------------------------------------------------
void _TravelExecuteSetLayoutChanged (Movable *mov, Any *data, bool &goOn)
{
	PX2_UNUSED(data);
	PX2_UNUSED(goOn);

	SizeNode *sn = DynamicCast<SizeNode>(mov);
	if (sn)
	{
		sn->_MarkRelatvieLayoutChange();
		sn->_MarkRelatvieScreenChange();
	}
}
//----------------------------------------------------------------------------
void _UITabFrameCallback(UIFrame *frame, UICallType type)
{
	UITabFrame *callTabFrame = DynamicCast<UITabFrame>(frame);
	if (callTabFrame)
	{
		std::string actTabName = callTabFrame->GetActiveTab();
		int numTabs = callTabFrame->GetNumTabs();
		if (UICT_TABFRAME_DRAG_BEGIN == type)
		{
			if (!actTabName.empty())
			{
				const Sizef &tfSize = callTabFrame->GetSize();
				Movable *topestParent = callTabFrame->GetTopestParent();
				Canvas *topestCanvas = DynamicCast<Canvas>(topestParent);
				Canvas *parentCanvas = DynamicCast<Canvas>(callTabFrame->GetParent());
				UIAuiBlockFrame *blockFrameParent = DynamicCast<UIAuiBlockFrame>(parentCanvas->GetParent());
				UIAuiBlockFrame *blockFrameParentParent = DynamicCast<UIAuiBlockFrame>(blockFrameParent->GetParent());

				const APoint &curPickPos = topestCanvas->GetCurPickPos();

				UIFramePtr cotFrame = callTabFrame->GetTab(actTabName);
				callTabFrame->RemoveTab(actTabName);

				if (1 == numTabs)
				{
					blockFrameParentParent->RemovePosFrame(blockFrameParent->GetLayOutPosType());
				}

				RenderWindow *mainRW = PX2_GR.GetMainWindow();
				RenderWindow *window = PX2_APP.CreateUIWindow(mainRW, actTabName,
					actTabName, curPickPos, tfSize, true);
				Canvas *canvasMain = window->GetMainCanvas();
				UIAuiFrame *contentFrame = DynamicCast<UIAuiFrame>(
					canvasMain->GetObjectByName("UIAuiFrame"));

				UIAuiBlockFrame *auiBlockFrame = PX2EU_MAN.CreateUIAuiBlockFrame(
					contentFrame->AuiBlockDefault, UILPT_CENTER);

				UITabFrame *tabFrame = DynamicCast<UITabFrame>(
					auiBlockFrame->GetObjectByName("UITabFrame_" + auiBlockFrame->GetName()));

				tabFrame->AddTab(actTabName, actTabName, cotFrame);
				tabFrame->SetActiveTab(actTabName);

				UIFrame *titleBarFrame = tabFrame->GetTitleBarFrame();

				float leftMinus = -10.0f;

				UIButton *maxBut = new0 UIButton();
				titleBarFrame->AttachChild(maxBut);
				maxBut->SetName("Max");
				maxBut->SetSize(10.0f, 10.0f);
				maxBut->LocalTransform.SetTranslateY(-5.0f);
				maxBut->SetAnchorHor(1.0f, 1.0f);
				maxBut->SetAnchorVer(0.5f, 0.5f);
				maxBut->SetAnchorParamHor(-18.0f + leftMinus, 0.0f);
				maxBut->SetAnchorParamVer(0.0f, 0.0f);
				maxBut->AddUICallback(_RenderWindowButCallback);
				maxBut->SetUserData("window", window);

				UIButton *closeBut = new0 UIButton();
				titleBarFrame->AttachChild(closeBut);
				closeBut->SetName("Close");
				closeBut->SetSize(10.0f, 10.0f);
				closeBut->LocalTransform.SetTranslateY(-5.0f);
				closeBut->SetAnchorHor(1.0f, 1.0f);
				closeBut->SetAnchorVer(0.5f, 0.5f);
				closeBut->SetAnchorParamHor(-6.0f + leftMinus, 0.0f);
				closeBut->SetAnchorParamVer(0.0f, 0.0f);
				closeBut->AddUICallback(_RenderWindowButCallback);
				closeBut->SetUserData("window", window);

				Node::TravelExecute(auiBlockFrame, _TravelExecuteSetLayoutChanged);
			}
		}
	}
}
//----------------------------------------------------------------------------
UIAuiBlockFrame *EU_Manager::CreateUIAuiBlockFrame(UIAuiBlockFrame *parent,
	UILayoutPosType pos, const Sizef &size)
{
	UIAuiBlockFrame *blockFrame = parent->CreateAddPosFrame(pos, 
		size);

	blockFrame->SetName(PX2_UIAUIM.GenName("UIAuiBlockFrame"));

	Canvas *canvas = new0 Canvas();
	canvas->CreateUICameraNode();
	canvas->SetActivateSelfCtrled(false);
	blockFrame->AttachChild(canvas);
	canvas->SetAnchorHor(0.0f, 1.0f);
	canvas->SetAnchorVer(0.0f, 1.0f);
	canvas->SetName("AuiBlockFrameCanvas");

	UITabFrame *tabFrame = new0 UITabFrame();
	canvas->AttachChild(tabFrame);
	tabFrame->LocalTransform.SetTranslateY(-5.0f);
	tabFrame->SetName("UITabFrame_" + blockFrame->GetName());
	//tabFrame->AddUICallback(_UITabFrameCallback);

	return blockFrame;
}
//----------------------------------------------------------------------------
UIAuiBlockFrame *EU_Manager::CreateUIAuiBlockFrame2(UIAuiBlockFrame *parent,
	UILayoutPosType pos, UIAuiBlockFrame *&outCenter, const Sizef &size)
{
	std::vector<MovablePtr> children = parent->GetChildren();
	parent->DestoryBackgroundPicBox();
	parent->DetachAllChildren();

	UIAuiBlockFrame *blockFrame = parent->CreateAddPosFrame(pos, size);
	UIAuiBlockFrame *blockFrameCenter = parent->CreateAddPosFrame(UILPT_CENTER,
		size);
	outCenter = blockFrameCenter;
	blockFrame->SetBrotherFrame(blockFrameCenter);
	blockFrameCenter->SetBrotherFrame(blockFrame);

	Canvas *canvas = new0 Canvas();
	canvas->CreateUICameraNode();
	canvas->SetActivateSelfCtrled(false);
	Float4 blackGroundColor = Float4(PX2_UISM.Color_ViewBackground.X(),
		PX2_UISM.Color_ViewBackground.Y(), PX2_UISM.Color_ViewBackground.Z(), 1.0f);
	canvas->SetClearColor(blackGroundColor);
	blockFrame->AttachChild(canvas);
	canvas->SetAnchorHor(0.0f, 1.0f);
	canvas->SetAnchorVer(0.0f, 1.0f);

	for (int i = 0; i < (int)children.size(); i++)
	{
		if (children[i] && "BackPicBox"!=children[i]->GetName() && 
			"MaskPicBox" != children[i]->GetName())
			blockFrameCenter->AttachChild(children[i]);
	}

	blockFrame->SetName(PX2_UIAUIM.GenName("UIAuiBlockFrame"));

	UITabFrame *tabFrame = new0 UITabFrame();
	canvas->AttachChild(tabFrame);
	tabFrame->SetName("UITabFrame_" + blockFrame->GetName());
	//tabFrame->AddUICallback(_UITabFrameCallback);

	return blockFrame;
}
//----------------------------------------------------------------------------
void EU_Manager::SetWelcomeFrame(UIFrame *frame)
{
	mWelcomeFrame = frame;
}
//----------------------------------------------------------------------------
UIFrame *EU_Manager::GetWelcomeFrame()
{
	return mWelcomeFrame;
}
//----------------------------------------------------------------------------
void EU_Manager::SetLogicCanvas(Canvas *logicCanvas)
{
	mLogicCanvas = logicCanvas;
}
//----------------------------------------------------------------------------
Canvas *EU_Manager::GetLogicCanvas()
{
	return mLogicCanvas;
}
//----------------------------------------------------------------------------
void EU_Manager::ShowWindowUserLeaveUp(bool show)
{
	if (show)
	{
		if (!mUserLeaveUpWindow)
		{
			RenderWindow *mainRW = PX2_GR.GetMainWindow();

			mUserLeaveUpWindow = PX2_APP.CreateUIWindow(
				mainRW, std::string("BluePrintTreeWindow"), 
				std::string("BluePrint"), APoint::ORIGIN,
				Sizef(600.0f, 400.0f), true);
			mUserLeaveUpWindow->Centre();
			Canvas *canvas = mUserLeaveUpWindow->GetMainCanvas();
			UIFrame *contentFrame = DynamicCast<UIFrame>(canvas->GetObjectByName("CanvasContentFrame"));
			contentFrame->DetachAllChildren();

			UIFrame *frame = new0 UIFrame();
			contentFrame->AttachChild(frame);
			frame->CreateAddBackgroundPicBox();
			frame->SetAnchorHor(0.0f, 1.0f);
			frame->SetAnchorVer(0.0f, 1.0f);

			UIFrame *topFrame = new0 UIFrame();
			frame->AttachChild(topFrame);
			topFrame->LocalTransform.SetTranslateY(-1.0f);
			topFrame->SetAnchorHor(0.0f, 1.0f);
			topFrame->SetAnchorVer(1.0f, 1.0f);
			topFrame->SetSize(0.0f, 30.0f);
			topFrame->SetPivot(0.5f, 1.0f);

			UIButton *but = new0 UIButton();
			topFrame->AttachChild(but);
			but->SetName("ButLevelUpClose");
			but->SetAnchorHor(1.0f, 1.0f);
			but->SetAnchorParamHor(-30.0f, -30.0f);
			but->SetAnchorVer(0.5f, 0.5f);
			but->SetSize(28.0f, 28.0f);
			but->CreateAddText("X");
			but->AddVisitor(this);
		}

		mUserLeaveUpWindow->Show(true);
	}
	else
	{
		if (mUserLeaveUpWindow)
			mUserLeaveUpWindow->Show(false);
	}
}
//----------------------------------------------------------------------------
bool EU_Manager::IsWindowUserLeaveUpShow() const
{
	return 0 != mUserLeaveUpWindow;
}
//----------------------------------------------------------------------------
void EU_Manager::SetInspectorView(int val)
{
	Event *ent = EditorEventSpace::CreateEventX(
		EditorEventSpace::SetInspectorView);
	ent->SetData(val);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EU_Manager::SetProjectTreeLevel(int level)
{
	Event *ent = EditorEventSpace::CreateEventX(
		EditorEventSpace::SetProjectTreeLevel);
	ent->SetData(level);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void EU_Manager::Visit(Object *obj, int info)
{
	Application::PlayType pt = PX2_APP.GetPlayType();
	PX2_UNUSED(pt);

	Object *butSimu = mFrame_ToolBar->GetObjectByName("ButSimu");
	Object *butPlay = mFrame_ToolBar->GetObjectByName("ButPlay");

	const std::string &name = obj->GetName();
	UICheckButton *checkBut = DynamicCast<UICheckButton>(obj);
	UIButton *but = DynamicCast<UIButton>(obj);
	if (checkBut)
	{
		if (UICT_CHECKED == info)
		{
			if ("ButSimu" == name)
			{
				PX2_APP.Play(Application::PT_SIMULATE);

				butPlay->Enable(false);
			}
			else if ("ButPlay" == name)
			{
				PX2_APP.Play(Application::PT_PLAY);

				butSimu->Enable(false);
			}
		}
		else if (UICT_DISCHECKED == info)
		{
			if ("ButSimu" == name || "ButPlay" == name)
			{
				PX2_APP.Play(Application::PT_NONE);

				butSimu->Enable(true);
				butPlay->Enable(true);

				std::string projPath = PX2_APP.GetProjectFilePath();
				PX2_APP.LoadProjectByPath(projPath);
			}
		}
	}
	else if (but)
	{
		if (UICT_RELEASED == info)
		{
			if ("ButPlayInWindow" == name)
			{
				Event *ent = EditorEventSpace::CreateEventX(EditorEventSpace::N_PlayInWindow);
				PX2_EW.BroadcastingLocalEvent(ent);
			}
			else if ("ButLevelUpClose" == name)
			{
				PX2EU_MAN.ShowWindowUserLeaveUp(false);
			}
		}
	}
}
//----------------------------------------------------------------------------
void EU_Manager::OnEvent(Event *event)
{
	if (ProjectES::IsEqual(event, ProjectES::NewProject) ||
		ProjectES::IsEqual(event, ProjectES::LoadedProject))
	{
		if (mFrame_ToolBar)
		{
			Object *butSimu = mFrame_ToolBar->GetObjectByName("ButSimu");
			butSimu->Enable(true);

			Object *butPlay = mFrame_ToolBar->GetObjectByName("ButPlay");
			butPlay->Enable(true);

			Object *butPlayInWindow = mFrame_ToolBar->GetObjectByName("ButPlayInWindow");
			butPlayInWindow->Enable(true);
		}

		PX2_SELECTM_E->Clear();
	}
	else if (ProjectES::IsEqual(event, ProjectES::CloseProject))
	{
		if (mFrame_ToolBar)
		{
			Object *butSimu = mFrame_ToolBar->GetObjectByName("ButSimu");
			butSimu->Enable(false);

			Object *butPlay = mFrame_ToolBar->GetObjectByName("ButPlay");
			butPlay->Enable(false);

			Object *butPlayInWindow = mFrame_ToolBar->GetObjectByName("ButPlayInWindow");
			butPlayInWindow->Enable(false);
		}

		PX2_SELECTM_E->Clear();
	}
}
//----------------------------------------------------------------------------