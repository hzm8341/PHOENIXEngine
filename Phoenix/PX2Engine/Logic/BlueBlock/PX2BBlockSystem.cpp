// PX2BBlockSystem.cpp

#include "PX2BBlockSystem.hpp"
#include "PX2Log.hpp"
#include "PX2SoundSystem.hpp"
#include "PX2StringHelp.hpp"
#include "PX2StringTokenizer.hpp"
#include "PX2Net.hpp"
#include "PX2VoiceSDK.hpp"
#include "PX2BBlockEvent.hpp"
#include "PX2BBlockEvents.hpp"
#include "PX2Application.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2ProjectEvent.hpp"
#include "PX2Project.hpp"
#include "PX2LogicManager.hpp"
#include "PX2VoiceEventType.hpp"
#include "PX2EngineCanvas.hpp"
#include "PX2Serial.hpp"
#include "PX2Timestamp.hpp"
#include "PX2LocalDateTime.hpp"
#include "PX2BBManager.hpp"
#include "PX2BDefine.hpp"
#include "PX2LuaPlusContext.hpp"
#include "PX2Arduino.hpp"
#include "PX2System.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
void _BBlockSystem_ArduinoReceiveCallback (ArduinoRectType type, int val)
{
	if (type == ART_RECV_IR)
	{
		PX2BBLOCK_SYS._OnIRReceive(val);
	}
}
//----------------------------------------------------------------------------
BBlockSystem::BBlockSystem()
{
	mIsRuning = false;
	mSetType = ST_BLUETOOTH;
	mTargetRobotID = 0;
	mDeviceID = 0;
	mIsInitlized = false;
}
//----------------------------------------------------------------------------
BBlockSystem::~BBlockSystem()
{
}
//----------------------------------------------------------------------------
void BBlockSystem::Initlize()
{
	mIsInitlized = true;

	PX2_ARDUINO.AddArduinoReceiveCallbacks(
		_BBlockSystem_ArduinoReceiveCallback);
}
//----------------------------------------------------------------------------
bool BBlockSystem::IsInitlized() const
{
	return mIsInitlized;
}
//----------------------------------------------------------------------------
std::string _GetProjectSavePath(const std::string &projname)
{
	const std::string &writeablePath = PX2_RM.GetWriteablePath();
	std::string projWritePath = writeablePath + projname + "/";
	return projWritePath;
}
//----------------------------------------------------------------------------
void _BBSystemReceiveCallback (std::string recvVal)
{
	if (!PX2BBLOCK_SYS.IsInitlized())
		return;

	PX2_LOG_INFO("BlueBlock Receive:%s", recvVal.c_str());

	PX2BBLOCK_SYS.EventObjectName = "Bluetooth";
	PX2BBLOCK_SYS.EventDataFloat = 0.0f;
	PX2BBLOCK_SYS.EventDataString = recvVal;

	Event *ent = PX2_CREATEEVENTEX(BBlockEventS, BluetoothReceive);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
void BBlockSystem::OnEvent(Event *event)
{
	std::string writeablePath = PX2_RM.GetWriteablePath();

	if (ProjectES::IsEqual(event, ProjectES::NewProject))
	{
		PX2_BLUETOOTH.AddCMDCallback(_BBSystemReceiveCallback);
	}
	else if (ProjectES::IsEqual(event, ProjectES::LoadedProject))
	{
		Clear();

		PX2_BLUETOOTH.AddCMDCallback(_BBSystemReceiveCallback);

		Project *proj = Project::GetSingletonPtr();
		if (proj)
		{
			const std::string &projName = proj->GetName();
			std::string projWritePath = _GetProjectSavePath(projName);
			const std::string bbFilename = projWritePath + "blueblock.xml";
			if (PX2_RM.IsFileFloderExist(bbFilename))
			{
				Load(bbFilename);
			}
		}
	}
	else if (ProjectES::IsEqual(event, ProjectES::SavedProject))
	{
		Project *proj = Project::GetSingletonPtr();
		if (proj)
		{
			const std::string &projName = proj->GetName();
			std::string projWritePath = _GetProjectSavePath(projName);
			if (!PX2_RM.IsFileFloderExist(projWritePath))
			{
				PX2_RM.CreateFloder(writeablePath, projName + "/");
			}
			const std::string bbFilename = projWritePath + "blueblock.xml";
			Save(bbFilename);
		}
	}
	else if (ProjectES::IsEqual(event, ProjectES::CloseProject))
	{
		Clear();
	}
	else if (BBlockES::IsEqual(event, BBlockES::CreateVariable))
	{
		auto params = PX2_LOGICM.GetParams();
		auto paramsCreatedVaiable = params["ParamCreated"];

		FunObject *funObj = event->GetData<FunObject*>();
		const std::string &funObjName = funObj->Name;

		const FunParam &funParam = funObj->GetInParam(0);
		if (FPT_INT == funParam.Type)
		{
			FunObject *paramsInt = PX2_LOGICM.GetParam("ParamsInt");
			paramsInt->AddInput(funObjName, funParam.Type, "ParamsInt", funParam.Value);

			Event *ent = BBlockES::CreateEventX(BBlockES::RefreshParamObject);
			ent->SetData<FunObject*>(paramsInt);
			PX2_EW.BroadcastingLocalEvent(ent);
		}
		else if (FPT_FLOAT == funParam.Type)
		{
			FunObject * paramsFloat = PX2_LOGICM.GetParam("ParamsFloat");
			paramsFloat->AddInput(funObjName, funParam.Type, "ParamsFloat", funParam.Value);

			Event *ent = BBlockES::CreateEventX(BBlockES::RefreshParamObject);
			ent->SetData<FunObject*>(paramsFloat);
			PX2_EW.BroadcastingLocalEvent(ent);
		}
		else if (FPT_BOOL == funParam.Type)
		{
			FunObject * paramsBool = PX2_LOGICM.GetParam("ParamsBool");
			paramsBool->AddInput(funObjName, funParam.Type, "ParamsBool", funParam.Value);

			Event *ent = BBlockES::CreateEventX(BBlockES::RefreshParamObject);
			ent->SetData<FunObject*>(paramsBool);
			PX2_EW.BroadcastingLocalEvent(ent);
		}
		else if (FPT_CHAR == funParam.Type)
		{
			FunObject * paramsChar = PX2_LOGICM.GetParam("ParamsChar");
			paramsChar->AddInput(funObjName, funParam.Type, "ParamsChar", funParam.Value);

			Event *ent = BBlockES::CreateEventX(BBlockES::RefreshParamObject);
			ent->SetData<FunObject*>(paramsChar);
			PX2_EW.BroadcastingLocalEvent(ent);
		}
		else if (FPT_STRING == funParam.Type)
		{
			FunObject * paramsString = PX2_LOGICM.GetParam("ParamsString");
			paramsString->AddInput(funObjName, funParam.Type, "ParamsString", funParam.Value);

			Event *ent = BBlockES::CreateEventX(BBlockES::RefreshParamObject);
			ent->SetData<FunObject*>(paramsString);
			PX2_EW.BroadcastingLocalEvent(ent);
		}
	}
	else if (BBlockES::IsEqual(event, BBlockES::DeleteVariable))
	{
		auto params = PX2_LOGICM.GetParams();
		auto paramsCreatedVaiable = params["ParamCreated"];

		FunObject *funObj = event->GetData<FunObject*>();
		const std::string &funObjName = funObj->Name;

		const FunParam &funParam = funObj->GetInParam(0);
		if (FPT_INT == funParam.Type)
		{
			FunObject *paramsInt = PX2_LOGICM.GetParam("ParamsInt");
			paramsInt->RemoveInput(funObjName);

			Event *ent = BBlockES::CreateEventX(BBlockES::RefreshParamObject);
			ent->SetData<FunObject*>(paramsInt);
			PX2_EW.BroadcastingLocalEvent(ent);
		}
		else if (FPT_FLOAT == funParam.Type)
		{
			FunObject * paramsFloat = PX2_LOGICM.GetParam("ParamsFloat");
			paramsFloat->RemoveInput(funObjName);

			Event *ent = BBlockES::CreateEventX(BBlockES::RefreshParamObject);
			ent->SetData<FunObject*>(paramsFloat);
			PX2_EW.BroadcastingLocalEvent(ent);
		}
		else if (FPT_BOOL == funParam.Type)
		{
			FunObject * paramsBool = PX2_LOGICM.GetParam("ParamsBool");
			paramsBool->RemoveInput(funObjName);

			Event *ent = BBlockES::CreateEventX(BBlockES::RefreshParamObject);
			ent->SetData<FunObject*>(paramsBool);
			PX2_EW.BroadcastingLocalEvent(ent);
		}
		else if (FPT_CHAR == funParam.Type)
		{
			FunObject * paramsChar = PX2_LOGICM.GetParam("ParamsChar");
			paramsChar->RemoveInput(funObjName);

			Event *ent = BBlockES::CreateEventX(BBlockES::RefreshParamObject);
			ent->SetData<FunObject*>(paramsChar);
			PX2_EW.BroadcastingLocalEvent(ent);
		}
		else if (FPT_STRING == funParam.Type)
		{
			FunObject * paramsString = PX2_LOGICM.GetParam("ParamsString");
			paramsString->RemoveInput(funObjName);

			Event *ent = BBlockES::CreateEventX(BBlockES::RefreshParamObject);
			ent->SetData<FunObject*>(paramsString);
			PX2_EW.BroadcastingLocalEvent(ent);
		}
	}
	else if (VoiceSDKSpace::IsEqual(event, VoiceSDKSpace::RecognizeResults))
	{
		VoiceData data = event->GetData<VoiceData>();
		const std::string &retStr = data.StrRet;

		EventObjectName = "Voice";
		EventDataFloat = 0.0f;
		EventDataString = retStr;

		Event *ent = PX2_CREATEEVENTEX(BBlockEventS, VoiceResult);
		PX2_EW.BroadcastingLocalEvent(ent);
	}
}
//----------------------------------------------------------------------------
void BBlockSystem::Save(const std::string &filename)
{
	XMLData data;
	data.Create();

	XMLNode rootNode = data.NewChild("rootnode");
	XMLNode paramcreatedNode = rootNode.NewChild("paramcreated");

	LogicManager::ParamsType &paramsMap = PX2_LOGICM.GetParams();
	auto params = paramsMap["ParamCreated"];
	for (int i = 0; i < (int)params.size(); i++)
	{
		std::string paramName = params[i];
		XMLNode node = paramcreatedNode.NewChild("param");

		FunObject *paramObj = PX2_LOGICM.GetParam(paramName);
		if (paramObj)
			paramObj->Save(node);
	}

	data.SaveFile(filename);
}
//----------------------------------------------------------------------------
bool BBlockSystem::Load(const std::string &filename)
{
	std::string strBuf;
    int bufSize = 0;
    char *buf = 0;
    if (FileIO::Load(filename, true, bufSize, buf))
    {
        strBuf = std::string(buf, bufSize);
        
        delete1(buf);
    }
    else
    {
        return false;
    }
    
	if (strBuf.empty())
		return false;

	XMLData data;
	if (data.LoadBuffer(strBuf.c_str(), (int)strBuf.size()))
	{
		PX2_RM.ClearRes(filename);

		XMLNode rootNode = data.GetRootNode();

		XMLNode paramCreated = rootNode.GetChild("paramcreated");
		XMLNode funObjectNode = paramCreated.IterateChild();
		while (!funObjectNode.IsNull())
		{
			std::string name = funObjectNode.AttributeToString("Name");
			FunObject *funObject = PX2_LOGICM.GetParam(name);

			if (!funObject)
			{
				std::string name = funObjectNode.AttributeToString("Name");
				bool isClassCatalogue = funObjectNode.AttributeToBool("IsClassCatalogue");
				PX2_UNUSED(isClassCatalogue);
				std::string parentClassName = funObjectNode.AttributeToString("ParentClassName");
				bool isStatic = funObjectNode.AttributeToBool("IsStatic");
				PX2_UNUSED(isStatic);
				std::string className = funObjectNode.AttributeToString("ClassName");
				std::string sigletonName = funObjectNode.AttributeToString("SigletonName");
				int paramType = funObjectNode.AttributeToInt("ParamType");
				int numParamIn = funObjectNode.AttributeToInt("NumInParam");
				PX2_UNUSED(numParamIn);
				int numParamOut = funObjectNode.AttributeToInt("NumOutParam");
				PX2_UNUSED(numParamOut);
				FunObject::ParamType pt = (FunObject::ParamType)paramType;
				PX2_UNUSED(pt);

				PX2_LOGICM.BeginAddParam(name, FunObject::PT_VARIABLE);

				XMLNode nodeParamsIn = funObjectNode.GetChild("ParamsIn");
				if (!nodeParamsIn.IsNull())
				{
					XMLNode inputNode = nodeParamsIn.IterateChild();
					while (!inputNode.IsNull())
					{
						std::string paramName = inputNode.AttributeToString("name");
						int paramType1 = inputNode.AttributeToInt("type");
						FunParamType fpt = (FunParamType)paramType1;
						if (FPT_INT == fpt)
							PX2_LOGICM.AddInputInt(paramName, 0);
						else if (FPT_FLOAT == fpt)
							PX2_LOGICM.AddInputFloat(paramName, 0.0f);
						else if (FPT_CHAR == fpt)
							PX2_LOGICM.AddInputChar(paramName, 65);
						else if (FPT_STRING == fpt)
							PX2_LOGICM.AddInputString(paramName, "defstring");
						else if (FPT_BOOL == fpt)
							PX2_LOGICM.AddInputBool(paramName, true);

						inputNode = nodeParamsIn.IterateChild(inputNode);
					}
				}

				PX2_LOGICM.EndAddFun_Param("ParamCreated");

				FunObject *curFunObj = PX2_LOGICM.GetCurAddFunObject();
				if (curFunObj)
				{
					Event *ent = BBlockES::CreateEventX(BBlockES::CreateVariable);
					ent->SetData<FunObject*>(curFunObj);
					PX2_EW.BroadcastingLocalEvent(ent);
				}
			}

			funObjectNode = paramCreated.IterateChild(funObjectNode);
		}

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void BBlockSystem::Clear()
{
	EventObjectName = "";
	EventDataFloat = 0.0f;
	EventDataString = "";

	std::map<std::string, FunObjectPtr> &paramMap = PX2_LOGICM.GetParamMap();

	LogicManager::ParamsType &paramsMap = PX2_LOGICM.GetParams();
	auto params = paramsMap["ParamCreated"];
	for (int i = 0; i < (int)params.size(); i++)
	{
		const std::string &name = params[i];
		paramMap.erase(name);
	}

	paramsMap["ParamCreated"].clear();
}
//----------------------------------------------------------------------------
void BBlockSystem::Run(bool run)
{
	if (run)
	{
		PX2_BBM.SaveProject();
	}
	else
	{
		PX2_TIMERM.ClearTimers();
		PX2_SC_LUA->ClearEventObjectFunctions();
		
		std::string curAppName = PX2_BBM.GetAppName();
		std::string projName = PX2_BBM.GetProjectName();
		PX2_BBM.LoadProject(curAppName, projName);
	}

	mIsRuning = run;
	PX2_ARDUINO._SetDist(0.0f);

	std::string dataStr = mIsRuning ? "true" : "false";

	Event *ent = PX2_CREATEEVENTEX(BBlockES, Run);
	ent->SetDataStr0(dataStr);
	ent->SetData<bool>(run);
	PX2_EW.BroadcastingLocalEvent(ent);

	if (mIsRuning)
	{
		Event *ent = PX2_CREATEEVENTEX(BBlockEventS, Play);
		PX2_EW.BroadcastingLocalEvent(ent);
	}
	else
	{
		Event *ent = PX2_CREATEEVENTEX(BBlockEventS, Stop);
		PX2_EW.BroadcastingLocalEvent(ent);
	}
}
//----------------------------------------------------------------------------
void BBlockSystem::ReStart()
{
	Run(false);
	Run(true);
}
//----------------------------------------------------------------------------
bool BBlockSystem::IsRunning() const
{
	return mIsRuning;
}
//----------------------------------------------------------------------------
void BBlockSystem::Update(float elapsedTime)
{
	if (mServerWifi)
		mServerWifi->Update(elapsedTime);
}
//----------------------------------------------------------------------------
void BBlockSystem::SetSysType(SysType st, int targetRobotID,
	const std::string &serialPort, int baudrate)
{
	mSetType = st;
	mTargetRobotID = targetRobotID;

	PX2_ARDUINO.Terminate();

	if (mServerWifi)
	{
		mServerWifi->Stop();
		mServerWifi = 0;
	}

	if (ST_SERIAL == mSetType)
	{
		PX2_ARDUINO.Initlize(Arduino::M_SERIAL, serialPort, baudrate);
		System::SleepSeconds(1.0f);
	}
	else if (ST_BLUETOOTH == st)
	{
		PX2_ARDUINO.Initlize(Arduino::M_BLUETOOTH);

		SocketAddress udpAddr(BBlockSystemUDPPortRobot);
		mServerWifi = new0 UDPServer(udpAddr);
		mServerWifi->AddRecvCallback(_UDPServerRecvCallback);
		mServerWifi->Start();
	}
	else if (ST_WIFI_ROBOT == st)
	{
		PX2_ARDUINO.InitlizeSocketUDP_Broadcast(mTargetRobotID, BBlockSystemUDPPortRobot);
	}
}
//----------------------------------------------------------------------------
void BBlockSystem::_UDPServerRecvCallback(SocketAddress &address,
	const std::string &buf)
{
	StringTokenizer stk(buf, "$");

	std::string portStr;
	std::string cmd;
	std::string param0;
	std::string param1;

	if (stk.Count() > 0)
		portStr = stk[0];
	if (stk.Count() > 1)
		cmd = stk[1];
	if (stk.Count() > 2)
		param0 = stk[2];
	if (stk.Count() > 3)
		param1 = stk[3];

	int robotID = 0;
	if (!param0.empty())
		robotID = StringHelp::StringToInt(param0);

	if ("rs" == cmd)
	{
		int deviceID = PX2BBLOCK_SYS.getDeviceID();
		if (deviceID == robotID)
		{
			PX2_ARDUINO._Send(param1);
		}
	}
}
//----------------------------------------------------------------------------
BBlockSystem::SysType BBlockSystem::GetSysType() const
{
	return mSetType;
}
//----------------------------------------------------------------------------
void BBlockSystem::setName(const std::string &name)
{
	BBlockSprite *curSprite = 
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
	{
		curSprite->setName(name);
	}
}
//----------------------------------------------------------------------------
std::string BBlockSystem::getName() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->getName();
	return "";
}
//----------------------------------------------------------------------------
void BBlockSystem::setFixUpdateFPS(int fps)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setFixUpdateFPS(fps);
}
//----------------------------------------------------------------------------
int BBlockSystem::getFixUpdateFPS() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->getFixUpdateFPS();

	return 0;
}
//----------------------------------------------------------------------------
void BBlockSystem::show(bool show)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->show(show);
}
//----------------------------------------------------------------------------
bool BBlockSystem::isShow() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		return curSprite->isShow();
	return false;
}
//----------------------------------------------------------------------------
void BBlockSystem::setText(const std::string &str)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setText(str);
}
//----------------------------------------------------------------------------
std::string BBlockSystem::getText()
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		return curSprite->getText();
	return "";
}
//----------------------------------------------------------------------------
void BBlockSystem::setScale(float val)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setScale(val);
}
//----------------------------------------------------------------------------
float BBlockSystem::getScale() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->getScale();
	return 1.0f;
}
//----------------------------------------------------------------------------
void BBlockSystem::setScaleXZ(float scaleX, float scaleZ)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setScaleXZ(scaleX, scaleZ);
}
//----------------------------------------------------------------------------
void BBlockSystem::setScaleX(float val)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setScaleX(val);
}
//----------------------------------------------------------------------------
void BBlockSystem::setScaleZ(float val)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setScaleZ(val);
}
//----------------------------------------------------------------------------
float BBlockSystem::getScaleX() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->getScaleX();
	return 1.0;
}
//----------------------------------------------------------------------------
float BBlockSystem::getScaleZ() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->getScaleZ();
	return 1.0;
}
//----------------------------------------------------------------------------
void BBlockSystem::addScale(float scale)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->addScale(scale);
}
//----------------------------------------------------------------------------
void BBlockSystem::setRotateXYZ(float x, float y, float z)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setRotateXYZ(x, y, z);
}
//----------------------------------------------------------------------------
void BBlockSystem::setRotateX(float degree)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setRotateX(degree);
}
//----------------------------------------------------------------------------
void BBlockSystem::setRotateY(float degree)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setRotateY(degree);
}
//----------------------------------------------------------------------------
void BBlockSystem::setRotateZ(float degree)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setRotateZ(degree);
}
//----------------------------------------------------------------------------
float BBlockSystem::getRotateX() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		return curSprite->getRotateX();
	return 1.0;
}
//----------------------------------------------------------------------------
float BBlockSystem::getRotateY() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		return curSprite->getRotateY();
	return 1.0;
}
//----------------------------------------------------------------------------
float BBlockSystem::getRotateZ() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		return curSprite->getRotateZ();
	return 1.0;
}
//----------------------------------------------------------------------------
void BBlockSystem::addRotate(float degree)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->addRotate(degree);
}
//----------------------------------------------------------------------------
void BBlockSystem::setLayout(float horA, float horB, float horParamA, float horParamB,
	float verA, float verB, float verParamA, float verParamB,
	float pivotX, float pivotY, float width, float height)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setLayout(horA, horB, horParamA, horParamB,
		verA, verB, verParamA, verParamB,
		pivotX, pivotY, width, height);
}
//----------------------------------------------------------------------------
void BBlockSystem::setPostion(float posX, float posZ)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setPostion(posX, posZ);
}
//----------------------------------------------------------------------------
void BBlockSystem::setAnchorHor(float valA, float valB)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setAnchorHor(valA, valB);
}
//----------------------------------------------------------------------------
void BBlockSystem::setAnchorParamHor(float valA, float valB)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setAnchorParamHor(valA, valB);
}
//----------------------------------------------------------------------------
void BBlockSystem::setAnchorVer(float valA, float valB)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setAnchorVer(valA, valB);
}
//----------------------------------------------------------------------------
void BBlockSystem::setAnchorParamVer(float valA, float valB)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setAnchorParamVer(valA, valB);
}
//----------------------------------------------------------------------------
void BBlockSystem::move(float moveX, float moveZ)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->move(moveX, moveZ);
}
//----------------------------------------------------------------------------
void BBlockSystem::setLayer(int layer)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setLayer(layer);
}
//----------------------------------------------------------------------------
int BBlockSystem::getLayer() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		return curSprite->getLayer();
	return 0;
}
//----------------------------------------------------------------------------
void BBlockSystem::setPivot(float pivotX, float pivotY)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setPivot(pivotX, pivotY);
}
//----------------------------------------------------------------------------
void BBlockSystem::setSize(float size)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setSize(size);
}
//----------------------------------------------------------------------------
void BBlockSystem::setSizeWidthHeight(float width, float height)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setSizeWidthHeight(width, height);
}
//----------------------------------------------------------------------------
float BBlockSystem::getDragingDirX() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		return curSprite->getDragingDirX();
	return 1.0f;
}
//----------------------------------------------------------------------------
float BBlockSystem::getDragingDirY() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		return curSprite->getDragingDirY();
	return 1.0f;
}
//----------------------------------------------------------------------------
BBlockSystem::SimpleDirectionType BBlockSystem::getDragingDirSimple() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		return (BBlockSystem::SimpleDirectionType)curSprite->getDragingDirSimple();

	return BBlockSystem::SDT_NONE;
}
//----------------------------------------------------------------------------
float BBlockSystem::getDragingPercent() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		return curSprite->getDragingPercent();
	return 1.0f;
}
//----------------------------------------------------------------------------
BBlockSystem::DirectionType BBlockSystem::getDragingLeftMoveType() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		return (BBlockSystem::DirectionType)curSprite->getDragingLeftMoveType();

	return BBlockSystem::DT_NONE;
}
//----------------------------------------------------------------------------
float BBlockSystem::getDragingLeftMoveSpeed() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		return curSprite->getDragingLeftMoveSpeed();

	return 0.0f;
}
//----------------------------------------------------------------------------
BBlockSystem::DirectionType BBlockSystem::getDragingRightMoveType() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		return (BBlockSystem::DirectionType)curSprite->getDragingRightMoveType();

	return BBlockSystem::DT_NONE;
}
//----------------------------------------------------------------------------
float BBlockSystem::getDragingRightMoveSpeed() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		return curSprite->getDragingRightMoveSpeed();

	return 0.0f;
}
//----------------------------------------------------------------------------
void BBlockSystem::setSliderPercent(float perc)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setSliderPercent(perc);
}
//----------------------------------------------------------------------------
void BBlockSystem::setSlider100(int val)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setSlider100(val);
}
//----------------------------------------------------------------------------
void BBlockSystem::setSlider180(int val)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setSlider180(val);
}
//----------------------------------------------------------------------------
float BBlockSystem::getSliderPercent() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		return curSprite->getSliderPercent();

	return 0.0f;
}
//----------------------------------------------------------------------------
int BBlockSystem::getSlider100() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		return curSprite->getSlider100();

	return 0;
}
//----------------------------------------------------------------------------
int BBlockSystem::getSlider180() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		return curSprite->getSlider180();

	return 0;
}
//----------------------------------------------------------------------------
int BBlockSystem::getSlider360() const
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		return curSprite->getSlider360();

	return 0;
}
//----------------------------------------------------------------------------
void BBlockSystem::addChooseString(const std::string &str)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->addChooseString(str);
}
//----------------------------------------------------------------------------
void BBlockSystem::chooseString(const std::string &str)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->chooseString(str);
}
//----------------------------------------------------------------------------
void BBlockSystem::chooseIndex(int index)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->chooseIndex(index);
}
//----------------------------------------------------------------------------
std::string BBlockSystem::getChooseString()
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		return curSprite->getChooseString();
	return "";
}
//----------------------------------------------------------------------------
int BBlockSystem::getChooseIndex()
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		return curSprite->getChooseIndex();
	return 0;
}
//----------------------------------------------------------------------------
void BBlockSystem::setURL(const std::string &url)
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	if (curSprite)
		curSprite->setURL(url);
}
//----------------------------------------------------------------------------
BBlockSprite *BBlockSystem::setCurBBlockSprite(const std::string &name)
{
	Project *proj = Project::GetSingletonPtr();
	if (!proj) return 0;

	UI *ui = proj->GetUI();
	Object *obj = ui->GetObjectByName(name);
	PX2_LOGICM.SetCurLogicObject(obj);
	BBlockSprite *curSprite = DynamicCast<BBlockSprite>(obj);
	return curSprite;
}
//----------------------------------------------------------------------------
BBlockSprite *BBlockSystem::getCurBBlockSprite()
{
	BBlockSprite *curSprite =
		DynamicCast<BBlockSprite>(PX2_LOGICM.GetCurLogicObject());
	return curSprite;
}
//----------------------------------------------------------------------------
BBlockSprite *BBlockSystem::createSpriteFrame()
{
	BBlockSprite *curSprite = new0 BBlockSprite(BBlockSprite::ST_FRAME);
	PX2_LOGICM.SetCurLogicObject(curSprite);
	
	UI *ui = PX2_PROJ.GetUI();
	ui->AttachChild(curSprite);

	return curSprite;
}
//----------------------------------------------------------------------------
BBlockSprite *BBlockSystem::createSpritePicBox()
{
	BBlockSprite *curSprite = new0 BBlockSprite(BBlockSprite::ST_PICBOX);
	PX2_LOGICM.SetCurLogicObject(curSprite);

	UI *ui = PX2_PROJ.GetUI();
	ui->AttachChild(curSprite);

	return curSprite;
}
//----------------------------------------------------------------------------
BBlockSprite *BBlockSystem::createSpriteButton()
{
	BBlockSprite *curSprite = new0 BBlockSprite(BBlockSprite::ST_BUTTON);
	PX2_LOGICM.SetCurLogicObject(curSprite);

	UI *ui = PX2_PROJ.GetUI();
	ui->AttachChild(curSprite);

	return curSprite;
}
//----------------------------------------------------------------------------
BBlockSprite *BBlockSystem::createSpriteText()
{
	BBlockSprite *curSprite = new0 BBlockSprite(BBlockSprite::ST_TEXT);
	PX2_LOGICM.SetCurLogicObject(curSprite);

	UI *ui = PX2_PROJ.GetUI();
	ui->AttachChild(curSprite);

	return curSprite;
}
//----------------------------------------------------------------------------
BBlockSprite *BBlockSystem::createSpriteEditBox()
{
	BBlockSprite *curSprite = new0 BBlockSprite(BBlockSprite::ST_EDITBOX);
	PX2_LOGICM.SetCurLogicObject(curSprite);

	UI *ui = PX2_PROJ.GetUI();
	ui->AttachChild(curSprite);

	return curSprite;
}
//----------------------------------------------------------------------------
BBlockSprite *BBlockSystem::createSpriteComboBox()
{
	BBlockSprite *curSprite = new0 BBlockSprite(BBlockSprite::ST_COMBOXBOX);
	PX2_LOGICM.SetCurLogicObject(curSprite);

	UI *ui = PX2_PROJ.GetUI();
	ui->AttachChild(curSprite);

	return curSprite;
}
//----------------------------------------------------------------------------
BBlockSprite *BBlockSystem::createSpriteWebView()
{
	BBlockSprite *curSprite = new0 BBlockSprite(BBlockSprite::ST_WEBVIEW);
	PX2_LOGICM.SetCurLogicObject(curSprite);

	UI *ui = PX2_PROJ.GetUI();
	ui->AttachChild(curSprite);

	return curSprite;
}
//----------------------------------------------------------------------------
BBlockSprite *BBlockSystem::createSpriteRound()
{
	BBlockSprite *curSprite = new0 BBlockSprite(BBlockSprite::ST_ROUND);
	PX2_LOGICM.SetCurLogicObject(curSprite);

	UI *ui = PX2_PROJ.GetUI();
	ui->AttachChild(curSprite);

	return curSprite;
}
//----------------------------------------------------------------------------
void BBlockSystem::setBluetooth()
{
	SetSysType(BBlockSystem::ST_BLUETOOTH);
}
//----------------------------------------------------------------------------
void BBlockSystem::setSerial(const std::string &port)
{
	SetSysType(BBlockSystem::ST_SERIAL, 0, port);
}
//----------------------------------------------------------------------------
void BBlockSystem::setWifiRobot(int robotID)
{
	SetSysType(BBlockSystem::ST_WIFI_ROBOT, robotID);
}
//----------------------------------------------------------------------------
void BBlockSystem::setDeviceID(int id)
{
	mDeviceID = id;
}
//----------------------------------------------------------------------------
int BBlockSystem::getDeviceID() const
{
	return mDeviceID;
}
//----------------------------------------------------------------------------
void BBlockSystem::log(const std::string &str)
{
	PX2_LOG_INFO(str.c_str());

	EngineCanvas *engineCanvas = EngineCanvas::GetSingletonPtr();
	if (engineCanvas)
	{
		engineCanvas->AddInfoText(str);
	}
}
//----------------------------------------------------------------------------
int BBlockSystem::rand255()
{
	return (int)Mathf::IntervalRandom(0.0f, 255.0f);
}
//----------------------------------------------------------------------------
int BBlockSystem::randZeroOne()
{
	float val = Mathf::SymmetricRandom();
	if (val > 0.0f)
		return 1;

	return 0;
}
//----------------------------------------------------------------------------
float BBlockSystem::randZero2One()
{
	return Mathf::UnitRandom();
}
//----------------------------------------------------------------------------
void BBlockSystem::playMusic(const std::string &key)
{
	PX2_UNUSED(key);
}
//----------------------------------------------------------------------------
void BBlockSystem::stopMusic()
{
	PX2_SS.PlayMusic(0, 0, true, 0.0f);
}
//----------------------------------------------------------------------------
void BBlockSystem::playCam()
{
}
//----------------------------------------------------------------------------
int BBlockSystem::stringToInt(const std::string &str)
{
	return StringHelp::StringToInt(str);
}
//----------------------------------------------------------------------------
float BBlockSystem::stringToFloat(const std::string &str)
{
	return StringHelp::StringToFloat(str);
}
//----------------------------------------------------------------------------
std::string BBlockSystem::intToString(int val)
{
	return StringHelp::IntToString(val);
}
//----------------------------------------------------------------------------
std::string BBlockSystem::floatToString(float val)
{
	return StringHelp::FloatToString(val);
}
//----------------------------------------------------------------------------
std::string BBlockSystem::getStringParam(const std::string &paramStr, int index)
{
	StringTokenizer tok(paramStr, " ");

	if (0 <= index && index < (int)tok.Count())
		return tok[index];

	return "";
}
//----------------------------------------------------------------------------
std::string BBlockSystem::stringAdd(const std::string &str0, const std::string &str1)
{
	std::string str;
	str.append(str0);
	str.append(str1);
	return str;
}
//----------------------------------------------------------------------------
int BBlockSystem::getYear() const
{
	LocalDateTime time;
	return time.Year();
}
//----------------------------------------------------------------------------
int BBlockSystem::getMonth() const
{
	LocalDateTime time;
	return time.Month();
}
//----------------------------------------------------------------------------
int BBlockSystem::getWeek() const
{
	LocalDateTime time;
	return time.Week();
}
//----------------------------------------------------------------------------
int BBlockSystem::getDay() const
{
	LocalDateTime time;
	return time.Day();
}
//----------------------------------------------------------------------------
int BBlockSystem::getDayOfWeek() const
{
	LocalDateTime time;
	return time.DayOfWeek();
}
//----------------------------------------------------------------------------
int BBlockSystem::getTimeHour() const
{
	LocalDateTime time;
	return time.Hour();
}
//----------------------------------------------------------------------------
int BBlockSystem::getTimeMinute() const
{
	LocalDateTime time;
	return time.Minute();
}
//----------------------------------------------------------------------------
int BBlockSystem::getTimeSecond() const
{
	LocalDateTime time;
	return time.Second();
}
//----------------------------------------------------------------------------
std::string BBlockSystem::getTimeString() const
{
	LocalDateTime time;
	int year = time.Year();
	int month = time.Month();
	int day = time.Day();
	int hour = time.Hour();
	int minute = time.Minute();
	std::string strResult;
	strResult += StringHelp::IntToString(year);
	strResult += PX2_LM_APP.GetValue("Year");
	strResult += StringHelp::IntToString(month);
	strResult += PX2_LM_APP.GetValue("Month");
	strResult += StringHelp::IntToString(day);
	strResult += PX2_LM_APP.GetValue("Day");
	strResult += StringHelp::IntToString(hour);
	strResult += PX2_LM_APP.GetValue("Hour");
	strResult += StringHelp::IntToString(hour);
	strResult += PX2_LM_APP.GetValue("Minute");
	strResult += StringHelp::IntToString(minute);
	strResult += PX2_LM_APP.GetValue("Second");

	return strResult;
}
//----------------------------------------------------------------------------
void BBlockSystem::sendEvent(const std::string &str)
{
	EventDataString = str;

	Event *ent = PX2_CREATEEVENTEX(BBlockEventS, String);
	ent->SetData(str);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
std::string BBlockSystem::getEventObjectName() const
{
	return EventObjectName;
}
//----------------------------------------------------------------------------
float BBlockSystem::getEventDataFloat() const
{
	return EventDataFloat;
}
//----------------------------------------------------------------------------
std::string BBlockSystem::getEventDataString() const
{
	return EventDataString;
}
//----------------------------------------------------------------------------
void BBlockSystem::bluetoothSendString(const std::string &str)
{
	PX2_BLUETOOTH.Send(str);
}
//----------------------------------------------------------------------------
void BBlockSystem::voiceStart()
{
	PX2_VOICESDK.StartVoiceListening();
}
//----------------------------------------------------------------------------
void BBlockSystem::voiceEnd()
{
	PX2_VOICESDK.EndVoiceListening();
}
//----------------------------------------------------------------------------
void BBlockSystem::voiceSpeak(const std::string &str)
{
	PX2_VOICESDK.Speak(str);
}
//----------------------------------------------------------------------------
void BBlockSystem::voiceAutoSpeakEnable(bool enable)
{
	PX2_VOICESDK.EnableAutoSpeak(enable);
}
//----------------------------------------------------------------------------
bool BBlockSystem::voiceIsAutoSpeakEnable() const
{
	return PX2_VOICESDK.IsAutoSpeakEnabled();
}
//----------------------------------------------------------------------------
void BBlockSystem::_OnIRReceive(int val)
{
	PX2BBLOCK_SYS.EventObjectName = "IR";
	PX2BBLOCK_SYS.EventDataFloat = (float)val;
	PX2BBLOCK_SYS.EventDataString = "";

	Event *ent = PX2_CREATEEVENTEX(BBlockEventS, IRReceive);
	PX2_EW.BroadcastingLocalEvent(ent);
}
//----------------------------------------------------------------------------
