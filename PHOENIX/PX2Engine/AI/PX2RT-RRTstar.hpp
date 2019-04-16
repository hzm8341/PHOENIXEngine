// PX2RT-RRTstar.hpp

#ifndef PX2RT_RRTSTAR_HPP
#define PX2RT_RRTSTAR_HPP

#include "PX2RRTInformedstar.hpp"

namespace PX2
{

	class RRTRobot;

	class PX2_ENGINE_ITEM RTRRTstar : public InformedRRTstar
	{
	public:
		static std::set<Nodes*, nodes_compare> visited_set;
		static bool goalDefined;

	public:
		RTRRTstar();
		~RTRRTstar();

		void nextIter(std::list<Nodes> &nodes, const std::list<RRTobstacles*>& obst, RRTRobot* agent);
		std::list<Nodes*> currPath;

	private:
		void expandAndRewire(std::list<Nodes>& nodes, const std::list<RRTobstacles*>& obst);
		void updateNextBestPath();
		Nodes sample();
		Nodes* getClosestNeighbour(Nodes u, std::list<Nodes>& nodes);
		void addNode(Nodes n, Nodes* closest, std::list<Nodes>& nodes, const std::list<RRTobstacles*>& obst);
		void rewireRandomNode(const std::list<RRTobstacles*> &obst, std::list<Nodes> &nodes);
		void rewireFromRoot(const std::list<RRTobstacles*> &obst, std::list<Nodes> &nodes);
		float cost(Nodes* node);
		float getHeuristic(Nodes* u);
		void changeRoot(Nodes* nextPoint);
		bool isPathToGoalAvailable();

		std::list<Nodes*> rewireRand;
		std::list<Nodes*> rewireRoot;
		std::list<Nodes*> closestNeighbours;

		std::list<Nodes*> pushedToRewireRoot;

		float timeKeeper;
	};



}

#endif