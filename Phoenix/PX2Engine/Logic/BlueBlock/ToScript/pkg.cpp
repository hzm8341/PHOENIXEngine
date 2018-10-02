// pkg.cpp

#include <pkg.hpp>
#include "angelscript.h"
using namespace std;

void FakeAddRef(void* ptr) {}
void FakeReleaseRef(void* ptr) {}

template<class A, class B>
B* RefCast(A* a)
{
	if( !a )
		return 0;
	B* b = dynamic_cast<B*>(a);
	return b;
}

static UIBBlockCataFrame * fUIBBlockCataFrame0()
{
	UIBBlockCataFrame* pointer = new0 UIBBlockCataFrame();
	pointer->IncrementReferences();
	return pointer;
}
static UIBBlockPanels * fUIBBlockPanels0()
{
	UIBBlockPanels* pointer = new0 UIBBlockPanels();
	pointer->IncrementReferences();
	return pointer;
}
static UIBBlockEdit * fUIBBlockEdit0()
{
	UIBBlockEdit* pointer = new0 UIBBlockEdit();
	pointer->IncrementReferences();
	return pointer;
}
static UIBBlockEditToolFrame * fUIBBlockEditToolFrame0()
{
	UIBBlockEditToolFrame* pointer = new0 UIBBlockEditToolFrame();
	pointer->IncrementReferences();
	return pointer;
}
static BBlockScriptGenController * fBBlockScriptGenController0()
{
	BBlockScriptGenController* pointer = new0 BBlockScriptGenController();
	pointer->IncrementReferences();
	return pointer;
}
int pkg(asIScriptEngine* asEngine)
{
	int r = 0;
	r = asEngine->RegisterObjectType("UIBBlockCataFrame", 0,  asOBJ_REF | asOBJ_NOCOUNT);
	assert(r >= 0);
	r = asEngine->RegisterObjectType("UIBBlockPanels", 0,  asOBJ_REF | asOBJ_NOCOUNT);
	assert(r >= 0);
	r = asEngine->RegisterObjectType("UIBBlockEdit", 0,  asOBJ_REF | asOBJ_NOCOUNT);
	assert(r >= 0);
	r = asEngine->RegisterObjectType("UIBBlockEditToolFrame", 0,  asOBJ_REF | asOBJ_NOCOUNT);
	assert(r >= 0);
	r = asEngine->RegisterObjectType("BBlockScriptGenController", 0,  asOBJ_REF | asOBJ_NOCOUNT);
	assert(r >= 0);
	// Class: UIBBlockCataFrame
	r = asEngine->RegisterObjectBehaviour("UIBBlockCataFrame", asBEHAVE_FACTORY, "UIBBlockCataFrame @ f()", asFUNCTION(fUIBBlockCataFrame0), asCALL_CDECL);
	assert(r >= 0);
	r = asEngine->RegisterObjectMethod("UIBBlockCataFrame", "UIBBlockCataFrame @ New()", asFUNCTIONPR(UIBBlockCataFrame::New, (), UIBBlockCataFrame * ), asCALL_CDECL_OBJLAST);
	assert(r >= 0);
	r = asEngine->RegisterObjectMethod("UIBBlockCataFrame", "UIBBlockCataFrame @ New(const string & name)", asFUNCTIONPR(UIBBlockCataFrame::New, (const std::string & ), UIBBlockCataFrame * ), asCALL_CDECL_OBJLAST);
	assert(r >= 0);
	// Class: UIBBlockPanels
	r = asEngine->RegisterObjectBehaviour("UIBBlockPanels", asBEHAVE_FACTORY, "UIBBlockPanels @ f()", asFUNCTION(fUIBBlockPanels0), asCALL_CDECL);
	assert(r >= 0);
	r = asEngine->RegisterObjectMethod("UIBBlockPanels", "UIBBlockPanels @ New()", asFUNCTIONPR(UIBBlockPanels::New, (), UIBBlockPanels * ), asCALL_CDECL_OBJLAST);
	assert(r >= 0);
	r = asEngine->RegisterObjectMethod("UIBBlockPanels", "UIBBlockPanels @ New(const string & name)", asFUNCTIONPR(UIBBlockPanels::New, (const std::string & ), UIBBlockPanels * ), asCALL_CDECL_OBJLAST);
	assert(r >= 0);
	r = asEngine->RegisterObjectMethod("UIBBlockPanels", "void ShowPanel(const string & panelName)", asMETHODPR(UIBBlockPanels, ShowPanel, (const std::string & ), void), asCALL_THISCALL);
	assert(r >= 0);
	// Class: UIBBlockEdit
	r = asEngine->RegisterObjectBehaviour("UIBBlockEdit", asBEHAVE_FACTORY, "UIBBlockEdit @ f()", asFUNCTION(fUIBBlockEdit0), asCALL_CDECL);
	assert(r >= 0);
	r = asEngine->RegisterObjectMethod("UIBBlockEdit", "UIBBlockEdit @ New()", asFUNCTIONPR(UIBBlockEdit::New, (), UIBBlockEdit * ), asCALL_CDECL_OBJLAST);
	assert(r >= 0);
	r = asEngine->RegisterObjectMethod("UIBBlockEdit", "UIBBlockEdit @ New(const string & name)", asFUNCTIONPR(UIBBlockEdit::New, (const std::string & ), UIBBlockEdit * ), asCALL_CDECL_OBJLAST);
	assert(r >= 0);
	// Class: UIBBlockEditToolFrame
	r = asEngine->RegisterObjectBehaviour("UIBBlockEditToolFrame", asBEHAVE_FACTORY, "UIBBlockEditToolFrame @ f()", asFUNCTION(fUIBBlockEditToolFrame0), asCALL_CDECL);
	assert(r >= 0);
	r = asEngine->RegisterObjectMethod("UIBBlockEditToolFrame", "UIBBlockEditToolFrame @ New()", asFUNCTIONPR(UIBBlockEditToolFrame::New, (), UIBBlockEditToolFrame * ), asCALL_CDECL_OBJLAST);
	assert(r >= 0);
	r = asEngine->RegisterObjectMethod("UIBBlockEditToolFrame", "UIBBlockEditToolFrame @ New(const string & name)", asFUNCTIONPR(UIBBlockEditToolFrame::New, (const std::string & ), UIBBlockEditToolFrame * ), asCALL_CDECL_OBJLAST);
	assert(r >= 0);
	r = asEngine->RegisterObjectMethod("UIBBlockEditToolFrame", "UIButton @ GetButtonRecycle()", asMETHODPR(UIBBlockEditToolFrame, GetButtonRecycle, (), UIButton * ), asCALL_THISCALL);
	assert(r >= 0);
	// Class: BBlockScriptGenController
	// Enum: GenerateType
	r = asEngine->RegisterEnum("GenerateType");
	assert(r >= 0);
	r = asEngine->RegisterEnumValue("GenerateType", "GT_ENGINE", BBlockScriptGenController::GenerateType::GT_ENGINE);
	assert(r >= 0);
	r = asEngine->RegisterEnumValue("GenerateType", "GT_ARDUINO", BBlockScriptGenController::GenerateType::GT_ARDUINO);
	assert(r >= 0);
	r = asEngine->RegisterEnumValue("GenerateType", "GT_NODEMCU", BBlockScriptGenController::GenerateType::GT_NODEMCU);
	assert(r >= 0);
	r = asEngine->RegisterEnumValue("GenerateType", "GT_RASPBERRY", BBlockScriptGenController::GenerateType::GT_RASPBERRY);
	assert(r >= 0);
	r = asEngine->RegisterEnumValue("GenerateType", "GT_MAX_TYPE", BBlockScriptGenController::GenerateType::GT_MAX_TYPE);
	assert(r >= 0);
	r = asEngine->RegisterObjectBehaviour("BBlockScriptGenController", asBEHAVE_FACTORY, "BBlockScriptGenController @ f()", asFUNCTION(fBBlockScriptGenController0), asCALL_CDECL);
	assert(r >= 0);
	r = asEngine->RegisterObjectMethod("BBlockScriptGenController", "BBlockScriptGenController @ New()", asFUNCTIONPR(BBlockScriptGenController::New, (), BBlockScriptGenController * ), asCALL_CDECL_OBJLAST);
	assert(r >= 0);
	r = asEngine->RegisterObjectMethod("BBlockScriptGenController", "BBlockScriptGenController @ New(const string & name)", asFUNCTIONPR(BBlockScriptGenController::New, (const std::string & ), BBlockScriptGenController * ), asCALL_CDECL_OBJLAST);
	assert(r >= 0);
	r = asEngine->RegisterObjectMethod("BBlockScriptGenController", "void SetGenerateType(GenerateType at)", asMETHODPR(BBlockScriptGenController, SetGenerateType, (BBlockScriptGenController::GenerateType), void), asCALL_THISCALL);
	assert(r >= 0);
	r = asEngine->RegisterObjectMethod("BBlockScriptGenController", "GenerateType GetGenerateType() const", asMETHODPR(BBlockScriptGenController, GetGenerateType, () const, BBlockScriptGenController::GenerateType), asCALL_THISCALL);
	assert(r >= 0);
	r = asEngine->RegisterObjectMethod("BBlockScriptGenController", "LFile @ GetLFile()", asMETHODPR(BBlockScriptGenController, GetLFile, (), LFile * ), asCALL_THISCALL);
	assert(r >= 0);

	return 0;
}