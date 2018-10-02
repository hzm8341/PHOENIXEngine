// PX2AIAgent.hpp

#ifndef PX2AIAGENT_HPP
#define PX2AIAGENT_HPP

#include "PX2CorePre.hpp"
#include "PX2Controller.hpp"

#include "OpenSteer/AbstractVehicle.h"
#include "OpenSteer/LocalSpace.h"
#include "OpenSteer/SteerLibrary.h"

namespace PX2
{

	class PX2_ENGINE_ITEM AIAgentController : public Controller, private
		OpenSteer::SteerLibraryMixin<OpenSteer::AbstractVehicle>
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_STREAM(AIAgentController);

		friend class AgentGroup;
	public:
		AIAgentController();
		virtual ~AIAgentController();

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
	};

	PX2_REGISTER_STREAM(AIAgentController);
	typedef Pointer0<AIAgentController> AIAgentControllerPtr;
#include "PX2AIAgentController.inl"

}

#endif