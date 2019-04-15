// PX2RRTRobot.cpp

#include "PX2RRTRobot.hpp"
#include "PX2RRTStarParam.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
void RRTRobot::setup()
{
	alive = true;
	mass = 5.0; 
	scanRadius = RRT_sensorRadius;
	accuracy = RRT_accur;
	location = Vector2f::ZERO;
	HOME = location;
	velocity = Vector2f::ZERO;
	accelaration = Vector2f::ZERO;

	maxVelocity = Vector2f(RRT_mVal, RRT_mVal);
	maxForce = Vector2f(RRT_mForce, RRT_mForce);
	
	color = Float3(50, 145, 80);
}
//----------------------------------------------------------------------------
void RRTRobot::setup(Vector2f loc)
{
	alive = true;
	mass = 5.0;
	scanRadius = RRT_sensorRadius;
	accuracy = RRT_accur;
	location = loc;
	HOME = location;

	velocity = Vector2f(0.0, 0.0);
	accelaration = Vector2f(0.0, 0.0);
	maxVelocity = Vector2f(RRT_mVal, RRT_mVal);
	maxForce = Vector2f(RRT_mForce, RRT_mForce);

	color = Float3(50, 145, 80 );
}
//----------------------------------------------------------------------------
void RRTRobot::update()
{
}
//----------------------------------------------------------------------------
void RRTRobot::render()
{
}
//----------------------------------------------------------------------------
void RRTRobot::addForce(Vector2f force)
{
	accelaration += (force / mass);
}
//----------------------------------------------------------------------------
float ofMap(float value, float inputMin, float inputMax, float outputMin, float outputMax, bool clamp) {

	if (fabs(inputMin - inputMax) < FLT_EPSILON) {
		return outputMin;
	}
	else {
		float outVal = ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);

		if (clamp) {
			if (outputMax < outputMin) {
				if (outVal < outputMax)outVal = outputMax;
				else if (outVal > outputMin)outVal = outputMin;
			}
			else {
				if (outVal > outputMax)outVal = outputMax;
				else if (outVal < outputMin)outVal = outputMin;
			}
		}
		return outVal;
	}

}
void RRTRobot::controller(Vector2f target)
{
	Vector2f error = (target - location);

	float m;
	float length = error.Length();
	if (length < RRT_converge) {
		m = ofMap(length, 0, RRT_converge, 0, RRT_mVal, false);
	}
	else {
		m = RRT_mVal;
	}

	error.Normalize();

	Vector2f temp = error*m;
	Vector2f steer = (temp - velocity);
	Vector2f steerNormalize = steer;
	steerNormalize.Normalize();

	float steerLength = steer.Length();

	steer = (steerLength <= maxForce.Length()) ?
		steer : (steerNormalize *RRT_mForce);

	addForce(steer);
}
//----------------------------------------------------------------------------
void RRTRobot::fillEnviroment(const std::list<RRTobstacles*> obst, 
	std::list<Nodes>& node)
{
	//check for enviroment
	for (auto index : obst) 
	{
		float dist = this->location.DistanceTo(index->loc());

		if (dist <= this->scanRadius + index->rad()) 
		{
			updateEnviroment(node, index);
		}
	}
}
//----------------------------------------------------------------------------
void RRTRobot::updateEnviroment(std::list<Nodes>& node, RRTobstacles *obst)
{
	std::list<Nodes>::iterator it = node.begin();
	while (it != node.end())
	{
		float dist = it->location.DistanceTo(obst->loc());
		if (dist <= obst->rad()) 
		{
			it->costToStart = inf;
			it->alive = false;
		}
		it++;
	}
}
//----------------------------------------------------------------------------