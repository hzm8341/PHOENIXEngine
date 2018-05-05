// PX2UIBBlockCataFrame.cpp

#include "PX2UIBBlockCataFrame.hpp"
#include "PX2UIButton.hpp"
#include "PX2LanguageManager.hpp"
#include "PX2BBManager.hpp"
#include "PX2LogicManager.hpp"
#include "PX2BBManager.hpp"
#include "PX2BBlockEvents.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIFrame, UIBBlockCataFrame);
PX2_IMPLEMENT_STREAM(UIBBlockCataFrame);
PX2_IMPLEMENT_FACTORY(UIBBlockCataFrame);

//----------------------------------------------------------------------------
UIBBlockCataFrame::UIBBlockCataFrame()
{
	ComeInEventWorld();
	SetChildNotPickRecursion(false);

	mCataType = CT_VER;

	SetWidget(true);
}
//----------------------------------------------------------------------------
UIBBlockCataFrame::~UIBBlockCataFrame()
{
}
//----------------------------------------------------------------------------
void UIBBlockCataFrame::SetCataType(CataType cataType)
{
	mCataType = cataType;

	if (cataType == UIBBlockCataFrame::CT_NORMAL)
	{
		PX2_BBM.SetSideCata(true);
	}
	else if (cataType == UIBBlockCataFrame::CT_VER ||
		cataType == UIBBlockCataFrame::CT_VER_BOTTOM)
	{
		PX2_BBM.SetSideCata(true);
	}
}
//----------------------------------------------------------------------------
void UIBBlockCataFrame::OnEvent(Event *ent)
{
	//if (BBlockES::IsEqual(ent, BBlockES::SelectSprite))
	//{
	//	Object *obj = (Object*)ent->GetDataPointer0();
	//	if (obj)
	//	{
	//		BBlockSprite *sprite = DynamicCast<BBlockSprite>(obj);
	//		if (sprite)
	//		{
	//			BBlockSprite::SpriteType st = sprite->GetSpriteType();
	//			if (BBlockSprite::ST_ARDUINO == st)
	//			{
	//				_RefreshCata(true);
	//			}
	//			else
	//			{
	//				_RefreshCata(false);
	//			}
	//		}
	//	}
	//}
}
//----------------------------------------------------------------------------
void UIBBlockCataFrame::CreateCataButs()
{
	float butHeight = 60.0f;
	float butSpace = 0.0f;

	float startPos = 0.0f + butHeight * 0.5f;
	float butPos = startPos;

	int numCata = 8;
	for (int i = 0; i < numCata; i++)
	{
		UIButton *but = new0 UIButton(UIButtonBase::BT_PICBOXSWAP);
		AttachChild(but);
		mUIButtons.push_back(but);
		but->LocalTransform.SetTranslateY(-1.0f);
		but->SetMemUICallback(this,
			(UIFrame::MemUICallback)(&UIBBlockCataFrame::_UICataButCallback));

		std::string name;
		int arduinoPhoenixType = 0; // 0 common, 1 arduino, 2 phoenix
		std::string imageStr;
		if (0 == i)
		{
			name = "Ctrl";
			imageStr = "control";
		}
		else if (1 == i)
		{
			name = "Test";
			imageStr = "logicoperator";
		}
		else if (2 == i)
		{
			name = "Math";
			imageStr = "mathoperator";
		}
		else if (3 == i)
		{
			name = "Param";
			imageStr = "param";
		}
		// phoenix
		else if (4 == i)
		{
			name = "Event";
			arduinoPhoenixType = 2;
			imageStr = "event";
		}
		else if (5 == i)
		{
			name = "Func";
			arduinoPhoenixType = 2;
			imageStr = "function";
		}
		else if (6 == i)
		{
			name = "System";
			arduinoPhoenixType = 2;
			imageStr = "system";
		}
		else if (7 == i)
		{
			name = "Extend";
			arduinoPhoenixType = 2;
			imageStr = "extend";
		}

		Float4 color = PX2_BBM.CateColors[name];

		but->SetName(name);
		but->SetStateColorDefaultWhite();
		std::string textPath = "Data/BlueBlock/images/cata/" + imageStr + ".png";
		std::string textPathPress = "Data/BlueBlock/images/cata/" + imageStr + "press.png";
		but->GetPicBoxAtState(UIButtonBase::BS_NORMAL)->SetTexture(textPath);
		but->GetPicBoxAtState(UIButtonBase::BS_HOVERED)->SetTexture(textPath);
		but->GetPicBoxAtState(UIButtonBase::BS_PRESSED)->SetTexture(textPathPress);
		but->SetUserDataFloat("ArduinoPhoenixType", (float)arduinoPhoenixType);
		but->SetPivot(0.5f, 0.5f);
		but->SetAnchorHor(0.0f, 1.0f);
		but->SetHeight(butHeight);
	}
	_RefreshCata(false);
}
//----------------------------------------------------------------------------
UIBBlockCataFrame::CataType UIBBlockCataFrame::GetCataType() const
{
	return mCataType;
}
//----------------------------------------------------------------------------
void UIBBlockCataFrame::_RefreshCata(bool isArduino)
{
	float butHeight = 60.0f;
	float butSpace = 1.0f;
	float startPos = 0.0f + butHeight * 0.5f;;
	float butPos = startPos;

	int numCata = 7;
	float allHeight = (butHeight + butSpace)*numCata + butSpace;

	int butIndex = 0;
	for (int i = 0; i < (int)mUIButtons.size(); i++)
	{
		UIButton *but = mUIButtons[i];
		but->Show(true);
		const std::string &name = GetName();
		float dataFloat = but->GetUserDataFloat("ArduinoPhoenixType");

		if (0.0f == dataFloat)
		{
			but->Show(true);
		}
		else if (1.0f == dataFloat && isArduino)
		{
			but->Show(true);
		}
		else if (2.0f == dataFloat && !isArduino)
		{
			but->Show(true);
		}
		else
		{
			but->Show(false);
		}

		if (CT_VER == mCataType)
		{
			if (but->IsShow())
			{
				but->SetSize(0.0f, butHeight);
				but->SetAnchorHor(0.0f, 1.0f);
				but->SetAnchorVer(1.0f, 1.0f);
				but->SetAnchorParamVer(-butPos, -butPos);

				butPos += (butHeight + butSpace);
			}
		}
		else if (CT_VER_BOTTOM == mCataType)
		{
			if (but->IsShow())
			{
				but->SetSize(0.0f, butHeight);
				but->SetAnchorHor(0.5f, 0.5f);
				but->SetAnchorVer(0.0f, 0.0f);
				but->SetAnchorParamVer(allHeight - butPos, allHeight - butPos);
				but->SetSize(80.0f, 80.0f);

				butPos += (butHeight + butSpace);
			}
		}
		if (CT_NORMAL == mCataType)
		{
			int indexX = (butIndex + 2) % 2;
			int indexY = butIndex / 2;

			but->SetSize(0.0f, butHeight);
			if (0 == indexX)
			{
				but->SetAnchorHor(0.0f, 0.5f);
			}
			else if (1 == indexX)
			{
				but->SetAnchorHor(0.5f, 1.0f);
			}
			but->SetAnchorParamHor(2.0f, -2.0f);
			butPos = startPos + indexY * (butHeight + butSpace);
			but->SetAnchorVer(1.0f, 1.0f);
			but->SetAnchorParamVer(-butPos, -butPos);
		}

		if (but->IsShow())
		{
			butIndex++;
		}
	}
}
//----------------------------------------------------------------------------
void UIBBlockCataFrame::_UICataButCallback(UIFrame *frame, UICallType type)
{
	const std::string &name = frame->GetName();

	UIButton *but = DynamicCast<UIButton>(frame);
	if (but)
	{
		if (UICT_RELEASED == type)
		{
			PX2_BBM.ShowBlockCata(name);
		}
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
UIBBlockCataFrame::UIBBlockCataFrame(LoadConstructor value) :
UIFrame(value)
{
}
//----------------------------------------------------------------------------
void UIBBlockCataFrame::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIFrame::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(UIBBlockCataFrame, source);
}
//----------------------------------------------------------------------------
void UIBBlockCataFrame::Link(InStream& source)
{
	UIFrame::Link(source);
}
//----------------------------------------------------------------------------
void UIBBlockCataFrame::PostLink()
{
	UIFrame::PostLink();
}
//----------------------------------------------------------------------------
bool UIBBlockCataFrame::Register(OutStream& target) const
{
	if (UIFrame::Register(target))
	{
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void UIBBlockCataFrame::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIFrame::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(UIBBlockCataFrame, target);
}
//----------------------------------------------------------------------------
int UIBBlockCataFrame::GetStreamingSize(Stream &stream) const
{
	int size = UIFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------