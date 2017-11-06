// PX2AIAgent.hpp

#ifndef PX2AIAGENT_HPP
#define PX2AIAGENT_HPP

#include "PX2CorePre.hpp"
#include "PX2Controller.hpp"
#include "PX2BtPhysicsUtilities.hpp"
#include "PX2AIAgentPath.hpp"
#include "PX2HQuaternion.hpp"
#include "OpenSteer/AbstractVehicle.h"
#include "OpenSteer/LocalSpace.h"
#include "OpenSteer/SteerLibrary.h"

namespace PX2
{
	class Node;
	class AIAgentWorld;

	class PX2_ENGINE_ITEM AIAgent : public Controller, private
		OpenSteer::SteerLibraryMixin<OpenSteer::AbstractVehicle>
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(AIAgent);

		friend class AgentGroup;
	public:
		AIAgent(int agentId, Node *sceneNode, btRigidBody* rigidBody);
		virtual ~AIAgent();

		static const float DEFAULT_AGENT_HEALTH;
		static const float DEFAULT_AGENT_HEIGHT;
		static const float DEFAULT_AGENT_MASS;
		static const float DEFAULT_AGENT_MAX_FORCE;
		static const float DEFAULT_AGENT_MAX_SPEED;
		static const float DEFAULT_AGENT_RADIUS;
		static const float DEFAULT_AGENT_SPEED;
		static const float DEFAULT_AGENT_TARGET_RADIUS;
		static const float DEFAULT_AGENT_WALKABLE_CLIMB;
		static const float DEFAULT_AGENT_WALKABLE_SLOPE;
		static const std::string DEFAULT_AGENT_TEAM;

	public:
		void RemovePath();
		void SetForward(const Vector3f& forward);
		void SetForward(const HQuaternion& orientation);
		void SetHealth(float health);
		void SetHeight(float  height);
		void SetMass(float  mass);
		void SetMaxForce(float force);
		void SetMaxSpeed(float speed);
		void SetPath(const AIAgentPath& path);
		void SetPosition(const Vector3f& position);
		void SetRadius(float radius);
		void SetRigidBody(btRigidBody* rigidBody);
		void SetAgentWorld(AIAgentWorld *agentWorld);
		void SetSpeed(float speed);
		void SetTarget(const Vector3f& target);
		void SetTargetRadius(float radius);
		void SetTeam(const std::string& team);
		void SetVelocity(const Vector3f& velocity);

		btRigidBody* GetRigidBody();
		AIAgentWorld *GetAgentWorld();

		Vector3f GetForward() const;
		Vector3f GetPosition() const;
		HQuaternion GetOrientation() const;

		float GetHealth() const;
		float GetHeight() const;
		float GetRadius() const;
		float GetMass() const;

		// AbstractLocalSpace
	public:
		virtual OpenSteer::Vec3 side(void) const;
		virtual OpenSteer::Vec3 setSide(OpenSteer::Vec3 s);
		virtual OpenSteer::Vec3 up(void) const;
		virtual OpenSteer::Vec3 setUp(OpenSteer::Vec3 u);
		virtual OpenSteer::Vec3 forward(void) const;
		virtual OpenSteer::Vec3 setForward(OpenSteer::Vec3 f);
		virtual OpenSteer::Vec3 position(void) const;
		virtual OpenSteer::Vec3 setPosition(OpenSteer::Vec3 p);
		virtual bool rightHanded(void) const;
		virtual void resetLocalSpace(void);
		virtual OpenSteer::Vec3 localizeDirection(const OpenSteer::Vec3& globalDirection) const;
		virtual OpenSteer::Vec3 localizePosition(const OpenSteer::Vec3& globalPosition) const;
		virtual OpenSteer::Vec3 globalizePosition(const OpenSteer::Vec3& localPosition) const;
		virtual OpenSteer::Vec3 globalizeDirection(const OpenSteer::Vec3& localDirection) const;
		virtual void setUnitSideFromForwardAndUp(void);
		virtual void regenerateOrthonormalBasisUF(const OpenSteer::Vec3& newUnitForward);
		virtual void regenerateOrthonormalBasis(const OpenSteer::Vec3& newForward);
		virtual void regenerateOrthonormalBasis(const OpenSteer::Vec3& newForward, const OpenSteer::Vec3& newUp);
		virtual OpenSteer::Vec3 localRotateForwardToSide(const OpenSteer::Vec3& v) const;
		virtual OpenSteer::Vec3 globalRotateForwardToSide(const OpenSteer::Vec3& globalForward) const;

		// AbstractVehicle
	public:
		virtual float mass(void) const;
		virtual float setMass(float);

		virtual float radius(void) const;
		virtual float setRadius(float);

		virtual OpenSteer::Vec3 velocity(void) const;
		virtual float speed(void) const;
		virtual float setSpeed(float);

		virtual OpenSteer::Vec3 predictFuturePosition(const float predictionTime) const;

		virtual float maxForce(void) const;
		virtual float setMaxForce(float);

		virtual float maxSpeed(void) const;
		virtual float setMaxSpeed(float);

		virtual void update(const float currentTime, const float elapsedTime);

	private:
		AIAgentWorld *mAgentWorld;

		Node* sceneNode_;
		btRigidBody* rigidBody_;

		AIAgentPath path_;
		bool hasPath_;

		float height_;
		float maxForce_;
		float maxSpeed_;
		float radius_;
		float speed_;
		float mass_;
		Vector3f target_;
		float targetRadius_;
		float health_;
		std::string team_;
	};

	PX2_REGISTER_STREAM(AIAgent);
	typedef Pointer0<AIAgent> AIAgentControllerPtr;
#include "PX2AIAgent.inl"

}

#endif