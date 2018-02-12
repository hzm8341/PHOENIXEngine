// SamplePlugin.cpp

#include "SamplePlugin.hpp"
#include "PX2PluginManager.hpp"
#include "PX2Log.hpp"
#include "SampleToLua.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2LuaPlusContext.hpp"
#include "PX2Project.hpp"

#include "PX2InterpCurveAlphaCtrl.hpp"
#include "PX2UIButton.hpp"
#include "PX2FramesMesh.hpp"
#include "PX2UIFrame.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2UISkinManager.hpp"
#include "PX2UIPicBox.hpp"
#include "PX2UIComboBox.hpp"
#include "PX2UIProgressBar.hpp"
#include "PX2UITree.hpp"
#include "PX2UIRound.hpp"
#include "PX2UIWebFrame.hpp"
#include "PX2StringHelp.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2SoundSystem.hpp"
#include "PX2SoundSystem.hpp"
#include "PX2ObjCast.hpp"
#include "PX2ProjectEvent.hpp"
#include "PX2EventWorld.hpp"
#include "PX2EngineClientConnector.hpp"
#include "PX2StreamSocket.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
Plugin* SamplePlugin::sPlugin = 0;
auto FrameWidth = 150.0f;
Bluetooth* g_s_ClientConnector = 0;
const std::string* g_s_ClienMsgEditBox = 0;
//----------------------------------------------------------------------------
SamplePlugin::SamplePlugin()
:ch_MT(0.75),
ch_LT(2.0),
ch_LastDelay(0.8)
{
	mName = "SamplePlugin";
}
//----------------------------------------------------------------------------
SamplePlugin::~SamplePlugin()
{
}
//----------------------------------------------------------------------------
void SamplePlugin::OnInstall()
{
	PX2_LOG_INFO("SamplePlugin::OnInstall()");
	PX2_EW.ComeIn(this);
	LuaPlusContext *luaContext = (LuaPlusContext*)PX2_SC_LUA;
	// Lua
	tolua_Sample_open((lua_State*)luaContext->GetLuaState());
	LuaPlus::LuaState *luaPlusState = luaContext->GetLuaPlusState();
	PX2_UNUSED(luaPlusState);
	mUI = PX2_PROJ.GetUI();
}
//----------------------------------------------------------------------------
//添加“按钮”框中按钮1按钮
void UIButtonCallBack(UIFrame* frame, UICallType type)
{
	UIButton* cb = DynamicCast<UIButton>(frame);

	const  std::string &name = cb->GetName();
	if (UICT_PRESSED == type)
	{
		if ("But0" == name)
		{
			SamplePlugin::GetSingleton().PrintMsg(PX2_LM_APP.GetValue("UICT_PRESSED But0"));
		}
		else if ("But1" == name)
		{
			SamplePlugin::GetSingleton().PrintMsg(PX2_LM_APP.GetValue("UICT_PRESSED But1"));
		}
		else if ("But2" == name)
		{
			SamplePlugin::GetSingleton().PrintMsg(PX2_LM_APP.GetValue("UICT_PRESSED But2"));
		}
		else if ("ButtonMenu" == name)
		{
			SamplePlugin::GetSingleton().ShowABCD();
		}
		else if ("ButtonNewProject" == name)
		{
			SamplePlugin::GetSingleton().ShowProject();
		}
		else if ("Cancel"==name)
		{
			SamplePlugin::GetSingleton().ShowProject();
		}
	}
	else if (UICT_RELEASED == type)
	{
		if ("ButHome" == name)
		{
			SamplePlugin::GetSingleton().Show();
		}
		if ("But0" == name)
		{
			SamplePlugin::GetSingleton().PrintMsg(PX2_LM_APP.GetValue("UICT_PRESSED But0"));
		}
		else if ("But1" == name)
		{
			SamplePlugin::GetSingleton().PrintMsg(PX2_LM_APP.GetValue("UICT_PRESSED But1"));
		}
		else if ("But2" == name)
		{
			SamplePlugin::GetSingleton().PrintMsg(PX2_LM_APP.GetValue("UICT_PRESSED But2"));
		}
	}
	else if (UICT_RELEASED_NOTPICK == type)
	{
		SamplePlugin::GetSingleton().PrintMsg("UICT_RELEASED_NOTPICK");
	}
	else if (UICT_CHECKED == type)
	{
		SamplePlugin::GetSingleton().PrintMsg("UICT_CHECKED");
	}
	else if (UICT_DISCHECKED == type)
	{
		SamplePlugin::GetSingleton().PrintMsg("UICT_DISCHECKED");
	}
	else if (UICT_EDITBOX_TEXTCHANGED == type)
	{
		SamplePlugin::GetSingleton().PrintMsg("UICT_EDITBOX_TEXTCHANGED");
	}
	else if (UICT_EDITBOX_ENTER == type)
	{
		SamplePlugin::GetSingleton().PrintMsg("UICT_EDITBOX_ENTER");
	}
	else if (UICT_LIST_SELECTED == type)
	{
		SamplePlugin::GetSingleton().PrintMsg("UICT_EDITBOX_ENTER");
	}
	else if (UICT_COMBOBOX_CHOOSED == type)
	{
		SamplePlugin::GetSingleton().PrintMsg("UICT_COMBOBOX_CHOOSED");
	}
	else if (UICT_TREE_SELECTED == type)
	{
		SamplePlugin::GetSingleton().PrintMsg("UICT_TREE_SELECTED");
	}
}  
//----------------------------------------------------------------------------
void UIServerCallBack(UIFrame* frame, UICallType type)
{
	UITabFrame* ab = DynamicCast<UITabFrame>(frame);
	const std::string &name = ab->GetName();
	if (UICT_PRESSED == type)
	{
	}
	else if (UICT_RELEASED==type)
	{ 
		if (nullptr != g_s_ClientConnector)
		{
			if ("ButConnect" == name)
			{
				if (g_s_ClientConnector->IsConnected())
				{
					g_s_ClientConnector->DisConnect();
				}
				else
				{
					//g_s_ClientConnector->ConnectNB("127.0.0.1", 18180);
				}
			}
			else if ("ButSend" == name)
			{
				if (g_s_ClientConnector->IsConnected())
				{
					//const std::string* text = g_s_ClienMsgEditBox->GetText();
					//g_s_ClientConnector->SendString(text);
				}
			}
		}
	}	
}
//----------------------------------------------------------------------------
void SamplePlugin::OnUninstall()
{
	PX2_LOG_INFO("SamplePlugin::OnUninstall()");
	PX2_EW.GoOut(this);
}
//----------------------------------------------------------------------------
void SamplePlugin::OnUpdate()
{
}
//----------------------------------------------------------------------------
void SamplePlugin::OnEvent(Event *event)
{

	if (ProjectES::IsEqual(event, ProjectES::Play))
	{
		_Play();
	}
	else if (ProjectES::IsEqual(event, ProjectES::Stop))
	{
	}
	else if (ProjectES::IsEqual(event, ProjectES::NewProject))
	{
		mIsNewProject = true;
	}
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::_Play()
{
	//添加音乐
	AddMusic();

	//主按钮设置
	MainButton();

	//添加菜单框属性
	AddMenuBoxProperties();

	//创建新的框架类型
	AddFrameType();

	//关于框
	OnCreateUIFrameAbout();

	//框架框
	OnCreateUIFrame();

	//图片框
	OnCreateUIFPicBox();

	//文字框
	OnCreateUIFText();

	//按钮框
	OnCreateUIButton();

	//判断框
	OnCreateUICheckBox();

	//选择框
	OnCreateUIComboBox();

	//编辑文字
	OnCreateUIEditBox();

	//进度条
	OnCreateUIProgress();

	//颜色选择
	OnCreateUIColorSelect();

	//列表
	OnCreateUIList();

	//树
	OnCreateUITree();

	//分隔线
	OnCreateUISplitter();

	//滑动条
	OnCreateUISlider();

	//方向盘
	OnCreateUIRound();

	//服务器
	OnCreateUIServer();

	//默认点击的是"关于"框
	mMenuCase->SetActiveTab("About");

	//右浏览框
	AddRightUIFrame();

	//添加其他元素
	AddOtherElements();

	//设置初始背景框为不可见
	MenuBg->Show(false);

	//添加按钮A
	OnCreateButtonA();

	//添加按钮B
	OnCreateButtonB();

	//添加按钮C
	OnCreateButtonC();

	//添加按钮D
	OnCreateButtonD();

	//添加“打开“按钮
	OnCreateMenu();

	//添加“创建”按钮
	OnCreateNewProject();

	//创建框
	OnCreateProject();

	//OnCreatebuttonE();
}
//----------------------------------------------------------------------------
void SamplePlugin::AddMusic()
{
	//添加音乐
	auto musicName = "march.mp3";
	std::string filePath = "Data/General/media/music/";
	PX2_RM.ReWriteFileToWriteablePath(filePath + musicName, musicName);
	std::string dstPath = ResourceManager::GetWriteablePath() + musicName;
	PX2_SS.PlayMusic(0, dstPath.c_str(), true, 0.0f, 1.0f);
}
//----------------------------------------------------------------------------
void SamplePlugin::MainButton()
{
	//背景
	frame = UIFrame::New();
	mUI->AttachChild(frame);
	frame->LocalTransform.SetTranslateY(-1.0);
	frame->SetAnchorHor(0.0, 1.0);
	frame->SetAnchorVer(0.0, 1.0);
	//创建第一个主按钮
	mButBag = UIButton::New();
	frame->AttachChild(mButBag);
	mButBag->SetName("ButHome");
	mButBag->SetAnchorHor(0.0, 0.0);
	mButBag->SetAnchorVer(1.0, 1.0);
	mButBag->SetSize(50, 50);
	mButBag->SetAnchorParamHor(50, 50);
	mButBag->SetAnchorParamVer(-50, -50);
	mButBag->SetScriptHandler("S_Callback");
	//添加主按钮
	mButBag->AddUICallback(UIButtonCallBack);
	//框内图案
	UIFPicBox* but = UIFPicBox::New();
	but->GetUIPicBox()->SetTexture("Data/General/images/icons/run.png");
	but->SetSize(30.0, 30.0);
	mButBag->AttachChild(but);
	but->LocalTransform.SetTranslateY(-2.0);
}
//----------------------------------------------------------------------------
void SamplePlugin::AddMenuBoxProperties()
{
	//背景
	MenuBg = UIFrame::New();
	frame->AttachChild(MenuBg);
	MenuBg->SetAnchorHor(0.0, 1.0);
	MenuBg->SetAnchorVer(0.0, 1.0);
	MenuBg->SetAnchorParamHor(25.0, -25.0);
	MenuBg->SetAnchorParamVer(25.0, -100.0);
	//浏览菜单
	mMenuCase = UITabFrame::New();
	MenuBg->AttachChild(mMenuCase);
	mMenuCase->SetAnchorParamHor(0.0, -FrameWidth);
	mMenuCase->CreateAddBackgroundPicBox(true, Float3::MakeColor(200, 200, 200));
	mMenuCase->SetTabBarHeight(40);
	mMenuCase->SetTabHeight(35);
	mMenuCase->SetTabWidth(60);
}
//----------------------------------------------------------------------------
void SamplePlugin::AddFrameType()
{
	mFrameAbout = new0 UITabFrame();
	frameUIFrame = new0 UIFrame();
	frameUIFPicBox = new0 UIFrame();
	frameUIFText = new0 UIFrame();
	frameUIButtom = new0 UIFrame();
	frameUICheckBox = new0 UIFrame();
	frameUIComboBox = new0 UIFrame();
	frameUIEditBox = new0 UIFrame();
	frameUIProgress = new0 UIFrame();
	frameUIColorSelect = new0 UIFrame();
	frameUIList = new0 UIFrame();
	frameUITree = new0 UIFrame();
	frameUISplitter = new0 UIFrame();
	frameUISlider = new0 UIFrame();
	frameUIRound = new0 UIFrame();
	frameServer = new0 UIFrame();
}
//----------------------------------------------------------------------------
void SamplePlugin::OnCreateUIFrameAbout()
{
	//关于
	mMenuCase->AddTab("About", PX2_LM_APP.GetValue("About"), mFrameAbout);
	mFrameAbout->LocalTransform.SetTranslateY(-1.0);
	mFrameAbout->SetAnchorHor(0.0, 1.0);
	mFrameAbout->SetAnchorVer(0.0, 1.0);
	mAboutfText = UIFText::New();
	mFrameAbout->AttachChild(mAboutfText);
	mAboutfText->SetAnchorHor(0.0, 1.0);
	mAboutfText->SetAnchorVer(0.0, 1.0);
	mAboutfText->GetText()->SetText(PX2_LM_APP.GetValue("wecome to"));
}
//----------------------------------------------------------------------------
void SamplePlugin::OnCreateUIFrame()
{
	//框架
	mMenuCase->AddTab("UIFrame", PX2_LM_APP.GetValue("UIFrame"), frameUIFrame);
	frameUIFrame->LocalTransform.SetTranslateY(-1.0);
	frameUIFrame->SetAnchorHor(0.0, 1.0);
	frameUIFrame->SetAnchorVer(0.0, 1.0);
	UIFrame* frameUIFrame0 = UIFrame::New();
	frameUIFrame->AttachChild(frameUIFrame0);
	frameUIFrame0->CreateAddBackgroundPicBox(true, Float3::YELLOW);
	frameUIFrame0->SetAnchorHor(0.0, 1.0);
	frameUIFrame0->SetAnchorVer(1.0, 1.0);
	frameUIFrame0->SetSize(0.0, 100.0);
	frameUIFrame0->SetAnchorParamHor(50.0, -50.0);
	frameUIFrame0->SetAnchorParamVer(-50.0, -5.0);
	UIFrame* frameUIFrame1 = UIFrame::New();
	frameUIFrame->AttachChild(frameUIFrame1);
	frameUIFrame1->CreateAddBackgroundPicBox(true, Float3::GREEN);
	frameUIFrame1->SetPivot(0.5, 1.0);
	frameUIFrame1->SetAnchorHor(0.0, 1.0);
	frameUIFrame1->SetAnchorVer(1.0, 1.0);
	frameUIFrame1->SetAnchorParamHor(50.0, -50.0);
	frameUIFrame1->SetAnchorParamVer(-100.0, -100.0);
	UIFrame* frameUIFrame2 = UIFrame::New();
	frameUIFrame->AttachChild(frameUIFrame2);
	frameUIFrame2->CreateAddBackgroundPicBox(false);
	frameUIFrame2->SetPivot(0.5, 1.0);
	frameUIFrame2->SetAnchorHor(0.0, 0.0);
	frameUIFrame2->SetAnchorVer(1.0, 1.0);
	frameUIFrame2->SetSize(200.0, 200.0);
	frameUIFrame2->SetAnchorParamHor(150.0, 0.0);
	frameUIFrame2->SetAnchorParamVer(-200.0, 0.0);
}
//----------------------------------------------------------------------------
void SamplePlugin::OnCreateUIFPicBox()
{
	//图片
	mMenuCase->AddTab("UIFPicBox",PX2_LM_APP.GetValue("UIFPicBox"), frameUIFPicBox);
	frameUIFPicBox->LocalTransform.SetTranslateY(-1.0);
	frameUIFPicBox->SetAnchorHor(0.0, 1.0);
	frameUIFPicBox->SetAnchorVer(0.0, 1.0);
	auto PicSize = 120;
	UIFrameGridAlignControl* gridAliginCtrl = frameUIFPicBox->CreateAddGridAlignCtrl();
	//设置纵向格式位置：y轴往中部
	gridAliginCtrl->SetChildAlignment(UIFrameGridAlignControl::CAT_MIDDLE_CENTER);
	//设置横向格式位置：x轴往中部
	gridAliginCtrl->SetConstraintType(UIFrameGridAlignControl::CT_FIXED_COLUMN_COUNT);
	//设置x轴中的值为4个
	gridAliginCtrl->SetConstraintValue(4);
	gridAliginCtrl->SetBorder(10.0, 10.0, 10.0, 10.0);
	gridAliginCtrl->SetCellSize(Sizef(PicSize, PicSize));
	//第一张图片
	UIFPicBox* fPicBox = UIFPicBox::New();
	frameUIFPicBox->AttachChild(fPicBox);
	fPicBox->SetSize(PicSize, PicSize);
	fPicBox->GetUIPicBox()->SetTexture("Data/General/images/pics/arduino.png");
	fPicBox->RegistToScriptSystem();
	//第二张图片
	UIFPicBox* fPicBox1 = UIFPicBox::New();
	frameUIFPicBox->AttachChild(fPicBox1);
	fPicBox1->SetSize(PicSize, PicSize);
	fPicBox1->GetUIPicBox()->SetUVRepeat(3, 3);
	fPicBox1->GetUIPicBox()->SetTexture("Data/General/images/pics/raspberry.png");
	fPicBox1->RegistToScriptSystem();
	//第三张图片
	UIFPicBox* fPicBox2 = UIFPicBox::New();
	frameUIFPicBox->AttachChild(fPicBox2);
	fPicBox2->SetSize(PicSize, PicSize);
	fPicBox2->GetUIPicBox()->SetTexCornerSize(8, 8, 8, 8);
	fPicBox2->GetUIPicBox()->SetTexture("Data/General/images/pics/but.png");
	fPicBox2->RegistToScriptSystem();
	UIFPicBox* fPicBox3 = UIFPicBox::New();
	frameUIFPicBox->AttachChild(fPicBox3);
	fPicBox3->SetSize(PicSize, PicSize);
	fPicBox3->GetUIPicBox()->SetPicBoxType(UIPicBox::PBT_NINE);
	fPicBox3->GetUIPicBox()->SetTexCornerSize(8, 8, 8, 8);
	fPicBox3->GetUIPicBox()->SetTexture("Data/engine/common.xml", "but_normal");
	fPicBox3->RegistToScriptSystem();
}
//----------------------------------------------------------------------------
void SamplePlugin::OnCreateUIFText()
{
	//文字
	mMenuCase->AddTab("UIFText", PX2_LM_APP.GetValue("UIFText"), frameUIFText);
	frameUIFText->LocalTransform.SetTranslateY(-1.0);
	frameUIFText->SetAnchorHor(0.0, 1.0);
	frameUIFText->SetAnchorVer(0.0, 1.0);
	auto Textsize = 200;

	UIFrameGridAlignControl* gridAliginCtrl0 = frameUIFText->CreateAddGridAlignCtrl();
	gridAliginCtrl0->SetChildAlignment(UIFrameGridAlignControl::CAT_MIDDLE_CENTER);
	gridAliginCtrl0->SetConstraintType(UIFrameGridAlignControl::CT_FIXED_COLUMN_COUNT);
	gridAliginCtrl0->SetConstraintValue(3);
	gridAliginCtrl0->SetBorder(10.0, 10.0, 10.0, 10.0);
	gridAliginCtrl0->SetCellSize(Sizef(Textsize, Textsize));

	UIFText* fText0 = UIFText::New();
	frameUIFText->AttachChild(fText0);
	fText0->SetSize(Textsize, Textsize);
	fText0->GetText()->SetFontColor(Float3::MakeColor(55, 0, 0));
	fText0->GetText()->SetFontScale(1.0);
	fText0->RegistToScriptSystem();

	UIFText* fText1 = UIFText::New();
	frameUIFText->AttachChild(fText1);
	fText1->SetSize(Textsize, Textsize);
	fText1->CreateAddBackgroundPicBox(true);
	fText1->GetText()->SetFont("Data/General/fonts/hyswlongfangsong.ttf", 24, 24, FES_UNDERLINE);
	fText1->GetText()->SetText(PX2_LM_APP.GetValue("welcome"));
	fText1->GetText()->SetBorderShadowColor(Float3(100, 0.0, 0.0));
	//添加下划线属性（格式样式）
	fText1->GetText()->SetDrawStyle(FD_SHADOW);
	//添加向上顶格（位置设置）
	fText1->GetText()->SetAligns(TEXTALIGN_LEFT + TEXTALIGN_TOP);
	fText1->RegistToScriptSystem();

	UIFText* fText2 = UIFText::New();
	frameUIFText->AttachChild(fText2);
	fText2->SetSize(Textsize, Textsize);
	fText2->CreateAddBackgroundPicBox(true, Float3::MakeColor(100, 200, 200));
	fText2->GetText()->SetText(PX2_LM_APP.GetValue("intelligente underholdning"));
	//紧靠方式
	fText2->GetText()->SetRectUseage(UIText::RU_CLIPWARP);
	//（根据形状的大小来控制间距）默认为false，意思为不控制
	fText2->GetText()->SetAutoWarp(true);
	fText2->RegistToScriptSystem();
}
//----------------------------------------------------------------------------
void SamplePlugin::OnCreateUIButton()
{
	//按钮
	mMenuCase->AddTab("UIButtom", PX2_LM_APP.GetValue("UIButton"), frameUIButtom);
	frameUIButtom->LocalTransform.SetTranslateY(-1.0);
	frameUIButtom->SetAnchorHor(0.0, 1.0);
	frameUIButtom->SetAnchorVer(0.0, 1.0);
	auto ButtonSize = 200;

	UIFText* text1 = UIFText::New();
	frameUIButtom->AttachChild(text1);
	text1->SetAnchorVer(0.9, 0.9);
	text1->GetText()->SetText("hello");

	UIFrameGridAlignControl* gridAliginCtrl1 = frameUIButtom->CreateAddGridAlignCtrl();
	//位置纵方向（默认为顶格，这里设置为中心）
	gridAliginCtrl1->SetChildAlignment(UIFrameGridAlignControl::CAT_MIDDLE_CENTER);
	//位置横方向（默认为左对其，这里也是设置为居中）
	gridAliginCtrl1->SetConstraintType(UIFrameGridAlignControl::CT_FIXED_COLUMN_COUNT);
	//设置横向设置值，默认为2个
	gridAliginCtrl1->SetConstraintValue(3);
	gridAliginCtrl1->SetCellSize(Sizef(ButtonSize, ButtonSize));

	UIButton* but0 = UIButton::New();
	frameUIButtom->AttachChild(but0);
	but0->SetName("But0");
	but0->SetSize(ButtonSize, ButtonSize);
	but0->CreateAddText(PX2_LM_APP.GetValue("But0"));
	but0->SetScriptHandler("S_Callback");
	but0->RegistToScriptSystem();
	//添加按钮响应
	but0->AddUICallback(UIButtonCallBack);

	

	UIButton* but1 = UIButton::New();
	frameUIButtom->AttachChild(but1);
	but1->SetName("But1");
	but1->SetButType(UIButtonBase::BT_PICBOXSWAP);
	//but1->SetStateColorDefaultWhite();
	but1->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetPicBoxType(UIPicBox::PBT_NINE);
	but1->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexCornerSize(8, 8, 8, 8);
	//but1->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexture("Data/engine/common.xml", "but_normal");
	but1->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexture("Data/General/images/pics/whitern.png");
	but1->GetPicBoxAtState(UIButtonBase::BS_HOVERED)->SetPicBoxType(UIPicBox::PBT_NINE);
	but1->GetPicBoxAtState(UIButtonBase::BS_HOVERED)->SetTexCornerSize(8, 8, 8, 8);
	but1->GetPicBoxAtState(UIButtonBase::BS_HOVERED)->SetTexture("Data/General/images/pics/blueBtn.png");
	//but1->GetPicBoxAtState(UIButtonBase::BS_HOVERED)->SetTexture("Data/engine/common.xml", "but_over");
	but1->GetPicBoxAtState(UIButtonBase::BS_PRESSED)->SetPicBoxType(UIPicBox::PBT_NINE);
	but1->GetPicBoxAtState(UIButtonBase::BS_PRESSED)->SetTexCornerSize(8, 8, 8, 8);
	but1->GetPicBoxAtState(UIButtonBase::BS_PRESSED)->SetTexture("Data/General/images/pics/blueBtn.png");
	but1->SetSize(ButtonSize, ButtonSize);
	but1->CreateAddText(PX2_LM_APP.GetValue("button1"));
	but1->SetScriptHandler("S_Callback");
	but1->RegistToScriptSystem();
	//添加按钮响应
	but1->AddUICallback(UIButtonCallBack);

	UIButton* but2 = UIButton::New();
	frameUIButtom->AttachChild(but2);
	but2->SetName("But2");
	but2->SetSize(ButtonSize, ButtonSize);
	but2->CreateAddText(PX2_LM_APP.GetValue("button2"));
	but2->SetScriptHandler("S_Callback");
	but2->RegistToScriptSystem();
	//添加按钮响应
	but2->AddUICallback(UIButtonCallBack);
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::OnCreateButtonA()
{
	ButtonA = UIButton::New();
	ButtonA->LocalTransform.SetTranslateY(-1.0);
	ButtonA->SetAnchorHor(0.4, 0.4);
	ButtonA->SetAnchorVer(0.5, 0.5);
	mUI->AttachChild(ButtonA);
	ButtonA->SetSize(70, 70);
	ButtonA->SetName("ButtinA");
	ButtonA->CreateAddText(("A"));
	ButtonA->Show(false);
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::OnCreateButtonB()
{
	ButtonB = UIButton::New();
	ButtonB->LocalTransform.SetTranslateY(-1.0);
	ButtonB->SetAnchorHor(0.6, 0.6);
	ButtonB->SetAnchorVer(0.5, 0.5);
	mUI->AttachChild(ButtonB);
	ButtonB->SetSize(70, 70);
	ButtonB->SetName("ButtinB");
	ButtonB->CreateAddText(("B"));
	ButtonB->Show(false);
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::OnCreateButtonC()
{
	ButtonC = UIButton::New();
	ButtonC->LocalTransform.SetTranslateY(-1.0);
	ButtonC->SetAnchorHor(0.5, 0.5);
	ButtonC->SetAnchorVer(0.65, 0.65);
	mUI->AttachChild(ButtonC);
	ButtonC->SetSize(70, 70);
	ButtonC->SetName("ButtinC");
	ButtonC->CreateAddText(("C"));
	ButtonC->Show(false);
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::OnCreateButtonD()
{
	ButtonD = UIButton::New();
	ButtonD->LocalTransform.SetTranslateY(-1.0);
	ButtonD->SetAnchorHor(0.5, 0.5);
	ButtonD->SetAnchorVer(0.35, 0.35);
	mUI->AttachChild(ButtonD);
	ButtonD->SetSize(70, 70);
	ButtonD->SetName("ButtinD");
	ButtonD->CreateAddText(("D"));
	ButtonD->Show(false);
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::OnCreateMenu()
{
	UIButton* ButtonMenu = UIButton::New();
	ButtonMenu->LocalTransform.SetTranslateY(-1.0);
	ButtonMenu->SetAnchorHor(0.95,0.95);
	ButtonMenu->SetAnchorVer(0.9, 0.9);
	mUI->AttachChild(ButtonMenu);
	ButtonMenu->SetSize(50,50);
	ButtonMenu->SetName("ButtonMenu");
	ButtonMenu->CreateAddText(PX2_LM_APP.GetValue("ButtonMenu"));
	ButtonMenu->AddUICallback(UIButtonCallBack);
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::OnCreateNewProject()
{
	UIButton* ButtonNewProject = UIButton::New();
	ButtonNewProject->LocalTransform.SetTranslateY(-1.0);
	ButtonNewProject->SetAnchorHor(0.9, 0.9);
	ButtonNewProject->SetAnchorVer(0.9, 0.9);
	mUI->AttachChild(ButtonNewProject);
	ButtonNewProject->SetSize(50, 50);
	ButtonNewProject->SetName("ButtonNewProject");
	ButtonNewProject->CreateAddText(PX2_LM_APP.GetValue("ButtonNewProject"));
	ButtonNewProject->AddUICallback(UIButtonCallBack);
}
//----------------------------------------------------------------------------
void SamplePlugin::OnCreateUICheckBox()
{
	//判断框
	mMenuCase->AddTab("UICheckBox", PX2_LM_APP.GetValue("UICheckBox"), frameUICheckBox);
	frameUICheckBox->LocalTransform.SetTranslateY(-1.0);
	frameUICheckBox->SetAnchorHor(0.0, 1.0);
	frameUICheckBox->SetAnchorVer(0.0, 1.0);

	UICheckButton* checkButton = UICheckButton::New();
	frameUICheckBox->AttachChild(checkButton);
	checkButton->SetName("CheckButton");
	checkButton->SetSize(40.0, 40.0);
	checkButton->SetScriptHandler("S_Callback");
	checkButton->RegistToScriptSystem();
	checkButton->SetAnchorHor(0.2, 0.2);

	UIFText* text0 = UIFText::New();
	frameUICheckBox->AttachChild(text0);
	text0->SetAnchorHor(0.2, 0.2);
	text0->SetAnchorVer(0.8, 0.8);
	text0->GetText()->SetText(PX2_LM_APP.GetValue("DefaultSele"));

	UICheckButton* checkButton1 = UICheckButton::New();
	frameUICheckBox->AttachChild(checkButton1);
	checkButton1->SetName("CheckButton1");
	checkButton1->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexture("Data/General/images/pics/whitern.png");
	checkButton1->GetPicBoxAtState(UIButtonBase::BS_PRESSED)->SetTexture("Data/General/images/pics/Tick.png");
	checkButton1->SetAnchorHor(0.8, 0.8);
	
	UIFText* text1 = UIFText::New();
	frameUICheckBox->AttachChild(text1);
	text1->SetAnchorHor(0.8, 0.8);
	text1->SetAnchorVer(0.8, 0.8);
	text1->GetText()->SetText(PX2_LM_APP.GetValue("CustomSele"));
}
//----------------------------------------------------------------------------
void SamplePlugin::OnCreateUIComboBox()
{
	//选择框
	mMenuCase->AddTab("UIComboBox", PX2_LM_APP.GetValue("UIComboBox"), frameUIComboBox);
	frameUIComboBox->LocalTransform.SetTranslateY(-1.0);
	frameUIComboBox->SetAnchorHor(0.0, 1.0);
	frameUIComboBox->SetAnchorVer(0.0, 1.0);
	
	UIComboBox* comboBox = UIComboBox::New();
	frameUIComboBox->AttachChild(comboBox);
	comboBox->AddChooseStr(PX2_LM_APP.GetValue("Choose0"));
	comboBox->AddChooseStr(PX2_LM_APP.GetValue("Choose1"));
	comboBox->ChooseStr(PX2_LM_APP.GetValue("Choose0"));
	comboBox->SetScriptHandler("S_Callback");
	comboBox->RegistToScriptSystem();
	comboBox->SetAnchorHor(0.2, 0.2);
	comboBox->SetAnchorVer(0.6, 0.6);

	UIFText* text0 = UIFText::New();
	frameUIComboBox->AttachChild(text0);
	text0->SetAnchorHor(0.2, 0.2);
	text0->SetAnchorVer(0.8, 0.8);
	text0->GetText()->SetText(PX2_LM_APP.GetValue("DefaultcheckBox"));

	UIComboBox* comboBox1 = UIComboBox::New();
	frameUIComboBox->AttachChild(comboBox1);
	comboBox1->GetChooseList()->GetBackgroundPicBox()->SetTexture("Data/General/images/pics/whitern.png");
	comboBox1->GetSelectButton()->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetPicBoxType(UIPicBox::PBT_NINE);
	comboBox1->GetSelectButton()->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexture("Data/General/images/pics/whitern.png");
	comboBox1->GetSelectButton()->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexCornerSize(12, 12, 12, 12);
	comboBox1->GetSelectButton()->SetStateColorDefaultWhite();
	comboBox1->GetSelectButton()->SetColor(Float3::MakeColor(180,179,171));
	comboBox1->GetChooseList()->GetBackgroundPicBox()->SetColor(Float3::MakeColor(219, 218, 211));
	comboBox1->GetChooseList()->GetSlider()->GetButSlider()->SetStateColorDefaultWhite();
	comboBox1->GetChooseList()->GetSlider()->GetButSlider()->SetColor(Float3::MakeColor(219,218,211));
	comboBox1->GetChooseList()->GetSlider()->GetButSlider()->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetPicBoxType(UIPicBox::PBT_NINE);
	comboBox1->GetChooseList()->GetSlider()->GetButSlider()->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexture("Data/General/images/pics/ButSlider.png");
	comboBox1->AddChooseStr(PX2_LM_APP.GetValue("Choose0"));
	comboBox1->AddChooseStr(PX2_LM_APP.GetValue("Choose1"));
	comboBox1->ChooseStr(PX2_LM_APP.GetValue("Choose0"));
	comboBox1->SetAnchorHor(0.8, 0.8);
	comboBox1->SetAnchorVer(0.6, 0.6);

	UIFText* text1 = UIFText::New();
	frameUIComboBox->AttachChild(text1);
	text1->SetAnchorHor(0.8, 0.8);
	text1->SetAnchorVer(0.8, 0.8);
	text1->GetText()->SetText(PX2_LM_APP.GetValue("CustomcheckBox"));
	
}
//----------------------------------------------------------------------------
void SamplePlugin::OnCreateUIEditBox()
{
	//编辑框
	mMenuCase->AddTab("UIEditBox", PX2_LM_APP.GetValue("UIEditBox"), frameUIEditBox);
	frameUIEditBox->LocalTransform.SetTranslateY(-1.0);
	frameUIEditBox->SetAnchorHor(0.0, 1.0);
	frameUIEditBox->SetAnchorVer(0.0, 1.0);
	UIEditBox* editbox = UIEditBox::New();
	frameUIEditBox->AttachChild(editbox);
	editbox->SetScriptHandler("S_Callback");
	editbox->SetAnchorHor(0.3, 0.3);
	editbox->SetAnchorVer(0.7, 0.7);
	editbox->RegistToScriptSystem();
	
	UIFText* text0 = UIFText::New();
	frameUIEditBox->AttachChild(text0);
	text0->SetAnchorHor(0.3, 0.3);
	text0->SetAnchorVer(0.8, 0.8);
	text0->GetText()->SetText(PX2_LM_APP.GetValue("Defaulteditor"));

	UIEditBox* editbox1 = UIEditBox::New();
	frameUIEditBox->AttachChild(editbox1);
	editbox1->SetAnchorHor(0.7, 0.7);
	editbox1->SetAnchorVer(0.7, 0.7);
	editbox1->SetScriptHandler("S_Callback");
	editbox1->RegistToScriptSystem();
	editbox1->SetPassword(true);

	UIFText* text1 = UIFText::New();
	frameUIEditBox->AttachChild(text1);
	text1->SetAnchorHor(0.7, 0.7);
	text1->SetAnchorVer(0.8, 0.8);
	text1->GetText()->SetText(PX2_LM_APP.GetValue("passwordtype"));
	text1->SetWidth(200);

	UIEditBox* editbox2 = UIEditBox::New();
	frameUIEditBox->AttachChild(editbox2);
	editbox2->GetBackPicBox()->GetUIPicBox()->SetPicBoxType(UIPicBox::PBT_NINE);
	editbox2->GetBackPicBox()->GetUIPicBox()->SetTexture("Data/General/images/pics/whitern.png");
	editbox2->GetBackPicBox()->GetUIPicBox()->SetTexCornerSize(12.0f, 12.0f, 12.0f, 12.0f);
	editbox2->SetAnchorHor(0.3, 0.3);
	editbox2->SetAnchorVer(0.3, 0.3);
	
	UIFText* text2 = UIFText::New();
	frameUIEditBox->AttachChild(text2);
	text2->SetAnchorHor(0.3, 0.3);
	text2->SetAnchorVer(0.4, 0.4);
	text2->GetText()->SetText(PX2_LM_APP.GetValue("Customeditor"));

	UIEditBox* editbox3 = UIEditBox::New();
	frameUIEditBox->AttachChild(editbox3);
	editbox3->GetBackPicBox()->GetUIPicBox()->SetPicBoxType(UIPicBox::PBT_NINE);
	editbox3->GetBackPicBox()->GetUIPicBox()->SetTexture("Data/General/images/pics/whitern.png");
	editbox3->GetBackPicBox()->GetUIPicBox()->SetTexCornerSize(12.0f, 12.0f, 12.0f, 12.0f);
	editbox3->SetAnchorHor(0.7, 0.7);
	editbox3->SetAnchorVer(0.3, 0.3);
	editbox3->SetPassword(true);

	UIFText* text3 = UIFText::New();
	frameUIEditBox->AttachChild(text3);
	text3->SetAnchorHor(0.7, 0.7);
	text3->SetAnchorVer(0.4, 0.4);
	text3->GetText()->SetText(PX2_LM_APP.GetValue("CustomPassword"));
	text3->SetWidth(200);
}
//----------------------------------------------------------------------------
void SamplePlugin::OnCreateUIProgress()
{
	//进度条
	mMenuCase->AddTab("UIProgress", PX2_LM_APP.GetValue("UIProgress"), frameUIProgress);
	frameUIProgress->LocalTransform.SetTranslateY(-1.0);
	frameUIProgress->SetAnchorHor(0.0, 1.0);
	frameUIProgress->SetAnchorVer(0.0, 1.0);
	UIProgressBar* progressBar = UIProgressBar::New();
	frameUIProgress->AttachChild(progressBar);
	progressBar->SetProgress(0.0);
	progressBar->SetScriptHandler("S_Callback");
	progressBar->RegistToScriptSystem();
	progressBar->SetAnchorHor(0.2,0.2);
	progressBar->SetAnchorVer(0.6, 0.6);
	progressBar->SetProgress(0.2);
	
	UIFText* text1 = UIFText::New();
	frameUIProgress->AttachChild(text1);
	text1->SetAnchorHor(0.2, 0.2);
	text1->SetAnchorVer(0.8, 0.8);
	text1->GetText()->SetText(PX2_LM_APP.GetValue("DefaultProgress"));
	
	progressBar1 = UIProgressBar::New();
	frameUIProgress->AttachChild(progressBar1);
	progressBar1->SetAnchorVer(0.6, 0.6);
	
	UIFText* text2 = UIFText::New();
	frameUIProgress->AttachChild(text2);
	text2->SetAnchorVer(0.8, 0.8);
	text2->GetText()->SetText(PX2_LM_APP.GetValue("Progressload"));

	UIButton* but1 = UIButton::New();
	frameUIProgress->AttachChild(but1);
	but1->SetName("start");
	but1->SetWidth(60);
	but1->SetAnchorVer(0.4, 0.4);
	but1->CreateAddText(PX2_LM_APP.GetValue("Start"));
	but1->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetPicBoxType(UIPicBox::PBT_NINE);
	but1->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexture("Data/General/images/pics/whitern.png");
	but1->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexCornerSize(12.0f, 12.0f, 12.0f, 12.0f);
	but1->AddUICallback(UIButtonCallBack);

	UIProgressBar* progressBar2 = UIProgressBar::New();
	frameUIProgress->AttachChild(progressBar2);
	progressBar2->SetAnchorVer(0.6, 0.6);
	progressBar2->SetAnchorHor(0.8, 0.8);
	progressBar2->GetBackPicBox()->GetUIPicBox()->SetTexture("Data/General/images/pics/progress.png");
	progressBar2->GetProgressPicBox()->GetUIPicBox()->SetColor(Float3::GREEN);
	progressBar2->SetProgress(0.5);
	
	UIFText* text3 = UIFText::New();
	frameUIProgress->AttachChild(text3);
	text3->SetAnchorVer(0.8, 0.8);
	text3->SetAnchorHor(0.8, 0.8);
	text3->GetText()->SetText(PX2_LM_APP.GetValue("CustomProgress"));
}
//----------------------------------------------------------------------------
void SamplePlugin::OnCreateUIColorSelect()
{
	//颜色选择
	mMenuCase->AddTab("UIColorSelect", PX2_LM_APP.GetValue("UIColorSelect"), frameUIColorSelect);
	frameUIColorSelect->LocalTransform.SetTranslateY(-1.0);
	frameUIColorSelect->SetAnchorHor(0.0, 1.0);
	frameUIColorSelect->SetAnchorVer(0.0, 1.0);
	UIColorSelector* colorSelect = UIColorSelector::New();
	frameUIColorSelect->AttachChild(colorSelect);
	colorSelect->SetScriptHandler("S_Callback");
	colorSelect->SetSize(300, 300);
	colorSelect->SetAnchorHor(0.5, 0.5);
	colorSelect->SetAnchorVer(0.5, 0.5);
	colorSelect->RegistToScriptSystem();
}
//----------------------------------------------------------------------------
void SamplePlugin::OnCreateUIList()
{
	//列表
	mMenuCase->AddTab("UIList",PX2_LM_APP.GetValue("UIList"), frameUIList);
	frameUIList->LocalTransform.SetTranslateY(-1.0);
	frameUIList->SetAnchorHor(0.0, 1.0);
	frameUIList->SetAnchorVer(0.0, 1.0);
	UIList* list = UIList::New();
	frameUIList->AttachChild(list);
	list->SetScriptHandler("S_Callback");
	list->AddItem("a");
	list->AddItem("b");
	list->AddItem("c");
	list->AddItem("d");
	list->RegistToScriptSystem();
}
//----------------------------------------------------------------------------
void SamplePlugin::OnCreateUITree()
{
	//树
	mMenuCase->AddTab("UITree", PX2_LM_APP.GetValue("UITree"), frameUITree);
	frameUITree->LocalTransform.SetTranslateY(-1.0);
	frameUITree->SetAnchorHor(0.0, 1.0);
	frameUITree->SetAnchorVer(0.0, 1.0);
	UITree* tree = UITree::New();
	frameUITree->AttachChild(tree);
	tree->SetScriptHandler("S_Callback");
	UIItem* itemA = tree->AddItem(tree->GetRootItem(), "a", "a");
	tree->AddItem(itemA, "aa", "aa");
	UIItem* itemB = tree->AddItem(tree->GetRootItem(), "b", "b");
	tree->AddItem(itemB, "bb", "bb");
	UIItem* itemC = tree->AddItem(tree->GetRootItem(), "c", "c");
	tree->AddItem(itemC, "cc", "cc");
	tree->SetSize(200, 200);
	tree->RegistToScriptSystem();
}
//----------------------------------------------------------------------------
void SamplePlugin::OnCreateUISlider()
{
	//滑动条
	mMenuCase->AddTab("UISlider", PX2_LM_APP.GetValue("UISlider"), frameUISlider);
	frameUISlider->LocalTransform.SetTranslateY(-1.0);
	frameUISlider->SetAnchorHor(0.0, 1.0);
	frameUISlider->SetAnchorVer(0.0, 1.0);

	UISlider* slider = UISlider::New();
	frameUISlider->AttachChild(slider);
	slider->SetName("Slider");
	slider->LocalTransform.SetTranslateY(-1.0);
	slider->GetFPicBoxBack()->GetUIPicBox()->SetPicBoxType(UIPicBox::PBT_NINE);
	slider->GetFPicBoxBack()->GetUIPicBox()->SetTexture("Data/General/images/pics/progressback.png");
	slider->GetButSlider()->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexture("Data/General/images/pics/slider1.png");
	slider->SetScriptHandler("S_Callback");
	slider->SetAnchorHor(0.3, 0.3);
	
	UISlider* slider1 = UISlider::New();
	frameUISlider->AttachChild(slider1);
	slider1->SetName("Slider1");
	slider1->LocalTransform.SetTranslateY(-1.0);
	slider1->GetFPicBoxBack()->GetUIPicBox()->SetPicBoxType(UIPicBox::PBT_NINE);
	slider1->GetFPicBoxBack()->GetUIPicBox()->SetTexture("Data/General/images/pics/progressback.png");
	slider1->GetButSlider()->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexture("Data/General/images/pics/slider1.png");
	slider1->SetAnchorHor(0.7, 0.7);
	slider1->SetScriptHandler("S_Callback");
	slider1->SetDirectionType(UISlider::DT_VERTICALITY);
	slider1->SetSize(20.0f, 200.0f);

	UIFText* Text1 = UIFText::New();
	frameUISlider->AttachChild(Text1);
	Text1->SetAnchorVer(0.8, 0.8);
	Text1->SetAnchorHor(0.3, 0.3);
	Text1->GetText()->SetText(PX2_LM_APP.GetValue("Transverseslider"));

	UIFText* Text2 = UIFText::New();
	frameUISlider->AttachChild(Text2);
	Text2->SetAnchorHor(0.7, 0.7);
	Text2->SetAnchorVer(0.8, 0.8);
	Text2->GetText()->SetText(PX2_LM_APP.GetValue("Longitudinalslider"));
}
//----------------------------------------------------------------------------
void SamplePlugin::OnCreateUIRound()
{
	//方向盘
	mMenuCase->AddTab("UIRound", PX2_LM_APP.GetValue("UIRound"), frameUIRound);
	frameUIRound->LocalTransform.SetTranslateY(-1.0);
	frameUIRound->SetAnchorHor(0,1.0);
	frameUIRound->SetAnchorVer(0.0, 1.0);

	UIRound* round0 = UIRound::New();
	frameUIRound->AttachChild(round0);
	round0->LocalTransform.SetTranslateY(-1.0);
	round0->SetAnchorHor(0.3, 0.3);
	round0->SetScriptHandler("s_CallBack");
	round0->RegistToScriptSystem();

	UIFText* Text0 = UIFText::New();
	frameUIRound->AttachChild(Text0);
	Text0->SetAnchorHor(0.3, 0.3);
	Text0->SetAnchorVer(0.8, 0.8);
	Text0->GetText()->SetText(PX2_LM_APP.GetValue("DefaultRound"));

	UIRound* round1 = UIRound::New();
	frameUIRound->AttachChild(round1);
	round1->GetButton()->SetStateColorDefaultWhite();
	round1->GetButton()->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexture("Data/General/images/pics/fangxiang.png");
	round1->GetButton()->GetPicBoxAtState(UIButtonBase::BS_HOVERED)->SetTexture("Data/General/images/pics/fangxiang.png");
	round1->GetButton()->GetPicBoxAtState(UIButtonBase::BS_PRESSED)->SetTexture("Data/General/images/pics/fangxiang.png");
	round1->GetButton()->SetSize(80, 80);
	round1->GetBack()->GetUIPicBox()->SetTexture("Data/General/images/pics/fangxiang1.png");
	round1->GetBack()->SetSize(200, 200);
	round1->SetAnchorHor(0.7, 0.7);

	UIFText* Text1 = UIFText::New();
	frameUIRound->AttachChild(Text1);
	Text1->SetAnchorHor(0.7, 0.7);
	Text1->SetAnchorVer(0.8, 0.8);
	Text1->GetText()->SetText(PX2_LM_APP.GetValue("Customwheel"));
}
//----------------------------------------------------------------------------
void SamplePlugin::OnCreateUIServer()
{
	//服务器
	mMenuCase->AddTab("Server", PX2_LM_APP.GetValue("Server"), frameServer);
	frameServer->LocalTransform.SetTranslateY(-1.0);
	frameServer->SetAnchorHor(0.0, 1.0);
	frameServer->SetAnchorVer(0.0, 1.0);
	UIWebFrame* webFrame = UIWebFrame::New();
	frameServer->AttachChild(webFrame);
	webFrame->SetAnchorHor(0.0, 1.0);
	webFrame->SetAnchorVer(0.0, 1.0);
	webFrame->SetUpdateToTex(true);
	webFrame->LoadURL("https://github.com/PhoenixCreate");
}
//----------------------------------------------------------------------------
void SamplePlugin::OnCreateUISplitter()
{
	//分隔线
	mMenuCase->AddTab("UISplitter", PX2_LM_APP.GetValue("UISplitter"), frameUISplitter);
	frameUISplitter->LocalTransform.SetTranslateY(-1.0);
	frameUISplitter->SetAnchorHor(0.0, 1.0);
	frameUISplitter->SetAnchorVer(0.0, 1.0);
	UISplitterFrame* splitter = UISplitterFrame::New();
	frameUISplitter->AttachChild(splitter);
	splitter->LocalTransform.SetTranslateY(-1.0);
	splitter->SetScriptHandler("S_Callback");
	splitter->SetSize(0.0, 4.0);
	splitter->SetAnchorHor(0.0, 1.0);
	splitter->SetAnchorParamHor(0.0, 0.0);
	splitter->SetAnchorVer(0.0, 0.0);
	splitter->SetAnchorParamVer(400.0, 400.0);
	splitter->RegistToScriptSystem();
}
//----------------------------------------------------------------------------
void SamplePlugin::AddRightUIFrame()
{
	//创建一个右的浏览框下内容
	UIFrame* rightFrame = UIFrame::New();
	MenuBg->AttachChild(rightFrame);
	rightFrame->CreateAddBackgroundPicBox(true, Float3::MakeColor(100, 200, 200));
	rightFrame->SetSize(FrameWidth, 0.0);
	rightFrame->SetPivot(0.0, 0.3);
	rightFrame->SetAnchorHor(1.0, 1.0);
	rightFrame->SetAnchorParamHor(-FrameWidth, 0.0);
	rightFrame->SetAnchorVer(0.0, 1.0);
	//添加一个上链表
	MsgList = UIList::New();
	rightFrame->AttachChild(MsgList);
	MsgList->SetAnchorHor(0.0, 1.0);
	MsgList->SetAnchorVer(0.0, 1.0);
	MsgList->AddItem(PX2_LM_APP.GetValue("Add+"));
}
//----------------------------------------------------------------------------
void SamplePlugin::AddOtherElements()
{
	//添加Logo图案
	UIFPicBox* logo = UIFPicBox::New();
	frame->AttachChild(logo);
	logo->SetName("Logo");
	logo->SetAnchorHor(0.0, 0.0);
	logo->SetAnchorParamHor(230.0, 230.0);
	logo->SetAnchorVer(1.0, 1.0);
	logo->SetAnchorParamVer(-50.0, -50.0);
	logo->SetSize(50.0, 50.0);
	logo->GetUIPicBox()->SetTexture("Data/engine/phoenix.png");
	//添加叙述性文本文字
	UIFText* textInfo = UIFText::New();
	frame->AttachChild(textInfo);
	textInfo->GetText()->SetText(PX2_LM_APP.GetValue("use the machine"));
	textInfo->SetAnchorHor(0.0, 0.0);
	textInfo->SetAnchorParamHor(270.0, 270.0);
	textInfo->SetPivot(0.0, 0.5);
	textInfo->SetAnchorVer(1.0, 1.0);
	textInfo->SetAnchorParamVer(-50.0, -50.0);
	textInfo->SetWidth(700.0);
	textInfo->GetText()->SetFontColor(Float3::WHITE);
	textInfo->GetText()->SetAligns(TEXTALIGN_LEFT + TEXTALIGN_TOP);
}
//----------------------------------------------------------------------------
void SamplePlugin::PrintMsg(const std::string &str)
{
	MsgList->AddItem(str);
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::RobotAction()
{

	//外圆
	UIFPicBox* fPicCircleOut = UIFPicBox::New();
	circleOut = fPicCircleOut;
	frame->AttachChild(fPicCircleOut);
	fPicCircleOut->LocalTransform.SetTranslateY(-1.0);
	fPicCircleOut->GetUIPicBox()->SetTexture("Data/Chaos/images/circle256.png");
	SetCircleOutColor(Float3::MakeColor(0, 54, 97));
	SetCircleOutSize(300);
	//内圆
	UIFPicBox* fPicCircleIn = UIFPicBox::New();
	circleIn = fPicCircleIn;
	frame->AttachChild(fPicCircleIn);
	fPicCircleIn->LocalTransform.SetTranslateY(-2.0);
	fPicCircleIn->GetUIPicBox()->SetTexture("Data/Chaos/images/circle256.png");
	SetCircleInColor(Float3::MakeColor(0, 121, 216));
	SetCircleInSize(260);
	//机器人脸部按钮
	uiBtn = UIButton::New();
	frame->AttachChild(uiBtn);
	uiBtn->LocalTransform.SetTranslateY(-3.0);
	uiBtn->SetStateColorDefaultWhite();
	uiBtn->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexture("Data/Chaos/images/circle256.png");
	SetFaceColor(Float3::MakeColor(0, 0, 0));
	SetCircleInSize(200);
	UIFPicBox* fPicYi = UIFPicBox::New();
	yiBackground = fPicYi;
	uiBtn->AttachChild(fPicYi);
	fPicYi->LocalTransform.SetTranslateY(-3.0);
	//是否显示图片
	fPicYi->SetColorSelfCtrled(true);
	fPicYi->GetUIPicBox()->SetTexture("Data/Chaos/images/yi.png");
	fPicYi->SetAnchorHor(0.0, 1.0);
	fPicYi->SetAnchorVer(0.0, 1.0);
	fPicYi->SetAnchorParamVer(1.0, 4.0);
	fPicYi->SetAlpha(0.2);
	//文本
	text = UIFText::New();
	frame->AttachChild(text);
	text->LocalTransform.SetTranslateY(-5.0);
	text->GetText()->SetFontColor(Float3::WHITE);
	text->GetText()->SetFontSize(36);
	text->SetAnchorVer(0.0, 0.0);
	text->SetAnchorParamVer(100.0, 100.0);
	text->SetSize(660.0, 200.0);
	//自动换行
	text->GetText()->SetAutoWarp(true);
	text->SetPivot(0.5, 0.5);
	//添加机器人控制（动作）
	ctrlOut = InterpCurveUniformScaleController::New();
	circleOutCtrl = ctrlOut;
	fPicCircleOut->AttachController(ctrlOut);
	ctrlIn = InterpCurveUniformScaleController::New();
	circleInCtrl = ctrlIn;
	fPicCircleIn->AttachController(ctrlIn);
	ctrlBtn = InterpCurveUniformScaleController::New();
	circleBtnCtrl = ctrlBtn;
	uiBtn->AttachController(ctrlBtn);
	//机器人自动说话
	PX2_VOICESDK.Speak("你好，我是混沌机器人");
	PX2_VOICESDK.EnableAutoSpeak(true);
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::SetCircleOutColor(const Float3 &color)
{
	circleOut->SetColor(color);
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::SetCircleOutSize(float size)
{
	circleOut->SetSize(Sizef(size, size));
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::SetCircleInColor(const Float3 &color)
{
	circleIn->SetColor(color);
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::SetCircleInSize(float size)
{
	circleIn->SetSize(Sizef(size, size));
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::SetFaceColor(const Float3 &color)
{
	uiBtn->SetColor(color);
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::SetFaceSize(float size)
{
	uiBtn->SetSize(Sizef(size, size));
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::RobotStartUp()
{
	//圆外
	circleOutCtrl->Clear();
	circleOutCtrl->AddPoint(0.0, 0.01, ICM_LINEAR);
	circleOutCtrl->AddPoint(ch_MT, 1.05, ICM_LINEAR);
	circleOutCtrl->AddPoint(ch_LT, 1.0, ICM_LINEAR);
	circleOutCtrl->MaxTime = ch_LT;
	circleOutCtrl->Repeat = Controller::RT_CLAMP;
	circleOutCtrl->SetDelayPlayTime(0.0);
	circleOutCtrl->ResetPlay();
	//圆内
	circleInCtrl->Clear();
	circleInCtrl->AddPoint(0.0, 0.01, ICM_LINEAR);
	circleInCtrl->AddPoint(ch_MT, 1.2, ICM_LINEAR);
	circleInCtrl->AddPoint(ch_LT, 1.0, ICM_LINEAR);
	circleInCtrl->MaxTime = ch_LT;
	circleInCtrl->Repeat = Controller::RT_CLAMP;
	circleInCtrl->SetDelayPlayTime(0.4);
	circleInCtrl->ResetPlay();
	//圆中心
	circleBtnCtrl->Clear();
	circleBtnCtrl->AddPoint(0.0, 0.01, ICM_LINEAR);
	circleBtnCtrl->AddPoint(ch_MT, 0.88, ICM_LINEAR);
	circleBtnCtrl->AddPoint(ch_LT, 1.0, ICM_LINEAR);
	circleBtnCtrl->MaxTime = ch_LT;
	circleBtnCtrl->Repeat = Controller::RT_CLAMP;
	circleBtnCtrl->SetDelayPlayTime(ch_LastDelay);
	circleBtnCtrl->ResetPlay();
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::RobotFreeze()
{
	//外圆
	circleOutCtrl->Clear();
	circleOutCtrl->AddPoint(0.0, 1.0, ICM_CURVE_AUTO);
	circleOutCtrl->MaxTime = 1.0;
	circleOutCtrl->Repeat = Controller::RT_WRAP;
	circleOutCtrl->ResetPlay();
	//内圆
	circleInCtrl->Clear();
	circleInCtrl->AddPoint(0.0, 1.0, ICM_CURVE_AUTO);
	circleInCtrl->MaxTime = 1.0;
	circleInCtrl->Repeat = Controller::RT_WRAP;
	circleInCtrl->ResetPlay();
	//圆中心
	circleBtnCtrl->Clear();
	circleBtnCtrl->AddPoint(0.0, 1.0, ICM_CURVE_AUTO);
	circleBtnCtrl->MaxTime = 1.0;
	circleBtnCtrl->Repeat = Controller::RT_WRAP;
	circleBtnCtrl->ResetPlay();
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::RobotIdle()
{
	//外圆
	circleOutCtrl->Clear();
	circleOutCtrl->AddPoint(0.0, 1.0, ICM_CURVE_AUTO);
	circleOutCtrl->AddPoint(1.5, 1.05, ICM_CURVE_AUTO);
	circleOutCtrl->AddPoint(3.0, 1.0, ICM_CURVE_AUTO);
	circleOutCtrl->MaxTime = 3.0;
	circleOutCtrl->Repeat = Controller::RT_WRAP;
	circleOutCtrl->ResetPlay();
	//内圆
	circleInCtrl->Clear();
	circleInCtrl->AddPoint(0.0, 1.0, ICM_CURVE_AUTO);
	circleInCtrl->AddPoint(1.5, 0.9, ICM_CURVE_AUTO);
	circleInCtrl->AddPoint(3.0, 1.0, ICM_CURVE_AUTO);
	circleInCtrl->MaxTime = 3.0;
	circleInCtrl->Repeat = Controller::RT_WRAP;
	circleInCtrl->ResetPlay();
	//圆心
	circleBtnCtrl->Clear();
	circleBtnCtrl->AddPoint(0.0, 1.0, ICM_CURVE_AUTO);
	circleBtnCtrl->AddPoint(1.5, 0.88, ICM_CURVE_AUTO);
	circleBtnCtrl->AddPoint(3.0, 1.0, ICM_CURVE_AUTO);
	circleBtnCtrl->MaxTime = 3.0;
	circleBtnCtrl->Repeat = Controller::RT_WRAP;
	circleBtnCtrl->ResetPlay();
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::RobotExcite()
{
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::Progressmove()
{
	progressBar1->SetProgressAnimInit(0.0);
	progressBar1->SetProgressAnim(1.0);
	progressBar1->SetProgressAnimSpeed(1.0);
}
//----------------------------------------------------------------------------
//界面是否显示
void PX2::SamplePlugin::Show()
{
	MenuBg->Show(!MenuBg->IsShow());
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::ShowABCD()
{
	ButtonA->Show(!ButtonA->IsShow());
	ButtonB->Show(!ButtonB->IsShow());
	ButtonC->Show(!ButtonC->IsShow());
	ButtonD->Show(!ButtonD->IsShow());
}
//----------------------------------------------------------------------------

void PX2::SamplePlugin::OnCreateProject()
{
	//背景
	ProjectBg = UIFrame::New();
	frame->AttachChild(ProjectBg);
	ProjectBg->SetAnchorHor(0.3, 0.7);
	ProjectBg->SetAnchorVer(0.3, 0.7);
	ProjectBg->SetAnchorParamHor(25.0, -25.0);
	ProjectBg->SetAnchorParamVer(25.0, -100.0);
	UITabFrame* ProjectCase = UITabFrame::New();
	ProjectBg->AttachChild(ProjectCase);
	ProjectCase->SetAnchorParamHor(0.0, -20);
	ProjectCase->CreateAddBackgroundPicBox(true, Float3::MakeColor(200, 200, 200));
	ProjectCase->SetTabBarHeight(20);
	//添加文本“创建新项目”名称
	UIFText* text = UIFText::New();
	ProjectCase->AttachChild(text);
	text->SetSize(90,90);
	text->GetText()->SetText(PX2_LM_APP.GetValue("Create new project"));
	text->SetWidth(300.0);
	text->SetAnchorVer(0.7,0.7);
	//添加编辑框
	UIEditBox* editbox1 = UIEditBox::New();
	ProjectCase->AttachChild(editbox1);
	editbox1->LocalTransform.SetTranslateY(-2.0);
	//确定按钮
	UIButton* ConfirmButton = UIButton::New();
	ProjectCase->AttachChild(ConfirmButton);
	ConfirmButton->SetAnchorHor(0.35, 0.45);
	ConfirmButton->SetAnchorVer(0.2, 0.3);
	ConfirmButton->LocalTransform.SetTranslateY(-2.0);
	ConfirmButton->CreateAddText(PX2_LM_APP.GetValue("Certain"));
	//取消按钮
	UIButton* CancelButton = UIButton::New();
	ProjectCase->AttachChild(CancelButton);
	CancelButton->SetAnchorHor(0.55,0.65);
	CancelButton->SetAnchorVer(0.2, 0.3);
	CancelButton->LocalTransform.SetTranslateY(-2.0);
	CancelButton->CreateAddText(PX2_LM_APP.GetValue("Cancel"));
	CancelButton->SetName("Cancel");
	CancelButton->AddUICallback(UIButtonCallBack);
	ProjectBg->Show(false);
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::ShowProject()
{
	ProjectBg->Show(!ProjectBg->IsShow());
}
//----------------------------------------------------------------------------
void PX2::SamplePlugin::OnCreatebuttonE()
{
	UIList* ButtonE = UIList::New();
	mUI->AttachChild(ButtonE);
	ButtonE->AddItem("a");

	ButtonE->AddItem("b");

	ButtonE->AddItem("c");

	ButtonE->AddItem("d");

	
}

































//void SamplePlugin::DoNewProject()
//{
//	mIsNewProject = false;
//	SamplePlugin dlg(Singleton);
//	int showModel =5001;
// 	if (5001==showModel)
// 	{
//		std::string name = mProjName;
//		int screenOriention = mSceenOrientation;
//		int width = mProjWidth;
//		int height = mProjHeight;
//		std::string pathName = name + "/";
//		bool isProjctFolderExist = PX2_RM.IsFileFloderExist("Data/" + pathName);
//		if (isProjctFolderExist)
//		{
//			//MessageBox(PX2_LM_EDITOR.V("n_Notice"), PX2_LM_EDITOR.V("n_TipCreateProject"),0);
//			return;
//		}
//		else
//		{
//			PX2_APP.CloseProject();
//			PX2_RM.CreateFloder("Data/", pathName);
//			PX2_RM.CreateFloder("Data/", pathName + "images/"); 
//			PX2_RM.CreateFloder("Data/", pathName + "models/");
//			PX2_RM.CreateFloder("Data/", pathName + "scenes/");
//			PX2_RM.CreateFloder("Data/", pathName + "scripts/");
//			PX2_RM.CreateFloder("Data/", pathName + "scripts/lua/");
//			PX2_RM.CreateFloder("Data/", pathName + "scripts/lua/editor/");
//			PX2_RM.CreateFloder("Data/", pathName + "scripts_server/");
//			PX2_RM.CreateFloder("Data/", pathName + "scripts_server/lua/");
//			PX2_RM.CreateFloder("Data/", pathName + "scripts_server/lua/editor/");
//
//// 			_CreateScriptFile(pathName, "scripts/lua/", "play.lua", "play");
//// 			_CreateScriptFile(pathName, "scripts/lua/", "stop.lua", "stop");
//// 			_CreateScriptFile(pathName, "scripts/lua/editor/", "editor.lua", "editorplay");
//// 
//// 			_CreateScriptFile(pathName, "scripts_server/lua/", "play.lua", "play");
//// 			_CreateScriptFile(pathName, "scripts_server/lua/", "stop.lua", "stop");
//// 			_CreateScriptFile(pathName, "scripts_server/lua/editor/", "editor.lua", "editorstop");
//
//			std::string path = "Data/" + pathName + name + ".px2proj";
//			PX2_APP.NewProject(path, name, screenOriention, width,
//				height);
//
//		}
// 	}	
//	
//	
//}















