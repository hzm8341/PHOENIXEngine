// PX2AIAgentUtilities.hpp

#ifndef PX2AIAGENTUTILITIES_HPP
#define PX2AIAGENTUTILITIES_HPP

#include "PX2Vector3.hpp"

namespace PX2
{

	class AIAgent;

	class AIAgentUtilities
	{
	public:
		static void UpdateRigidBodyCapsule(AIAgent* agent);
		static void CreateRigidBodyCapsule(AIAgent* agent);
	};

}

#endif