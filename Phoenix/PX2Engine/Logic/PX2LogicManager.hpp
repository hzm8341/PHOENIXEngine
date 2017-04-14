// PX2LogicManager.hpp

#ifndef PX2LOGICMANAGER_HPP
#define PX2LOGICMANAGER_HPP

#include "PX2LogicPre.hpp"
#include "PX2Singleton_NeedNew.hpp"
#include "PX2InterpCurve.hpp"
#include "PX2FunObject.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM LogicManager : public Singleton<LogicManager>
	{
	public:
		LogicManager();
		virtual ~LogicManager();

		bool Initlize();

		bool LoadPkgInfo(const std::string &filename);

	protected:
		void _InitBlocks();
		bool _InitlizeBP();

		// add funs
	public:
		void BeginAddFunObj(const std::string &funName);
		void BeginAddClassFunObj(const std::string &className, const std::string &funName,
			bool isStatic=false, const std::string &singltonName="", const std::string &tag="");
		void BeginAddParam(const std::string &paramName, FunObject::ParamType pt);
		void BeginAddEvent(const std::string &className, const std::string &entName);
		void RemoveParam(const std::string &paramName);

		void AddInput(const std::string &name, FunParamType funParamType);
		void AddInputChar(const std::string &name, char val);
		void AddInputInt(const std::string &name, int val);
		void AddInputFloat(const std::string &name, float val);
		void AddInputBool(const std::string &name, bool val);
		void AddInputString(const std::string &name, const std::string &val);
		void AddInputObj(const std::string &name);
		void AddOutput(const std::string &name, FunParamType funParamType);

		void EndAddFun_Ctrl(const std::string &catalogue);
		void EndAddFun_Param(const std::string &catalogue);
		void EndAddFun_Operator(const std::string &catalogue);
		void EndAddFun_General(const std::string &catalogue);
		void EndAddFun_Event(const std::string &catalogue);

		FunObject *GetCurAddFunObject();

	public:
		FunObject *GetFunObject(const std::string &name);

		// Events
		const std::map<std::string, std::vector<std::string> > &GetEvents() const;
		std::map<std::string, FunObjectPtr> &GetEventMap();
		FunObject *GetEvent(const std::string &name);

		const FunObject *GetStartGF() const;

		// General Functions
		const std::map<std::string, std::vector<std::string> > &GetGFs() const;
		std::map<std::string, FunObjectPtr> &GetGFMap();
		FunObject *GetGF(const std::string &name);

		// Ctrls
		const std::map<std::string, std::vector<std::string> > &GetCtrls() const;
		std::map<std::string, FunObjectPtr> &GetCtrlMap();
		FunObject *GetCtrl(const std::string &name);

		// Params
		const std::map<std::string, std::vector<std::string> > &GetParams() const;
		std::map<std::string, FunObjectPtr> &GetParamMap();
		FunObject *GetParam(const std::string &name);

		// Operators
		const std::map<std::string, std::vector<std::string> > &GetOperators() const;
		std::map<std::string, FunObjectPtr> &GetOperatorMap();
		FunObject *GetOperator(const std::string &name);

	protected:
		void _AddGenFun(const std::string &catalogue, FunObject *funObj);
		void _AddCtrl(const std::string &catalogue, FunObject *funObj);
		void _AddParam(const std::string &catalogue, FunObject *funObj);
		void _AddEvent(const std::string &catalogue, FunObject *funObj);
		void _AddOPerator(const std::string &catalogue, FunObject *funObj);

		FunObjectPtr mCurAddFunObj;

		int mParamIndex;

		// Events
		std::map<std::string, std::vector<std::string> > mEvents;
		std::map<std::string, FunObjectPtr> mEventObjects;

		// General Fun
		std::map<std::string, std::vector<std::string> > mGeneralFunctions;
		std::map<std::string, std::string> mGeneralFunctionMap;
		std::map<std::string, FunObjectPtr> mGenFunObjects;
		FunObjectPtr mFunStartObject;

		// Option
		std::map<std::string, std::vector<std::string> >mCtrls;
		std::map<std::string, FunObjectPtr> mCtrlObjects;

		// Param
		std::map<std::string, std::vector<std::string> > mParams;
		std::map<std::string, FunObjectPtr> mParamObjects;

		// Operators
		std::map<std::string, std::vector<std::string> > mOperators;
		std::map<std::string, FunObjectPtr> mOperatorsObjects;
	};

#include "PX2LogicManager.inl"
#define  PX2_LOGICM LogicManager::GetSingleton()

}

#endif

