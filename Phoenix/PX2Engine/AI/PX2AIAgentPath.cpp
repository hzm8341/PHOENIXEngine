// PX2AIAgentPath.cpp

#include "PX2AIAgentPath.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
AIAgentPath::AIAgentPath() : 
PolylinePathway()
{
}
//----------------------------------------------------------------------------
AIAgentPath::AIAgentPath(const std::vector<Vector3f> &points,
	const float radius, const bool cyclic)
{
	OpenSteer::Vec3 vec3Point[MAX_PATH_POINTS];

	assert(points.size() < MAX_PATH_POINTS);

	std::vector<Vector3f>::const_iterator it;
	int count = 0;

	for (it = points.begin(); it != points.end(); ++it)
	{
		const Vector3f& vec = *it;

		vec3Point[count].x = vec.X();
		vec3Point[count].y = vec.Y();
		vec3Point[count].z = vec.Z();

		++count;
	}

	initialize(count, vec3Point, static_cast<float>(radius), cyclic);
}
//----------------------------------------------------------------------------
AIAgentPath::~AIAgentPath()
{
}
//----------------------------------------------------------------------------
AIAgentPath::AIAgentPath(const AIAgentPath& path)
{
	initialize(path.pointCount, path.points, path.radius, path.cyclic);
}
//----------------------------------------------------------------------------
AIAgentPath& AIAgentPath::operator=(const AIAgentPath& path)
{
	initialize(path.pointCount, path.points, path.radius, path.cyclic);
	return *this;
}
//----------------------------------------------------------------------------
int AIAgentPath::GetNumberOfPathPoints() const
{
	return pointCount;
}
//----------------------------------------------------------------------------
float AIAgentPath::GetPathLength() const
{
	return (float)totalPathLength;
}
//----------------------------------------------------------------------------
void AIAgentPath::GetPathPoints(std::vector<Vector3f>& outPoints) const
{
	outPoints.clear();

	const size_t pathPoints = GetNumberOfPathPoints();

	for (size_t index = 0; index < pathPoints; ++index)
	{
		const OpenSteer::Vec3& vec3 = points[index];
		outPoints.push_back(Vector3f(vec3.x, vec3.y, vec3.z));
	}
}
//----------------------------------------------------------------------------
float AIAgentPath::GetDistanceAlongPath(const Vector3f& position) const
{
	const OpenSteer::Vec3 vec3(position.X(), position.Y(), position.Z());

	return const_cast<AIAgentPath*>(this)->mapPointToPathDistance(vec3);
}
//----------------------------------------------------------------------------
Vector3f AIAgentPath::GetNearestPointOnPath(const Vector3f& position) const
{
	const OpenSteer::Vec3 vec3(position.X(), position.Y(), position.Z());
	OpenSteer::Vec3 tangent;
	float outside;

	const OpenSteer::Vec3 pointOnPath =
		const_cast<AIAgentPath*>(this)->mapPointToPath(vec3, tangent, outside);

	return Vector3f(pointOnPath.x, pointOnPath.y, pointOnPath.z);
}
//----------------------------------------------------------------------------
Vector3f AIAgentPath::GetPointOnPath(const float distance) const
{
	const OpenSteer::Vec3 pointOnPath =
		const_cast<AIAgentPath*>(this)->mapPathDistanceToPoint(distance);

	return Vector3f(pointOnPath.x, pointOnPath.y, pointOnPath.z);
}
//----------------------------------------------------------------------------
float AIAgentPath::GetRadius() const
{
	return radius;
}
//----------------------------------------------------------------------------
unsigned int AIAgentPath::GetSegmentCount() const
{
	return static_cast<unsigned int>(pointCount)-1;
}
//----------------------------------------------------------------------------