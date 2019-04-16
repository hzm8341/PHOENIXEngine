// PX2RRTEnviroment.cpp

#include "PX2RRTEnviroment.hpp"
#include "PX2RRTStarParam.hpp"
#include "PX2Robot.hpp"
#include "PX2EngineSceneCanvas.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
inline void Enviroment::setup()
{
	home = Vector2f(RRT_startx, RRT_starty);
	Nodes start(RRT_startx, RRT_starty, 0);
	this->nodes.clear();
	this->nodes.push_back(start);

	goal = Vector2f(RRT_goalx, RRT_goaly);
	SMP::goal = goal;
	SMP::root = &(this->nodes.front());

	SMP::start = Vector2f(RRT_startx, RRT_starty);
	SMP::goalFound = false;
}
//----------------------------------------------------------------------------
inline void Enviroment::setup(Vector2f _start)
{
	home = _start;

	Nodes start(home.X(), home.Y(), 0);
	this->nodes.clear();
	this->nodes.push_back(start);

	SMP::root = &(this->nodes.front());
	SMP::goal = goal;
	goal = Vector2f(RRT_goalx, RRT_goaly);
	SMP::start = Vector2f(RRT_startx, RRT_starty);
	SMP::goalFound = false;
}
//----------------------------------------------------------------------------
inline void Enviroment::update(RRTRobot *car, std::list<RRTobstacles*> obst,
	Robot *robot)
{
	if (car->getLocation().DistanceTo(SMP::goal) < RRT_converge)
		isHasPlanNow = false;

	if (isHasPlanNow)
	{
		car->fillEnviroment(obst, nodes);
		Vector2f target = SMP::root->location;
		AIAgent *agent = robot->GetAIAgent();
		if (agent)
			agent->SetTarget(APoint(target.X(), target.Y(), 0.0f));
	}

	rtrrtstar.nextIter(nodes, obst, car);

	if (isHasPlanNow && SMP::targetNode != 0)
	{
		path = rtrrtstar.currPath;
		rtrrtstar.currPath.clear();
	}

	EngineSceneCanvas *esc = EngineSceneCanvas::GetSingletonPtr();
	if (esc)
	{
		for (auto i : this->nodes)
		{
			if (i.costToStart == inf)
			{

			}

			if (i.parent != NULL) 
			{
				APoint from(i.location.X(), i.location.Y(), 0.05f);
				APoint to(i.parent->location.X(), i.parent->location.Y(), 0.05f);
				esc->AddDebugLine(from, to, Float4::BLUE);
			}
		}
	}

	if (!path.empty())
	{
		for (auto i : path) 
		{
			if (i->parent != 0) 
			{
				APoint from(i->location.X(), i->location.Y(), 0.2f);
				APoint to(i->parent->location.X(), i->parent->location.Y(), 0.2f);
				esc->AddDebugLine(from, to, Float4::RED);
			}
		}
	}
}
//----------------------------------------------------------------------------
inline void Enviroment::targetSet(Vector2f loc)
{
	goal = loc;
	SMP::goal = goal;
	RTRRTstar::goalDefined = true;

	isHasPlanNow = true;
	std::list<Nodes>::iterator it = nodes.begin();
	while (it != nodes.end())
	{
		if ((*it).location.DistanceTo(loc) < RRT_converge)
		{
			SMP::targetNode = &(*it);
			return;
		}
		it++;
	}
	SMP::goalFound = false;
	SMP::targetNode = 0;
	path.clear();
	goalin = true;
}
//----------------------------------------------------------------------------