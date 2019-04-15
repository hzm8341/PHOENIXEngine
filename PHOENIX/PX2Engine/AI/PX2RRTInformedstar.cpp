// PX2RRTInformedstar.cpp

#include "PX2RRTInformedstar.hpp"
using namespace PX2;

bool InformedRRTstar::usingInformedRRTstar = false;
//----------------------------------------------------------------------------
void InformedRRTstar::nextIter(std::list<Nodes> &nodes,
	std::list<RRTobstacles*> obst)
{
	if (sol_nodes.empty())
	{
		RRTstar::nextIter(nodes, obst);
	}
	else
	{
		float min_cost = sol_nodes.front()->costToStart;
		std::list<Nodes*>::iterator it = sol_nodes.begin();
		while (it != sol_nodes.end())
		{
			if ((*it)->costToStart < min_cost)
			{
				min_cost = (*it)->costToStart;
				SMP::target = *it;
			}
			it++;
		}

		Nodes nodes1 = InformedRRTstar::sample(min_cost);
		RRTstar::nextIter(nodes, obst, &nodes1);
	}
	if (SMP::sampledInGoalRegion)
		sol_nodes.push_back(&nodes.back());
}
//----------------------------------------------------------------------------
Nodes InformedRRTstar::sample(float c_max)
{
	float c_min = SMP::goal.DistanceTo(SMP::start);

	if (std::abs(c_max - c_min) < 100 && usingInformedRRTstar)
		SMP::moveNow = true;

	Vector2f x_centre = (SMP::start + SMP::goal) / 2;
	Vector2f dir = SMP::goal - SMP::start;
	dir.Normalize();
	float angle = std::atan2(-dir.Y(), dir.X());
	float r1 = c_max / 2;
	float r2 = std::sqrt(std::pow(c_max, 2) - std::pow(c_min, 2)) / 2;

	float x = Mathf::SymmetricRandom();
	float y = Mathf::SymmetricRandom();

	float x2 = x * r1 * std::cos(angle) + y * r2 * std::sin(angle);
	float y2 = -x * r1 * std::sin(angle) + y * r2 * std::cos(angle);

	Vector2f rot_sample, rot_trans_sample;
	rot_sample = Vector2f(x2, y2);
	rot_trans_sample = rot_sample + x_centre;

	Nodes n;
	n.location.X() = rot_trans_sample.X();
	n.location.Y() = rot_trans_sample.Y();

	return n;
}
//----------------------------------------------------------------------------