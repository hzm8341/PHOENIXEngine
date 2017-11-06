// PX2AIAgent.cpp

#include "PX2AIAgent.hpp"
#include "PX2BtPhysicsUtilities.hpp"
#include "Bullet/BulletDynamics/Dynamics/btRigidBody.h"
#include "Bullet/BulletCollision/CollisionShapes/btCollisionShape.h"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Controller, AIAgent);
PX2_IMPLEMENT_STREAM(AIAgent);
PX2_IMPLEMENT_FACTORY(AIAgent);
PX2_IMPLEMENT_DEFAULT_NAMES(Controller, AIAgent);
//----------------------------------------------------------------------------
const float AIAgent::DEFAULT_AGENT_HEALTH = 100.0f;
const float AIAgent::DEFAULT_AGENT_HEIGHT = 1.6f;  // meters (5.2 feet)
const float AIAgent::DEFAULT_AGENT_MASS = 90.7f;  // kilograms (200 lbs)
const float AIAgent::DEFAULT_AGENT_MAX_FORCE = 1000.0f;  // newtons (kg*m/s^2)
const float AIAgent::DEFAULT_AGENT_MAX_SPEED = 7.0f;  // m/s (23.0 ft/s)
const float AIAgent::DEFAULT_AGENT_RADIUS = 0.3f;  // meters (1.97 feet)
const float AIAgent::DEFAULT_AGENT_SPEED = 0.0f;  // m/s (0 ft/s)
const float AIAgent::DEFAULT_AGENT_TARGET_RADIUS = 0.5f;  // meters (1.64 feet)
const float AIAgent::DEFAULT_AGENT_WALKABLE_CLIMB = DEFAULT_AGENT_RADIUS / 2.0f;
const float AIAgent::DEFAULT_AGENT_WALKABLE_SLOPE = 45.0f;
const std::string AIAgent::DEFAULT_AGENT_TEAM = "team1";
//----------------------------------------------------------------------------
AIAgent::AIAgent(int agentId, Node *sceneNode, btRigidBody* rigidBody) :
mAgentWorld(0),
health_(DEFAULT_AGENT_HEALTH),
height_(DEFAULT_AGENT_HEIGHT),
hasPath_(false),
sceneNode_(sceneNode),
maxForce_(DEFAULT_AGENT_MAX_FORCE),
maxSpeed_(DEFAULT_AGENT_MAX_SPEED),
mass_(DEFAULT_AGENT_MASS),
radius_(DEFAULT_AGENT_RADIUS),
speed_(DEFAULT_AGENT_SPEED),
rigidBody_(rigidBody),
targetRadius_(DEFAULT_AGENT_TARGET_RADIUS),
team_(DEFAULT_AGENT_TEAM),
target_(Vector3f::ZERO)
{
	SetID(agentId);

	if (rigidBody_)
	{
		PhysicsUtilities::SetRigidBodyMass(rigidBody_, DEFAULT_AGENT_MASS);
		rigidBody_->setUserPointer(this);
	}

	SetForward(Vector3f::UNIT_Z);
}
//----------------------------------------------------------------------------
AIAgent::~AIAgent()
{
	if (rigidBody_)
	{
		PhysicsUtilities::DeleteRigidBody(rigidBody_);
	}
	rigidBody_ = 0;
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::side(void) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::setSide(OpenSteer::Vec3 s)
{
	(void)s;
	// not implemented
	assert(false);

	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::up(void) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::setUp(OpenSteer::Vec3 u)
{
	(void)u;
	// not implemented
	assert(false);

	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::forward(void) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::setForward(OpenSteer::Vec3 f)
{
	(void)f;
	// not implemented
	assert(false);

	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::position(void) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::setPosition(OpenSteer::Vec3 p)
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
bool AIAgent::rightHanded(void) const
{
	return true;
}
//----------------------------------------------------------------------------
void AIAgent::resetLocalSpace(void)
{
	// not imp
	assert(false);
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::localizeDirection(
	const OpenSteer::Vec3& globalDirection) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::localizePosition(
	const OpenSteer::Vec3& globalPosition) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::globalizePosition(
	const OpenSteer::Vec3& localPosition) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::globalizeDirection(
	const OpenSteer::Vec3& localDirection) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
void AIAgent::setUnitSideFromForwardAndUp(void)
{

}
//----------------------------------------------------------------------------
void AIAgent::regenerateOrthonormalBasisUF(
	const OpenSteer::Vec3& newUnitForward)
{

}
//----------------------------------------------------------------------------
void AIAgent::regenerateOrthonormalBasis(
	const OpenSteer::Vec3& newForward)
{

}
//----------------------------------------------------------------------------
void AIAgent::regenerateOrthonormalBasis(
	const OpenSteer::Vec3& newForward, const OpenSteer::Vec3& newUp)
{

}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::localRotateForwardToSide(
	const OpenSteer::Vec3& v) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::globalRotateForwardToSide(
	const OpenSteer::Vec3& globalForward) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
float AIAgent::mass(void) const
{
	return 0.0f;
}
//----------------------------------------------------------------------------
float AIAgent::setMass(float)
{
	return 0.0f;
}
//----------------------------------------------------------------------------
float AIAgent::radius(void) const
{
	return 0.0f;
}
//----------------------------------------------------------------------------
float AIAgent::setRadius(float)
{
	return 0.0f;
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::velocity(void) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
float AIAgent::speed(void) const
{
	return 0.0f;
}
//----------------------------------------------------------------------------
float AIAgent::setSpeed(float)
{
	return 0.0f;
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::predictFuturePosition(const float predictionTime) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
float AIAgent::maxForce(void) const
{
	return 0.0f;
}
//----------------------------------------------------------------------------
float AIAgent::setMaxForce(float)
{
	return 0.0f;
}
//----------------------------------------------------------------------------
float AIAgent::maxSpeed(void) const
{
	return 0.0f;
}
//----------------------------------------------------------------------------
float AIAgent::setMaxSpeed(float)
{
	return 0.0f;
}
//----------------------------------------------------------------------------
void AIAgent::update(const float currentTime, const float elapsedTime)
{

}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ³Ö¾Ã»¯
//----------------------------------------------------------------------------
AIAgent::AIAgent(LoadConstructor value) :
Controller(value)
{
}
//----------------------------------------------------------------------------
void AIAgent::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Controller::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(AIAgent, source);
}
//----------------------------------------------------------------------------
void AIAgent::Link(InStream& source)
{
	Controller::Link(source);
}
//----------------------------------------------------------------------------
void AIAgent::PostLink()
{
	Controller::PostLink();
}
//----------------------------------------------------------------------------
bool AIAgent::Register(OutStream& target) const
{
	if (Controller::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void AIAgent::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Controller::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(AIAgent, target);
}
//----------------------------------------------------------------------------
int AIAgent::GetStreamingSize(Stream &stream) const
{
	int size = Controller::GetStreamingSize(stream);

	return size;
}
//----------------------------------------------------------------------------
