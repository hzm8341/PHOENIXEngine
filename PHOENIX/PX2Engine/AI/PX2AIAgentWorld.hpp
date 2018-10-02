// PX2AIAgentWorld.hpp

#ifndef PX2AIAGENTWORLD_HPP
#define PX2AIAGENTWORLD_HPP

#include "PX2AxisAlignedBox3.hpp"
#include "PX2Controller.hpp"

namespace PX2
{

	class AIAgent;
	class AIAgentObject;
	class PhysicsWorld;
	class NavigationMesh;
	class Node;

	class PX2_ENGINE_ITEM AIAgentWorld : public Controller
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(AIAgentWorld);

	public:
		AIAgentWorld();
		virtual ~AIAgentWorld();

		void Clear();

		const AxisAlignedBox3f& GetWorldAABB() const;

		Node *GetRootNode();
		const Node *GetRootNode() const;

		PhysicsWorld* GetPhysicsWorld();
		const PhysicsWorld* GetPhysicsWorld() const;

		bool AddAgent(AIAgent * agent);
		bool IsHasAgent(AIAgent *agent);
		bool RemoveAgent(AIAgent *agent);
		void RemoveAllAgents();
		AIAgent* GetAgent(int agentID);
		const AIAgent* GetAgent(int agentID) const;
		std::vector<AIAgent*>& GetAgents();
		const std::vector<AIAgent*>& GetAgents() const;

		void AddAgentObject(AIAgentObject* agentObject);
		void RemoveAgentObject(AIAgentObject* agentObject);
		void RemoveAllAgentObjects();
		std::vector<AIAgentObject*>& GetObjects();
		const std::vector<AIAgentObject*>& GetObjects() const;

		void AddNavigationMesh(const std::string& name, NavigationMesh *navMesh);

	public_internal:
		void SetNode(Node *sceneNode);

	protected:
		virtual void _Update(double applicationTime, double elapsedTime);

		AxisAlignedBox3f mWorldAABB;
		Node* mNode;

		PhysicsWorld* mPhysicsWorld;
		bool mIsDrawPhysicsWorld;
		std::vector<AIAgent*> mAgents;

		std::vector<AIAgentObject*> mObjects;
		std::map<std::string, NavigationMesh*> mNavMeshes;
	};

	PX2_REGISTER_STREAM(AIAgentWorld);
	typedef Pointer0<AIAgentWorld> AIAgentWorldPtr;

}

#endif