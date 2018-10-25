// UIBBlockPanelList.cpp

#include "PX2UIBBlockPanelList.hpp"
#include "PX2UIButton.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2LogicES.hpp"
#include "PX2LogicManager.hpp"
#include "PX2BBlockScriptGenController.hpp"
#include "PX2UIBBlockPanelBlock.hpp"
#include "PX2BBlockSprite.hpp"
#include "PX2BBManager.hpp"
#include "PX2BBlockEvents.hpp"
#include "PX2LanguageManager.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIFrame, UIBBlockPanelList);
PX2_IMPLEMENT_STREAM(UIBBlockPanelList);
PX2_IMPLEMENT_FACTORY(UIBBlockPanelList);

//----------------------------------------------------------------------------
UIBBlockPanelList::UIBBlockPanelList()
{
	ComeInEventWorld();

	SetAnchorHor(0.0f, 1.0f);
	SetAnchorVer(0.0f, 1.0f);

	mCollapsePanel = new0 UICollapsePanel();
	AttachChild(mCollapsePanel);

	UIPicBox *picBox = new0 UIPicBox();
	picBox->SetTexture("Data/BlueBlock/images/cata/tagbackground.png");
	picBox->SetPicBoxType(UIPicBox::PBT_NINE);
	picBox->SetTexCornerSize(6.0f, 6.0f, 6.0f, 6.0f);
	picBox->SetColor(Float3::MakeColor(0, 105, 112));

	mCollapsePanel->SetBarPicBox(picBox);
	mCollapsePanel->SetExpandBarHeight(40.0f);
	mCollapsePanel->LocalTransform.SetTranslateY(-2.0f);
	mCollapsePanel->SetAnchorHor(0.0, 1.0f);
	mCollapsePanel->SetAnchorVer(0.0, 1.0f);
	mCollapsePanel->GetSlider()->LocalTransform.SetTranslateY(-25.0f);
	mCollapsePanel->SetSliderWidth(30.0f);
	mCollapsePanel->SetAnchorParamHor(0.0f, 0.0f);
	mCollapsePanel->SetFont("Data/BlueBlock/fonts/font.ttf");

	UISlider *slider = mCollapsePanel->GetSlider();
	if (slider)
	{
		slider->GetButSlider()->SetStateBrightness(UIButtonBase::BS_NORMAL, 1.0f);
		slider->GetButSlider()->SetStateBrightness(UIButtonBase::BS_PRESSED, 1.2f);
		slider->GetButSlider()->SetStateColor(UIButtonBase::BS_NORMAL, Float3::MakeColor(232, 206, 93));
		slider->GetButSlider()->SetStateColor(UIButtonBase::BS_HOVERED, Float3::MakeColor(232, 206, 93));
		slider->GetButSlider()->SetStateColor(UIButtonBase::BS_PRESSED, Float3::MakeColor(232, 206, 93));
	}

	ComeInEventWorld();
}
//----------------------------------------------------------------------------
UIBBlockPanelList::~UIBBlockPanelList()
{
}
//----------------------------------------------------------------------------
void UIBBlockPanelList::SetCatalogue(const std::string &cata)
{
	mCatalogue = cata;
	SetName(cata);

	if ("System" == mCatalogue)
	{
		_AddCataFun("System", "setBluetooth");
		_AddCataFun("System", "setSerial");
		_AddCataFun("System", "setWifiRobot");

		_AddCataFun("Sprite", "setCurBBlockSprite");

		_AddCataFun("Time", "getTimeString");
		_AddCataFun("Time", "getYear");
		_AddCataFun("Time", "getMonth");
		_AddCataFun("Time", "getWeek");
		_AddCataFun("Time", "getDay");
		_AddCataFun("Time", "getDayOfWeek");
		_AddCataFun("Time", "getTimeHour");
		_AddCataFun("Time", "getTimeMinute");
		_AddCataFun("Time", "getTimeSecond");

		_AddCataFun("String", "stringToInt");
		_AddCataFun("String", "stringToFloat");
		_AddCataFun("String", "intToString");
		_AddCataFun("String", "floatToString");
		_AddCataFun("String", "getStringParam");
		_AddCataFun("String", "stringAdd");

		_AddCataFun("Log", "log");

		_AddCataFun("Random", "rand255");
		_AddCataFun("Random", "randZeroOne");
		_AddCataFun("Random", "randZero2One");

		_AddCataFun("Media", "playMusic");
		_AddCataFun("Media", "stopMusic");
		_AddCataFun("Media", "playCam");

		_AddCataFun("Bluetooth", "bluetoothSendString");

		_AddCataFun("Voice", "voiceStart");
		_AddCataFun("Voice", "voiceEnd");
		_AddCataFun("Voice", "voiceSpeak");
		_AddCataFun("Voice", "voiceAutoSpeakEnable");
		_AddCataFun("Voice", "voiceIsAutoSpeakEnable");

		_UpdateObjectFunctionsSystem();
	}
	else if ("Extend" == mCatalogue)
	{
		_AddCataFun("PHOENIXFrame_Arduino", "pinMode");
		_AddCataFun("PHOENIXFrame_Arduino", "digitalWrite");
		_AddCataFun("PHOENIXFrame_Arduino", "analogWrite");
		_AddCataFun("PHOENIXFrame_Arduino", "digitalRead");
		_AddCataFun("PHOENIXFrame_Arduino", "analogRead");

		_AddCataFun("PHOENIXFrame_Server", "serverInit");
		_AddCataFun("PHOENIXFrame_Server", "serverWrite");

		_AddCataFun("PHOENIXFrame_Dist", "distInit");
		_AddCataFun("PHOENIXFrame_Dist", "distTest");
		_AddCataFun("PHOENIXFrame_Dist", "getDist");

		_AddCataFun("PHOENIXFrame_Vehicle", "vehicleInitMotoBoard");
		_AddCataFun("PHOENIXFrame_Vehicle", "vehicleInitMotoBoard4567");
		_AddCataFun("PHOENIXFrame_Vehicle", "vehicleRun");
		_AddCataFun("PHOENIXFrame_Vehicle", "vehicleRunSimple");
		_AddCataFun("PHOENIXFrame_Vehicle", "vehicleGetSpeed");
		_AddCataFun("PHOENIXFrame_Vehicle", "vehicleStop");
		_AddCataFun("PHOENIXFrame_Vehicle", "vehicleSpeedInit");
		_AddCataFun("PHOENIXFrame_Vehicle", "vehicleGetSpeed");

		_AddCataFun("PHOENIXFrame_MP3", "mp3Init");
		_AddCataFun("PHOENIXFrame_MP3", "mp3Play");
		_AddCataFun("PHOENIXFrame_MP3", "mp3PlayNext");
		_AddCataFun("PHOENIXFrame_MP3", "mp3PlayAtIndex");
		_AddCataFun("PHOENIXFrame_MP3", "mp3SetVolume");
		_AddCataFun("PHOENIXFrame_MP3", "mp3Stop");

		_AddCataFun("PHOENIXFrame_IR", "irSend");
		_AddCataFun("PHOENIXFrame_IR", "irRecvInit");
		_AddCataFun("PHOENIXFrame_IR", "getIRReceive");


		_UpdateObjectFunctionsSystem();
	}
	else if ("Func" == mCatalogue)
	{
		std::string tag = PX2_BBM.GetProductTag();
		if (tag.empty())
		{
			_AddCataFun("Base", "setName");
			_AddCataFun("Base", "getName");

			_AddCataFun("Base", "setFixUpdateFPS");
			_AddCataFun("Base", "getFixUpdateFPS");

			_AddCataFun("View", "show");
			_AddCataFun("View", "isShow");

			_AddCataFun("View", "setText");
			_AddCataFun("View", "getText");

			_AddCataFun("Transform", "setScale");
			_AddCataFun("Transform", "getScale");
			_AddCataFun("Transform", "setScaleXZ");
			_AddCataFun("Transform", "setScaleX");
			_AddCataFun("Transform", "setScaleZ");
			_AddCataFun("Transform", "getScaleX");
			_AddCataFun("Transform", "getScaleZ");
			_AddCataFun("Transform", "addScale");

			_AddCataFun("Transform", "setRotateXYZ");
			_AddCataFun("Transform", "setRotateX");
			_AddCataFun("Transform", "setRotateY");
			_AddCataFun("Transform", "setRotateZ");
			_AddCataFun("Transform", "getRotateX");
			_AddCataFun("Transform", "getRotateY");
			_AddCataFun("Transform", "getRotateZ");
			_AddCataFun("Transform", "addRotate");

			_AddCataFun("Transform", "setPostion");
			_AddCataFun("Transform", "setAnchorHor");
			_AddCataFun("Transform", "setAnchorParamHor");
			_AddCataFun("Transform", "setAnchorVer");
			_AddCataFun("Transform", "setAnchorParamVer");
			_AddCataFun("Transform", "move");
			_AddCataFun("Transform", "setLayer");
			_AddCataFun("Transform", "getLayer");

			_AddCataFun("Transform", "setPivot");
			_AddCataFun("Transform", "setSize");
			_AddCataFun("Transform", "setSizeWidthHeight");

			_AddCataFun("Round", "getDragingDirX");
			_AddCataFun("Round", "getDragingDirY");
			_AddCataFun("Round", "getDragingDirSimple");
			_AddCataFun("Round", "getDragingPercent");

			_AddCataFun("Round", "getDragingLeftMoveType");
			_AddCataFun("Round", "getDragingLeftMoveSpeed");
			_AddCataFun("Round", "getDragingRightMoveType");
			_AddCataFun("Round", "getDragingRightMoveSpeed");

			_AddCataFun("Slider", "setSliderPercent");
			_AddCataFun("Slider", "setSlider100");
			_AddCataFun("Slider", "setSlider180");
			_AddCataFun("Slider", "getSliderPercent");
			_AddCataFun("Slider", "getSlider100");
			_AddCataFun("Slider", "getSlider180");
			_AddCataFun("Slider", "getSlider360");

			_AddCataFun("Combo", "addChooseString");
			_AddCataFun("Combo", "chooseString");
			_AddCataFun("Combo", "chooseIndex");
			_AddCataFun("Combo", "getChooseString");
			_AddCataFun("Combo", "getChooseIndex");

			_UpdateObjectFunctionsSystemClass();
		}
		else if ("RobotCtrl" == tag)
		{
			_AddCataFun("Base", "getName");
			_AddCataFun("Base", "setFixUpdateFPS");

			_AddCataFun("View", "show");
			_AddCataFun("View", "isShow");

			_AddCataFun("View", "setText");
			_AddCataFun("View", "getText");

			_AddCataFun("Transform", "setScale");
			_AddCataFun("Transform", "getScale");

			_AddCataFun("Round", "getDragingDirX");
			_AddCataFun("Round", "getDragingDirY");
			_AddCataFun("Round", "getDragingDirSimple");
			_AddCataFun("Round", "getDragingPercent");
			_AddCataFun("Round", "getDragingLeftMoveType");
			_AddCataFun("Round", "getDragingLeftMoveSpeed");
			_AddCataFun("Round", "getDragingRightMoveType");
			_AddCataFun("Round", "getDragingRightMoveSpeed");

			_AddCataFun("Slider", "setSliderPercent");
			_AddCataFun("Slider", "getSliderPercent");

			_AddCataFun("Slider", "setSlider100");
			_AddCataFun("Slider", "getSlider100");

			_AddCataFun("Slider", "setSlider180");
			_AddCataFun("Slider", "getSlider180");
			_AddCataFun("Slider", "getSlider360");

			_UpdateObjectFunctionsSystemClass();
		}
	}
}
//----------------------------------------------------------------------------
void UIBBlockPanelList::ShowCata(const std::string &cata, bool show)
{
	mCollapsePanel->ShowItem(cata, show);
}
//----------------------------------------------------------------------------
void UIBBlockPanelList::OnEvent(Event *ent)
{
	UIFrame::OnEvent(ent);

	//if (BBlockES::IsEqual(ent, BBlockES::SelectSprite))
	//{
		//void *ptr = ent->GetDataPointer0();
		//BBlockSprite *sprite = (BBlockSprite*)(ptr);
		//if (sprite)
		//{
		//	BBlockSprite::SpriteType spt = sprite->GetSpriteType();
		//	if (BBlockSprite::ST_BUTTON == spt)
		//	{
		//	}
		//	else if (BBlockSprite::ST_TEXT == spt)
		//	{
		//	}
		//	else if (BBlockSprite::ST_EDITBOX == spt)
		//	{
		//	}
		//	else if (BBlockSprite::ST_WEBVIEW == spt)
		//	{
		//		ShowCata("Web", true);
		//	}
		//	else if (BBlockSprite::ST_ROUND == spt)
		//	{
		//		ShowCata("Round", true);
		//	}
		//	else if (BBlockSprite::ST_SLIDER == spt)
		//	{
		//		ShowCata("Slider", true);
		//	}
		//}
	//}
}
//----------------------------------------------------------------------------
bool _IsContain(std::vector<FString> &funs, FString name)
{
	for (int i = 0; i < (int)funs.size(); i++)
	{
		if (name == funs[i])
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void UIBBlockPanelList::_UpdateObjectFunctionsPanelTag(UICollapseItem *item,
	FunObject *funObj, const std::string &tag)
{
	UIFrame *cntFrame = item->GetContentFrame();

	BUIBlockPanelBlock *blockFrame = new0 BUIBlockPanelBlock();
	cntFrame->AttachChild(blockFrame);
	blockFrame->SetName(tag);

	// reset
	funObj->CateName = mCatalogue;

	for (int i = 0; i < (int)funObj->mChildFunObjectVec.size(); i++)
	{
		FunObject *childFunObj = funObj->mChildFunObjectVec[i];

		// reset
		childFunObj->CateName = mCatalogue;

		const std::string &funObjName = childFunObj->Name;
		FString fStrFunObj = FString(funObjName.c_str());
		std::vector<FString> funs = mCataFunnames[tag.c_str()];
		if (_IsContain(funs, fStrFunObj))
		{
			BBlock *uiblock = new0 BBlock();
			LBlock *lBlock = 0;
			if (childFunObj->GetOutParams().size() > 0)
			{
				lBlock = new0 LBlock(LBlock::MT_FUNCTION_OUTPUT);
			}
			else
			{
				lBlock = new0 LBlock(LBlock::MT_FUNCTION_GENERAL);
			}

			lBlock->RegistFunObj(*childFunObj);
			uiblock->SetLBlock(lBlock);

			blockFrame->AddBBlock(uiblock);
		}
	}
	float height = blockFrame->_UpdateAligns(0);
	item->SetContentHeight(height);
	item->Expand(false);
	blockFrame->SetUserDataPointer("UICollapseItem", item);
}
//----------------------------------------------------------------------------
void UIBBlockPanelList::_UpdateObjectFunctionsSystem()
{
	FunObject *bsFunObject = PX2_LOGICM.GetClassFunObject("BBlockSystem");
	if (bsFunObject)
	{
		mCollapsePanel->RemoveAllItems();

		for (int i = 0; i < (int)mCatas.size(); i++)
		{
			FString cataStr = mCatas[i];
			std::string strCata = (const char*)cataStr;

			UICollapseItem *itemCreate = mCollapsePanel->AddItem(strCata, 
				PX2_LM_APP.GetValue(strCata));
			_UpdateObjectFunctionsPanelTag(itemCreate, bsFunObject, (const char*)cataStr);

			auto it = PX2_BBM.CateColors.find(mCatalogue);
			if (it != PX2_BBM.CateColors.end())
			{
				Float4 color = it->second;
				itemCreate->GetButton()->SetStateColor(UIButtonBase::BS_NORMAL,
					MathHelp::Float4ToFloat3(color));
				itemCreate->GetButton()->SetStateColor(UIButtonBase::BS_HOVERED,
					MathHelp::Float4ToFloat3(color));
				itemCreate->GetButton()->SetStateColor(UIButtonBase::BS_PRESSED,
					MathHelp::Float4ToFloat3(color));

				itemCreate->GetButton()->SetStateBrightness(
					UIButtonBase::BS_NORMAL, 1.0f);
				itemCreate->GetButton()->SetStateBrightness(
					UIButtonBase::BS_HOVERED, 0.8f);
				itemCreate->GetButton()->SetStateBrightness(
					UIButtonBase::BS_PRESSED, 1.0f);
			}
		}
	}
}
//----------------------------------------------------------------------------
void UIBBlockPanelList::_UpdateObjectFunctionsSystemClass()
{
	FunObject *bsFunObject = PX2_LOGICM.GetClassFunObject("BBlockSystem");
	if (bsFunObject)
	{
		mCollapsePanel->RemoveAllItems();

		for (int i = 0; i < (int)mCatas.size(); i++)
		{
			FString cataStr = mCatas[i];
			std::string strCata = (const char*)cataStr;

			UICollapseItem *itemCreate = mCollapsePanel->AddItem(strCata,
				PX2_LM_APP.GetValue(strCata));
			_UpdateObjectFunctionsPanelTag(itemCreate, bsFunObject, (const char*)cataStr);

			auto it = PX2_BBM.CateColors.find(mCatalogue);
			if (it != PX2_BBM.CateColors.end())
			{
				Float4 color = it->second;
				itemCreate->GetButton()->SetStateColor(UIButtonBase::BS_NORMAL,
					MathHelp::Float4ToFloat3(color));
				itemCreate->GetButton()->SetStateColor(UIButtonBase::BS_HOVERED,
					MathHelp::Float4ToFloat3(color));
				itemCreate->GetButton()->SetStateColor(UIButtonBase::BS_PRESSED,
					MathHelp::Float4ToFloat3(color));

				itemCreate->GetButton()->SetStateBrightness(
					UIButtonBase::BS_NORMAL, 1.0f);
				itemCreate->GetButton()->SetStateBrightness(
					UIButtonBase::BS_HOVERED, 0.8f);
				itemCreate->GetButton()->SetStateBrightness(
					UIButtonBase::BS_PRESSED, 1.0f);
			}
		}
	}
}
//----------------------------------------------------------------------------
void UIBBlockPanelList::_UpdateObjectFunctionsClass(const std::string &calssName)
{
	FunObject *funObj = FunObjectManager::GetSingleton().GetObjectFunObject();
	FunObject *classFunObj = funObj->GetClass(calssName);
	if (classFunObj)
	{
		mCollapsePanel->RemoveAllItems();

		for (int i = 0; i < (int)mCatas.size(); i++)
		{
			FString cataStr = mCatas[i];
			std::string strCata = (const char*)cataStr;

			UICollapseItem *itemCreate = mCollapsePanel->AddItem(strCata,
				PX2_LM_APP.GetValue(strCata));
			_UpdateObjectFunctionsPanelTag(itemCreate, classFunObj, (const char*)cataStr);
		}
	}
}
//----------------------------------------------------------------------------
void _UIBBlockPanelListCallback(UIFrame *frame, UICallType type)
{
	UICheckButton *checkBut = DynamicCast<UICheckButton>(frame);
	if (checkBut)
	{
		UIItem *item = checkBut->GetUserData<UIItem*>("Item");

		if (UICT_CHECKED == type)
		{
			item->Expand(false);
		}
		else if (UICT_DISCHECKED == type)
		{
			item->Expand(true);
		}
	}
}
//----------------------------------------------------------------------------
bool UIBBlockPanelList::_IsHasCata(FString cata)
{
	for (int i = 0; i < (int)mCatas.size(); i++)
	{
		if (cata == mCatas[i])
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void UIBBlockPanelList::_AddCataFun(FString cata, FString funname)
{
	if (!_IsHasCata(cata))
		mCatas.push_back(cata);

	mCataFunnames[cata].push_back(funname);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
UIBBlockPanelList::UIBBlockPanelList(LoadConstructor value) :
UIFrame(value)
{
}
//----------------------------------------------------------------------------
void UIBBlockPanelList::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIFrame::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(UIBBlockPanelList, source);
}
//----------------------------------------------------------------------------
void UIBBlockPanelList::Link(InStream& source)
{
	UIFrame::Link(source);
}
//----------------------------------------------------------------------------
void UIBBlockPanelList::PostLink()
{
	UIFrame::PostLink();
}
//----------------------------------------------------------------------------
bool UIBBlockPanelList::Register(OutStream& target) const
{
	if (UIFrame::Register(target))
	{
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void UIBBlockPanelList::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIFrame::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(UIBBlockPanelList, target);
}
//----------------------------------------------------------------------------
int UIBBlockPanelList::GetStreamingSize(Stream &stream) const
{
	int size = UIFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------