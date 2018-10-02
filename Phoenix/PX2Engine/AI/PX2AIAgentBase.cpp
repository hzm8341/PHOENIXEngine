// PX2AIAgentBase.cpp

#include "PX2AIAgentBase.hpp"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "PX2BtPhysicsWorld.hpp"
#include "PX2AIAgentUtilities.hpp"
#include "PX2BtPhysicsUtilities.hpp"
#include "PX2AIAgentWorld.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
PX2_IMPLEMENT_RTTI(PX2, Controller, AIAgentBase);
PX2_IMPLEMENT_STREAM(AIAgentBase);
PX2_IMPLEMENT_FACTORY(AIAgentBase);
PX2_IMPLEMENT_DEFAULT_NAMES(Controller, AIAgentBase);
//----------------------------------------------------------------------------
const float AIAgentBase::DEFAULT_AGENT_MASS = 90.7f;  // kilograms (200 lbs)
//----------------------------------------------------------------------------
AIAgentBase::AIAgentBase(Node *node, AgentType at) :
mNode(node),
mAgentType(at),
mAgentWorld(0),
mRigidBody(0),
mMass(DEFAULT_AGENT_MASS),
mRobot(0)
{
}
//----------------------------------------------------------------------------
AIAgentBase::~AIAgentBase()
{
	if (mRigidBody)
	{
		PhysicsUtilities::DeleteRigidBody(mRigidBody);
		mRigidBody = 0;
	}
}
//----------------------------------------------------------------------------
void AIAgentBase::Enable(bool enable)
{
	Controller::Enable(enable);

	if (mRigidBody)
	{
		mRigidBody->activate(enable);
	}
}
//----------------------------------------------------------------------------
void AIAgentBase::SetMass(float mass)
{
	if (mRigidBody)
	{
		PhysicsUtilities::SetRigidBodyMass(
			mRigidBody, std::max(0.0f, mass));
	}

	mMass = mass;
}
//----------------------------------------------------------------------------
float AIAgentBase::GetMass() const
{
	if (mRigidBody)
	{
		return PhysicsUtilities::GetRigidBodyMass(mRigidBody);
	}
	else
	{
		return mMass;
	}
}
//----------------------------------------------------------------------------
void AIAgentBase::SetOrientation(const HQuaternion& quaternion)
{
	PhysicsUtilities::SetRigidBodyOrientation(
		mRigidBody,
		PhysicsUtilities::QuaterionToBtQuaternion(quaternion));

	if (mRigidBody)
	{
		AIAgentUtilities::UpdateWorldTransform(this);
	}
}
//----------------------------------------------------------------------------
HQuaternion AIAgentBase::GetOrientation() const
{
	const btQuaternion& rotation =
		mRigidBody->getCenterOfMassTransform().getRotation();

	return HQuaternion(
		rotation.w(), rotation.x(), rotation.y(), rotation.z());
}
//----------------------------------------------------------------------------
void AIAgentBase::SetPosition(const APoint& position)
{
	if (mRigidBody)
	{
		PhysicsUtilities::SetRigidBodyPosition(
			mRigidBody, PhysicsUtilities::Vector3ToBtVector3(position));
	}

	if (mNode)
	{
		AIAgentUtilities::SetWorldTansform(mNode, position);
	}
}
//----------------------------------------------------------------------------
APoint AIAgentBase::GetPosition() const
{
	if (mRigidBody)
	{
		return PhysicsUtilities::BtVector3ToVector3(
			mRigidBody->getCenterOfMassPosition());
	}
	else if (mNode)
	{
		return mNode->WorldTransform.GetTranslate();
	}

	return APoint::ORIGIN;
}
//----------------------------------------------------------------------------
float AIAgentBase::GetRadius() const
{
	return PhysicsUtilities::GetRigidBodyRadius(mRigidBody);
}
//----------------------------------------------------------------------------
void AIAgentBase::SetRigidBody(btRigidBody* rigidBody)
{
	mRigidBody = rigidBody;

	if (mRigidBody)
	{
		mRigidBody->setUserPointer(this);
	}

	if (AT_AGENT == mAgentType)
		_RefreshRigidValue();
}
//----------------------------------------------------------------------------
void AIAgentBase::_RefreshRigidValue()
{
	SetMass(mMass);
}
//----------------------------------------------------------------------------
btRigidBody* AIAgentBase::GetRigidBody()
{
	return mRigidBody;
}
//----------------------------------------------------------------------------
const btRigidBody* AIAgentBase::GetRigidBody() const
{
	return mRigidBody;
}
//----------------------------------------------------------------------------
void AIAgentBase::SetNode(Node *node)
{
	mNode = node;
}
//----------------------------------------------------------------------------
void AIAgentBase::SetAgentWorld(AIAgentWorld *agentWorld)
{
	mAgentWorld = agentWorld;
}
//----------------------------------------------------------------------------
AIAgentWorld* AIAgentBase::GetAIAgentWorld()
{
	return mAgentWorld;
}
//----------------------------------------------------------------------------
const AIAgentWorld* AIAgentBase::GetAIAgentWorld() const
{
	return mAgentWorld;
}
//----------------------------------------------------------------------------
Node *AIAgentBase::GetNode()
{
	return mNode;
}
//----------------------------------------------------------------------------
const Node *AIAgentBase::GetNode() const
{
	return mNode;
}
//----------------------------------------------------------------------------
void AIAgentBase::_InitUpdate(double applicationTime, double elapsedTime)
{
	Movable *mov = DynamicCast<Movable>(GetControlledable());
	if (mov)
	{
		APoint pos = mov->WorldTransform.GetTranslate();
		SetPosition(pos);

		HMatrix rotMat = mov->WorldTransform.GetRotate();
		HQuaternion quat;
		quat.FromRotationMatrix(rotMat);
		SetOrientation(quat);
	}
}
//----------------------------------------------------------------------------
void AIAgentBase::_Update(double applicationTime, double elapsedTime)
{
	AIAgentUtilities::UpdateWorldTransform(this);
}
//----------------------------------------------------------------------------
void AIAgentBase::SetRobot(Robot *robot)
{
	mRobot = robot;
}
//----------------------------------------------------------------------------
Robot *AIAgentBase::GetRobot()
{
	return mRobot;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Property
//----------------------------------------------------------------------------
void AIAgentBase::RegistProperties()
{
	Controller::RegistProperties();

	AddPropertyClass("AIAgentBase");

	std::vector<std::string> atTypes;
	atTypes.push_back("AT_AGENT");
	atTypes.push_back("AT_OBJCT");
	AddPropertyEnum("AgentType", (int)mAgentType, atTypes, false);

	AddProperty("Mass", Object::PT_FLOAT, mMass);
}
//----------------------------------------------------------------------------
void AIAgentBase::OnPropertyChanged(const PropertyObject &obj)
{
	Controller::OnPropertyChanged(obj);

	if (obj.Name == "Mass")
	{
		SetMass(PX2_ANY_AS(obj.Data, float));
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ³Ö¾Ã»¯
//----------------------------------------------------------------------------
AIAgentBase::AIAgentBase(LoadConstructor value) :
Controller(value),
mAgentWorld(0),
mRigidBody(0),
mNode(0),
mRobot(0)
{
}
//----------------------------------------------------------------------------
void AIAgentBase::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Controller::Load(source);
	PX2_VERSION_LOAD(source);

	source.ReadEnum(mAgentType);
	source.Read(mMass);

	PX2_END_DEBUG_STREAM_LOAD(AIAgentBase, source);
}
//----------------------------------------------------------------------------
void AIAgentBase::Link(InStream& source)
{
	Controller::Link(source);
}
//----------------------------------------------------------------------------
void AIAgentBase::PostLink()
{
	Controller::PostLink();
}
//----------------------------------------------------------------------------
bool AIAgentBase::Register(OutStream& target) const
{
	if (Controller::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void AIAgentBase::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Controller::Save(target);
	PX2_VERSION_SAVE(target);

	target.WriteEnum(mAgentType);
	target.Write(mMass);

	PX2_END_DEBUG_STREAM_SAVE(AIAgentBase, target);
}
//----------------------------------------------------------------------------
int AIAgentBase::GetStreamingSize(Stream &stream) const
{
	int size = Controller::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	size += PX2_ENUMSIZE(mAgentType);
	size += sizeof(mMass);

	return size;
}
//----------------------------------------------------------------------------
