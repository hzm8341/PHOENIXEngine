// PX2AIAgent.hpp

#ifndef PX2AIAGENT_HPP
#define PX2AIAGENT_HPP

#include "PX2CorePre.hpp"
#include "PX2Controller.hpp"
#include "PX2HQuaternion.hpp"
#include "PX2AIAgentBase.hpp"
#include "PX2NavMoveUnit.hpp"
#include "PX2Smoother.hpp"
#include "PX2AISteeringBehavior.hpp"
#include "PX2AISteeringPath.hpp"

namespace PX2
{

	class AIAgentGroup;
	class AIAgentObject;

	class PX2_ENGINE_ITEM AIAgent : public AIAgentBase
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(AIAgent);
		PX2_DECLARE_PROPERTY;

		friend class AIAgentGroup;
	public:
		AIAgent();
		AIAgent(Node *node);
		virtual ~AIAgent();

		void InitializeCapsule();

		static const float DEFAULT_AGENT_HEALTH;
		static const float DEFAULT_AGENT_HEIGHT;
		static const float DEFAULT_AGENT_MAX_FORCE;
		static const float DEFAULT_AGENT_MAX_SPEED;
		static const float DEFAULT_AGENT_SPEED;
		static const float DEFAULT_AGENT_TARGET_RADIUS;
		static const float DEFAULT_AGENT_WALKABLE_CLIMB;
		static const float DEFAULT_AGENT_WALKABLE_SLOPE;
		static const std::string DEFAULT_AGENT_TEAM;

	public:	
		void RemovePath();
		void SetForward(const AVector& forward);
		void EnableForwarding(bool enable);
		bool IsForwardingEnabled() const;
		void SetForwarding(const AVector& forwarding);
		void SetHeight(float  height);
		void SetMaxForce(float force);
		void SetMaxSpeed(float speed);
		void SetPath(const AIAgentPath& path);
		bool IsPathOver() const;

		void SetSpeed(float speed);
		void SetTarget(const APoint& target);
		void SetTargetRadius(float radius);
		void SetTeam(const std::string& team);
		void SetVelocity(const AVector& velocity);

		AVector GetRight() const;
		AVector GetUp() const;
		AVector GetForward() const;

		void SetHealth(float health);
		float GetHealth() const;

		void SetPhysicsRadius(float radius);
		float GetPhysicsRadius() const;

		float GetHeight() const;

		float GetMaxForce() const;
		float GetMaxSpeed() const;

		float GetSpeed() const;

		APoint GetTarget() const;
		float GetTargetRadius() const;

		AVector GetVelocity() const;

	public_internal:
		void SetAIAgentWorld(AIAgentWorld *agentWorld);

	private:
		virtual void _Update(double applicationTime, double elapsedTime);

		SteeringBehavior *mSteeringBehavior;

		bool mIsHasPath;

		float mHealth;
		float mHeight;
		float mPhysicsRaduis;
		float mMaxForce;
		float mMaxSpeed;
		float mSpeed;
		APoint mTarget;
		float mTargetRadius;
		std::string mTeam;

		bool mIsEnableForwarding;
		AVector mForwarding;
		Smoother<AVector> *mSmoother;

		AVector mForcing;
		Smoother<AVector> *mSmootherForcing;

		AIAgentObject *mLastMinObject;
	};

	PX2_REGISTER_STREAM(AIAgent);
	typedef Pointer0<AIAgent> AIAgentControllerPtr;
#include "PX2AIAgent.inl"

}

#endif