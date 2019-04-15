// PX2RRTEnviroment.cpp

#include "PX2RRTEnviroment.hpp"
#include "PX2RRTStarParam.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
inline void Enviroment::setup()
{
	home = Vector2f(RRT_startx, RRT_starty);
	Nodes start(RRT_startx, RRT_starty, 0);
	this->nodes.push_back(start);

	SMP::root = &(this->nodes.front());

	SMP::start = Vector2f(RRT_startx, RRT_starty);
	SMP::goalFound = false;
}
//----------------------------------------------------------------------------
inline void Enviroment::setup(Vector2f _start)
{
	home = _start;

	Nodes start(home.X(), home.Y(), 0);
	this->nodes.push_back(start);

	SMP::root = &(this->nodes.front());
	goal = Vector2f(RRT_goalx, RRT_goaly);
	SMP::start = Vector2f(RRT_startx, RRT_starty);
	SMP::goalFound = false;
}
//----------------------------------------------------------------------------
inline void Enviroment::update(RRTRobot *car, std::list<RRTobstacles*> obst)
{
	if (car->getLocation().DistanceTo(SMP::goal) < RRT_converge)
		planner = false;

	if (planner)
	{
		car->fillEnviroment(obst, nodes);
		car->controller(SMP::root->location);
		car->update();
	}

	rtrrtstar.nextIter(nodes, obst, car);

	if (planner && SMP::target != NULL)
	{
		path = rtrrtstar.currPath;
		rtrrtstar.currPath.clear();
	}
}
//----------------------------------------------------------------------------
inline void Enviroment::targetSet(Vector2f loc)
{
	goal = loc;
	SMP::goal = goal;
	RTRRTstar::goalDefined = true;

	planner = true;
	std::list<Nodes>::iterator it = nodes.begin();
	while (it != nodes.end())
	{
		if ((*it).location.DistanceTo(loc) < RRT_converge)
		{
			SMP::target = &(*it);
			return;
		}
		it++;
	}
	SMP::goalFound = false;
	SMP::target = NULL;
	path.clear();
	goalin = true;
}
//----------------------------------------------------------------------------