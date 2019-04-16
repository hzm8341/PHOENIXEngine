// PX2RRTSamplingMotionPlanning.hpp

#ifndef PX2RRTSAMPLINGMOTIONPLANNING_HPP
#define PX2RRTSAMPLINGMOTIONPLANNING_HPP

#include "PX2CorePre.hpp"
#include "PX2RRTObstacle.hpp"
#include "PX2RRTnodeStruct.hpp"
#include "PX2Vector2.hpp"

namespace PX2
{

	struct PX2_ENGINE_ITEM nodes_compare 
	{

		bool operator() (const Nodes* lhs, const Nodes* rhs) const
		{
			if (lhs->location.X() != rhs->location.X())
				return lhs->location.X() < rhs->location.X();
			else
				return lhs->location.Y() < rhs->location.Y();
		}

	};

	class PX2_ENGINE_ITEM SMP
	{
	public:
		SMP();
		~SMP();

		static void addNode(Nodes n, std::list<Nodes>& nodes);
		static Nodes* nearestNode(Nodes n, std::list<Nodes>& nodes);
		static Nodes* nearestNode(Nodes n, std::list<Nodes*>& nodes);
		static bool checkCollision(Nodes n1, Nodes n2, std::list<RRTobstacles*> obst);
		static bool checkSample(Nodes n, std::list<RRTobstacles*> obst);
		static Nodes sampler();

		static bool goalFound;
		static bool sampledInGoalRegion;
		static Vector2f start;
		static Vector2f goal;
		static Nodes* SMP::root;
		static Nodes* SMP::targetNode;
		static Nodes* SMP::nextTarget;
	};

}

#endif