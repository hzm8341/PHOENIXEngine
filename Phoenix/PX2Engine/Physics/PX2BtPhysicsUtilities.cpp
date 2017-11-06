// PX2BtPhysicsUtilities.cpp

#include "PX2BtPhysicsUtilities.hpp"
#include "Bullet/BulletCollision/CollisionShapes/btCapsuleShape.h"
#include "Bullet/LinearMath/btMotionState.h"
#include "Bullet/LinearMath/btDefaultMotionState.h"
#include "Bullet/BulletDynamics/Dynamics/btRigidBody.h"
#include "Bullet/BulletCollision/CollisionShapes/btCollisionShape.h"
using namespace PX2;

//----------------------------------------------------------------------------
void PhysicsUtilities::ApplyForce(
	btRigidBody* rigidBody, const btVector3& force)
{
	rigidBody->applyCentralForce(force);
	rigidBody->activate(true);
}
//----------------------------------------------------------------------------
Vector3f PhysicsUtilities::BtVector3ToVector3(const btVector3& vector)
{
	return Vector3f(
		vector.m_floats[0], vector.m_floats[1], vector.m_floats[2]);
}
//----------------------------------------------------------------------------
btVector3 PhysicsUtilities::Vector3ToBtVector3(const Vector3f& vector)
{
	return btVector3(
		vector.X(), vector.Y(), vector.Z());
}
//----------------------------------------------------------------------------
HQuaternion PhysicsUtilities::BtQuaterionToQuaternion(const btQuaternion& quaternion)
{
	return HQuaternion(
		quaternion.w(), quaternion.x(), quaternion.y(), quaternion.z());
}
//----------------------------------------------------------------------------
btRigidBody* PhysicsUtilities::CreateCapsule(
	const btScalar height, const btScalar radius)
{
	// Since the height of
	btCapsuleShape* const capsuleShape = new btCapsuleShape(
		radius, height - radius * 2);

	btDefaultMotionState* const capsuleMotionState = new btDefaultMotionState();

	btVector3 localInertia(0, 0, 0);
	capsuleShape->calculateLocalInertia(1.0f, localInertia);

	btRigidBody::btRigidBodyConstructionInfo
		capsuleRigidBodyCI(
		1.0f, capsuleMotionState, capsuleShape, localInertia);

	// Prevent rolling forever.
	capsuleRigidBodyCI.m_rollingFriction = 0.2f;

	btRigidBody* const rigidBody = new btRigidBody(capsuleRigidBodyCI);

	rigidBody->setCcdMotionThreshold(0.5f);
	rigidBody->setCcdSweptSphereRadius(radius);

	return rigidBody;
}
//----------------------------------------------------------------------------
void PhysicsUtilities::DeleteRigidBody(btRigidBody* rigidBody)
{
	delete rigidBody->getMotionState();
	delete rigidBody->getCollisionShape();
	delete rigidBody;
}
//----------------------------------------------------------------------------
btScalar PhysicsUtilities::GetRigidBodyRadius(const btRigidBody* rigidBody)
{
	btVector3 aabbMin;
	btVector3 aabbMax;
	rigidBody->getAabb(aabbMin, aabbMax);

	return aabbMax.distance(aabbMin) / 2.0f;
}
//----------------------------------------------------------------------------
btScalar PhysicsUtilities::GetRigidBodyMass(const btRigidBody* rigidBody)
{
	btScalar inverseMass = rigidBody->getInvMass();

	if (inverseMass == 0)
		return 0;

	return 1.0f / inverseMass;
}
//----------------------------------------------------------------------------
void PhysicsUtilities::SetRigidBodyMass(
	btRigidBody* rigidBody, const btScalar mass)
{
	btVector3 localInertia(0, 0, 0);
	rigidBody->getCollisionShape()->calculateLocalInertia(mass, localInertia);
	rigidBody->setMassProps(mass, localInertia);
	rigidBody->updateInertiaTensor();
	rigidBody->activate(true);
}
//----------------------------------------------------------------------------
void PhysicsUtilities::SetRigidBodyOrientation(
	btRigidBody* rigidBody, const btQuaternion& orientation)
{
	btTransform transform = rigidBody->getWorldTransform();
	transform.setRotation(orientation);

	rigidBody->setWorldTransform(transform);
	rigidBody->activate(true);
}
//----------------------------------------------------------------------------
void PhysicsUtilities::SetRigidBodyPosition(
	btRigidBody* rigidBody, const btVector3& position)
{
	btTransform transform = rigidBody->getWorldTransform();
	transform.setOrigin(position);

	rigidBody->setWorldTransform(transform);
	rigidBody->activate(true);
}
//----------------------------------------------------------------------------
void PhysicsUtilities::SetRigidBodyVelocity(
	btRigidBody* rigidBody, const btVector3& velocity)
{
	rigidBody->setLinearVelocity(velocity);
	rigidBody->activate(true);
}
//----------------------------------------------------------------------------