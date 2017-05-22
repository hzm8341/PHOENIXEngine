// PX2EngineCanvas.cpp

#include "PX2EngineCanvas.hpp"
#include "PX2ProjectEvent.hpp"
#include "PX2Project.hpp"
#include "PX2GraphicsRoot.hpp"
#include "PX2UIFPicBox.hpp"
#include "PX2ProjectEvent.hpp"
#include "PX2ProjectEventController.hpp"
#include "PX2Application.hpp"
#include "PX2UIProgressBar.hpp"
#include "PX2DNS.hpp"
#include "PX2HostEntry.hpp"
#include "PX2VoiceSDK.hpp"
#include "PX2Float3.hpp"
#include "PX2GraphicsEventType.hpp"
#include "PX2EngineNetEvent.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Canvas, EngineCanvas);
PX2_IMPLEMENT_STREAM(EngineCanvas);
PX2_IMPLEMENT_FACTORY(EngineCanvas);
PX2_IMPLEMENT_DEFAULT_NAMES(Canvas, EngineCanvas);

//----------------------------------------------------------------------------
void _EngineUICallback (UIFrame *frame, UICallType type)
{
	EngineCanvas *engineCanvas = EngineCanvas::GetSingletonPtr();
	UIFrame *engineFrame = engineCanvas->GetEngineFrame();

	const std::string &name = frame->GetName();
	UIButton *but = DynamicCast<UIButton>(frame);
	UICheckButton *checkBut = DynamicCast<UICheckButton>(frame);
	if (UICT_RELEASED == type)
	{
		if (but)
		{
			if ("ButEngine" == name)
			{
				engineFrame->Show(!engineFrame->IsShow());
			}
			else if ("ButClose" == name)
			{
				engineFrame->Show(false);
			}
			else if ("ButSpeak" == name)
			{
				UIFText *text = DynamicCast<UIFText>(
					engineCanvas->GetEngineFrame()->GetObjectByName("TextIP"));
				const std::string &strText = text->GetText()->GetText();
				if (!strText.empty())
				{
					PX2_VOICESDK.Speak(strText);
				}
			}
			else if ("ButStartEngineServer" == name)
			{
				EngineServer *es = PX2_APP.GetEngineServer();
				if (es)
				{
					if (!es->IsStarted())
					{
						bool ret = es->Start();
						if (ret)
						{
							but->GetText()->SetText("ShutdownEngineServer");

							UIFText *text = DynamicCast<UIFText>(
								engineCanvas->GetEngineFrame()->GetObjectByName("TextIP"));
							std::string ipStr;
							int port = es->GetPort();
#if defined (__ANDROID__)
							ipStr = HostEntry::GetAndroidIP(); 
#else
							HostEntry hostEntry = DNS::GetThisHost();
							HostEntry::AddressList addressList = hostEntry.GetAddresses();
							if (addressList.size() > 0)
							{
								IPAddress ipAddress = addressList[0];
								ipStr = ipAddress.ToString();
							}
#endif
							std::string ipPortStr = ipStr + ":" + 
								StringHelp::IntToString(port);
							text->GetText()->SetText(ipPortStr);
						}
					}
					else
					{
						es->Shutdown();
						but->GetText()->SetText("StartEngineServer");

						UIFText *text = DynamicCast<UIFText>(
							engineCanvas->GetEngineFrame()->GetObjectByName("TextIP"));
						text->GetText()->SetText("");
					}
				}
			}
			else if ("ButClientConnect" == name)
			{
				bool isConnected = PX2_APP.GetEngineClientConnector()->IsConnected();
				if (!isConnected)
				{
					UIEditBox *editBoxIP = DynamicCast<UIEditBox>(
						engineCanvas->GetEngineFrame()->GetObjectByName("EditBoxIP"));
					const std::string &editBoxIPText = editBoxIP->GetText();

					UIEditBox *editBoxPort = DynamicCast<UIEditBox>(
						engineCanvas->GetEngineFrame()->GetObjectByName("EditBoxPort"));
					const std::string &editBoxPortText = editBoxPort->GetText();
					int port = StringHelp::StringToInt(editBoxPortText);

					std::string cntStr = editBoxIPText + ":" + editBoxPortText;
					engineCanvas->GetEngineInfoList()->AddItem(cntStr);

					PX2_APP.GetEngineClientConnector()->ConnectNB(editBoxIPText, port);
				}
				else
				{
					PX2_APP.GetEngineClientConnector()->Disconnect();
					but->GetText()->SetText("ConnectToServer");

					UIEditBox *editBoxIP = DynamicCast<UIEditBox>(
						engineCanvas->GetEngineFrame()->GetObjectByName("EditBoxIP"));
					editBoxIP->Enable(true);
					UIEditBox *editBoxPort = DynamicCast<UIEditBox>(
						engineCanvas->GetEngineFrame()->GetObjectByName("EditBoxPort"));
					editBoxPort->Enable(true);
				}
			}
		}
	}
	else if (UICT_CHECKED == type)
	{
		if (checkBut)
		{
			if ("CheckAutoConnect" == name)
			{
				UIEditBox *editBoxIP = DynamicCast<UIEditBox>(
					engineCanvas->GetEngineFrame()->GetObjectByName("EditBoxIP"));
				UIEditBox *editBoxPort = DynamicCast<UIEditBox>(
					engineCanvas->GetEngineFrame()->GetObjectByName("EditBoxPort"));
				const std::string &textIP = editBoxIP->GetText();
				const std::string &textPort = editBoxPort->GetText();
				int port = StringHelp::StringToInt(textPort);

				bool isCheck = checkBut->IsCheck();
				EngineClientConnector *cnt = PX2_APP.GetEngineClientConnector();
				cnt->SetAutoConnectIP(textIP);
				cnt->SetAutoConnectPort(port);
				cnt->SetAutoConnect(isCheck);
			}
		}
	}
}
//----------------------------------------------------------------------------
EngineCanvas::EngineCanvas()
{
	CreateUICameraNode();

	SetClearFlag(true, true, true);
	SetClearColor(Float4::MakeColor(0, 0, 0, 255));

	EngineSceneCanvas *sceneCanvas = new0 EngineSceneCanvas();
	AttachChild(sceneCanvas);
	mEngineSceneCanvas = sceneCanvas;

	sceneCanvas->AttachController(new0 ProjectEventController());
	sceneCanvas->SetName("ProjectSceneCanvas");
	sceneCanvas->EnableAnchorLayout(true);
	sceneCanvas->SetAnchorHor(0.0f, 1.0f);
	sceneCanvas->SetAnchorVer(0.0f, 1.0f);
	sceneCanvas->SetClearFlag(true, true, true);
	sceneCanvas->SetClearColor(Float4::MakeColor(30, 30, 30, 255));
	sceneCanvas->SetRenderNodeUpdate(true);

	EngineUICanvas *uiCanvas = new0 EngineUICanvas();
	AttachChild(uiCanvas);
	mEngineUICanvas = uiCanvas;
	uiCanvas->SetUpdatePriority(10);
	uiCanvas->LocalTransform.SetTranslateY(-10.0f);
	uiCanvas->AttachController(new0 ProjectEventController());
	uiCanvas->SetName("ProjectUICanvas");
	uiCanvas->EnableAnchorLayout(true);
	uiCanvas->SetAnchorHor(0.0f, 1.0f);
	uiCanvas->SetAnchorVer(0.0f, 1.0f);
	uiCanvas->SetClearFlag(false, true, true);
	uiCanvas->SetRenderNodeUpdate(true);

	UIFramePtr frame = new0 UIFrame();
	AttachChild(frame);
	UIPicBox *backPic = frame->CreateAddBackgroundPicBox();
	backPic->UseAlphaBlend(true);
	backPic->SetAlpha(0.4f);
	frame->SetAnchorHor(0.0f, 1.0f);
	frame->SetAnchorVer(1.0f, 1.0f);
	frame->SetSize(0.0f, 24.0f);
	frame->SetPivot(0.5f, 1.0f);
	mInfoFrame = frame;
	mInfoFrame->LocalTransform.SetTranslateY(-50.0f);

	UIFTextPtr infoText = new0 UIFText();
	frame->AttachChild(infoText);
	infoText->SetAnchorHor(0.0f, 1.0f);
	infoText->SetAnchorVer(0.0f, 1.0f);
	infoText->SetPivot(0.5f, 0.5f);
	infoText->GetText()->SetText("FPS:0");
	infoText->GetText()->SetFontWidthHeight(16, 16);
	infoText->GetText()->SetFontColor(Float3::WHITE);
	infoText->GetText()->SetAligns(TEXTALIGN_LEFT | TEXTALIGN_VCENTER);
	mInfoText = infoText;

	float butWidth = 140.0f;
	mEngineBut = new0 UIButton();
	frame->AttachChild(mEngineBut);
	mEngineBut->SetAnchorHor(1.0f, 1.0f);
	mEngineBut->SetAnchorVer(0.0f, 1.0f);
	mEngineBut->SetPivot(1.0f, 0.5f);
	mEngineBut->SetWidth(butWidth);
	mEngineBut->LocalTransform.SetTranslateY(-1.0f);
	mEngineBut->SetName("ButEngine");
	mEngineBut->CreateAddText("Engine");
	mEngineBut->AddUICallback(_EngineUICallback);

	UIFTextPtr debugText = new0 UIFText();
	frame->AttachChild(debugText);
	debugText->SetAnchorHor(0.0f, 1.0f);
	debugText->SetAnchorVer(0.0f, 1.0f);
	debugText->SetAnchorParamHor(0.0f, -butWidth);
	debugText->SetPivot(0.5f, 0.5f);
	debugText->GetText()->SetText("");
	debugText->GetText()->SetFontWidthHeight(16, 16);
	debugText->GetText()->SetFontColor(Float3::WHITE);
	debugText->GetText()->SetAligns(TEXTALIGN_RIGHT | TEXTALIGN_VCENTER);
	mDebugText = debugText;
	_CreateEngineFrame();

	mFPS = 0;
	mFPSUpdate = 0;
	mFPSUpdateTime = 0.0f;

	SetName("EngineCanvas");

	EnableAnchorLayout(true);
	SetSize(800.0f, 800.0f);
	SetAnchorHor(0.5f, 0.5f);
	SetAnchorVer(0.5f, 0.5f);
	EnableScreenRectLayout(false);

	ComeInEventWorld();
}
//----------------------------------------------------------------------------
EngineCanvas::~EngineCanvas()
{
}
//----------------------------------------------------------------------------
void EngineCanvas::_CreateEngineFrame()
{
	mEngineFrame = new0 UIFrame();
	AttachChild(mEngineFrame);
	mEngineFrame->SetWidget(true);
	UIPicBox *picBox = mEngineFrame->CreateAddBackgroundPicBox();
	picBox->UseAlphaBlend(true);
	picBox->SetColor(Float3::MakeColor(180, 180, 180));
	picBox->SetAlpha(0.6f);
	mEngineFrame->LocalTransform.SetTranslateY(-50.0f);
	mEngineFrame->SetAnchorHor(0.0f, 1.0f);
	mEngineFrame->SetAnchorParamHor(200.0f, -200.0f);
	mEngineFrame->SetAnchorVer(0.0f, 1.0f);
	mEngineFrame->SetAnchorParamVer(60.0f, -60.0f);
	mEngineFrame->Show(false);

	UIButton *butClose = new0 UIButton();
	mEngineFrame->AttachChild(butClose);
	butClose->SetName("ButClose");
	butClose->LocalTransform.SetTranslateY(-1.0f);
	butClose->SetAnchorHor(1.0f, 1.0f);
	butClose->SetAnchorVer(1.0f, 1.0f);
	butClose->SetPivot(1.0f, 1.0f);
	butClose->SetSize(30.0f, 30.0f);
	butClose->CreateAddText("X");
	butClose->GetText()->SetFontColor(Float3::WHITE);
	butClose->AddUICallback(_EngineUICallback);

	Float4 clearColor = Float4::MakeColor(150, 150, 150, 255);
	Float3 clearColor3 = Float3::MakeColor(150, 150, 150);

	Canvas *canvas = new0 Canvas();
	mEngineFrame->AttachChild(canvas);
	canvas->LocalTransform.SetTranslateY(-1.0f);
	canvas->SetAnchorHor(0.0, 1.0f);
	canvas->SetAnchorVer(0.0, 1.0f);
	canvas->SetAnchorParamHor(10.0f, -10.0f);
	canvas->SetAnchorParamVer(10.0f, -40.0f);
	canvas->CreateUICameraNode();
	canvas->SetClearColor(clearColor);

	mEngineCollapsePanel = new0 UICollapsePanel();
	canvas->AttachChild(mEngineCollapsePanel);
	mEngineCollapsePanel->LocalTransform.SetTranslateY(-1.0f);
	mEngineCollapsePanel->SetAnchorHor(0.0, 1.0f);
	mEngineCollapsePanel->SetAnchorVer(0.0, 1.0f);

	// Engine Server
	UICollapseItem *itemEngineServer = mEngineCollapsePanel->AddItem("EngineServer");

	UIFrame *frameInfo = new0 UIFrame();
	itemEngineServer->GetContentFrame()->AttachChild(frameInfo);
	frameInfo->SetAnchorHor(0.0f, 1.0f);
	frameInfo->SetAnchorVer(0.0f, 1.0f);
	frameInfo->SetPivot(0.5f, 1.0f);

	float spaceHeight = 5.0f;
	float textIPHeight = 20.0f;
	float posVer = -textIPHeight*0.5f;
	posVer -= spaceHeight;

	UIFText *textIP = new0 UIFText();
	frameInfo->AttachChild(textIP);
	textIP->SetName("TextIP");
	UIPicBox *picBoxBack = textIP->CreateAddBackgroundPicBox();
	picBoxBack->UseAlphaBlend(true);
	picBoxBack->SetColor(Float3::MakeColor(200, 200, 200));
	textIP->LocalTransform.SetTranslateY(-1.0f);
	textIP->GetText()->SetAligns(TEXTALIGN_LEFT | TEXTALIGN_VCENTER);
	textIP->SetAnchorHor(0.0f, 1.0f);
	textIP->SetAnchorParamHor(100.0f, -100.0f);
	textIP->SetAnchorVer(1.0f, 1.0f);
	textIP->SetAnchorParamVer(posVer, posVer);
	textIP->GetText()->SetText("");
	textIP->SetHeight(textIPHeight);

	UIButton *butSpeakIP = new0 UIButton();
	frameInfo->AttachChild(butSpeakIP);
	butSpeakIP->LocalTransform.SetTranslateY(-2.0f);
	butSpeakIP->SetName("ButSpeak");
	butSpeakIP->SetPivot(0.0f, 0.5f);
	butSpeakIP->SetAnchorHor(1.0f, 1.0f);
	butSpeakIP->SetAnchorParamHor(-95.0f, -95.0f);
	butSpeakIP->SetAnchorVer(1.0f, 1.0f);
	butSpeakIP->SetAnchorParamVer(posVer, posVer);
	butSpeakIP->SetSize(20.0f, 20.0f);
	butSpeakIP->CreateAddText("Say");
	butSpeakIP->AddUICallback(_EngineUICallback);

	posVer -= textIPHeight*0.5f;
	posVer -= spaceHeight;

	float progBarHeight = 30.0f;
	posVer -= progBarHeight*0.5f;

	UIProgressBar *pbBar = new0 UIProgressBar();
	frameInfo->AttachChild(pbBar);
	pbBar->LocalTransform.SetTranslateY(-1.0f);
	pbBar->SetHeight(25.0f);
	pbBar->SetProgress(0.0f, false);
	pbBar->CreateAddProgressText();
	pbBar->SetAnchorHor(0.0f, 1.0f);
	pbBar->SetAnchorParamHor(100.0f, -100.0f);
	pbBar->SetAnchorVer(1.0f, 1.0f);
	pbBar->SetAnchorParamVer(posVer, posVer);

	posVer -= progBarHeight*0.5f;
	posVer -= spaceHeight;

	float butStartEngineHeight = 30.0f;
	posVer -= butStartEngineHeight*0.5f;

	UIButton *butStartEngineServer = new0 UIButton();
	frameInfo->AttachChild(butStartEngineServer);
	butStartEngineServer->SetHeight(butStartEngineHeight);
	butStartEngineServer->SetName("ButStartEngineServer");
	butStartEngineServer->LocalTransform.SetTranslateY(-1.0f);
	butStartEngineServer->SetAnchorVer(1.0f, 1.0f);
	butStartEngineServer->SetAnchorParamVer(posVer, posVer);
	butStartEngineServer->SetAnchorHor(0.0f, 1.0f);
	butStartEngineServer->SetAnchorParamHor(100.0f, -100.0f);
	butStartEngineServer->CreateAddText("StartEngineServer");
	butStartEngineServer->GetText()->SetFontColor(Float3::WHITE);
	butStartEngineServer->AddUICallback(_EngineUICallback);

	posVer -= butStartEngineHeight*0.5f;
	posVer -= spaceHeight;

	itemEngineServer->SetContentHeight(-posVer);

	// Engine Client Connector
	UICollapseItem *itemClientConnector = mEngineCollapsePanel->AddItem("EngineClientConnector");
	UIFrame *frameClientConnector = new0 UIFrame();
	itemClientConnector->GetContentFrame()->AttachChild(frameClientConnector);
	frameClientConnector->SetAnchorHor(0.0f, 1.0f);
	frameClientConnector->SetAnchorVer(0.0f, 1.0f);

	float textConnectIPHeight = 20.0f;
	posVer = -textConnectIPHeight*0.5f;
	posVer -= spaceHeight;

	UIEditBox *editBoxIP = new0 UIEditBox();
	frameClientConnector->AttachChild(editBoxIP);
	editBoxIP->SetName("EditBoxIP");
	editBoxIP->LocalTransform.SetTranslateY(-1.0f);
	editBoxIP->GetBackPicBox()->SetColor(Float3::MakeColor(200, 200, 200));
	editBoxIP->SetAnchorHor(0.0f, 0.5f);
	editBoxIP->SetAnchorParamHor(100.0f, 0.0f);
	editBoxIP->SetAnchorVer(1.0f, 1.0f);
	editBoxIP->SetAnchorParamVer(posVer, posVer);
	editBoxIP->SetHeight(textConnectIPHeight);
	editBoxIP->SetText("127.0.0.1");
	UIFText *textCntIP = new0 UIFText();
	frameClientConnector->AttachChild(textCntIP);
	textCntIP->LocalTransform.SetTranslateY(-1.0f);
	textCntIP->SetWidth(95.0f);
	textCntIP->SetPivot(0.0f, 0.5f);
	textCntIP->SetAnchorHor(0.0f, 0.0f);
	textCntIP->SetAnchorVer(1.0f, 1.0f);
	textCntIP->SetAnchorParamVer(posVer, posVer);
	textCntIP->SetHeight(textConnectIPHeight);
	textCntIP->GetText()->SetAligns(TEXTALIGN_RIGHT | TEXTALIGN_VCENTER);
	textCntIP->GetText()->SetText("IP:");
	textCntIP->GetText()->SetFontScale(0.8f);

	UIEditBox *editBoxPort = new0 UIEditBox();
	frameClientConnector->AttachChild(editBoxPort);
	editBoxPort->SetName("EditBoxPort");
	editBoxPort->LocalTransform.SetTranslateY(-1.0f);
	editBoxPort->GetBackPicBox()->SetColor(Float3::MakeColor(200, 200, 200));
	editBoxPort->SetAnchorHor(0.5f, 1.0f);
	editBoxPort->SetAnchorParamHor(50.0f, -100.0f);
	editBoxPort->SetAnchorVer(1.0f, 1.0f);
	editBoxPort->SetAnchorParamVer(posVer, posVer);
	editBoxPort->SetHeight(textConnectIPHeight);
	editBoxPort->SetText("7717");
	UIFText *textCntPort = new0 UIFText();
	frameClientConnector->AttachChild(textCntPort);
	textCntPort->SetName("EditBoxPort");
	textCntPort->SetWidth(45.0f);
	textCntPort->SetPivot(0.0f, 0.5f);
	textCntPort->SetAnchorHor(0.5f, 0.5f);
	textCntPort->SetAnchorVer(1.0f, 1.0f);
	textCntPort->SetAnchorParamVer(posVer, posVer);
	textCntPort->SetHeight(textConnectIPHeight);
	textCntPort->GetText()->SetAligns(TEXTALIGN_RIGHT | TEXTALIGN_VCENTER);
	textCntPort->GetText()->SetText("Port:");
	textCntPort->GetText()->SetFontScale(0.8f);

	posVer -= textConnectIPHeight*0.5f;
	posVer -= spaceHeight;

	float butConnectHeight = 30.0f;
	posVer -= butConnectHeight*0.5f;

	UIButton *butConnect = new0 UIButton();
	frameClientConnector->AttachChild(butConnect);
	butConnect->SetHeight(butConnectHeight);
	butConnect->SetName("ButClientConnect");
	butConnect->LocalTransform.SetTranslateY(-1.0f);
	butConnect->SetAnchorVer(1.0f, 1.0f);
	butConnect->SetAnchorParamVer(posVer, posVer);
	butConnect->SetAnchorHor(0.0f, 1.0f);
	butConnect->SetAnchorParamHor(100.0f + butConnectHeight + 10.0f, -100.0f);
	butConnect->CreateAddText("ConnectToServer");
	butConnect->GetText()->SetFontColor(Float3::WHITE);
	butConnect->AddUICallback(_EngineUICallback);

	UICheckButton *checkAutoCnt = new0 UICheckButton();
	frameClientConnector->AttachChild(checkAutoCnt);
	checkAutoCnt->SetName("CheckAutoConnect");
	checkAutoCnt->LocalTransform.SetTranslateY(-1.0f);
	checkAutoCnt->SetPivot(0.0f, 0.5f);
	checkAutoCnt->SetAnchorVer(1.0f, 1.0f);
	checkAutoCnt->SetAnchorParamHor(100.0f, 100.0f);
	checkAutoCnt->SetAnchorParamVer(posVer, posVer);
	checkAutoCnt->SetAnchorHor(0.0f, 0.0f);
	checkAutoCnt->SetSize(butConnectHeight, butConnectHeight);
	checkAutoCnt->AddUICallback(_EngineUICallback);
	checkAutoCnt->Check(false, false);

	UIFText *textAutoCnt = new0 UIFText();
	frameClientConnector->AttachChild(textAutoCnt);
	textAutoCnt->LocalTransform.SetTranslateY(-1.0f);
	textAutoCnt->SetWidth(95.0f);
	textAutoCnt->SetPivot(0.0f, 0.5f);
	textAutoCnt->SetAnchorHor(0.0f, 0.0f);
	textAutoCnt->SetAnchorVer(1.0f, 1.0f);
	textAutoCnt->SetAnchorParamVer(posVer, posVer);
	textAutoCnt->SetHeight(textConnectIPHeight);
	textAutoCnt->GetText()->SetAligns(TEXTALIGN_RIGHT | TEXTALIGN_VCENTER);
	textAutoCnt->GetText()->SetText("IsAutoConnect");
	textAutoCnt->GetText()->SetFontScale(0.8f);

	posVer -= butConnectHeight*0.5f;
	posVer -= spaceHeight;

	itemClientConnector->SetContentHeight(-posVer);

	// Infos
	UICollapseItem *itemInfos = mEngineCollapsePanel->AddItem("Infos");
	mEngineInfoList = new0 UIList();
	mEngineInfoList->SetNumMaxItems(20);
	UIPicBox *backInfoList = mEngineInfoList->CreateAddBackgroundPicBox(true);
	backInfoList->UseAlphaBlend(true);
	itemInfos->GetContentFrame()->AttachChild(mEngineInfoList);
	mEngineInfoList->LocalTransform.SetTranslateY(-2.0f);
	mEngineInfoList->SetAnchorHor(0.0f, 1.0f);
	mEngineInfoList->SetAnchorVer(0.0f, 1.0f);
	itemInfos->SetContentHeight(300.0f);
}
//----------------------------------------------------------------------------
void EngineCanvas::SetScreenRect(const Rectf &rect)
{
	Canvas::SetScreenRect(rect);
}
//----------------------------------------------------------------------------
void EngineCanvas::OnEvent(Event *event)
{
	if (ProjectES::IsEqual(event, ProjectES::NewProject) || 
		ProjectES::IsEqual(event, ProjectES::LoadedProject))
	{
		const Sizef &projSize = PX2_PROJ.GetSize();
		_CalSize(projSize);
	}
	else if (GraphicsES::IsEqual(event, GraphicsES::WindowSizeChanged))
	{
		Project *proj = Project::GetSingletonPtr();
		if (proj)
		{
			const Sizef &projSize = proj->GetSize();
			_CalSize(projSize);
		}
	}
	else if (EngineNetES::IsEqual(event, EngineNetES::OnEngineClientConnected))
	{
		UIButton *butClientConnect = DynamicCast<UIButton>(
			GetEngineFrame()->GetObjectByName("ButClientConnect"));
		butClientConnect->GetText()->SetText("DisConnect");

		UIEditBox *editBoxIP = DynamicCast<UIEditBox>(
			GetEngineFrame()->GetObjectByName("EditBoxIP"));
		editBoxIP->Enable(false);
		UIEditBox *editBoxPort = DynamicCast<UIEditBox>(
			GetEngineFrame()->GetObjectByName("EditBoxPort"));
		editBoxPort->Enable(false);

		UIList *list = GetEngineInfoList();
		list->AddItem("EngineClientConnectorConnected");
	}
	else if (EngineNetES::IsEqual(event, EngineNetES::OnEngineClientDisConnected))
	{
		UIList *list = GetEngineInfoList();
		list->AddItem("EngineClientConnectorDisConnected");
	}
	else if (EngineNetES::IsEqual(event, EngineNetES::OnEngineServerBeConnected))
	{
		const std::string &cntStr = event->GetDataStr0();

		UIList *list = GetEngineInfoList();
		list->AddItem("EngineServerBeConnected :" + cntStr);
	}
	else if (EngineNetES::IsEqual(event, EngineNetES::OnEngineServerBeDisConnected))
	{
		const std::string &cntStr = event->GetDataStr0();

		UIList *list = GetEngineInfoList();
		list->AddItem("EngineServerBeDisConnected :" + cntStr);
	}
}
//----------------------------------------------------------------------------
void EngineCanvas::OnSizeChanged()
{
	Canvas::OnSizeChanged();
}
//----------------------------------------------------------------------------
void EngineCanvas::_CalSize(const Sizef &projSize)
{
	SizeNode *parent = DynamicCast<SizeNode>(GetParent());
	if (!parent) return;

	const Sizef &parentSize = parent->GetSize();

	float parentHeightOverWidth = parentSize.Height / parentSize.Width;
	float projHeightOverWidth = projSize.Height / projSize.Width;

	float useWidth = projSize.Width;
	float useHeight = projSize.Height;

	if (parentHeightOverWidth > projHeightOverWidth)
	{
		useWidth = projSize.Width;
		useHeight = useWidth * parentHeightOverWidth;
	}
	else
	{
		useHeight = projSize.Height;
		useWidth = useHeight / parentHeightOverWidth;
	}

	SetSize(useWidth, useHeight);
}
//----------------------------------------------------------------------------
void EngineCanvas::UpdateLayout(Movable *parent)
{
	bool isLayoutChanged = mIsLayoutChanged;
	Canvas::UpdateLayout(parent);
	if (isLayoutChanged)
	{
		Project *proj = Project::GetSingletonPtr();
		if (proj)
		{
			const Sizef &projSize = proj->GetSize();
			_CalSize(projSize);
		}
	}
}
//----------------------------------------------------------------------------
void EngineCanvas::SetDebugText(const std::string &debugText)
{
	if (mDebugText)
	{
		mDebugText->GetText()->SetText(debugText);
		mEngineInfoList->AddItem(debugText);
	}
}
//----------------------------------------------------------------------------
UIFrame *EngineCanvas::GetEngineFrame()
{
	return mEngineFrame;
}
//----------------------------------------------------------------------------
UIList *EngineCanvas::GetEngineInfoList()
{
	return mEngineInfoList;
}
//----------------------------------------------------------------------------
void EngineCanvas::UpdateWorldData(double applicationTime,
	double elapsedTime)
{
	Canvas::UpdateWorldData(applicationTime, elapsedTime);

	Project *proj = Project::GetSingletonPtr();
	if (!proj)
	{
		SetAnchorHor(0.0, 1.0);
		SetAnchorVer(0.0, 1.0);
	}
	else
	{
		SetAnchorHor(0.5f, 0.5f);
		SetAnchorVer(0.5f, 0.5f);
	}

	SizeNode *parent = DynamicCast<SizeNode>(GetParent());
	if (!parent) return;
	SetScreenRect(parent->GetScreenRect());

	bool isShowInfo = PX2_APP.IsShowInfo();
	mInfoFrame->Show(isShowInfo);
	if (!isShowInfo)
		return;

	mFPSUpdate++;
	mFPSUpdateTime += (float)elapsedTime;

	if (mFPSUpdateTime > 0.1f)
	{
		mFPS = (int)((float)mFPSUpdate / (float)mFPSUpdateTime);
		mFPSUpdate = 0;
		mFPSUpdateTime = 0.0f;
	}

	int numPerFrame = 0;
	Renderer *renderer = Renderer::GetDefaultRenderer();
	if (renderer)
	{
		numPerFrame = renderer->GetNumDrawPrimitivePerFrame();
	}		

	std::string infoStr = std::string("FPS:" + StringHelp::IntToString(mFPS) +
		" DrCall:" + StringHelp::IntToString(numPerFrame));
	mInfoText->GetText()->SetText(infoStr);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// EngineCanvas
//----------------------------------------------------------------------------
EngineCanvas::EngineCanvas(LoadConstructor value) :
Canvas(value)
{
	mFPS = 0;
	mFPSUpdate = 0;
	mFPSUpdateTime = 0.0f;
}
//----------------------------------------------------------------------------
void EngineCanvas::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Canvas::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(EngineCanvas, source);
}
//----------------------------------------------------------------------------
void EngineCanvas::Link(InStream& source)
{
	Canvas::Link(source);
}
//----------------------------------------------------------------------------
void EngineCanvas::PostLink()
{
	Canvas::PostLink();
}
//----------------------------------------------------------------------------
bool EngineCanvas::Register(OutStream& target) const
{
	if (Canvas::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EngineCanvas::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Canvas::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(EngineCanvas, target);
}
//----------------------------------------------------------------------------
int EngineCanvas::GetStreamingSize(Stream &stream) const
{
	int size = Canvas::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------