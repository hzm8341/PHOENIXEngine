// PX2AIAgentPath.hpp

#ifndef PX2AIAGENTPATH_HPP
#define PX2AIAGENTPATH_HPP

#include "PX2CorePre.hpp"
#include "OpenSteer/Pathway.h"
#include "OpenSteer/OldPathway.h"
#include "PX2Vector3.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM AIAgentPath : private OpenSteer::Old::PolylinePathway
	{
		friend class AIAgent;

	public:
		const static size_t MAX_PATH_POINTS = 255;

		AIAgentPath();
		AIAgentPath( const std::vector<Vector3f> &points,
			const float radius, const bool cyclic);
		virtual ~AIAgentPath();

		AIAgentPath(const AIAgentPath& path);
		AIAgentPath& operator=(const AIAgentPath& path);

		int GetNumberOfPathPoints() const;

		float GetPathLength() const;

		void GetPathPoints(std::vector<Vector3f>& outPoints) const;
		float GetDistanceAlongPath(const Vector3f& position) const;
		Vector3f GetNearestPointOnPath(const Vector3f& position) const;
		Vector3f GetPointOnPath(const float distance) const;

		float GetRadius() const;
		unsigned int GetSegmentCount() const;
	};

}

#endif