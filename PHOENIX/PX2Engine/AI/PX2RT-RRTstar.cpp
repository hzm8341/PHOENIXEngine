// PX2RRTSamplingMotionPlanning.cpp

#include "PX2RT-RRTstar.hpp"
#include "PX2RRTStarParam.hpp"
#include "PX2RRTRobot.hpp"
#include "PX2Application.hpp"
using namespace PX2;

std::set<Nodes*, nodes_compare> RTRRTstar::visited_set;
bool RTRRTstar::goalDefined = false;
//----------------------------------------------------------------------------
RTRRTstar::RTRRTstar()
{
}
//----------------------------------------------------------------------------
RTRRTstar::~RTRRTstar()
{
}
//----------------------------------------------------------------------------
void RTRRTstar::nextIter(std::list<Nodes> &nodes,
	const std::list<RRTobstacles*>& obst, RRTRobot* agent)
{
	timeKeeper = PX2_APP.GetElapsedTime();
	expandAndRewire(nodes, obst);
	if (SMP::goalFound)
		updateNextBestPath();
	if (currPath.size() > 1 && agent->getLocation().DistanceTo(SMP::root->location) < 0.1)
	{
		//We have to pre-increment rather than post-increment
		Nodes* nextPoint = *((++currPath.begin())); //Change the DS for path to vector?
		changeRoot(nextPoint, nodes);

		RTRRTstar::visited_set.clear();
		pushedToRewireRoot.clear();
		rewireRoot.clear();
	}
	closestNeighbours.clear();
}
//----------------------------------------------------------------------------
void RTRRTstar::changeRoot(Nodes* nextPoint, std::list<Nodes>& nodes)
{
	nextPoint->children.push_back(SMP::root);
	nextPoint->parent = NULL;
	nextPoint->prevParent = NULL;
	nextPoint->costToStart = 0;

	SMP::root->parent = nextPoint;
	SMP::root->costToStart = SMP::root->location.DistanceTo(nextPoint->location);
	SMP::root = nextPoint;
}
//----------------------------------------------------------------------------
void RTRRTstar::expandAndRewire(std::list<Nodes>& nodes, 
	const std::list<RRTobstacles*>& obst)
{
	Nodes u = sample();
	Nodes* v = RTRRTstar::getClosestNeighbour(u, nodes);
	double dist = u.location.DistanceTo((*v).location);

	if (dist > RRT_epsilon)
	{
		float x_n = v->location.X() +
			(u.location.X() - v->location.X())  * RRT_epsilon / dist;
		float y_n = v->location.Y() +
			(u.location.Y() - v->location.Y())  * RRT_epsilon / dist;
		u.location.X() = x_n;
		u.location.Y() = y_n;
	}

	if (!SMP::checkSample(u, obst))
		return;

	if (SMP::checkCollision(u, *v, obst))
	{
		if (this->closestNeighbours.size() < RRT_maxNeighbours)
		{
			this->addNode(u, v, nodes, obst);
		}
		else
		{
			this->rewireRand.push_front(v);
		}
		rewireRandomNode(obst, nodes);
	}
	rewireFromRoot(obst, nodes);
}
//----------------------------------------------------------------------------
void RTRRTstar::updateNextBestPath()
{
	std::list<Nodes*> updatedPath;
	Nodes *pathNode = target;
	if (SMP::goalFound) {
		do
		{
			currPath.push_back(pathNode);
			pathNode = pathNode->parent;
		} while (pathNode != NULL);
		currPath.reverse();
		return;
	}
	else {
		if (!goalDefined)
			return;
		Nodes* curr_node = SMP::root;
		while (!curr_node->children.empty())
		{
			std::list<Nodes*>::iterator it = curr_node->children.begin();
			Nodes* tempNode = curr_node->children.front();
			float cost_ = cost(tempNode);
			float minCost = cost_ + getHeuristic(*it);
			while (it != curr_node->children.end()) {
				cost_ = cost(*it);
				float cost_new = cost_ + getHeuristic(*it);
				if (cost_new < minCost) {
					minCost = cost_new;
					tempNode = *it;
				}
				it++;
			}
			updatedPath.push_back(tempNode);
			if (tempNode->children.empty() || cost(tempNode) == inf)
			{
				visited_set.insert(tempNode);
				break;
			}
			curr_node = tempNode;
		}
		if (currPath.size() == 0)
			currPath.push_back(SMP::root);

		if (updatedPath.back()->location.DistanceTo(SMP::goal) <
			currPath.back()->location.DistanceTo(SMP::goal))
			currPath = updatedPath;
	}

}
//----------------------------------------------------------------------------
Nodes RTRRTstar::sample()
{
	float rand_num = Mathf::UnitRandom();

	if (rand_num > 1 - RRT_alpha && SMP::target != NULL)
	{
		float x = Mathf::IntervalRandom(SMP::root->location.X(), 
			SMP::target->location.X());
		float y = Mathf::IntervalRandom(SMP::root->location.Y(), 
			SMP::target->location.Y());
		Nodes new_node;
		new_node.location.X() = x;
		new_node.location.Y() = y;
		return new_node;
	}
	else if (rand_num >= (1 - RRT_alpha) / RRT_beta && SMP::goalFound)
	{
		return InformedRRTstar::sample(cost(SMP::target));
	}
	else
	{
		return SMP::sampler();
	}

}
//----------------------------------------------------------------------------
Nodes* RTRRTstar::getClosestNeighbour(Nodes u, std::list<Nodes>& nodes)
{
	double min_dist = u.location.SquaredDistanceTo(nodes.front().location);
	Nodes* near_node = &(nodes.front());
	std::list<Nodes>::iterator it = nodes.begin();

	/*float rrtstarradius = std::sqrt((ofGetWindowWidth() * ofGetWindowHeight() * maxNeighbours) / (3.146 * nodes.size()));
	if (rrtstarradius < minDistClosestNode)
	rrtstarradius = minDistClosestNode;*/

	while (it != nodes.end())
	{
		float dist = u.location.SquaredDistanceTo((*it).location);
		if (dist < min_dist)
		{
			min_dist = dist;
			near_node = &(*it);
		}
		if (u.location.DistanceTo(it->location) < RRT_starradius)
		{
			closestNeighbours.push_back(&(*it));
		}
		it++;
	}
	return near_node;
}
//----------------------------------------------------------------------------
void RTRRTstar::addNode(Nodes n, Nodes* closest, std::list<Nodes>& nodes, 
	const std::list<RRTobstacles*>& obst)
{
	Nodes* parent = closest;
	float c_min = cost(closest) + n.location.DistanceTo(closest->location);
	std::list<Nodes*>::iterator it = (this->closestNeighbours).begin();
	float c_new;
	while (it != closestNeighbours.end())
	{
		c_new = cost(*it) + n.location.DistanceTo((*it)->location);
		if (c_new < c_min && SMP::checkCollision(n, *(*it), obst))
		{
			c_min = c_new;
			parent = *it;
			n.costToStart = c_min;
		}
		it++;
	}
	n.parent = parent;
	nodes.push_back(n);
	parent->children.push_back(&(nodes.back()));

	if (n.location.DistanceTo(SMP::goal) < RRT_converge)
	{
		if (SMP::target == 0 || 
			(SMP::target != 0 && SMP::target->costToStart > n.costToStart))
		{
			SMP::target = &(nodes.back());
		}
		SMP::goalFound = true;
	}

	this->rewireRand.push_front(&(nodes.back()));
}
//----------------------------------------------------------------------------
float RTRRTstar::cost(Nodes* node)
{
	bool badNode = false;
	float cost_ = 0;
	Nodes* curr = node;
	while (curr->parent != NULL)
	{
		if (curr->parent->costToStart == inf)
		{
			node->costToStart = inf;
			badNode = true;
			break;
		}
		cost_ += curr->location.DistanceTo(curr->parent->location);
		curr = curr->parent;
	}
	if (badNode)
		return inf;
	else
	{
		node->costToStart = cost_;
		return cost_;
	}
}
//----------------------------------------------------------------------------
void RTRRTstar::rewireRandomNode(const list<RRTobstacles*> &obst,
	std::list<Nodes> &nodes)
{
	float elapsedTime = PX2_APP.GetElapsedTime();

	while (!rewireRand.empty() && (elapsedTime - timeKeeper)
		< 0.5 * RRT_allowedTimeRewiring)
	{
		Nodes* Xr = rewireRand.front();
		rewireRand.pop_front();

		std::list<Nodes*> nearNodes = RRTstar::findClosestNeighbours(*Xr, nodes);
		std::list<Nodes*>::iterator it = nearNodes.begin();
		std::list<Nodes*> safeNeighbours;
		while (it != nearNodes.end())
		{
			if (SMP::checkCollision(*Xr, *(*it), obst))
				safeNeighbours.push_back(*it);
			it++;
		}
		if (safeNeighbours.empty()) continue;

		it = safeNeighbours.begin();
		float cost_ = cost(Xr);
		while (it != safeNeighbours.end())
		{

			float oldCost = cost(*it);
			float newCost = cost_ + Xr->location.DistanceTo((*it)->location);
			if (newCost < oldCost)
			{

				(*it)->prevParent = (*it)->parent;
				(*it)->parent->children.remove(*it);
				(*it)->parent = Xr;
				(*it)->costToStart = newCost;
				Xr->children.push_back(*it);
				rewireRand.push_back(*it);
			}
			it++;
		}
	}
}
//----------------------------------------------------------------------------
void RTRRTstar::rewireFromRoot(const list<RRTobstacles*> &obst, 
	std::list<Nodes> &nodes) {

	float elapsedTime = PX2_APP.GetElapsedTime();

	if (rewireRoot.empty()) {
		rewireRoot.push_back(SMP::root);
	}

	while (!rewireRoot.empty() && (elapsedTime - timeKeeper) < RRT_allowedTimeRewiring)
	{
		Nodes* Xs = rewireRoot.front();
		rewireRoot.pop_front();
		std::list<Nodes*> nearNeighbours;
		nearNeighbours = RRTstar::findClosestNeighbours(*Xs, nodes);

		std::list<Nodes*>::iterator it = nearNeighbours.begin();
		std::list<Nodes*> safeNeighbours;
		while (it != nearNeighbours.end())
		{
			if (SMP::checkCollision(*Xs, *(*it), obst))
				safeNeighbours.push_back(*it);
			it++;
		}
		if (safeNeighbours.empty()) continue;

		safeNeighbours.remove(Xs->parent);
		it = safeNeighbours.begin();
		while (it != safeNeighbours.end()) {

			float oldCost = cost(*it);
			float newCost = cost(Xs) + Xs->location.DistanceTo((*it)->location);
			if (newCost < oldCost) {

				(*it)->prevParent = (*it)->parent;
				(*it)->parent->children.remove(*it);
				(*it)->parent = Xs;
				(*it)->costToStart = newCost;
				Xs->children.push_back(*it);
			}
			//TODO: take care of restarting the queue part
			bool found = std::find(pushedToRewireRoot.begin(), pushedToRewireRoot.end(), (*it)) != pushedToRewireRoot.end();
			if (!found) {
				rewireRoot.push_back((*it));
				pushedToRewireRoot.push_back((*it));
			}
			it++;
		}
	}
}
//----------------------------------------------------------------------------
float RTRRTstar::getHeuristic(Nodes* u) {
	if (visited_set.find(u) != visited_set.end())
		return inf;
	else
		return u->location.DistanceTo(SMP::goal);
}
//----------------------------------------------------------------------------
//method not used
bool RTRRTstar::isPathToGoalAvailable()
{
	if (!SMP::goalFound)
		return false;

	std::list<Nodes*> tempPath = currPath;
	tempPath.reverse();
	Nodes* curr = tempPath.front();
	while (curr->parent != NULL)
	{
		if (curr->parent->costToStart == inf)
		{
			return false;
		}
		curr = curr->parent;
	}
	return true;
}
//----------------------------------------------------------------------------