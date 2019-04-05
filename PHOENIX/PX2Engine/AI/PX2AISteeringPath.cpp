// PX2AISteeringPath.cpp

#include "PX2AISteeringPath.hpp"
#include "PX2Math.hpp"
#include "PX2Matrix2.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
void AIAgentPath::AddWayPoint(const APoint &new_point)
{
	mWayPoints.push_back(Vector3f(new_point.X(), new_point.Y(), 0.0f));
}
//----------------------------------------------------------------------------
void AIAgentPath::Render()const
{
	//gdi->OrangePen();

	//std::list<Vector3f>::const_iterator it = mWayPoints.begin();

	//Vector3f wp = *it++;

	//while (it != mWayPoints.end())
	//{
	//	gdi->Line(wp, *it);

	//	wp = *it++;
	//}

	//if (m_bLooped) gdi->Line(*(--it), *mWayPoints.begin());
}
//----------------------------------------------------------------------------