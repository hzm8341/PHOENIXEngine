// PX2EU_WebFrame.cpp

#include "PX2EU_WebFrame.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIWebFrame, EU_WebFrame);
PX2_IMPLEMENT_STREAM(EU_WebFrame);
PX2_IMPLEMENT_FACTORY(EU_WebFrame);

//----------------------------------------------------------------------------
EU_WebFrame::EU_WebFrame()
{

}
//----------------------------------------------------------------------------
EU_WebFrame::~EU_WebFrame()
{
}
//----------------------------------------------------------------------------
void EU_WebFrame::SetToOpenString(const std::string &toOpenStr)
{
	mToOpenString = toOpenStr;
}
//----------------------------------------------------------------------------
void EU_WebFrame::Save()
{

}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
EU_WebFrame::EU_WebFrame(LoadConstructor value) :
UIWebFrame(value)
{
}
//----------------------------------------------------------------------------
void EU_WebFrame::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	UIWebFrame::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(EU_WebFrame, source);
}
//----------------------------------------------------------------------------
void EU_WebFrame::Link(InStream& source)
{
	UIFrame::Link(source);
}
//----------------------------------------------------------------------------
void EU_WebFrame::PostLink()
{
	UIWebFrame::PostLink();
}
//----------------------------------------------------------------------------
bool EU_WebFrame::Register(OutStream& target) const
{
	if (UIWebFrame::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void EU_WebFrame::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	UIWebFrame::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(EU_WebFrame, target);
}
//----------------------------------------------------------------------------
int EU_WebFrame::GetStreamingSize(Stream &stream) const
{
	int size = UIWebFrame::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	return size;
}
//----------------------------------------------------------------------------