// PX2Actor.cpp

#include "PX2Actor.hpp"
#include "PX2AIAgent.hpp"
#include "PX2AIAgentObject.hpp"
#include "PX2Scene.hpp"
#include "PX2AIAgentWorld.hpp"
#include "PX2ResourceManager.hpp"
#include "PX2Scene.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Node, Actor);
PX2_IMPLEMENT_STREAM(Actor);
PX2_IMPLEMENT_FACTORY(Actor);
PX2_IMPLEMENT_DEFAULT_NAMES(Node, Actor);

//----------------------------------------------------------------------------
Actor::Actor(AIType at)
{
	SetName("Actor");

	mAIType = at;
	mPhysicsShapeType = Actor::PST_GENERAL;

	int id = Scene::NextID(1);

	if (AIT_AGENT == mAIType)
	{
		mAgentBase = new0 AIAgent(this);
		mAgentBase->SetID(id);
	}
	else if (AIT_AGENTOBJECT == mAIType)
	{
		mAgentBase = new0 AIAgentObject(this);
		mAgentBase->SetID(id);
	}

	SetID(id);

	if (mAgentBase)
	{
		AttachController(mAgentBase);
	}

	mRobot = 0;
}
//----------------------------------------------------------------------------
Actor::~Actor()
{
	GoOutEventWorld();
}
//----------------------------------------------------------------------------
void Actor::SetPhysicsShapeType(Actor::PhysicsShapeType type, 
	Movable *meshMov)
{
	mPhysicsShapeType = type;
	mPhysicsMovable = meshMov;
}
//----------------------------------------------------------------------------
void Actor::_CreatePhysics()
{
	if (mPhysicsShapeType == PST_GENERAL)
	{
		AIAgent *agent = DynamicCast<AIAgent>(mAgentBase);
		if (agent)
			agent->InitializeCapsule();
	}
	else if (mPhysicsShapeType == PST_INFINITEPLANE)
	{
		AIAgentObject *agentObject = DynamicCast<AIAgentObject>(mAgentBase);
		if (agentObject)
			agentObject->InitializeInfinitePlane(AVector::UNIT_Z,
			this->WorldTransform.GetTranslate().Z());
	}
	else if (mPhysicsShapeType == PST_MESH)
	{
		UpdateWorldData(0.0f, 0.0f);

		AIAgentObject *agentObject = DynamicCast<AIAgentObject>(mAgentBase);
		if (agentObject)
			agentObject->InitializeMesh(mPhysicsMovable);
	}
}
//----------------------------------------------------------------------------
Actor::PhysicsShapeType Actor::GetPhysicsShapeType() const
{
	return mPhysicsShapeType;
}
//----------------------------------------------------------------------------
void Actor::SetAIType(AIType at)
{
	mAIType = at;
}
//----------------------------------------------------------------------------
Actor::AIType Actor::GetAIType() const
{
	return mAIType;
}
//----------------------------------------------------------------------------
AIAgentBase *Actor::GetAIAgentBase()
{
	return mAgentBase;
}
//----------------------------------------------------------------------------
AIAgent *Actor::GetAIAgent()
{
	return DynamicCast<AIAgent>(mAgentBase);
}
//----------------------------------------------------------------------------
void Actor::OnBeAttached()
{
	Node::OnBeAttached();

	UpdateWorldData(0.0f, 0.0f);

	_CreatePhysics();

	Scene *scene = GetFirstParentDerivedFromType<Scene>();
	if (scene)
	{
		AIAgentWorld *aiAgentWorld = scene->GetAIAgentWorld();
		if (aiAgentWorld)
		{
			AIAgent *agent = DynamicCast<AIAgent>(mAgentBase);
			if (agent)
			{
				aiAgentWorld->AddAgent(agent);
			}
			AIAgentObject *agentObject = DynamicCast<AIAgentObject>(mAgentBase);
			if (agentObject)
			{
				aiAgentWorld->AddAgentObject(agentObject);
			}
		}
	}
}
//----------------------------------------------------------------------------
void Actor::OnBeDetach()
{
	Node::OnBeDetach();

	Scene *scene = GetFirstParentDerivedFromType<Scene>();
	if (scene)
	{
		RemoveAgentStuff(scene);
	}
}
//----------------------------------------------------------------------------
void Actor::RemoveAgentStuff(Scene *scene)
{
	AIAgentWorld *aiAgentWorld = scene->GetAIAgentWorld();
	if (aiAgentWorld)
	{
		AIAgent *agent = DynamicCast<AIAgent>(mAgentBase);
		AIAgentObject *agentObject = DynamicCast<AIAgentObject>(
			mAgentBase);
		if (agent)
		{
			aiAgentWorld->RemoveAgent(agent);
		}
		if (agentObject)
		{
			aiAgentWorld->RemoveAgentObject(agentObject);
		}
	}
}
//----------------------------------------------------------------------------
void Actor::SetRobot(Robot *robot)
{
	mRobot = robot;
}
//----------------------------------------------------------------------------
Robot *Actor::GetRobot()
{
	return mRobot;
}
//----------------------------------------------------------------------------
void Actor::UpdateWorldData(double applicationTime, double elapsedTime)
{
	Node::UpdateWorldData(applicationTime, elapsedTime);
}
//----------------------------------------------------------------------------
void Actor::OnEvent(Event *ent)
{
	PX2_UNUSED(ent);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Property
//----------------------------------------------------------------------------
void Actor::RegistProperties()
{
	Node::RegistProperties();

	AddPropertyClass("Actor");

	std::vector<std::string> atTypes;
	atTypes.push_back("AIT_NONE");
	atTypes.push_back("AIT_AGENT");
	atTypes.push_back("AIT_AGENTOBJECT");
	AddPropertyEnum("AIType", (int)mAIType, atTypes, false);

	std::vector<std::string> psTypes;
	psTypes.push_back("PST_GENERAL");
	psTypes.push_back("PST_INFINITEPLANE");
	psTypes.push_back("PST_MESH");
	AddPropertyEnum("PhysicsShapeType", (int)mPhysicsShapeType, psTypes,
		false);
}
//----------------------------------------------------------------------------
void Actor::OnPropertyChanged(const PropertyObject &obj)
{
	Node::OnPropertyChanged(obj);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 持久化支持
//----------------------------------------------------------------------------
Actor::Actor(LoadConstructor value) :
Node(value)
{
	mRobot = 0;
}
//----------------------------------------------------------------------------
void Actor::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Node::Load(source);
	PX2_VERSION_LOAD(source);

	source.ReadEnum(mAIType);
	source.ReadPointer(mAgentBase);
	source.ReadEnum(mPhysicsShapeType);
	source.ReadPointer(mPhysicsMovable);

	PX2_END_DEBUG_STREAM_LOAD(Actor, source);
}
//----------------------------------------------------------------------------
void Actor::Link(InStream& source)
{
	Node::Link(source);

	if (mAgentBase)
	{
		source.ResolveLink(mAgentBase);
		mAgentBase->SetNode(this);
	}

	if (mPhysicsMovable)
		source.ResolveLink(mPhysicsMovable);
}
//----------------------------------------------------------------------------
void Actor::PostLink()
{
	Node::PostLink();

	if (mAgentBase)
	{
		mAgentBase->PostLink();
	}

	if (mPhysicsMovable)
	{
		mPhysicsMovable->PostLink();
	}
}
//----------------------------------------------------------------------------
bool Actor::Register(OutStream& target) const
{
	if (Node::Register(target))
	{
		if (mAgentBase)
		{
			target.Register(mAgentBase);
		}

		if (mPhysicsMovable)
		{
			target.Register(mPhysicsMovable);
		}

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void Actor::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Node::Save(target);
	PX2_VERSION_SAVE(target);

	target.WriteEnum(mAIType);
	target.WritePointer(mAgentBase);
	target.WriteEnum(mPhysicsShapeType);
	target.WritePointer(mPhysicsMovable);

	PX2_END_DEBUG_STREAM_SAVE(Actor, target);
}
//----------------------------------------------------------------------------
int Actor::GetStreamingSize(Stream &stream) const
{
	int size = Node::GetStreamingSize(stream);
	size += PX2_VERSION_SIZE(mVersion);

	size += PX2_ENUMSIZE(mAIType);
	size += PX2_POINTERSIZE(mAgentBase);
	size += PX2_ENUMSIZE(mPhysicsShapeType);
	size += PX2_POINTERSIZE(mPhysicsMovable);

	return size;
}
//----------------------------------------------------------------------------