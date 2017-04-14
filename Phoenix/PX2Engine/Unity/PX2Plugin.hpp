// PX2Plugin.hpp

#ifndef PX2PLUGIN_HPP
#define PX2PLUGIN_HPP

#include "PX2UnityPre.hpp"

namespace PX2
{
	typedef bool(*PluginInitlizeFun)();
	typedef bool(*PluginTernamateFun)();

#define PX2_DECLARE_PLUGIN(classname) \
	public:\
		static bool RegisterInitTerm (); \
		static bool UnRegisterInitTerm (); \
		static bool PluginInitialize (); \
		static bool PluginTerminate (); \
	private: \
		static bool msIsPluginInitTermRegistered

#define PX2_REGISTER_PLUGIN(classname) \
	static bool gsPluginInitializeRegistered_##classname = \
	classname::RegisterInitTerm ();

#define PX2_IMPLEMENT_PLUGIN(classname) \
	bool classname::msIsPluginInitTermRegistered = false; \
	\
	bool classname::RegisterInitTerm () \
	{ \
		if (!msIsPluginInitTermRegistered) \
		{ \
			Plugin::msPluginInitlizeFuns.push_back(&classname::PluginInitialize); \
			Plugin::msPluginTernamateFuns.push_back(&classname::PluginTerminate); \
			msIsPluginInitTermRegistered = true; \
		} \
		return msIsPluginInitTermRegistered; \
	} \
	bool classname::UnRegisterInitTerm () \
	{ \
		if (msIsPluginInitTermRegistered) \
		{ \
			Plugin::RemoveInit(&classname::PluginInitialize); \
			Plugin::RemoveTerm(&classname::PluginTerminate); \
			return true;\
		} \
		return false;\
	}

	class PX2_ENGINE_ITEM Plugin
	{
	public:
		Plugin();
		virtual ~Plugin();

		std::string GetName();

		virtual void OnInstall();
		virtual void OnUninstall();
		virtual void OnUpdate();

	protected:
		std::string mName;

	public:
		static void ExecuteInit();
		static void ExecuteTerm();

	protected:
		static void RemoveInit(PluginInitlizeFun fun);
		static void RemoveTerm(PluginTernamateFun fun);

		static std::vector<PluginInitlizeFun> msPluginInitlizeFuns;
		static std::vector<PluginTernamateFun> msPluginTernamateFuns;
	};

}

#endif