// PX2LFile.cpp

#include "PX2LFile.hpp"
#include "PX2FontManager.hpp"
#include "PX2StringHelp.hpp"
#include "PX2LogicManager.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Object, LFile);
PX2_IMPLEMENT_STREAM(LFile);
PX2_IMPLEMENT_FACTORY(LFile);
PX2_IMPLEMENT_DEFAULT_NAMES(Object, LFile);

//----------------------------------------------------------------------------
LFile::LFile() :
mPlatformType(PT_ENGINE)
{
	mBlockProgram = new0 LBlock(LBlock::MT_CONTROL);
	mBlockProgram->SetCtrlType(LBlock::CT_PROGRAM);
	mBlockProgram->RegistFunObj(*(PX2_LOGICM.GetCtrl("Program")));
}
//----------------------------------------------------------------------------
LFile::~LFile()
{
}
//----------------------------------------------------------------------------
LBlock * LFile::GetBlockProgram()
{
	return mBlockProgram;
}
//----------------------------------------------------------------------------
void LFile::SetPlatformType(LogicFilePlatformType pt)
{
	mPlatformType = pt;
}
//----------------------------------------------------------------------------
LogicFilePlatformType LFile::GetPlatformType() const
{
	return mPlatformType;
}
//----------------------------------------------------------------------------
bool LFile::IsPreCompiledParam(const std::string &paramName)
{
	for (int i = 0; i < (int)PreCompiledParams.size(); i++)
	{
		if (paramName == PreCompiledParams[i])
			return true;
	}

	return false;
}
//----------------------------------------------------------------------------
const std::string &LFile::Compile()
{
	PreCompiledParams.clear();
	mCompiledString.clear();

	if (PT_ENGINE == mPlatformType)
	{
		mCompiledString += "-- " + GetName() + ".lua";
	}

	mCompiledString += "\n";

	mBlockProgram->PreCompile(mCompiledString, this, true);

	mCompiledString += "\n";

	mBlockProgram->Compile(mCompiledString, 0, this, true);

	mCompiledString += "\n";

	return mCompiledString;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
LFile::LFile(LoadConstructor value) :
Object(value),
mPlatformType(PT_ENGINE)
{
}
//----------------------------------------------------------------------------
void LFile::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Object::Load(source);
	PX2_VERSION_LOAD(source);

	source.ReadEnum(mPlatformType);
	source.ReadPointer(mBlockProgram);

	PX2_END_DEBUG_STREAM_LOAD(LFile, source);
}
//----------------------------------------------------------------------------
void LFile::Link(InStream& source)
{
	Object::Link(source);

	if (mBlockProgram)
	{
		source.ResolveLink(mBlockProgram);
	}
}
//----------------------------------------------------------------------------
void LFile::PostLink()
{
	Object::PostLink();

	if (mBlockProgram)
	{
		mBlockProgram->PostLink();
	}
}
//----------------------------------------------------------------------------
bool LFile::Register(OutStream& target) const
{
	if (Object::Register(target))
	{
		if (mBlockProgram)
		{
			target.Register(mBlockProgram);
		}

		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void LFile::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Object::Save(target);
	PX2_VERSION_SAVE(target);

	target.WriteEnum(mPlatformType);
	target.WritePointer(mBlockProgram);

	PX2_END_DEBUG_STREAM_SAVE(LFile, target);
}
//----------------------------------------------------------------------------
int LFile::GetStreamingSize(Stream &stream) const
{
	int size = Object::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	size += PX2_ENUMSIZE(mPlatformType);
	size += PX2_POINTERSIZE(mBlockProgram);

	return size;
}
//----------------------------------------------------------------------------