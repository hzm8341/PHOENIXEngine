// BBlockScriptGenController.cpp

#include "PX2BBlockScriptGenController.hpp"
#include "PX2Creater.hpp"
#include "PX2BBlockEvents.hpp"
#include "PX2BBlockSprite.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Controller, BBlockScriptGenController);
PX2_IMPLEMENT_STREAM(BBlockScriptGenController);
PX2_IMPLEMENT_FACTORY(BBlockScriptGenController);

//----------------------------------------------------------------------------
BBlockScriptGenController::BBlockScriptGenController() :
mGenerateType(GT_ENGINE)
{
	mLFile = new0 LFile();
	SetName("BBlockScriptGenController");

	ComeInEventWorld();
}
//----------------------------------------------------------------------------
BBlockScriptGenController::~BBlockScriptGenController()
{
}
//----------------------------------------------------------------------------
void BBlockScriptGenController::SetName(const std::string& name)
{
	Controller::SetName(name);

	mLFile->SetName(name);
}
//----------------------------------------------------------------------------
void BBlockScriptGenController::SetGenerateType(GenerateType at)
{
	mGenerateType = at;

	if (GT_ENGINE == mGenerateType)
	{
		mLFile->SetPlatformType(PT_ENGINE);
	}
	else if (GT_ARDUINO == mGenerateType)
	{
		mLFile->SetPlatformType(PT_ARDUINO);
	}
	else if (GT_NODEMCU == mGenerateType)
	{
		mLFile->SetPlatformType(PT_NODEMCU);
	}
	else if (GT_RASPBERRY == mGenerateType)
	{
		mLFile->SetPlatformType(PT_ENGINE);
	}
}
//----------------------------------------------------------------------------
BBlockScriptGenController::GenerateType BBlockScriptGenController::
GetGenerateType() const
{
	return mGenerateType;
}
//----------------------------------------------------------------------------
LFile *BBlockScriptGenController::GetLFile()
{
	return mLFile;
}
//----------------------------------------------------------------------------
void BBlockScriptGenController::OnEvent(Event *ent)
{
	if (BBlockES::IsEqual(ent, BBlockES::Run))
	{
		bool isRun = ent->GetData<bool>();
		if (isRun)
		{
			if (mLFile)
			{
				_RemoveScriptCtrl();

				if (IsEnable())
				{
					Controlledable *ctrlable = GetControlledable();
					if (ctrlable)
					{
						if (LogicFilePlatformType::PT_ENGINE == mLFile->GetPlatformType())
						{
							std::string ctrlClassName = GetName();
							std::string compiledStr = mLFile->Compile();
							ScriptController *sc =
								PX2_CREATER.CreateScriptController_FromBuffer
								(compiledStr, ctrlClassName);
							sc->SetName("__BlockScriptCtrl");
							ctrlable->AttachController(sc);

							BBlockSprite *bbSprite = DynamicCast<BBlockSprite>(GetControlledable());
							if (bbSprite)
							{
								int fps = bbSprite->getFixUpdateFPS();
								sc->SetNumFixUpdatePerSeconds(fps);
							}
							sc->ResetPlay();
						}
					}
				}
			}
		}
		else
		{
			_RemoveScriptCtrl();
		}
	}
}
//----------------------------------------------------------------------------
void BBlockScriptGenController::_RemoveScriptCtrl()
{
	Controlledable *ctrlable = GetControlledable();
	if (ctrlable)
	{
		ScriptControllerPtr ctrl = DynamicCast<ScriptController>(
			ctrlable->GetControllerByName("__BlockScriptCtrl"));
		if (ctrl)
		{
			ctrl->Pause();
			ctrlable->DetachController(ctrl);
		}
		ctrl = 0;
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
BBlockScriptGenController::BBlockScriptGenController(LoadConstructor value) :
Controller(value)
{
}
//----------------------------------------------------------------------------
void BBlockScriptGenController::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Controller::Load(source);
	PX2_VERSION_LOAD(source);

	source.ReadEnum(mGenerateType);
	source.ReadPointer(mLFile);

	PX2_END_DEBUG_STREAM_LOAD(BBlockScriptGenController, source);
}
//----------------------------------------------------------------------------
void BBlockScriptGenController::Link(InStream& source)
{
	Controller::Link(source);

	if (mLFile)
	{
		source.ResolveLink(mLFile);
	}
}
//----------------------------------------------------------------------------
void BBlockScriptGenController::PostLink()
{
	Controller::PostLink();

	if (mLFile)
	{
		mLFile->PostLink();
	}

	ComeInEventWorld();
}
//----------------------------------------------------------------------------
bool BBlockScriptGenController::Register(OutStream& target) const
{
	if (Controller::Register(target))
	{
		if (mLFile)
		{
			target.Register(mLFile);
		}

		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void BBlockScriptGenController::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Controller::Save(target);
	PX2_VERSION_SAVE(target);

	target.WriteEnum(mGenerateType);
	target.WritePointer(mLFile);

	PX2_END_DEBUG_STREAM_SAVE(BBlockScriptGenController, target);
}
//----------------------------------------------------------------------------
int BBlockScriptGenController::GetStreamingSize(Stream &stream) const
{
	int size = Controller::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	size += PX2_ENUMSIZE(mGenerateType);
	size += PX2_POINTERSIZE(mLFile);

	return size;
}
//----------------------------------------------------------------------------