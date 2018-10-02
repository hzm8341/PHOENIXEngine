// PX2AIAgentPath.hpp

#ifndef PX2AIAGENTPATH_HPP
#define PX2AIAGENTPATH_HPP

#include "PX2CorePre.hpp"
#include "OpenSteer/OldPathway.h"
#include "PX2APoint.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM AIAgentPath : public OpenSteer::Old::PolylinePathway
	{
		friend class AIAgent;

	public:
		const static size_t MAX_PATH_POINTS = 255;

		AIAgentPath();
		AIAgentPath( const std::vector<APoint> &points, float radius,
			bool cyclic);
		virtual ~AIAgentPath();

		AIAgentPath(const AIAgentPath& path);
		AIAgentPath& operator=(const AIAgentPath& path);

		// config
		void AddPoint(const APoint &pt);
		void ConfigPoints(float radius, bool cyclic);

		int GetNumberOfPathPoints() const;

		float GetPathLength() const;

		void GetPathPoints(std::vector<APoint>& outPoints) const;
		float GetDistanceAlongPath(const APoint& position) const;
		APoint GetNearestPointOnPath(const APoint& position) const;
		APoint GetPointOnPath(const float distance) const;

		float GetRadius() const;
		unsigned int GetSegmentCount() const;

	private:
		std::vector<APoint> mPoints;
	};

}

#endif