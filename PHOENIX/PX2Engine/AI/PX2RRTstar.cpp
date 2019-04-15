// PX2RRTstar.cpp

#include "PX2RRTstar.hpp"
#include "PX2RRTStarParam.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
// RRTstar
//----------------------------------------------------------------------------
RRTstar::RRTstar()
{
}
//----------------------------------------------------------------------------
void RRTstar::nextIter(std::list<Nodes>& nodes, std::list<RRTobstacles*> obst,
	Nodes* u_)
{
	Nodes u;
	if (u_ == 0)
		u = SMP::sampler();
	else
		u = *u_;

	Nodes* v = SMP::nearestNode(u, nodes);
	float dist = u.location.DistanceTo((*v).location);

	if (dist > RRT_epsilon)
	{
		float x_n = v->location.X() + (u.location.X() - v->location.X())  * RRT_epsilon / dist;
		float y_n = v->location.Y() + (u.location.Y() - v->location.Y())  * RRT_epsilon / dist;
		u.location.X() = x_n;
		u.location.Y() = y_n;
	}
	if (!SMP::checkSample(u, obst)) return;

	std::list<Nodes*> closestNeighbours;
	closestNeighbours = RRTstar::findClosestNeighbours(u, nodes);

	if (closestNeighbours.empty()) return;

	std::list<Nodes*>::iterator it = closestNeighbours.begin();
	std::list<Nodes*> safeNeighbours;
	while (it != closestNeighbours.end())
	{
		if (SMP::checkCollision(u, *(*it), obst))
			safeNeighbours.push_back(*it);
		it++;
	}
	if (safeNeighbours.empty()) return;

	it = safeNeighbours.begin();

	float minDist = (*it)->costToStart + u.location.DistanceTo((*it)->location);
	auto index = it;

	while (it != safeNeighbours.end())
	{
		float dist1 = (*it)->costToStart + u.location.DistanceTo((*it)->location);
		if (dist1 < minDist) {
			minDist = dist1;
			index = it;
		}
		it++;
	}
	u.parent = *index;
	u.costToStart = minDist;

	SMP::addNode(u, nodes);

	safeNeighbours.remove(*index);

	// Bring the iterator to initial position again
	it = safeNeighbours.begin();
	while (it != safeNeighbours.end())
	{
		float dist1 = u.costToStart + u.location.DistanceTo((*it)->location);
		if ((*it)->costToStart > dist1)
		{
			(*it)->prevParent = (*it)->parent;
			(*it)->parent = &(nodes.back());
			(*it)->costToStart = dist1;
		}
		it++;
	}

}
//----------------------------------------------------------------------------
std::list<Nodes*> RRTstar::findClosestNeighbours(Nodes u, std::list<Nodes>& nodes)
{
	std::list<Nodes*> closestNeighbours;
	std::list<Nodes>::iterator it = nodes.begin();

	while (it != nodes.end())
	{
		float f = u.location.DistanceTo(it->location);
		if (f < RRT_starradius && f > 0.0001)
		{
			closestNeighbours.push_back(&(*it));
		}
		it++;
	}
	return closestNeighbours;
}
//----------------------------------------------------------------------------