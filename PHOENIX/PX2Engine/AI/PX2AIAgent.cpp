// PX2AIAgent.cpp

#include "PX2AIAgent.hpp"
#include "PX2BtPhysicsUtilities.hpp"
#include "PX2AIAgentUtilities.hpp"
#include "PX2Node.hpp"
#include "PX2AIAgentObject.hpp"
#include "PX2AIAgentGroup.hpp"
#include "PX2AIAgentPath.hpp"
#include "PX2AIAgentWorld.hpp"
#include "PX2BtPhysicsWorld.hpp"
#include "PX2Math.hpp"
#include "Bullet/BulletDynamics/Dynamics/btRigidBody.h"
#include "Bullet/BulletCollision/CollisionShapes/btCollisionShape.h"
#include "Bullet/BulletDynamics/Dynamics/btRigidBody.h"
#include "Bullet/BulletCollision/CollisionShapes/btCollisionShape.h"
#include "PX2NavMoveManager.hpp"
#include "PX2Robot.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
static OpenSteer::Vec3 _APointToVec3(const APoint& point)
{
	return OpenSteer::Vec3(
		static_cast<float>(point.X()),
		static_cast<float>(point.Y()),
		static_cast<float>(point.Z()));
}
OpenSteer::Vec3 _AVectorToVec3(const AVector& vector)
{
	return OpenSteer::Vec3(
		static_cast<float>(vector.X()),
		static_cast<float>(vector.Y()),
		static_cast<float>(vector.Z()));
}
//----------------------------------------------------------------------------
static APoint _Vec3ToAPoint(const  OpenSteer::Vec3 & point)
{
	return APoint(point.x, point.y, point.z);
}
//----------------------------------------------------------------------------
AVector _Vec3ToAVector(const OpenSteer::Vec3& vector)
{
	return AVector(vector.x, vector.y, vector.z);
}
//----------------------------------------------------------------------------
PX2_IMPLEMENT_RTTI(PX2, AIAgentBase, AIAgent);
PX2_IMPLEMENT_STREAM(AIAgent);
PX2_IMPLEMENT_FACTORY(AIAgent);
PX2_IMPLEMENT_DEFAULT_NAMES(AIAgentBase, AIAgent);
//----------------------------------------------------------------------------
const float AIAgent::DEFAULT_AGENT_HEALTH = 100.0f;
const float AIAgent::DEFAULT_AGENT_HEIGHT = 1.6f;  // meters (5.2 feet)
const float AIAgent::DEFAULT_AGENT_MAX_FORCE = 1000.0f;  // newtons (kg*_/s^2)
const float AIAgent::DEFAULT_AGENT_MAX_SPEED = 7.0f;  // m/s (23.0 ft/s)
const float AIAgent::DEFAULT_AGENT_SPEED = 0.0f;  // m/s (0 ft/s)
const float AIAgent::DEFAULT_AGENT_TARGET_RADIUS = 0.5f;  // meters (1.64 feet)
const float AIAgent::DEFAULT_AGENT_WALKABLE_CLIMB = DEFAULT_AGENT_RADIUS / 2.0f;
const float AIAgent::DEFAULT_AGENT_WALKABLE_SLOPE = 45.0f;
const std::string AIAgent::DEFAULT_AGENT_TEAM = "team1";
//----------------------------------------------------------------------------
AIAgent::AIAgent():
AIAgentBase(0, AT_AGENT),
mHealth(DEFAULT_AGENT_HEALTH),
mHeight(DEFAULT_AGENT_HEIGHT),
mIsHasPath(false),
mMaxForce(DEFAULT_AGENT_MAX_FORCE),
mMaxSpeed(DEFAULT_AGENT_MAX_SPEED),
mPhysicsRaduis(DEFAULT_AGENT_RADIUS),
mSpeed(DEFAULT_AGENT_SPEED),
mTargetRadius(DEFAULT_AGENT_TARGET_RADIUS),
mTeam(DEFAULT_AGENT_TEAM),
mTarget(Vector3f::ZERO)
{
	SetName("AIAgent");

	if (!IsRegistedToScriptSystem())
		RegistToScriptSystem();

	SetForward(Vector3f::UNIT_Y);

	mIsEnableForwarding = true;
	mForwarding = AVector::UNIT_Y;
	mSmoother = new0 Smoother<AVector>(16, AVector::UNIT_Y);
}
//----------------------------------------------------------------------------
AIAgent::AIAgent(Node *node) :
AIAgentBase(node),
mHealth(DEFAULT_AGENT_HEALTH),
mHeight(DEFAULT_AGENT_HEIGHT),
mIsHasPath(false),
mMaxForce(DEFAULT_AGENT_MAX_FORCE),
mMaxSpeed(DEFAULT_AGENT_MAX_SPEED),
mSpeed(DEFAULT_AGENT_SPEED),
mTargetRadius(DEFAULT_AGENT_TARGET_RADIUS),
mTeam(DEFAULT_AGENT_TEAM),
mTarget(Vector3f::ZERO)
{
	SetName("AIAgent");

	if (!IsRegistedToScriptSystem())
		RegistToScriptSystem();

	SetForward(Vector3f::UNIT_Y);

	mIsEnableForwarding = true;
	mForwarding = AVector::UNIT_Y;
	mSmoother = new0 Smoother<AVector>(16, AVector::UNIT_Y);
}
//----------------------------------------------------------------------------
AIAgent::~AIAgent()
{
	if (mSmoother)
	{
		delete0(mSmoother);
	}
}
//----------------------------------------------------------------------------
void AIAgent::InitializeCapsule()
{
	AIAgentUtilities::CreateRigidBodyCapsule(this);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Property
//----------------------------------------------------------------------------
void AIAgent::RegistProperties()
{
	AIAgentBase::RegistProperties();

	AddPropertyClass("AIAgent");

	AddProperty("Health", Object::PT_FLOAT, mHealth);
	AddProperty("Height", Object::PT_FLOAT, mHeight);
	AddProperty("MaxForce", Object::PT_FLOAT, mMaxForce);
	AddProperty("MaxSpeed", Object::PT_FLOAT, mMaxSpeed);
	AddProperty("Speed", Object::PT_FLOAT, mSpeed);
	AddProperty("Target", Object::PT_APOINT3, mTarget);
	AddProperty("TargetRadius", Object::PT_FLOAT, mTargetRadius);
}
//----------------------------------------------------------------------------
void AIAgent::OnPropertyChanged(const PropertyObject &obj)
{
	AIAgentBase::OnPropertyChanged(obj);

	if (obj.Name == "Health")
	{
		SetHealth(PX2_ANY_AS(obj.Data, float));
	}
	else if (obj.Name == "Height")
	{
		SetHeight(PX2_ANY_AS(obj.Data, float));
	}
	else if (obj.Name == "MaxForce")
	{
		SetMaxForce(PX2_ANY_AS(obj.Data, float));
	}
	else if (obj.Name == "MaxSpeed")
	{
		SetMaxSpeed(PX2_ANY_AS(obj.Data, float));
	}
	else if (obj.Name == "Speed")
	{
		SetSpeed(PX2_ANY_AS(obj.Data, float));
	}
	else if (obj.Name == "Target")
	{
		SetTarget(PX2_ANY_AS(obj.Data, APoint));
	}
	else if (obj.Name == "TargetRadius")
	{
		SetTargetRadius(PX2_ANY_AS(obj.Data, float));
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// options
//----------------------------------------------------------------------------
AVector AIAgent::ForceToAlign(float maxDistance, float maxAngle,
	const AIAgentGroup& group)
{
	float rad = maxAngle * Mathf::DEG_TO_RAD;
	float cosVal = Mathf::Cos(rad);
	return _Vec3ToAVector(steerForAlignment(maxDistance, cosVal, group));
}
//----------------------------------------------------------------------------
AVector AIAgent::ForceToAvoidAgents(const std::vector<AIAgent*>& agents,
	float predictionTime)
{
	const static float MIN_PREDICTION_TIME = 0.1f;

	OpenSteer::AVGroup group;
	std::vector<AIAgent*>::const_iterator it;

	for (it = agents.begin(); it != agents.end(); ++it)
	{
		AIAgent* const agent = *it;
		group.push_back(agent);
	}

	OpenSteer::Vec3 steerForce = steerToAvoidNeighbors(
		Mathf::Max(MIN_PREDICTION_TIME, predictionTime), group);

	return _Vec3ToAVector(steerForce);
}
//----------------------------------------------------------------------------
AVector AIAgent::ForceToAvoidObjects(
	const std::vector<AIAgentObject*>& objects,
	float predictionTime)
{
	const static float MIN_PREDICTION_TIME = 0.1f;
	const float timeToCollision = Mathf::Max(MIN_PREDICTION_TIME, predictionTime);

	OpenSteer::ObstacleGroup group;
	std::vector<AIAgentObject*>::const_iterator it;

	OpenSteer::Vec3 avoidForce = OpenSteer::Vec3::zero;

	for (it = objects.begin(); it != objects.end(); ++it)
	{
		AIAgentObject* const object = (*it);

		if (object->GetMass() > 0 || object->IsMassZeroAvoid())
		{
			avoidForce += object->_SteerToAvoid(*this, timeToCollision);
		}
	}

	return _Vec3ToAVector(avoidForce);
}
//----------------------------------------------------------------------------
AVector AIAgent::ForceToAvoidAgents(float predictionTime)
{
	AIAgentWorld* agentWorld = GetAIAgentWorld();

	if (agentWorld)
	{
		std::vector<AIAgent*>& agents = agentWorld->GetAgents();
		std::vector<AIAgent*> aliveAgents;

		std::vector<AIAgent*>::iterator it;

		for (it = agents.begin(); it != agents.end(); ++it)
		{
			if ((*it)->GetHealth() > 0)
			{
				aliveAgents.push_back(*it);
			}
		}

		return ForceToAvoidAgents(aliveAgents, predictionTime);
	}

	return AVector::ZERO;
}
//----------------------------------------------------------------------------
AVector AIAgent::ForceToAvoidObjects(float predictionTime)
{
	AIAgentWorld* const agentWorld = GetAIAgentWorld();

	if (agentWorld)
	{
		return ForceToAvoidObjects(agentWorld->GetObjects(), predictionTime);
	}

	return AVector::ZERO;
}
//----------------------------------------------------------------------------
AVector AIAgent::ForceToCombine(float maxDistance, float maxAngle,
	AIAgent *agent)
{
	std::vector<AIAgent*> agents;
	agents.push_back(agent);

	return ForceToCombine(maxDistance, maxAngle, agents);
}
//----------------------------------------------------------------------------
AVector AIAgent::ForceToCombine(float maxDistance, float maxAngle,
	const AIAgentGroup& group)
{
	float rad = maxAngle * Mathf::DEG_TO_RAD;
	float cosVal = Mathf::Cos(rad);

	return _Vec3ToAVector(steerForCohesion(maxDistance, cosVal, group));
}
//----------------------------------------------------------------------------
AVector AIAgent::ForceToCombine(float maxDistance, float maxAngle,
	const std::vector<AIAgent*>& agents)
{
	AIAgentGroup agentGroup;
	std::vector<AIAgent*>::const_iterator it;
	for (it = agents.begin(); it != agents.end(); ++it)
	{
		agentGroup.AddAgent(*it);
	}

	return ForceToCombine(maxDistance, maxAngle, agentGroup);
}
//----------------------------------------------------------------------------
AVector AIAgent::ForceToFleePosition(const APoint& position)
{
	return _Vec3ToAVector(steerForFlee(_APointToVec3(position)));
}
//----------------------------------------------------------------------------
AVector AIAgent::ForceToFollowPath(float predictionTime)
{
	return ForceToFollowPath(mPath, predictionTime);
}
//----------------------------------------------------------------------------
AVector AIAgent::ForceToFollowPath(AIAgentPath& path,
	float predictionTime)
{
	static int FORWARD_DIRECTION = 1;
	static float MIN_PREDICTION_TIME = 0.1f;

	if (path.GetNumberOfPathPoints() > 0)
	{
		AVector force = _Vec3ToAVector(steerToFollowPath(
			FORWARD_DIRECTION,
			Mathf::Max(MIN_PREDICTION_TIME, predictionTime),
			path));
		return force;
	}
	return AVector::ZERO;
}
//----------------------------------------------------------------------------
AVector AIAgent::ForceToPosition(const APoint& position)
{
	return _Vec3ToAVector(steerForSeek(_APointToVec3(position)));
}
//----------------------------------------------------------------------------
AVector AIAgent::ForceToSeparateAgents(float maxDistance, float maxAngle)
{
	if (mAgentWorld)
	{
		return ForceToSeparate(maxDistance, maxAngle, 
			mAgentWorld->GetAgents());
	}

	return AVector::ZERO;
}
//----------------------------------------------------------------------------
AVector AIAgent::ForceToSeparate(float maxDistance, float maxAngle,
	const AIAgentGroup& group)
{
	float rad = maxAngle * Mathf::DEG_TO_RAD;
	float cosVal = Mathf::Cos(rad);
	return _Vec3ToAVector(steerForSeparation(maxDistance, cosVal, group));
}
//----------------------------------------------------------------------------
AVector AIAgent::ForceToSeparate(float maxDistance, float maxAngle,
	std::vector<AIAgent*> agents)
{
	AIAgentGroup agentGroup;
	std::vector<AIAgent*>::const_iterator it;
	for (it = agents.begin(); it != agents.end(); ++it)
	{
		agentGroup.AddAgent(*it);
	}

	return ForceToSeparate(maxDistance, maxAngle, agentGroup);
}
//----------------------------------------------------------------------------
AVector AIAgent::ForceToSeparate(float maxDistance, float maxAngle,
	AIAgent *agent)
{
	std::vector<AIAgent*> agents;
	agents.push_back(agent);
	return ForceToSeparate(maxDistance, maxAngle, agents);
}
//----------------------------------------------------------------------------
AVector AIAgent::ForceToStayOnPath(const float predictionTime)
{
	return ForceToStayOnPath(mPath, predictionTime);
}
//----------------------------------------------------------------------------
AVector AIAgent::ForceToStayOnPath(AIAgentPath& path,
	float predictionTime)
{
	const static float MIN_PREDICTION_TIME = 0.1f;

	if (path.GetNumberOfPathPoints())
	{
		return _Vec3ToAVector(steerToStayOnPath(
			Mathf::Max(MIN_PREDICTION_TIME, predictionTime), path));
	}

	return AVector::ZERO;
}
//----------------------------------------------------------------------------
AVector AIAgent::ForceToTargetSpeed(const float speed)
{
	return _Vec3ToAVector(steerForTargetSpeed(float(speed)));
}
//----------------------------------------------------------------------------
AVector AIAgent::ForceToWander(float deltaMilliseconds)
{
	//return AVector::ZERO;
	return _Vec3ToAVector(steerForWander(deltaMilliseconds));
}
//----------------------------------------------------------------------------
void AIAgent::ApplyForce(const AVector &force)
{
	if (mRobot)
	{
		if (mRobot->GetLidar()->IsOpened()
			&& mRobot->IsArduinoConnected())
		{

		}

		mRobot->FakeGoForce(force);
	}
	else
	{
		if (mRigidBody)
		{
			PhysicsUtilities::ApplyForce(
				mRigidBody, btVector3(force.X(), force.Y(), force.Z()));
		}
	}
}
//----------------------------------------------------------------------------
APoint AIAgent::PredictFuturePosition(float predictionTime) const
{
	return GetPosition() + GetVelocity() * Mathf::Max(0.0f, predictionTime);
}
//----------------------------------------------------------------------------
void AIAgent::RemovePath()
{
	mIsHasPath = false;
}
//----------------------------------------------------------------------------
void AIAgent::EnableForwarding(bool enable)
{
	mIsEnableForwarding = enable;
}
//----------------------------------------------------------------------------
bool AIAgent::IsForwardingEnabled() const
{
	return mIsEnableForwarding;
}
//----------------------------------------------------------------------------
void AIAgent::SetForward(const AVector& forward)
{
	if (forward == AVector::ZERO)
		return;

	Vector3f up = Vector3f::UNIT_Z;
	AVector dir = forward;
	dir.Normalize();
	AVector right = dir.Cross(AVector::UNIT_Z);

	HMatrix mat(right, dir, up, APoint::ORIGIN, true);
	SetRotate(mat);
}
//----------------------------------------------------------------------------
void AIAgent::SetForwarding(const AVector& forwarding)
{
	if (mRobot)
	{
		/*_*/
	}
	else
	{
		mForwarding = forwarding;
		float length = mForwarding.Normalize();
		if (0.0f == length)
			return;

		if (!mIsEnableForwarding)
		{
			SetForward(mForwarding);
		}
	}
}
//----------------------------------------------------------------------------
void AIAgent::SetHeight(float height)
{
	mHeight = Mathf::Max(0.0f, height);

	if (mRigidBody)
	{
		AIAgentUtilities::UpdateRigidBodyCapsule(this);
	}
}
//----------------------------------------------------------------------------
void AIAgent::SetMaxForce(float force)
{
	mMaxForce = Mathf::Max(0.0f, force);
}
//----------------------------------------------------------------------------
void AIAgent::SetMaxSpeed(float speed)
{
	mMaxSpeed = Mathf::Max(0.0f, speed);
}
//----------------------------------------------------------------------------
void AIAgent::SetPath(const AIAgentPath& path)
{
	mPath = path;
	mIsHasPath = true;
}
//----------------------------------------------------------------------------
bool AIAgent::GetPathGoPercent() const
{
	APoint curPos = GetPosition();
	return mPath.GetPathGoPercent(curPos);
}
//----------------------------------------------------------------------------
bool AIAgent::IsPathOver() const
{
	APoint curPos = GetPosition();
	return mPath.IsPathOver(curPos);
}
//----------------------------------------------------------------------------
void AIAgent::SetPhysicsRadius(float radius)
{
	mPhysicsRaduis = Mathf::Max(0.0f, radius);

	if (mRigidBody)
	{
		AIAgentUtilities::UpdateRigidBodyCapsule(this);
	}
}
//----------------------------------------------------------------------------
float AIAgent::GetPhysicsRadius() const
{
	return mPhysicsRaduis;
}
//----------------------------------------------------------------------------
void AIAgent::SetSpeed(float speed)
{
	mSpeed = speed;
}
//----------------------------------------------------------------------------
void AIAgent::SetTarget(const APoint& target)
{
	mTarget = target;
}
//----------------------------------------------------------------------------
void AIAgent::SetTargetRadius(float radius)
{
	mTargetRadius = Mathf::Max(0.0f, radius);
}
//----------------------------------------------------------------------------
void AIAgent::SetTeam(const std::string& team)
{
	mTeam = team;
}
//----------------------------------------------------------------------------
void AIAgent::SetVelocity(const AVector& velocity)
{
	if (mRigidBody)
	{
		PhysicsUtilities::SetRigidBodyVelocity(
			mRigidBody, PhysicsUtilities::Vector3ToBtVector3(velocity));
	}

	SetSpeed(Vector3f(velocity.X(), velocity.Y(), 0.0f).Length());
}
//----------------------------------------------------------------------------
AVector AIAgent::GetRight() const
{
	if (mRobot)
	{
		return mRobot->GetRight();
	}
	else
	{
		if (mRigidBody)
		{
			const btQuaternion quaterion = mRigidBody->getOrientation();
			HQuaternion quat(quaterion.w(), quaterion.x(), quaterion.y(),
				quaterion.z());
			HMatrix mat;
			quat.ToRotationMatrix(mat);
			AVector right;
			mat.GetColumn(0, right);
			return right;
		}
		else if (mNode)
		{
			HMatrix rotMat = mNode->WorldTransform.GetRotate();
			AVector right;
			rotMat.GetColumn(0, right);
			return right;
		}
	}

	return AVector::UNIT_X;
}
//----------------------------------------------------------------------------
AVector AIAgent::GetUp() const
{
	if (mRobot)
	{
		return AVector::UNIT_Z;
	}
	else
	{
		if (mRigidBody)
		{
			const btQuaternion quaterion = mRigidBody->getOrientation();
			HQuaternion quat(quaterion.w(), quaterion.x(), quaterion.y(),
				quaterion.z());
			HMatrix mat;
			quat.ToRotationMatrix(mat);
			AVector up;
			mat.GetColumn(2, up);
			return up;
		}
		else if (mNode)
		{
			HMatrix rotMat = mNode->WorldTransform.GetRotate();
			AVector up;
			rotMat.GetColumn(2, up);
			return up;
		}
	}

	return AVector::UNIT_Z;
}
//----------------------------------------------------------------------------
AVector AIAgent::GetForward() const
{
	if (mRobot)
	{
		AVector dir = mRobot->GetDirection();
		dir.Normalize();
		return dir;
	}
	else
	{
		if (mRigidBody)
		{
			const btQuaternion quaterion = mRigidBody->getOrientation();

			HQuaternion quat = HQuaternion(
				quaterion.w(), quaterion.x(), quaterion.y(), quaterion.z());
			HMatrix mat;
			quat.ToRotationMatrix(mat);
			HPoint col;
			mat.GetColumn(1, col);
			return Vector3f(col[0], col[1], col[2]);
		}
		else if (mNode)
		{
			return mNode->WorldTransform.GetDirection();
		}
	}

	return Vector3f::UNIT_Y;
}
//----------------------------------------------------------------------------
void AIAgent::SetHealth(float health)
{
	mHealth = health;
}
//----------------------------------------------------------------------------
float AIAgent::GetHealth() const
{
	return mHealth;
}
//----------------------------------------------------------------------------
float AIAgent::GetMaxForce() const
{
	return mMaxForce;
}
//----------------------------------------------------------------------------
float AIAgent::GetMaxSpeed() const
{
	return mMaxSpeed;
}
//----------------------------------------------------------------------------
float AIAgent::GetSpeed() const
{
	if (mRobot)
	{
		return mSpeed;
	}
	else
	{
		if (mRigidBody)
		{
			const btVector3 velocity = mRigidBody->getLinearVelocity();
			return Vector3f(velocity.x(), velocity.y(), 0.0f).Length();
		}
		else
		{
			return mSpeed;
		}
	}
}
//----------------------------------------------------------------------------
AVector AIAgent::GetVelocity() const
{
	if (mRobot)
	{
		return mRobot->GetVelocity();
	}
	else
	{
		if (mRigidBody)
		{
			btVector3 velocity = mRigidBody->getLinearVelocity();
			return AVector(velocity.x(), velocity.y(), velocity.z());
		}
		return GetForward() * mSpeed;
	}
}
//----------------------------------------------------------------------------
APoint AIAgent::GetTarget() const
{
	return mTarget;
}
//----------------------------------------------------------------------------
float AIAgent::GetTargetRadius() const
{
	return mTargetRadius;
}
//----------------------------------------------------------------------------
void AIAgent::_Update(double applicationTime, double elapsedTime)
{
	AIAgentBase::_Update(applicationTime, elapsedTime);

	if (mRobot)
	{
		AVector vec = mRobot->GetVelocity();
		SetVelocity(vec);
	}
	else
	{
		if (mSmoother && mIsEnableForwarding)
		{
			AVector forward = mSmoother->Update(mForwarding, elapsedTime);
			forward.Z() = 0.0f;
			SetForward(forward);
		}

		if (mRigidBody)
		{
			const btVector3 velocity = mRigidBody->getLinearVelocity();
			SetSpeed(Vector3f(velocity.x(), velocity.y(), 0.0f).Length());
		}
	}

	mPath.Update(elapsedTime);
}
//----------------------------------------------------------------------------
void AIAgent::SetAIAgentWorld(AIAgentWorld *agentWorld)
{
	mAgentWorld = agentWorld;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// override
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::side() const
{
	return _AVectorToVec3(GetRight());
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::setSide(OpenSteer::Vec3 s)
{
	PX2_UNUSED(s);
	// not implemented
	assert(false);

	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::up(void) const
{
	return _AVectorToVec3(GetUp());
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
	return _AVectorToVec3(GetForward());
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
	APoint pos = GetPosition();
	pos.Z() = 0.0f;
	return _APointToVec3(pos);
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::setPosition(OpenSteer::Vec3 p)
{
	SetPosition(_Vec3ToAPoint(p));
	return this->position();
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
	return OpenSteer::Vec3(
		globalDirection.dot(_AVectorToVec3(GetRight())),
		globalDirection.dot(_AVectorToVec3(GetForward())),
		globalDirection.dot(_AVectorToVec3(GetUp())));
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::localizePosition(
	const OpenSteer::Vec3& globalPosition) const
{
	OpenSteer::Vec3 globalOffset =
		globalPosition - _APointToVec3(GetPosition());

	return localizeDirection(globalOffset);
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
	assert(false);
}
//----------------------------------------------------------------------------
void AIAgent::regenerateOrthonormalBasisUF(
	const OpenSteer::Vec3& newUnitForward)
{
	PX2_UNUSED(newUnitForward);
}
//----------------------------------------------------------------------------
void AIAgent::regenerateOrthonormalBasis(
	const OpenSteer::Vec3& newForward)
{
	PX2_UNUSED(newForward);
}
//----------------------------------------------------------------------------
void AIAgent::regenerateOrthonormalBasis(
	const OpenSteer::Vec3& newForward, const OpenSteer::Vec3& newUp)
{
	PX2_UNUSED(newForward);
	PX2_UNUSED(newUp);
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::localRotateForwardToSide(
	const OpenSteer::Vec3& v) const
{
	PX2_UNUSED(v);

	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::globalRotateForwardToSide(
	const OpenSteer::Vec3& globalForward) const
{
	PX2_UNUSED(globalForward);

	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
float AIAgent::mass() const
{
	return GetMass();
}
//----------------------------------------------------------------------------
float AIAgent::setMass(float mass)
{
	SetMass(mass);
	return this->mass();
}
//----------------------------------------------------------------------------
float AIAgent::radius(void) const
{
	return static_cast<float>(GetRadius());
}
//----------------------------------------------------------------------------
float AIAgent::setRadius(float radius)
{
	SetRadius(radius);
	return this->radius();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::velocity(void) const
{
	return _AVectorToVec3(GetVelocity());
}
//----------------------------------------------------------------------------
float AIAgent::speed() const
{
	return GetSpeed();
}
//----------------------------------------------------------------------------
float AIAgent::setSpeed(float spd)
{
	SetSpeed(spd);
	return this->speed();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgent::predictFuturePosition(const float predictionTime) const
{
	return _APointToVec3(PredictFuturePosition(predictionTime));
}
//----------------------------------------------------------------------------
float AIAgent::maxForce(void) const
{
	return GetMaxForce();
}
//----------------------------------------------------------------------------
float AIAgent::setMaxForce(float force)
{
	SetMaxForce(force);
	return maxForce();
}
//----------------------------------------------------------------------------
float AIAgent::maxSpeed(void) const
{
	return GetMaxSpeed();
}
//----------------------------------------------------------------------------
float AIAgent::setMaxSpeed(float speed)
{
	SetMaxSpeed(speed);
	return maxSpeed();
}
//----------------------------------------------------------------------------
void AIAgent::update(const float currentTime, const float elapsedTime)
{
	(void)currentTime;
	(void)elapsedTime;
	// not implemented
	assert(false);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ³Ö¾Ã»¯
//----------------------------------------------------------------------------
AIAgent::AIAgent(LoadConstructor value) :
AIAgentBase(value)
{
	mForwarding = AVector::UNIT_Y;
	mSmoother = new0 Smoother<AVector>(16, AVector::UNIT_Y);
}
//----------------------------------------------------------------------------
void AIAgent::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	AIAgentBase::Load(source);
	PX2_VERSION_LOAD(source);

	source.Read(mHealth);
	source.Read(mHeight);
	source.Read(mMaxForce);
	source.Read(mMaxSpeed);
	source.Read(mSpeed);
	source.ReadAggregate(mTarget);
	source.Read(mTargetRadius);
	source.ReadString(mTeam);
	source.ReadBool(mIsEnableForwarding);

	PX2_END_DEBUG_STREAM_LOAD(AIAgent, source);
}
//----------------------------------------------------------------------------
void AIAgent::Link(InStream& source)
{
	AIAgentBase::Link(source);
}
//----------------------------------------------------------------------------
void AIAgent::PostLink()
{
	AIAgentBase::PostLink();
}
//----------------------------------------------------------------------------
bool AIAgent::Register(OutStream& target) const
{
	if (AIAgentBase::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void AIAgent::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	AIAgentBase::Save(target);
	PX2_VERSION_SAVE(target);

	target.Write(mHealth);
	target.Write(mHeight);
	target.Write(mMaxForce);
	target.Write(mMaxSpeed);
	target.Write(mSpeed);
	target.WriteAggregate(mTarget);
	target.Write(mTargetRadius);
	target.WriteString(mTeam);
	target.WriteBool(mIsEnableForwarding);

	PX2_END_DEBUG_STREAM_SAVE(AIAgent, target);
}
//----------------------------------------------------------------------------
int AIAgent::GetStreamingSize(Stream &stream) const
{
	int size = AIAgentBase::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	size += sizeof(mHealth);
	size += sizeof(mHeight);
	size += sizeof(mMaxForce);
	size += sizeof(mMaxSpeed);
	size += sizeof(mSpeed);
	size += sizeof(mTarget);
	size += sizeof(mTargetRadius);
	size += PX2_STRINGSIZE(mTeam);
	size += PX2_BOOLSIZE(mIsEnableForwarding);

	return size;
}
//----------------------------------------------------------------------------
