// PX2AIAgent.hpp

#ifndef PX2AIAGENT_HPP
#define PX2AIAGENT_HPP

#include "PX2CorePre.hpp"
#include "PX2Controller.hpp"
#include "PX2AIAgentPath.hpp"
#include "PX2HQuaternion.hpp"
#include "PX2AIAgentBase.hpp"
#include "OpenSteer/AbstractVehicle.h"
#include "OpenSteer/LocalSpace.h"
#include "OpenSteer/SteerLibrary.h"
#include "PX2NavMoveUnit.hpp"
#include "PX2Smoother.hpp"

namespace PX2
{

	class AIAgentGroup;
	class AIAgentObject;

	class PX2_ENGINE_ITEM AIAgent : public AIAgentBase, private
		OpenSteer::SteerLibraryMixin<OpenSteer::AbstractVehicle>
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
		static const float DEFAULT_AGENT_RADIUS;
		static const float DEFAULT_AGENT_SPEED;
		static const float DEFAULT_AGENT_TARGET_RADIUS;
		static const float DEFAULT_AGENT_WALKABLE_CLIMB;
		static const float DEFAULT_AGENT_WALKABLE_SLOPE;
		static const std::string DEFAULT_AGENT_TEAM;

	public:
		AVector ForceToAlign(float maxDistance, float maxAngle, 
			const AIAgentGroup& group);
		AVector ForceToAvoidAgents(const std::vector<AIAgent*>& agents,
			float predictionTime = 2.0f);
		AVector ForceToAvoidObjects(
			const std::vector<AIAgentObject*>& objects,
			float predictionTime = 2.0f);
		
		AVector ForceToCombine(float maxDistance, float maxAngle,
			AIAgent *agent);
		AVector ForceToCombine(float maxDistance, float maxAngle,
			const AIAgentGroup& group);
		AVector ForceToCombine(float maxDistance, float maxAngle, 
			const std::vector<AIAgent*>& agents);

		AVector ForceToFleePosition(const APoint& position);
		AVector ForceToFollowPath(float predictionTime = 2.0f);
		AVector ForceToFollowPath(AIAgentPath& path, 
			float predictionTime = 2.0f);
		AVector ForceToPosition(const APoint& position);

		AVector ForceToSeparateAgents(float maxDistance, float maxAngle);
		AVector ForceToSeparate(float maxDistance, float maxAngle,
			const AIAgentGroup& group);
		AVector ForceToSeparate(float maxDistance, float maxAngle,
			std::vector<AIAgent*> agents);
		AVector ForceToSeparate(float maxDistance, float maxAngle,
			AIAgent *agent);

		AVector ForceToStayOnPath(float predictionTime = 2.0f);
		AVector ForceToStayOnPath(AIAgentPath& path, 
			float predictionTime = 2.0f);
		AVector ForceToTargetSpeed(const float speed);
		AVector ForceToWander(float deltaMilliseconds);

		AVector ForceToAvoidAgents(float predictionTime = 2.0f);
		AVector ForceToAvoidObjects(float predictionTime = 2.0f);

		void ApplyForce(const AVector &force);

		APoint PredictFuturePosition(float predictionTime) const;

		void RemovePath();
		void SetForward(const AVector& forward);
		void EnableForwarding(bool enable);
		bool IsForwardingEnabled() const;
		void SetForwarding(const AVector& forwarding);
		void SetHeight(float  height);
		void SetMaxForce(float force);
		void SetMaxSpeed(float speed);
		void SetPath(const AIAgentPath& path);
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

		void SetRadius(float radius);
		virtual float GetRadius() const;

		float GetHeight() const;

		float GetMaxForce() const;
		float GetMaxSpeed() const;

		float GetSpeed() const;

		APoint GetTarget() const;
		float GetTargetRadius() const;

		AVector GetVelocity() const;

		// AbstractLocalSpace
	public:
		virtual OpenSteer::Vec3 side(void) const;
		virtual OpenSteer::Vec3 setSide(OpenSteer::Vec3 s);
		virtual OpenSteer::Vec3 up(void) const;
		virtual OpenSteer::Vec3 setUp(OpenSteer::Vec3 u);
		virtual OpenSteer::Vec3 forward(void) const;
		virtual OpenSteer::Vec3 setForward(OpenSteer::Vec3 f);
		virtual OpenSteer::Vec3 setPosition(OpenSteer::Vec3 p);
		virtual OpenSteer::Vec3 position(void) const;
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
		virtual void update(const float, const float);

		// AbstractVehicle
	public:
		virtual float mass() const;
		virtual float setMass(float);

		virtual float radius() const;
		virtual float setRadius(float);

		virtual OpenSteer::Vec3 velocity() const;
		virtual float speed() const;
		virtual float setSpeed(float);

		virtual OpenSteer::Vec3 predictFuturePosition(const float predictionTime) const;

		virtual float maxForce() const;
		virtual float setMaxForce(float);

		virtual float maxSpeed() const;
		virtual float setMaxSpeed(float);

	public_internal:
		void SetAIAgentWorld(AIAgentWorld *agentWorld);

	private:
		virtual void _Update(double applicationTime, double elapsedTime);

		AIAgentPath mPath;
		bool mIsHasPath;

		float mHealth;
		float mHeight;
		float mRadius;
		float mMaxForce;
		float mMaxSpeed;
		float mSpeed;
		APoint mTarget;
		float mTargetRadius;
		std::string mTeam;

		bool mIsEnableForwarding;
		AVector mForwarding;
		Smoother<AVector> *mSmoother;
	};

	PX2_REGISTER_STREAM(AIAgent);
	typedef Pointer0<AIAgent> AIAgentControllerPtr;
#include "PX2AIAgent.inl"

}

#endif