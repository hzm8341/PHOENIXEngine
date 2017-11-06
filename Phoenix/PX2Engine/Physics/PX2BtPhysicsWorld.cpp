// PX2BtPhysicsWorld.cpp

#include "PX2BtPhysicsWorld.hpp"
#include "PX2BtPhysicsDebugDraw.hpp"
#include "Bullet/BulletDynamics/Dynamics/btRigidBody.h"
#include "Bullet/BulletCollision/CollisionShapes/btCollisionShape.h"
#include "Bullet/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"
#include "Bullet/BulletCollision/BroadphaseCollision/btDbvtBroadphase.h"
#include "Bullet/BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "Bullet/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "Bullet/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"
using namespace PX2;

//----------------------------------------------------------------------------
PhysicsWorld::PhysicsWorld(): 
dynamicsWorld_(0),
solver_(0),
dispatcher_(0),
collisionConfiguration_(0),
broadphase_(0),
debugDraw_(0)
{
}
//----------------------------------------------------------------------------
PhysicsWorld::~PhysicsWorld()
{
	Cleanup();
}
//----------------------------------------------------------------------------
btDiscreteDynamicsWorld* PhysicsWorld::GetDynamicsWorld()
{
	return dynamicsWorld_;
}
//----------------------------------------------------------------------------
void PhysicsWorld::Initialize()
{
	static const float gravity = -9.8f;

	broadphase_ = new btDbvtBroadphase();

	collisionConfiguration_ = new btDefaultCollisionConfiguration();

	dispatcher_ = new btCollisionDispatcher(collisionConfiguration_);

	solver_ = new btSequentialImpulseConstraintSolver();

	dynamicsWorld_ = new btDiscreteDynamicsWorld(
		dispatcher_, broadphase_, solver_, collisionConfiguration_);

	dynamicsWorld_->setGravity(btVector3(0, gravity, 0));

	debugDraw_ = new PhysicsDebugDraw();
	dynamicsWorld_->setDebugDrawer(debugDraw_);
	debugDraw_->setDebugMode(btIDebugDraw::DBG_DrawWireframe |
		btIDebugDraw::DBG_DrawAabb);
}
//----------------------------------------------------------------------------
void PhysicsWorld::AddRigidBody(btRigidBody* rigidBody)
{
	dynamicsWorld_->addRigidBody(rigidBody);
}
//----------------------------------------------------------------------------
void PhysicsWorld::RemoveRigidBody(btRigidBody* const rigidBody)
{
	dynamicsWorld_->removeRigidBody(rigidBody);
}
//----------------------------------------------------------------------------
void PhysicsWorld::Cleanup()
{
	if (dynamicsWorld_)
	{
		delete dynamicsWorld_;
		dynamicsWorld_ = 0;
	}

	if (solver_)
	{
		delete solver_;
		solver_ = 0;
	}

	if (dispatcher_)
	{
		delete dispatcher_;
		dispatcher_ = 0;
	}

	if (collisionConfiguration_)
	{
		delete collisionConfiguration_;
		collisionConfiguration_ = 0;
	}

	if (broadphase_)
	{
		delete broadphase_;
		broadphase_ = 0;
	}
}
//----------------------------------------------------------------------------
void PhysicsWorld::StepWorld()
{
	dynamicsWorld_->stepSimulation(1.0f / 30.0f, 1, 1.0f / 30.0f);
}
//----------------------------------------------------------------------------
void PhysicsWorld::DrawDebugWorld()
{
	dynamicsWorld_->debugDrawWorld();
}
//----------------------------------------------------------------------------