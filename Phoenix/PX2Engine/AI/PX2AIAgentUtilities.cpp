// PX2AIAgentUtilities.cpp

#include "PX2AIAgentUtilities.hpp"
#include "PX2AIAgent.hpp"
#include "PX2AIAgentWorld.hpp"
#include "PX2BtPhysicsWorld.hpp"
#include "Bullet/BulletDynamics/Dynamics/btRigidBody.h"
using namespace PX2;

//----------------------------------------------------------------------------
void AIAgentUtilities::UpdateRigidBodyCapsule(AIAgent* agent)
{
	agent->GetAgentWorld()->GetPhysicsWorld()->RemoveRigidBody(
		agent->GetRigidBody());

	PhysicsUtilities::DeleteRigidBody(agent->GetRigidBody());

	agent->SetRigidBody(0);

	CreateRigidBodyCapsule(agent);
}
//----------------------------------------------------------------------------
void AIAgentUtilities::CreateRigidBodyCapsule(AIAgent* agent)
{
	assert(!agent->GetRigidBody());

	btRigidBody* rigidBody =
		PhysicsUtilities::CreateCapsule(agent->GetHeight(), agent->GetRadius());

	rigidBody->setAngularFactor(btVector3(0, 0.0f, 0));

	const Vector3f position = agent->GetPosition();
	const HQuaternion rot = agent->GetOrientation();

	PhysicsUtilities::SetRigidBodyMass(rigidBody, btScalar(agent->GetMass()));
	PhysicsUtilities::SetRigidBodyPosition(
		rigidBody, btVector3(position.X(), position.Y(), position.Z()));
	PhysicsUtilities::SetRigidBodyOrientation(
		rigidBody, btQuaternion(rot.X(), rot.Y(), rot.Z(), rot.W()));

	agent->SetRigidBody(rigidBody);

	agent->GetAgentWorld()->GetPhysicsWorld()->AddRigidBody(rigidBody);
}
//----------------------------------------------------------------------------