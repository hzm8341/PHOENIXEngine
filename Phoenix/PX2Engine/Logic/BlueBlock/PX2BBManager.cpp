// PX2BBManager.cpp

#include "PX2BBManager.hpp"
#include "PX2EventWorld.hpp"
#include "PX2BBlockEvents.hpp"
#include "PX2LogicManager.hpp"
#include "PX2BBlockScriptGenController.hpp"
#include "PX2BBlockSystem.hpp"
#include "PX2BBlockSprite.hpp"
#include "PX2BBlockEvents.hpp"
#include "PX2GraphicsEventType.hpp"
#include "PX2GraphicsEventData.hpp"
#include "PX2BDefine.hpp"
#include "PX2EditEventType.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2Dir.hpp"
#include "PX2Time.hpp"
#include "PX2Log.hpp"
#include "PX2ScriptManager.hpp"
#include "PX2ProjectEvent.hpp"
#include "PX2Project.hpp"
#include "PX2Arduino.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
BBManager::BBManager()
{
	std::string name = "Ctrl";
	Float4 color = Float4::MakeColor(225, 169, 26, 255);
	CateColors[name.c_str()] = color;

	name = "Test";
	color = Float4::MakeColor(138, 85, 215, 255);
	CateColors[name.c_str()] = color;

	name = "Math";
	color = Float4::MakeColor(92, 183, 18, 255);
	CateColors[name.c_str()] = color;

	name = "Param";
	color = Float4::MakeColor(238, 125, 22, 255);
	CateColors[name.c_str()] = color;
	name = "ParamCreated";
	color = Float4::MakeColor(238, 125, 22, 255);
	CateColors[name.c_str()] = color;

	name = "Event";
	color = Float4::MakeColor(229, 2, 163, 255);
	CateColors[name.c_str()] = color;

	name = "Func";
	color = Float4::MakeColor(14, 154, 108, 255);
	CateColors[name.c_str()] = color;

	name = "System";
	color = Float4::MakeColor(0, 189, 204, 255);
	CateColors[name.c_str()] = color;

	name = "Extend";
	color = Float4::MakeColor(10, 183, 255, 255);
	CateColors[name.c_str()] = color;

	mIsSideCata = false;
	mIsNeedCompileScirpt = true;

	BBlockSystem *bbSys = new0 BBlockSystem();
	PX2_EW.ComeIn(bbSys);
	bbSys->Initlize();

	mProject = 0;
}
//----------------------------------------------------------------------------
BBManager::~BBManager()
{
	BBlockSystem *bbSys = BBlockSystem::GetSingletonPtr();
	if (bbSys)
	{
		PX2_EW.GoOut(bbSys);
		delete0(bbSys);
		BBlockSystem::Set(0);
	}
}
//----------------------------------------------------------------------------
void BBManager::OnEvent(Event *ent)
{
	if (EditES::IsEqual(ent, EditES::AddSelect))
	{
		Object *obj = ent->GetData<Object*>();
		if (obj)
		{
			BBlockSprite *sprite = DynamicCast<BBlockSprite>(obj);
			if (sprite)
			{
				SetSelectSprite(sprite);
			}
		}
	}
	else if (GraphicsES::IsEqual(ent, GraphicsES::RemoveObject))
	{
		Object *obj = ent->GetData<Object*>();
		if (obj == (Object*)mSelectSprite)
		{
			SetSelectSprite(0);
		}
	}
	else if (BBlockES::IsEqual(ent, BBlockES::Run))
	{
		bool run = ent->GetData<bool>();
		if (run)
		{
			SetSelectSprite(0);
		}
	}
	else if (ProjectES::IsEqual(ent, ProjectES::CloseProject))
	{
		PX2_SC_LUA->ClearEventFunctions();
	}
}
//----------------------------------------------------------------------------
Float3 BBManager::GetParamTypeColor(FunParamType fpt)
{
	if (fpt == FPT_CHAR)
		return Float3::MakeColor(255, 127, 39);
	else if (fpt == FPT_STRING)
		return Float3::MakeColor(230, 91, 0);
	else if (fpt == FPT_INT)
		return Float3::BLUE;
	else if (fpt == FPT_FLOAT)
		return Float3::MakeColor(0, 0, 200);
	else if (fpt == FPT_BOOL)
		return Float3::RED;

	return Float3::BLACK;
}
//----------------------------------------------------------------------------
void BBManager::Update(float elapsedTime)
{
	if (mIsNeedCompileScirpt)
	{
		mIsNeedCompileScirpt = false;
		CompileSetGenScript();
	}

	PX2BBLOCK_SYS.Update(elapsedTime);
}
//----------------------------------------------------------------------------
void BBManager::SetPlatformTag(const std::string &platTag)
{
	mPloatformTag = platTag;

	if ("Phone" == mPloatformTag)
	{
		PX2_LOGICM.SetPlatformType(LogicManager::PT_PHONE);

		BDefine::Config(0.8f, "flat");
	}
	else if ("PC" == mPloatformTag)
	{
		BDefine::Config(0.6f, "");
	}
	else
	{
		BDefine::Config(1.0f, "");
	}
}
//----------------------------------------------------------------------------
void BBManager::SetProductTag(const std::string &productTag)
{
	mProductTag = productTag;
}
//----------------------------------------------------------------------------
const std::string &BBManager::GetProductTag() const
{
	return mProductTag;
}
//----------------------------------------------------------------------------
const std::string &BBManager::GetPlatformTag() const
{
	return mPloatformTag;
}
//----------------------------------------------------------------------------
void BBManager::SetSideCata(bool isSideCata)
{
	mIsSideCata = isSideCata;
}
//----------------------------------------------------------------------------
bool BBManager::IsSideCata() const
{
	return mIsSideCata;
}
//----------------------------------------------------------------------------
void BBManager::Clear()
{
	mPressingBBlock = 0;
	mDragingBBlock = 0;
	mSelectBBlockCata = 0;
	mSelectBBlockEditor = 0;
	mCopyBBlock = 0;

	mRecycleButton = 0;

	mSelectSprite = 0;

	PX2_LOGICM.Clear();
}
//----------------------------------------------------------------------------
void BBManager::SetEditorPressingBBlock(BBlock *block)
{
	if (mPressingBBlock == block)
		return;

	mPressingBBlock = block;
}
//----------------------------------------------------------------------------
BBlock *BBManager::GetEditorPressingBBlock()
{
	return mPressingBBlock;
}
//----------------------------------------------------------------------------
void BBManager::SetDragingBBlock(BBlock *block)
{
	if (mDragingBBlock == block)
		return;

	if (mDragingBBlock)
	{
		mDragingBBlock->LocalTransform.SetTranslateY(0.0f);
	}

	mDragingBBlock = block;

	if (mDragingBBlock)
	{
		mDragingBBlock->LocalTransform.SetTranslateY(-50.0f);
	}

	Event *ent = BBlockES::CreateEventX(BBlockES::SetDragingBBlock);
	ent->SetData<BBlock*>(block);
	PX2_EW.BroadcastingLocalEvent(ent);

	bool isSideCata = PX2_BBM.IsSideCata();
	if (isSideCata)
	{
		Event *entShow = BBlockES::CreateEventX(BBlockES::ShowBlockCata);
		entShow->SetData<std::string>("");
		entShow->SetDataStr0("");
		PX2_EW.BroadcastingLocalEvent(entShow);
	}
}
//----------------------------------------------------------------------------
BBlock *BBManager::GetDragingBBlock()
{
	return mDragingBBlock;
}
//----------------------------------------------------------------------------
void BBManager::SetSelectBBlockCata(BBlock *block)
{
	if (block == mSelectBBlockCata)
		return;

	if (mSelectBBlockCata)
		mSelectBBlockCata->OnSelect(false);

	mSelectBBlockCata = block;

	if (mSelectBBlockCata)
		mSelectBBlockCata->OnSelect(true);
}
//----------------------------------------------------------------------------
BBlock *BBManager::GetSelectBBlockCata()
{
	return mSelectBBlockCata;
}
//----------------------------------------------------------------------------
void BBManager::SetSelectBBlockEditor(BBlock *block)
{
	if (block == mSelectBBlockEditor)
		return;

	if (mSelectBBlockEditor)
		mSelectBBlockEditor->OnSelect(false);

	mSelectBBlockEditor = block;

	Event *ent = PX2_CREATEEVENTEX(BBlockES, SetSelectBBlockEditor);
	ent->SetDataPointer0((Object*)mSelectBBlockEditor);
	PX2_EW.BroadcastingLocalEvent(ent);

	if (mSelectBBlockEditor)
		mSelectBBlockEditor->OnSelect(true);
}
//----------------------------------------------------------------------------
BBlock *BBManager::GetSelectBBlockEditor()
{
	return mSelectBBlockEditor;
}
//----------------------------------------------------------------------------
void BBManager::SetCopyBBlock(BBlock *block)
{
	mCopyBBlock = block;
}
//----------------------------------------------------------------------------
BBlock *BBManager::GetCopyBBlock()
{
	return mCopyBBlock;
}
//----------------------------------------------------------------------------
void BBManager::SetRecycleButton(UIButton *but)
{
	mRecycleButton = but;
}
//----------------------------------------------------------------------------
UIButton *BBManager::GetRecycleButton()
{
	return mRecycleButton;
}
//----------------------------------------------------------------------------
void BBManager::ShowBlockCata(const std::string &cata)
{
	Event *ent = PX2_CREATEEVENTEX(BBlockES, ShowBlockCata);
	ent->SetData<std::string>(cata);
	if (cata.empty())
		ent->SetDataStr0("null");
	else
		ent->SetDataStr0(cata);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void BBManager::SetNeedCompileScript(bool cmp)
{
	mIsNeedCompileScirpt = cmp;
}
//----------------------------------------------------------------------------
void BBManager::CompileSetGenScript()
{
	Object *obj = PX2_LOGICM.GetSelectLogicObject();
	if (obj)
	{
		BBlockSprite *sprite = DynamicCast<BBlockSprite>(obj);
		if (sprite)
		{
			BBlockScriptGenController *sGenCtrl = sprite->GetScriptGenController();
			if (sGenCtrl)
			{
				LFile *lFile = sGenCtrl->GetLFile();
				std::string str = lFile->Compile();
				PX2_LOGICM.SetCurGeneratedScript(str);
			}
		}
	}
}
//----------------------------------------------------------------------------
void BBManager::SetSelectSprite(BBlockSprite *sprite)
{
	mSelectSprite = sprite;

	PX2_LOGICM.SetSelectLogicObject(sprite);

	Event *ent = PX2_CREATEEVENTEX(BBlockES, SelectSprite);
	ent->SetDataPointer0((Object*)sprite);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
BBlockSprite *BBManager::GetSelectSprite()
{
	return mSelectSprite;
}
//----------------------------------------------------------------------------
BProject *BBManager::GetCurProject()
{
	return mProject;
}
//----------------------------------------------------------------------------
void BBManager::SetStageFrame(UIFrame *stageFrame)
{
	mStageFrame = stageFrame;
}
//----------------------------------------------------------------------------
UIFrame *BBManager::GetStageFrame()
{
	return mStageFrame;
}
//----------------------------------------------------------------------------
void BBManager::SetSmallFrame(UIFrame *smallFrame)
{
	mSmallFrame = smallFrame;
}
//----------------------------------------------------------------------------
UIFrame *BBManager::GetSmallFrame()
{
	return mSmallFrame;
}
//----------------------------------------------------------------------------
void BBManager::GetLocalProjects(const std::string &appName)
{
	_CheckCreateProjectPath(appName, "");

	std::string wirteablePath = PX2_RM.GetWriteablePath();
	std::string projectsXML = wirteablePath + _GetWritePath(appName) + "/"
		+ "projects.xml";
	
	PX2_LOG_INFO("GetLocalProjects %s", projectsXML.c_str());

	int bufferSize = 0;
	char *buffer = 0;
	if (!FileIO::Load(projectsXML, true, bufferSize, buffer))
		return;

	if (!buffer)
		return;

	PX2_LOG_INFO("GetLocalProjects LoadBuffer");

	mProjects.clear();

	XMLData data;
	if (data.LoadBuffer(buffer, bufferSize))
	{
		delete1(buffer);
		buffer = 0;

		XMLNode rootNode = data.GetRootNode();

		XMLNode projectNode = rootNode.IterateChild();
		while (!projectNode.IsNull())
		{
			std::string projectName = projectNode.AttributeToString("name");

			BProject *proj = new0 BProject();
			proj->SetName(projectName);

			mProjects.push_back(proj);

			projectNode = rootNode.IterateChild(projectNode);
		}
	}

	PX2_LOG_INFO("GetLocalProjects end");
}
//----------------------------------------------------------------------------
int BBManager::GetNumProject() const
{
	return (int)mProjects.size();
}
//----------------------------------------------------------------------------
std::string BBManager::GetProjectName(int i) const
{
	if (0 <= i && i < (int)mProjects.size())
	{
		return mProjects[i]->GetName();
	}

	return "";
}
//----------------------------------------------------------------------------
BProject *BBManager::GetProject(int i) const
{
	if (0 <= i && i < (int)mProjects.size())
	{
		return mProjects[i];
	}

	return 0;
}
//----------------------------------------------------------------------------
int BBManager::NewProject(const std::string &appName, 
	const std::string &projName)
{
	if (projName.empty())
		return 1;

	CloseProject();

	if (IsHasProject(projName))
		return 1;

	_CheckCreateProjectPath(appName, projName);

	mAppName = appName;
	mProject = new0 BProject();
	mProject->SetName(projName);

	Event *ent = PX2_CREATEEVENTEX(BBlockES, NewingProject);
	PX2_EW.BroadcastingLocalEvent(ent);

	PX2_ARDUINO.Reset();
	SaveProject();

	mProjects.push_back(mProject);
	_CreateSaveProjsectsXML(appName);

	LoadProject(appName, projName);

	return 0;
}
//----------------------------------------------------------------------------
bool BBManager::IsHasProject(const std::string &projName)
{
	for (int i = 0; i < (int)mProjects.size(); i++)
	{
		if (projName == mProjects[i]->GetName())
		{
			return true;
		}
	}

	return false;
}
//----------------------------------------------------------------------------
void BBManager::SaveProject()
{
	std::string wirteablePath = PX2_RM.GetWriteablePath();
	std::string projPath = wirteablePath + _GetWritePath(mAppName) + "/" +
		mProject->GetName() + "/";

	std::string xmlPath = projPath + "config.xml";	
	PX2BBLOCK_SYS.Save(xmlPath);

	std::string objPath = projPath + "object.px2obj";
	OutStream outStream;
	outStream.Insert(mProject);
	outStream.Save(objPath);
}
//----------------------------------------------------------------------------
void BBManager::SaveProject(const std::string &name, const std::string &date,
	const std::string &desc)
{
	mProject->SetName(name);
	mProject->DateStr = date;
	mProject->Desc = desc;

	SaveProject();
}
//----------------------------------------------------------------------------
bool BBManager::LoadProject(const std::string &appName, 
	const std::string &projName)
{
	_CheckCreateProjectPath(appName, projName);

	CloseProject();

	mAppName = appName;

	std::string wirteablePath = PX2_RM.GetWriteablePath();
	std::string projPath = wirteablePath + _GetWritePath(mAppName) + "/" +
		projName + "/";

	std::string xmlPath = projPath + "config.xml";
	PX2BBLOCK_SYS.Load(xmlPath);

	std::string objPath = projPath + "object.px2obj";
	InStream inStream;
	if (inStream.Load(objPath))
	{
		ObjectPtr obj = inStream.GetObjectAt(0);
		if (obj)
		{
			BProject *proj = DynamicCast<BProject>(obj);
			if (proj)
			{
				UIFrame *stageFrame = PX2_BBM.GetStageFrame();
				if (stageFrame)
				{
					stageFrame->DetachAllChildren();
					UIFrame *stageContentFrame = proj->GetContentFrame();
					stageFrame->AttachChild(stageContentFrame);
				}

				UIFrame *smallFrame = PX2_BBM.GetSmallFrame();
				if (smallFrame)
				{
					PX2_BBM.GetSmallFrame()->DetachAllChildren();
					UIFrame *smallFrame = proj->GetSmallFrame();
					PX2_BBM.GetSmallFrame()->AttachChild(smallFrame);
				}

				Scene *scene = proj->GetScene();
				if (scene)
				{
					PX2_PROJ.SetScene(scene);
				}
			}

			mProject = proj;
		}
	}

	PX2_RM.ClearRes(objPath);

	Event *ent = PX2_CREATEEVENTEX(BBlockES, OpenProject);
	PX2_EW.BroadcastingLocalEvent(ent);

	// select one
	if (mProject)
	{
		UIFrame *contentFrame = mProject->GetContentFrame();
		for (int i = 0; i < contentFrame->GetNumChildren(); i++)
		{
			BBlockSprite *sp = DynamicCast<BBlockSprite>(
				contentFrame->GetChild(i));
			if (sp)
			{
				SetSelectSprite(sp);
				break;
			}
		}
	}

	return true;
}
//----------------------------------------------------------------------------
const std::string &BBManager::GetAppName() const
{
	return mAppName;
}
//----------------------------------------------------------------------------
const std::string &BBManager::GetProjectName() const
{
	return mProject->GetName();
}
//----------------------------------------------------------------------------
void BBManager::CloseProject()
{
	PX2_ARDUINO.Reset();
	PX2_SC_LUA->UnRegistAllEventFunctions("BBlockEventS::Play");
	PX2_SC_LUA->UnRegistAllEventFunctions("BBlockEventS::Stop");
	PX2_SC_LUA->UnRegistAllEventFunctions("BBlockEventS::String");
	PX2_SC_LUA->UnRegistAllEventFunctions("BBlockEventS::UIButtonPressed");
	PX2_SC_LUA->UnRegistAllEventFunctions("BBlockEventS::UIButtonReleased");
	PX2_SC_LUA->UnRegistAllEventFunctions("BBlockEventS::UIButtonReleasedNotPick");
	PX2_SC_LUA->UnRegistAllEventFunctions("BBlockEventS::UIRoundDragChanged");
	PX2_SC_LUA->UnRegistAllEventFunctions("BBlockEventS::VoiceResult");
	PX2_SC_LUA->UnRegistAllEventFunctions("BBlockEventS::BluetoothReceive");
	PX2_SC_LUA->UnRegistAllEventFunctions("BBlockEventS::IRReceive");

	Event *ent = PX2_CREATEEVENTEX(BBlockES, CloseProject);
	PX2_EW.BroadcastingLocalEvent(ent);

	PX2_BBM.SetSelectSprite(0);
	PX2_BBM.SetEditorPressingBBlock(0);
	PX2_BBM.SetDragingBBlock(0);
	PX2_BBM.SetSelectBBlockCata(0);
	PX2_BBM.SetSelectBBlockEditor(0);

	mProject = 0;
	PX2BBLOCK_SYS.Clear();
	if (mStageFrame)
		mStageFrame->DetachAllChildren();
	PX2_PROJ.SetScene(0);
}
//----------------------------------------------------------------------------
void BBManager::DeleteProject(const std::string &appName, 
	const std::string &projName)
{
	if (projName.empty())
		return;

	if (appName == mAppName && projName == mProject->GetName())
	{
		CloseProject();
	}

	if (!IsHasProject(projName))
		return;

	auto it = mProjects.begin();
	for (; it != mProjects.end(); it++)
	{
		BProject *proj = *it;
		if (proj->GetName() == projName)
		{
			mProjects.erase(it);
			break;
		}
	}

	_CreateSaveProjsectsXML(appName);
}
//----------------------------------------------------------------------------
std::string BBManager::_GetWritePath(const std::string &appName)
{
	return "Write_" + appName;
}
//----------------------------------------------------------------------------
void BBManager::_CheckCreateProjectPath(const std::string &appName, 
	const std::string &projName)
{
	std::string wirteablePath = PX2_RM.GetWriteablePath();
	std::string appPath = _GetWritePath(appName) + "/";
	if (!PX2_RM.IsFileFloderExist(wirteablePath + appPath))
	{
		PX2_RM.CreateFloder(wirteablePath, appPath);
		_CreateSaveProjsectsXML(appName);
	}

	if (!projName.empty())
	{
		std::string projPath = appPath + projName + "/";
		if (!PX2_RM.IsFileFloderExist(projPath))
		{
			PX2_RM.CreateFloder(wirteablePath, projPath);
		}
	}
}
//----------------------------------------------------------------------------
void BBManager::_CreateSaveProjsectsXML(const std::string &appName)
{
	std::string wirteablePath = PX2_RM.GetWriteablePath();
	std::string projectsXML = wirteablePath + _GetWritePath(appName) + "/"
		+ "projects.xml";

	XMLData data;
	data.Create();

	XMLNode rootNode = data.NewChild("rootnode");

	for (int i = 0; i < (int)mProjects.size(); i++)
	{
		BProject *proj = mProjects[i];
		std::string projName = proj->GetName();
		std::string projDesc = proj->Desc;
		XMLNode node = rootNode.NewChild("project");
		node.SetAttributeString("name", projName);
	}

	data.SaveFile(projectsXML);
}
//----------------------------------------------------------------------------
void BBManager::_GenDefaultParams(BBlock* block)
{
	std::vector<Pointer0<BBlockConnector> > &ctns = block->GetConnectors();
	for (int i = 0; i < (int)ctns.size(); i++)
	{
		BBlockConnector *ctn = ctns[i];
		if (BBlockConnector::CT_PARAM == ctn->GetConnectorType())
		{
			LParam *lParam = ctn->GetLParam();
			FunParamType paramType = lParam->GetDataType();
			std::string typeName = lParam->GetDataTypeName();
			std::string paramName = lParam->GetName();
			bool isEnum = lParam->IsEnum();

			bool isVaiable = (paramName == "variable");
			bool isEvent = (paramName == "Event");
			bool isMusic = ("musicStr" == paramName);

			int iVal = 0;
			float fVal = 0.0f;
			char cVal = 0;
			std::string strVal;
			bool bVal = false;

			FunObject *funObj = 0;
			std::string genParamName = "";
			if (FPT_CHAR == paramType)
			{
				genParamName = "cValue";
				if (isVaiable)
					genParamName = "ParamsChar";

				cVal = lParam->GetValueChar();
			}
			else if (FPT_INT == paramType)
			{
				genParamName = "iValue";
				if (isVaiable)
					genParamName = "ParamsInt";

				iVal = lParam->GetValueI();
			}
			else if (FPT_FLOAT == paramType)
			{
				genParamName = "fValue";
				if (isVaiable)
					genParamName = "ParamsFloat";

				fVal = lParam->GetValueF();
			}
			else if (FPT_BOOL == paramType)
			{
				genParamName = "BoolSelect";
				if (isVaiable)
					genParamName = "ParamsBool";

				bVal = lParam->GetValueB();
			}
			else if (FPT_STRING == paramType)
			{
				genParamName = "strValue";
				if (isVaiable)
				{
					genParamName = "ParamsString";
				}
				else if (isEvent)
				{
					genParamName = "BBlockEventS";
				}
				else if (isMusic)
				{
					genParamName = "Musics";
				}

				strVal = lParam->GetValueStr();	
			}

			if (!isEnum)
			{
				if (!genParamName.empty())
				{
					funObj = PX2_LOGICM.GetParam(genParamName);
				}

				if (funObj)
				{
					LBlock *lBlock = new0 LBlock(LBlock::MT_PARAM);
					lBlock->RegistFunObj(*funObj);
					LParam *iParam = lBlock->GetInputParam(0);
					if (iParam)
						iParam->SetValue(lParam->GetValue());

					BBlock *uiBlock = new0 BBlock();
					uiBlock->SetLBlock(lBlock);
					ctn->AttachChild(uiBlock);
					uiBlock->SetEditState(BBlock::ES_EDITOR);
					ctn->Update(Time::GetTimeInSeconds(), 0.0f);
				}
			}
			else
			{
				FunObject *funObjBBS = PX2_LOGICM.GetClassFunObject("BBlockSystem");
				if (funObjBBS)
				{
					FunObject *funObjEnum = funObjBBS->GetEnum(typeName);
					if (funObjEnum)
					{
						funObj = funObjEnum;
					}
				}

				if (funObj)
				{
					LBlock *lBlock = new0 LBlock(LBlock::MT_PARAM);
					lBlock->RegistFunObj(*funObj);
					LParam *iParam = lBlock->GetInputParam(0);
					if (iParam)
						iParam->SetValue(lParam->GetValue());

					BBlock *uiBlock = new0 BBlock();
					uiBlock->SetLBlock(lBlock);
					ctn->AttachChild(uiBlock);
					uiBlock->SetEditState(BBlock::ES_EDITOR);
					ctn->Update(Time::GetTimeInSeconds(), 0.0f);
				}
			}
		}
	}
}
//----------------------------------------------------------------------------
