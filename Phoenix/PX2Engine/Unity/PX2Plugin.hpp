// PX2Plugin.hpp

#ifndef PX2PLUGIN_HPP
#define PX2PLUGIN_HPP

#include "PX2UnityPre.hpp"

namespace PX2
{

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
	};

}

#endif