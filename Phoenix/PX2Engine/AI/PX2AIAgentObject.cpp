// PX2AIAgentObject.cpp

#include "PX2AIAgentObject.hpp"
#include "PX2BtPhysicsUtilities.hpp"
#include "PX2AIAgentWorldUtilities.hpp"
#include "BulletDynamics/Dynamics/btRigidBody.h""
using namespace PX2;

//----------------------------------------------------------------------------
AIAgentObject::AIAgentObject(int objectID, Node *sceneNode, 
	btRigidBody* rigidBody):
	sceneNode_(sceneNode),
	rigidBody_(rigidBody)
{
	SetID(objectID);
}
//----------------------------------------------------------------------------
AIAgentObject::~AIAgentObject()
{
	PhysicsUtilities::DeleteRigidBody(rigidBody_);
}
//----------------------------------------------------------------------------
void AIAgentObject::Initialize()
{
}
//----------------------------------------------------------------------------
void AIAgentObject::Cleanup()
{
}
//----------------------------------------------------------------------------
void AIAgentObject::Update(float elapsedSeconds)
{
	PX2_UNUSED(elapsedSeconds);

	AIAgentWorldUtilities::UpdateWorldTransform(this);
}
//----------------------------------------------------------------------------
float AIAgentObject::GetMass() const
{
	return PhysicsUtilities::GetRigidBodyMass(rigidBody_);
}
//----------------------------------------------------------------------------
HQuaternion AIAgentObject::GetOrientation() const
{
	const btQuaternion& rotation =
		rigidBody_->getCenterOfMassTransform().getRotation();

	return HQuaternion(
		rotation.w(), rotation.x(), rotation.y(), rotation.z());
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgentObject::getPosition() const
{
	const btVector3& position = rigidBody_->getCenterOfMassPosition();

	return OpenSteer::Vec3(
		position.m_floats[0], position.m_floats[1], position.m_floats[2]);
}
//----------------------------------------------------------------------------
Vector3f AIAgentObject::GetPosition() const
{
	const btVector3& position = rigidBody_->getCenterOfMassPosition();

	return Vector3f(
		position.m_floats[0], position.m_floats[1], position.m_floats[2]);
}
//----------------------------------------------------------------------------
float AIAgentObject::GetRadius() const
{
	return PhysicsUtilities::GetRigidBodyRadius(rigidBody_);
}
//----------------------------------------------------------------------------
float AIAgentObject::getRadius() const
{
	return GetRadius();
}
//----------------------------------------------------------------------------
btRigidBody* AIAgentObject::GetRigidBody()
{
	return rigidBody_;
}
//----------------------------------------------------------------------------
const btRigidBody* AIAgentObject::GetRigidBody() const
{
	return rigidBody_;
}
//----------------------------------------------------------------------------
Node* AIAgentObject::GetSceneNode()
{
	return sceneNode_;
}
//----------------------------------------------------------------------------
const Node* AIAgentObject::GetSceneNode() const
{
	return sceneNode_;
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgentObject::steerToAvoid(
	const OpenSteer::AbstractVehicle& v,
	const float minTimeToCollision) const
{
	// minimum distance to obstacle before avoidance is required
	const float minDistanceToCollision = minTimeToCollision * v.speed();
	const float minDistanceToCenter = minDistanceToCollision + getRadius();

	// contact distance: sum of radii of obstacle and vehicle
	const float totalRadius = getRadius() + v.radius();

	// obstacle center relative to vehicle position
	const OpenSteer::Vec3 localOffset = getPosition() - v.position();

	// distance along vehicle's forward axis to obstacle's center
	const float forwardComponent = localOffset.dot(v.forward());
	const OpenSteer::Vec3 forwardOffset = forwardComponent * v.forward();

	// offset from forward axis to obstacle's center
	const OpenSteer::Vec3 offForwardOffset = localOffset - forwardOffset;

	// test to see if sphere overlaps with obstacle-free corridor
	const bool inCylinder = offForwardOffset.length() < totalRadius;
	const bool nearby = forwardComponent < minDistanceToCenter;
	const bool inFront = forwardComponent > 0;

	// if all three conditions are met, steer away from sphere center
	if (inCylinder && nearby && inFront)
	{
		return offForwardOffset * -1;
	}
	else
	{
		return OpenSteer::Vec3::zero;
	}
}
//----------------------------------------------------------------------------