// PX2RRTnodeStruct.hpp

#ifndef PX2RRTNODESTRUCT_HPP
#define PX2RRTNODESTRUCT_HPP

#include "PX2CorePre.hpp"
#include "PX2Vector2.hpp"
#include "PX2Float3.hpp"

namespace PX2
{

	struct PX2_ENGINE_ITEM Nodes
	{
		Vector2f location;

		Nodes *parent, *prevParent = NULL;

		bool alive = true;
		Float3 color = { 10, 12, 160 };
		float costToStart;
		std::list<Nodes*> children;
		Nodes()
		{

		}
		Nodes(float x_, float y_, float costToStart_, Nodes* p_ = NULL)
		{
			location.X() = x_;
			location.Y() = y_;
			costToStart = costToStart_;
			parent = p_;
		}
	};

}

#endif