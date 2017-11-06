// PX2AIAgentGroup.hpp

#ifndef PX2AIAGENTGROUP_HPP
#define PX2AIAGENTGROUP_HPP

#include "PX2CorePre.hpp"
#include "OpenSteer/AbstractVehicle.h"

namespace PX2
{

	class PX2_ENGINE_ITEM AIAgentGroup : private OpenSteer::AVGroup
	{
		friend class AIAgent;

	public:
		AIAgentGroup();
		AIAgentGroup(const AIAgentGroup& group);
		virtual ~AIAgentGroup();

		AIAgentGroup& operator=(const AIAgentGroup& group);

		void AddAgent(const AIAgent* agent);

		bool ContainsAgent(const AIAgent* agent) const;
		bool RemoveAgent(const AIAgent* agent);
		void RemoveAgents();
		size_t Size() const;
	};

}

#endif