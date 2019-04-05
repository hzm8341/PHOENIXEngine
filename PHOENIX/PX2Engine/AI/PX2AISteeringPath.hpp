// PX2AISteeringPath.hpp

#ifndef PX2AISTEERINGPATH_HPP
#define PX2AISTEERINGPATH_HPP

#include "PX2CorePre.hpp"
#include "PX2Vector3.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM Path
	{
	public:
		Path() :m_bLooped(false) {}

		Vector3f CurrentWaypoint()const { return *curWaypoint; }
		bool Finished() { return !(curWaypoint != m_WayPoints.end()); }
		inline void SetNextWaypoint();

		void LoopOn() { m_bLooped = true; }
		void LoopOff() { m_bLooped = false; }

		void AddWayPoint(Vector3f new_point);

		void Set(std::list<Vector3f> new_path) { m_WayPoints = new_path; curWaypoint = m_WayPoints.begin(); }
		void Set(const Path& path) { m_WayPoints = path.GetPath(); curWaypoint = m_WayPoints.begin(); }

		void Clear() { m_WayPoints.clear(); }

		std::list<Vector3f> GetPath()const { return m_WayPoints; }

		void Render()const;

	private:
		std::list<Vector3f> m_WayPoints;
		std::list<Vector3f>::iterator  curWaypoint;
		bool m_bLooped;

	};
	//----------------------------------------------------------------------------
	inline void Path::SetNextWaypoint()
	{
		assert(m_WayPoints.size() > 0);

		if (++curWaypoint == m_WayPoints.end())
		{
			if (m_bLooped)
			{
				curWaypoint = m_WayPoints.begin();
			}
		}
	}
	//----------------------------------------------------------------------------

}

#endif