// PX2AIAgentController.cpp

#include "PX2AIAgentController.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, Controller, AIAgentController);
PX2_IMPLEMENT_STREAM(AIAgentController);
PX2_IMPLEMENT_FACTORY(AIAgentController);
PX2_IMPLEMENT_DEFAULT_NAMES(Controller, AIAgentController);
//----------------------------------------------------------------------------
const float AIAgentController::DEFAULT_AGENT_HEALTH = 100.0f;
const float AIAgentController::DEFAULT_AGENT_HEIGHT = 1.6f;  // meters (5.2 feet)
const float AIAgentController::DEFAULT_AGENT_MASS = 90.7f;  // kilograms (200 lbs)
const float AIAgentController::DEFAULT_AGENT_MAX_FORCE = 1000.0f;  // newtons (kg*m/s^2)
const float AIAgentController::DEFAULT_AGENT_MAX_SPEED = 7.0f;  // m/s (23.0 ft/s)
const float AIAgentController::DEFAULT_AGENT_RADIUS = 0.3f;  // meters (1.97 feet)
const float AIAgentController::DEFAULT_AGENT_SPEED = 0.0f;  // m/s (0 ft/s)
const float AIAgentController::DEFAULT_AGENT_TARGET_RADIUS = 0.5f;  // meters (1.64 feet)
const float AIAgentController::DEFAULT_AGENT_WALKABLE_CLIMB = DEFAULT_AGENT_RADIUS / 2.0f;
const float AIAgentController::DEFAULT_AGENT_WALKABLE_SLOPE = 45.0f;
const std::string AIAgentController::DEFAULT_AGENT_TEAM = "team1";
//----------------------------------------------------------------------------
AIAgentController::AIAgentController()
{
}
//----------------------------------------------------------------------------
AIAgentController::~AIAgentController()
{
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgentController::side(void) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgentController::setSide(OpenSteer::Vec3 s)
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgentController::up(void) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgentController::setUp(OpenSteer::Vec3 u)
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgentController::forward(void) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgentController::setForward(OpenSteer::Vec3 f)
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgentController::position(void) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgentController::setPosition(OpenSteer::Vec3 p)
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
bool AIAgentController::rightHanded(void) const
{
	return true;
}
//----------------------------------------------------------------------------
void AIAgentController::resetLocalSpace(void)
{

}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgentController::localizeDirection(
	const OpenSteer::Vec3& globalDirection) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgentController::localizePosition(
	const OpenSteer::Vec3& globalPosition) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgentController::globalizePosition(
	const OpenSteer::Vec3& localPosition) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgentController::globalizeDirection(
	const OpenSteer::Vec3& localDirection) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
void AIAgentController::setUnitSideFromForwardAndUp(void)
{

}
//----------------------------------------------------------------------------
void AIAgentController::regenerateOrthonormalBasisUF(
	const OpenSteer::Vec3& newUnitForward)
{

}
//----------------------------------------------------------------------------
void AIAgentController::regenerateOrthonormalBasis(
	const OpenSteer::Vec3& newForward)
{

}
//----------------------------------------------------------------------------
void AIAgentController::regenerateOrthonormalBasis(
	const OpenSteer::Vec3& newForward, const OpenSteer::Vec3& newUp)
{

}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgentController::localRotateForwardToSide(
	const OpenSteer::Vec3& v) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgentController::globalRotateForwardToSide(
	const OpenSteer::Vec3& globalForward) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
float AIAgentController::mass(void) const
{
	return 0.0f;
}
//----------------------------------------------------------------------------
float AIAgentController::setMass(float)
{
	return 0.0f;
}
//----------------------------------------------------------------------------
float AIAgentController::radius(void) const
{
	return 0.0f;
}
//----------------------------------------------------------------------------
float AIAgentController::setRadius(float)
{
	return 0.0f;
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgentController::velocity(void) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
float AIAgentController::speed(void) const
{
	return 0.0f;
}
//----------------------------------------------------------------------------
float AIAgentController::setSpeed(float)
{
	return 0.0f;
}
//----------------------------------------------------------------------------
OpenSteer::Vec3 AIAgentController::predictFuturePosition(const float predictionTime) const
{
	return OpenSteer::Vec3();
}
//----------------------------------------------------------------------------
float AIAgentController::maxForce(void) const
{
	return 0.0f;
}
//----------------------------------------------------------------------------
float AIAgentController::setMaxForce(float)
{
	return 0.0f;
}
//----------------------------------------------------------------------------
float AIAgentController::maxSpeed(void) const
{
	return 0.0f;
}
//----------------------------------------------------------------------------
float AIAgentController::setMaxSpeed(float)
{
	return 0.0f;
}
//----------------------------------------------------------------------------
void AIAgentController::update(const float currentTime, const float elapsedTime)
{

}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ³Ö¾Ã»¯
//----------------------------------------------------------------------------
AIAgentController::AIAgentController(LoadConstructor value) :
Controller(value)
{
}
//----------------------------------------------------------------------------
void AIAgentController::Load(InStream& source)
{
	PX2_BEGIN_DEBUG_STREAM_LOAD(source);

	Controller::Load(source);
	PX2_VERSION_LOAD(source);

	PX2_END_DEBUG_STREAM_LOAD(AIAgentController, source);
}
//----------------------------------------------------------------------------
void AIAgentController::Link(InStream& source)
{
	Controller::Link(source);
}
//----------------------------------------------------------------------------
void AIAgentController::PostLink()
{
	Controller::PostLink();
}
//----------------------------------------------------------------------------
bool AIAgentController::Register(OutStream& target) const
{
	if (Controller::Register(target))
	{
		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void AIAgentController::Save(OutStream& target) const
{
	PX2_BEGIN_DEBUG_STREAM_SAVE(target);

	Controller::Save(target);
	PX2_VERSION_SAVE(target);

	PX2_END_DEBUG_STREAM_SAVE(AIAgentController, target);
}
//----------------------------------------------------------------------------
int AIAgentController::GetStreamingSize(Stream &stream) const
{
	int size = Controller::GetStreamingSize(stream);

	return size;
}
//----------------------------------------------------------------------------
