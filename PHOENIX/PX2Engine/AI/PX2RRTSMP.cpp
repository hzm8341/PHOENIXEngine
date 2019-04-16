// PX2RRTSMP.cpp

#include "PX2RRTSMP.hpp"
#include "PX2RRTStarParam.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
bool SMP::goalFound = false;
bool SMP::sampledInGoalRegion = false;
bool SMP::moveNow = false;
Vector2f SMP::goal;
Vector2f SMP::start;
Nodes* SMP::targetNode = 0;
Nodes* SMP::nextTarget = 0;
Nodes* SMP::root = 0;
//----------------------------------------------------------------------------
SMP::SMP()
{
}
//----------------------------------------------------------------------------
SMP::~SMP()
{
}
//----------------------------------------------------------------------------
void SMP::addNode(Nodes n, std::list<Nodes>& nodes)
{
	nodes.push_back(n);
	Vector2f diff = n.location - goal;
	float dist = diff.Length();

	if (dist < RRT_converge)
	{
		goalFound = true;
		sampledInGoalRegion = true;
		targetNode = &(nodes.back());
	}
}
//----------------------------------------------------------------------------
Nodes* SMP::nearestNode(Nodes n, std::list<Nodes>& nodes)
{
	Vector2f diff = n.location - nodes.front().location;
	float distSquare = diff.SquaredLength();

	double min_dist = distSquare;
	Nodes* near_node = &(nodes.front());
	if (!nodes.empty())
	{
		std::list<Nodes>::iterator it = nodes.begin();
		while (it != nodes.end())
		{
			Vector2f diff1 = n.location - (*it).location;
			float distSquare1 = diff1.SquaredLength();

			if (distSquare1 < min_dist)
			{
				min_dist = distSquare1;
				near_node = &(*it);
			}
			it++;
		}
		return near_node;
	}
	else
		return 0;
}
//----------------------------------------------------------------------------
Nodes* SMP::nearestNode(Nodes n, std::list<Nodes*>& nodes)
{
	Vector2f diff = n.location - nodes.front()->location;
	float distSquare = diff.SquaredLength();

	double min_dist = distSquare;
	Nodes* near_node = (nodes.front());
	if (!nodes.empty())
	{
		std::list<Nodes*>::iterator it = nodes.begin();
		while (it != nodes.end())
		{
			Vector2f diff1 = n.location - (*it)->location;
			float distSquare1 = diff1.SquaredLength();

			if (distSquare1 < min_dist)
			{
				min_dist = distSquare1;
				near_node = (*it);
			}
			it++;
		}
		return near_node;
	}
	else
		return 0;
}
//----------------------------------------------------------------------------
Nodes SMP::sampler()
{
	float x = Mathf::IntervalRandom(-10.0f, 10.0f);
	float y = Mathf::IntervalRandom(-10.0f, 10.0f);
	Nodes new_node;
	new_node.location.X() = x;
	new_node.location.Y() = y;
	return new_node;
}
//----------------------------------------------------------------------------
bool SMP::checkCollision(Nodes n1, Nodes n2, std::list<RRTobstacles*> obst)
{
	for (auto i : obst) {
		if (i->isCollide(n1.location, n2.location)) 	return false;
	}
	return true;
}
//----------------------------------------------------------------------------
bool SMP::checkSample(Nodes n, std::list<RRTobstacles*> obst)
{
	for (auto i : obst) {
		if (i->isInside(n.location)) return false;
	}
	return true;
}
//----------------------------------------------------------------------------