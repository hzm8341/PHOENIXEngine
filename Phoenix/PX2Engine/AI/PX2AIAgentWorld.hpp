// PX2AIAgentWorld.hpp

#ifndef PX2AIAGENTWORLD_HPP
#define PX2AIAGENTWORLD_HPP

#include "PX2AIAgent.hpp"

namespace PX2
{

	class PhysicsWorld;

	class PX2_ENGINE_ITEM AIAgentWorld
	{
	public:
		AIAgentWorld(int sandboxId, Node *sceneNode);
		~AIAgentWorld();

		enum ProfileTime
		{
			RENDER_TIME,
			SIMULATION_TIME,
			TOTAL_SIMULATION_TIME,
			PROFILE_TIME_COUNT
		};

		Node *GetRootNode();
		const Node *GetRootNode() const;

		PhysicsWorld* GetPhysicsWorld();
		const PhysicsWorld* GetPhysicsWorld() const;

		int GenerateAgentId();
		AIAgent* GetAgent(const unsigned int agentId);
		const AIAgent* GetAgent(const unsigned int agentId) const;
		std::vector<AIAgent*>& GetAgents();
		const std::vector<AIAgent*>& GetAgents() const;

	protected:
		long long profileTimes_[PROFILE_TIME_COUNT];

		Node* sandboxNode_;

		PhysicsWorld* physicsWorld_;
		bool drawPhysicsWorld_;
		std::vector<AIAgent*> agents_;

		int lastObjectId_;
	};

}

#endif