// PX2AIAgentWorld.cpp

#include "PX2AIAgentWorld.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
AIAgentWorld::AIAgentWorld(int sandboxId, Node *sceneNode) :
lastObjectId_(sandboxId),
sandboxNode_(sceneNode),
physicsWorld_(0)
{
	for (size_t index = 0; index < PROFILE_TIME_COUNT; ++index)
	{
		profileTimes_[index] = 0;
	}
}
//----------------------------------------------------------------------------
AIAgentWorld::~AIAgentWorld()
{
	std::vector<AIAgent*>::iterator it;

	for (it = agents_.begin(); it != agents_.end(); ++it)
	{
		delete *it;
	}
	agents_.clear();
}
//----------------------------------------------------------------------------
Node *AIAgentWorld::GetRootNode()
{
	return sandboxNode_;
}
//----------------------------------------------------------------------------
const Node *AIAgentWorld::GetRootNode() const
{
	return sandboxNode_;
}
//----------------------------------------------------------------------------
PhysicsWorld* AIAgentWorld::GetPhysicsWorld()
{
	return physicsWorld_;
}
//----------------------------------------------------------------------------
const PhysicsWorld* AIAgentWorld::GetPhysicsWorld() const
{
	return physicsWorld_;
}
//----------------------------------------------------------------------------
int AIAgentWorld::GenerateAgentId()
{
	return ++lastObjectId_;
}
//----------------------------------------------------------------------------
AIAgent* AIAgentWorld::GetAgent(const unsigned int agentId)
{
	std::vector<AIAgent*>::iterator it;

	for (it = agents_.begin(); it != agents_.end(); ++it)
	{
		if ((*it)->GetID() == agentId)
		{
			return *it;
		}
	}
	return 0;
}
//----------------------------------------------------------------------------
const AIAgent* AIAgentWorld::GetAgent(const unsigned int agentId) const
{
	std::vector<AIAgent*>::const_iterator it;

	for (it = agents_.begin(); it != agents_.end(); ++it)
	{
		if ((*it)->GetID() == agentId)
		{
			return *it;
		}
	}
	return 0;
}
//----------------------------------------------------------------------------
std::vector<AIAgent*>& AIAgentWorld::GetAgents()
{
	return agents_;
}
//----------------------------------------------------------------------------
const std::vector<AIAgent*>& AIAgentWorld::GetAgents() const
{
	return agents_;
}
//----------------------------------------------------------------------------