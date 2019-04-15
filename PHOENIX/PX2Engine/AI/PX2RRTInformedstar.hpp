// PX2RRTInformedstar.hpp

#ifndef PX2RRTINFORMEDSTAR_HPP
#define PX2RRTINFORMEDSTAR_HPP

#include "PX2CorePre.hpp"
#include "PX2RRTstar.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM InformedRRTstar : public RRTstar
	{
	public:
		void nextIter(std::list<Nodes> &nodes, std::list<RRTobstacles*> obst);
		static Nodes sample(float c_max);
		static bool usingInformedRRTstar;

	protected:
		std::list<Nodes*> sol_nodes;
	};

}

#endif