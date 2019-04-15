// PX2RRTstar.hpp

#ifndef PX2RRTSTAR_HPP
#define PX2RRTSTAT_HPP

#include "PX2CorePre.hpp"
#include "PX2RRTSMP.hpp"

namespace PX2
{

	class RRTobstacles;

	class PX2_ENGINE_ITEM RRTstar : public SMP
	{
	public:
		RRTstar();

		virtual void nextIter(std::list<Nodes> &nodes, 
			std::list<RRTobstacles*> obst, Nodes* u_ = 0);
		static std::list<Nodes*> findClosestNeighbours(Nodes n, 
			std::list<Nodes>& nodes);
	};

}

#endif