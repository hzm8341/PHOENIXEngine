// PX2AIAgentFunctions.cpp

#include "PX2AIAgent.hpp"
#include "PX2BtPhysicsUtilities.hpp"
#include "PX2AIAgentUtilities.hpp"
#include "PX2Node.hpp"
#include "Bullet/BulletDynamics/Dynamics/btRigidBody.h"
#include "Bullet/BulletCollision/CollisionShapes/btCollisionShape.h"
using namespace PX2;

//----------------------------------------------------------------------------
void AIAgent::RemovePath()
{
	hasPath_ = false;
}
//----------------------------------------------------------------------------
void AIAgent::SetForward(const Vector3f& forward)
{
	//Vector3f up = Vector3f::UNIT_Z;

	//const Ogre::Vector3 zAxis = forward.normalisedCopy();
	//const Ogre::Vector3 xAxis = up.crossProduct(zAxis);
	//const Ogre::Vector3 yAxis = zAxis.crossProduct(xAxis);

	//Ogre::Quaternion orientation(xAxis, yAxis, zAxis);

	//// Update both the rigid body and scene node.
	//if (rigidBody_)
	//{
	//	PhysicsUtilities::SetRigidBodyOrientation(
	//		rigidBody_, QuaternionToBtQuaternion(orientation));
	//}

	//if (sceneNode_)
	//{
	//	sceneNode_->setOrientation(orientation);
	//}
}
//----------------------------------------------------------------------------
void AIAgent::SetForward(const HQuaternion& orientation)
{
	//if (rigidBody_)
	//{
	//	PhysicsUtilities::SetRigidBodyOrientation(
	//		rigidBody_, QuaternionToBtQuaternion(orientation));
	//}

	//if (sceneNode_)
	//{
	//	sceneNode_->setOrientation(orientation);
	//}
}
//----------------------------------------------------------------------------
void AIAgent::SetHealth(float health)
{
	health_ = health;
}
//----------------------------------------------------------------------------
void AIAgent::SetHeight(float height)
{
	height_ = std::max(0.0f, height);

	if (rigidBody_)
	{
		AIAgentUtilities::UpdateRigidBodyCapsule(this);
	}
}
//----------------------------------------------------------------------------
void AIAgent::SetMass(float  mass)
{
	if (rigidBody_)
	{
		PhysicsUtilities::SetRigidBodyMass(
			rigidBody_, std::max(0.0f, mass));
	}

	mass_ = mass;
}
//----------------------------------------------------------------------------
void AIAgent::SetMaxForce(float force)
{
	maxForce_ = std::max(0.0f, force);
}
//----------------------------------------------------------------------------
void AIAgent::SetMaxSpeed(float speed)
{
	maxSpeed_ = std::max(0.0f, speed);
}
//----------------------------------------------------------------------------
void AIAgent::SetPath(const AIAgentPath& path)
{
	path_ = path;
	hasPath_ = true;
}
//----------------------------------------------------------------------------
void AIAgent::SetPosition(const Vector3f& position)
{
	if (rigidBody_)
	{
		PhysicsUtilities::SetRigidBodyPosition(
			rigidBody_, PhysicsUtilities::Vector3ToBtVector3(position));
	}

	if (sceneNode_)
	{
		sceneNode_->LocalTransform.SetTranslate(position);
	}
}
//----------------------------------------------------------------------------
void AIAgent::SetRadius(float radius)
{
	if (sceneNode_)
	{
		radius_ = std::max(0.0f, radius);
	}

	if (rigidBody_)
	{
		AIAgentUtilities::UpdateRigidBodyCapsule(this);
	}
}
//----------------------------------------------------------------------------
void AIAgent::SetRigidBody(btRigidBody* rigidBody)
{
	rigidBody_ = rigidBody;
}
//----------------------------------------------------------------------------
void AIAgent::SetAgentWorld(AIAgentWorld *agentWorld)
{
	mAgentWorld = agentWorld;
}
//----------------------------------------------------------------------------
void AIAgent::SetSpeed(float speed)
{
	speed_ = speed;
}
//----------------------------------------------------------------------------
void AIAgent::SetTarget(const Vector3f& target)
{
	target_ = target;
}
//----------------------------------------------------------------------------
void AIAgent::SetTargetRadius(float radius)
{
	targetRadius_ = std::max(0.0f, radius);
}
//----------------------------------------------------------------------------
void AIAgent::SetTeam(const std::string& team)
{
	team_ = team;
}
//----------------------------------------------------------------------------
void AIAgent::SetVelocity(const Vector3f& velocity)
{
	if (rigidBody_)
	{
		PhysicsUtilities::SetRigidBodyVelocity(
			rigidBody_, PhysicsUtilities::Vector3ToBtVector3(velocity));
	}

	SetSpeed(Vector3f(velocity.X(), 0, velocity.Z()).Length());
}
//----------------------------------------------------------------------------
Vector3f AIAgent::GetForward() const
{
	//if (rigidBody_)
	//{
	//	const btQuaternion quaterion = rigidBody_->getOrientation();
	//	return HQuaternion(
	//		quaterion.w(), quaterion.x(), quaterion.y(), quaterion.z()).zAxis();
	//}
	//else if (sceneNode_)
	//{
	//	return sceneNode_->getOrientation().zAxis();
	//}

	return Vector3f::UNIT_Z;
}
//----------------------------------------------------------------------------
Vector3f AIAgent::GetPosition() const
{
	if (rigidBody_)
	{
		return PhysicsUtilities::BtVector3ToVector3(
			rigidBody_->getCenterOfMassPosition());
	}
	else if (sceneNode_)
	{
		return sceneNode_->WorldTransform.GetTranslate();
	}

	return Vector3f::ZERO;
}
//----------------------------------------------------------------------------
HQuaternion AIAgent::GetOrientation() const
{
	if (rigidBody_)
	{
		return PhysicsUtilities::BtQuaterionToQuaternion(rigidBody_->getOrientation());
	}
	else if (sceneNode_)
	{
		//return sceneNode_->_getDerivedOrientation();
	}

	return HQuaternion::ZERO;
}
//----------------------------------------------------------------------------
float AIAgent::GetMass() const
{
	if (rigidBody_)
	{
		return PhysicsUtilities::GetRigidBodyMass(rigidBody_);
	}
	else
	{
		return mass_;
	}
}
//----------------------------------------------------------------------------