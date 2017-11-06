// PX2BtPhysicsWorld.hpp

#ifndef PX2BTPHYSICSWORLD_HPP
#define PX2BTPHYSICSWORLD_HPP

#include "PX2CorePre.hpp"

class btRigidBody;
class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;

namespace PX2
{

	class PhysicsDebugDraw;

	class PX2_ENGINE_ITEM PhysicsWorld
	{
	public:
		PhysicsWorld();
		~PhysicsWorld();

		btDiscreteDynamicsWorld* GetDynamicsWorld();

		void Initialize();

		void AddRigidBody(btRigidBody* rigidBody);
		void RemoveRigidBody(btRigidBody* rigidBody);
		void Cleanup();

		void StepWorld();
		void DrawDebugWorld();

	private:
		btBroadphaseInterface* broadphase_;
		btDefaultCollisionConfiguration* collisionConfiguration_;
		btCollisionDispatcher* dispatcher_;
		btSequentialImpulseConstraintSolver* solver_;
		btDiscreteDynamicsWorld* dynamicsWorld_;
		PhysicsDebugDraw* debugDraw_;
	};

}

#endif