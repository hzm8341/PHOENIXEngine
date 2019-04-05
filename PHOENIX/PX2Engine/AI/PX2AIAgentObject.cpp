// PX2AIAgentObject.cpp

#include "PX2AIAgentObject.hpp"
#include "PX2AIAgentWorld.hpp"
#include "PX2BtPhysicsUtilities.hpp"
#include "PX2AIAgentWorldUtilities.hpp"
#include "PX2AIAgentUtilities.hpp"
#include "PX2Node.hpp"
#include "BulletDynamics/Dynamics/btRigidBody.h""
#include "PX2BtPhysicsWorld.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, AIAgentBase, AIAgentObject);
PX2_IMPLEMENT_STREAM(AIAgentObject);
PX2_IMPLEMENT_FACTORY(AIAgentObject);
PX2_IMPLEMENT_DEFAULT_NAMES(AIAgentBase, AIAgentObject);
//----------------------------------------------------------------------------
AIAgentObject::AIAgentObject(Node *node) :
AIAgentBase(node, AT_OBJCT),
mLastWorldPosZ(0.0f),
mPhysicsShapeType(PST_MESH)
{
	if (!IsRegistedToScriptSystem())
		RegistToScriptSystem();

	SetName("AIAgentObject");
}
//----------------------------------------------------------------------------
AIAgentObject::~AIAgentObject()
{
}
//----------------------------------------------------------------------------
AIAgentObject::PhysicsShapeType AIAgentObject::GetPhysicsShapeType() const
{
	return mPhysicsShapeType;
}
//----------------------------------------------------------------------------
void AIAgentObject::InitializeInfinitePlane(const AVector &normal, 
	float originOffset)
{
	AIAgentUtilities::CreateRigidBodyInfinitePlane(this, normal, originOffset);

	mPhysicsShapeType = AIAgentObject::PST_INFINITEPLANE;
}
//----------------------------------------------------------------------------
void AIAgentObject::InitializeMesh(Movable *mov)
{
	AIAgentUtilities::CreateRigidBodyMesh(this, mov);

	mPhysicsShapeType = AIAgentObject::PST_MESH;
}
//----------------------------------------------------------------------------
void AIAgentObject::SetOrientation(const HQuaternion& quaternion)
{
	PhysicsUtilities::SetRigidBodyOrientation(
		mRigidBody,
		btQuaternion(quaternion.X(), quaternion.Y(), quaternion.Z(), 
		quaternion.W()));

	AIAgentUtilities::UpdateWorldTransTo(this);
}
//----------------------------------------------------------------------------
HQuaternion AIAgentObject::GetOrientation() const
{
	const btQuaternion& rotation =
		mRigidBody->getCenterOfMassTransform().getRotation();

	return HQuaternion(
		rotation.w(), rotation.x(), rotation.y(), rotation.z());
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgentObject::_GetPosition(float zetZ) const
{
	const btVector3& position = mRigidBody->getCenterOfMassPosition();
	return OpenSteer::Vec3(
		position.m_floats[0], position.m_floats[1], zetZ);
}
//----------------------------------------------------------------------------
float AIAgentObject::GetRigidBodyRadius() const
{
	return PhysicsUtilities::GetRigidBodyRadius(mRigidBody);
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgentObject::_SteerToAvoid(
	const OpenSteer::AbstractVehicle& v,
	const float minTimeToCollision) const
{
	// minimum distance to obstacle before avoidance is required
	const float minDistanceToCollision = minTimeToCollision * v.speed();
	const float minDistanceToCenter = minDistanceToCollision + GetRadius();

	// contact distance: sum of radii of obstacle and vehicle
	float radius = GetRadius();
	const float totalRadius = radius + v.radius();

	float sepForce = 2.0f;

	// obstacle center relative to vehicle position
	OpenSteer::Vec3 vPos = v.position();
	vPos.z = 0.0f;
	const OpenSteer::Vec3 localOffset = _GetPosition(0.0f) - vPos;
	float localOffsetLength = localOffset.length();
	float distPerc = localOffsetLength / totalRadius;

	// distance along vehicle's forward axis to obstacle's center
	const float forwardComponent = localOffset.dot(v.forward());
	const OpenSteer::Vec3 forwardOffset = forwardComponent * v.forward();

	// offset from forward axis to obstacle's center
	const OpenSteer::Vec3 offForwardOffset = localOffset - forwardOffset;

	// test to see if sphere overlaps with obstacle-free corridor
	float length = offForwardOffset.length();

	const bool inCylinder = length < totalRadius;
	const bool isInRadius = localOffsetLength < totalRadius;
	const bool nearby = forwardComponent < minDistanceToCenter;
	const bool inFront = forwardComponent > 0;

	OpenSteer::Vec3 vSide = v.side();
	offForwardOffset.normalize();

	// if all three conditions are met, steer away from sphere center
	if (inCylinder && nearby && inFront)
	{
		if (length == 0.0f)
		{
			return vSide;
		}
		else
		{
			return offForwardOffset * -1;
		}
	}
	else
	{
		return OpenSteer::Vec3::zero;
	}
}
//----------------------------------------------------------------------------
void AIAgentObject::_Update(double applicationTime, double elapsedTime)
{
	AIAgentBase::_Update(applicationTime, elapsedTime);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Property
//----------------------------------------------------------------------------
void AIAgentObject::RegistProperties()
{
	AIAgentBase::RegistProperties();

	AddPropertyClass("AIAgentObject");

	std::vector<std::string> pstTypes;
	pstTypes.push_back("PST_INFINITEPLANE");
	pstTypes.push_back("PST_MESH");
	AddPropertyEnum("PhysicsShapeType", (int)mPhysicsShapeType, pstTypes,
		false);
}
//----------------------------------------------------------------------------
void AIAgentObject::OnPropertyChanged(const PropertyObject &obj)
{
	AIAgentBase::OnPropertyChanged(obj);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ³Ö¾Ã»¯
//----------------------------------------------------------------------------
AIAgentObject::AIAgentObject(LoadConstructor value) :
AIAgentBase(value),
mLastWorldPosZ(0.0f)
{
	if (!IsRegistedToScriptSystem())
		RegistToScriptSystem();
}
//----------------------------------------------------------------------------
void AIAgentObject::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	AIAgentBase::Load(source);
	PX2_VERSION_LOAD(source);

	source.ReadEnum(mPhysicsShapeType);

	PX2_END_DEBUG_STREAM_LOAD(AIAgentObject, source);
}
//----------------------------------------------------------------------------
void AIAgentObject::Link(InStream& source)
{
	AIAgentBase::Link(source);
}
//----------------------------------------------------------------------------
void AIAgentObject::PostLink()
{
	AIAgentBase::PostLink();
}
//----------------------------------------------------------------------------
bool AIAgentObject::Register(OutStream& target) const
{
	if (AIAgentBase::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void AIAgentObject::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	AIAgentBase::Save(target);
	PX2_VERSION_SAVE(target);

	target.WriteEnum(mPhysicsShapeType);

	PX2_END_DEBUG_STREAM_SAVE(AIAgentObject, target);
}
//----------------------------------------------------------------------------
int AIAgentObject::GetStreamingSize(Stream &stream) const
{
	int size = AIAgentBase::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	size += PX2_ENUMSIZE(mPhysicsShapeType);

	return size;
}
//----------------------------------------------------------------------------
