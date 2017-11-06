// AIAgentWorldUtilities

#include "PX2AIAgentWorldUtilities.hpp"
#include "PX2Node.hpp"
#include "PX2AIAgentObject.hpp"
#include "PX2BtPhysicsUtilities.hpp"
#include "BulletDynamics/Dynamics/btRigidBody.h"
using namespace PX2;

//----------------------------------------------------------------------------
AIAgentObject* AIAgentWorldUtilities::CreateSandboxObject(
	AIAgentWorld* world, const std::string& meshFileName)
{
	return 0;
}
//----------------------------------------------------------------------------
AIAgentObject* AIAgentWorldUtilities::CreateSandboxObject(
	AIAgentWorld* world, Node* node)
{
	return 0;
}
//----------------------------------------------------------------------------
void AIAgentWorldUtilities::UpdateWorldTransform(AIAgentObject* agentObject)
{
	btRigidBody* rigidBody = agentObject->GetRigidBody();
	Node* sceneNode = agentObject->GetSceneNode();

	const btVector3& rigidBodyPosition =
		rigidBody->getWorldTransform().getOrigin();
	APoint pos = PhysicsUtilities::BtVector3ToVector3(rigidBodyPosition);
	sceneNode->LocalTransform.SetTranslate(pos);


	const btQuaternion rigidBodyOrientation =
		rigidBody->getWorldTransform().getRotation();
	HQuaternion quat = PhysicsUtilities::BtQuaterionToQuaternion(rigidBodyOrientation);
	HMatrix rotMat;
	quat.ToRotationMatrix(rotMat);
	sceneNode->LocalTransform.SetRotate(rotMat);
}
//----------------------------------------------------------------------------