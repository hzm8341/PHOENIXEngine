// PX2AIAgentGroup.hpp

#ifndef PX2AIAGENTGROUP_HPP
#define PX2AIAGENTGROUP_HPP

#include "PX2CorePre.hpp"
#include "OpenSteer/AbstractVehicle.h"
#include "PX2AIAgentBase.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM AIAgentGroup : public OpenSteer::AVGroup
	{
		friend class AIAgentBase;

	public:
		AIAgentGroup();
		AIAgentGroup(const AIAgentGroup& group);
		virtual ~AIAgentGroup();

		AIAgentGroup& operator=(const AIAgentGroup& group);

		void AddAgent(const AIAgentBase* agent);

		bool ContainsAgent(const AIAgentBase* agent) const;
		bool RemoveAgent(const AIAgentBase* agent);
		void RemoveAgents();
		size_t Size() const;
	};

}

#endif