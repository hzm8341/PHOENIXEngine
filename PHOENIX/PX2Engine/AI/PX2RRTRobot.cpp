// PX2RRTRobot.cpp

#include "PX2RRTRobot.hpp"
#include "PX2RRTStarParam.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
void RRTRobot::setup()
{
	alive = true;
	mass = 5.0; 
	scanObstRadius = RRT_sensorScanObstRadius;
	location = Vector2f::ZERO;
	HOME = location;
	
	color = Float3(50, 145, 80);
}
//----------------------------------------------------------------------------
void RRTRobot::setup(Vector2f loc)
{
	alive = true;
	mass = 5.0;
	scanObstRadius = RRT_sensorScanObstRadius;
	location = loc;
	HOME = location;

	color = Float3(50, 145, 80 );
}
//----------------------------------------------------------------------------
void RRTRobot::setPos(const Vector2f &pos)
{
	location = pos;
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
//----------------------------------------------------------------------------
void RRTRobot::fillEnviroment(const std::list<RRTobstacles*> obst, 
	std::list<Nodes>& node)
{
	for (auto index : obst) 
	{
		float dist = this->location.DistanceTo(index->loc());

		if (dist <= this->scanObstRadius + index->rad()) 
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