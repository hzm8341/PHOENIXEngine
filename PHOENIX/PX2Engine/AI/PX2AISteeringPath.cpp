// PX2AISteeringPath.cpp

#include "PX2AISteeringPath.hpp"
#include "PX2Math.hpp"
#include "PX2Matrix2.hpp"
#include "PX2EngineSceneCanvas.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
void AIAgentPath::AddWayPoint(const APoint &new_point)
{
	mWayPoints.push_back(Vector3f(new_point.X(), new_point.Y(), 0.0f));
}
//----------------------------------------------------------------------------
void AIAgentPath::Update()
{
	if ((int)mWayPoints.size() > 0)
	{
		std::list<Vector3f>::const_iterator it = mWayPoints.begin();
		Vector3f wp = *it++;
		while (it != mWayPoints.end())
		{
			EngineSceneCanvas::GetSingleton().AddDebugLine(wp, *it,
				Float4::RED);

			wp = *it++;
		}

		if (m_bLooped)
		{
			EngineSceneCanvas::GetSingleton().AddDebugLine(*(--it),
				*mWayPoints.begin(), Float4::RED);
		}
	}
}
//----------------------------------------------------------------------------