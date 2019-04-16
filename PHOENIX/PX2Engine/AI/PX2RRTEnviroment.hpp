// PX2RRTEnviroment.hpp

#ifndef PX2RRTENVIROMENT_HPP
#define PX2RRTENVIROMENT_HPP

#include "PX2CorePre.hpp"
#include "PX2Vector2.hpp"
#include "PX2RRTRobot.hpp"
#include "PX2RT-RRTstar.hpp"

namespace PX2
{

	class Robot;

	class PX2_ENGINE_ITEM Enviroment
	{
	public:
		Enviroment() { setup(); };
		Enviroment(Vector2f _start) { setup(_start); };
		~Enviroment() {};

		void setup();
		void setup(Vector2f _start);
		void update(RRTRobot * car, std::list<RRTobstacles*> obst, Robot *robot);
		void targetSet(Vector2f loc);

		int numofnode() { return (int)nodes.size(); };

		bool grid = false;
		bool goalin = false;

	protected:
		std::list<Nodes> nodes;
		std::list<Nodes*> path;
		RTRRTstar rtrrtstar;
		bool rrtFlag = true;
		bool isHasPlanNow = true;

		Vector2f goal;
		Vector2f home;
	};

}

#endif