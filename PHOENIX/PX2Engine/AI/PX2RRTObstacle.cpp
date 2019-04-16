// PX2RRTObstacle.cpp

#include "PX2RRTObstacle.hpp"
#include "PX2RRTStarParam.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
// RRTobstacles
//----------------------------------------------------------------------------
RRTobstacles::RRTobstacles()
{
	float x = Mathf::IntervalRandom(4, 10.0f);
	float y = Mathf::IntervalRandom(4, 10.0f);
	location = Vector2f(x, y);
	radius = 0.3f;
	color = { 200,50,10 };
	mass = 3.14*radius*radius;
}
//----------------------------------------------------------------------------
RRTobstacles::RRTobstacles(Vector2f loc)
{
	location = loc;
	radius = 10.0f;
	color = { 200,50,10 };
	mass = 3.14*radius*radius;
}
//----------------------------------------------------------------------------
RRTobstacles::~RRTobstacles()
{
}
//----------------------------------------------------------------------------
void RRTobstacles::SetPos(const Vector2f &pos)
{
	location = pos;
}
//----------------------------------------------------------------------------
void RRTobstacles::render()
{
}
//----------------------------------------------------------------------------
bool RRTobstacles::isCollide(Vector2f n1, Vector2f n2)
{
	float x1 = n1.X();
	float x2 = n2.X();
	float y1 = n1.Y();
	float y2 = n2.Y();

	float xo = location.X();
	float yo = location.Y();
	float lambda = std::pow((x1 - x2), 2) + std::pow((y1 - y2), 2);
	float t = (std::pow(x1, 2) + x2 * xo - x1*(x2 + xo) - (yo - y1)*(y1 - y2)) / lambda;
	float shortest_dist;
	if (t >= 0 && t <= 1) // If the perpendicular distance lies on the line 'segment' connecting point_1 and point_2
		shortest_dist = std::sqrt(std::pow((x2 * (y1 - yo) + x1 * (yo - y2) + xo * (y2 - y1)), 2) / lambda);
	else  // If not then only check for the end-points of the segment for the collision
	{
		float d1 = std::sqrt(std::pow((x1 - xo), 2) + std::pow((y1 - yo), 2));
		float d2 = std::sqrt(std::pow((x2 - xo), 2) + std::pow((y2 - yo), 2));
		shortest_dist = std::min(d1, d2);
	}

	if (shortest_dist < radius) 	return true;
	return false;
}
//----------------------------------------------------------------------------
bool RRTobstacles::isInside(Vector2f n)
{
	Vector2f diff = n - location;
	float dist = diff.Length();
	return (dist <= radius);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// RRTmovingObst
//----------------------------------------------------------------------------
RRTmovingObst::RRTmovingObst()
{
	radius = 0.3f;
	mass = 3.14*radius*radius;
	color = { 200,100,20 };
}
//----------------------------------------------------------------------------
RRTmovingObst::~RRTmovingObst()
{
}
//----------------------------------------------------------------------------
void RRTmovingObst::render()
{
}
//----------------------------------------------------------------------------
bool RRTmovingObst::isCollide(Vector2f n1, Vector2f n2)
{
	float x1 = n1.X();
	float x2 = n2.X();
	float y1 = n1.Y();
	float y2 = n2.Y();

	float xo = location.X();
	float yo = location.Y();
	float lambda = std::pow((x1 - x2), 2) + std::pow((y1 - y2), 2);
	float t = (std::pow(x1, 2) + x2 * xo - x1*(x2 + xo) - (yo - y1)*(y1 - y2)) / lambda;
	float shortest_dist;
	if (t >= 0 && t <= 1) // If the perpendicular distance lies on the line 'segment' connecting point_1 and point_2
	{
		shortest_dist = std::sqrt(std::pow((x2 * (y1 - yo) + x1 * (yo - y2) + xo * (y2 - y1)), 2) / lambda);
	}
	else  // If not then only check for the end-points of the segment for the collision
	{
		float d1 = std::sqrt(std::pow((x1 - xo), 2) + std::pow((y1 - yo), 2));
		float d2 = std::sqrt(std::pow((x2 - xo), 2) + std::pow((y2 - yo), 2));
		shortest_dist = std::min(d1, d2);
	}

	if (shortest_dist < radius) 
		return true;
	
	return false;
}
//----------------------------------------------------------------------------
bool RRTmovingObst::isInside(Vector2f n)
{
	Vector2f dir = n - location;
	float length = dir.Length();

	return (length <= radius);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// RRTmaze
//----------------------------------------------------------------------------
RRTmaze::RRTmaze(Vector2f loc)
{
	location = loc;
	color = { 10,10,50 };
	rect.Set(100.0f, 100.0f, 100.0f, 100.0f);
	mass = 1000;
}
//----------------------------------------------------------------------------
RRTmaze::RRTmaze(Vector2f loc, float width, float height)
{
	location = loc;
	color = { 10,10,50 };
	rect.Set(loc.X(), loc.Y(), loc.X()+width, loc.Y()+height);
	mass = 1000;
}
//----------------------------------------------------------------------------
RRTmaze::~RRTmaze()
{
}
//----------------------------------------------------------------------------
void RRTmaze::render()
{
}
//----------------------------------------------------------------------------
Vector2f RRTmaze::loc()
{
	Vector2f temp(rect.Width(), rect.Height());
	return location + temp;
}
//----------------------------------------------------------------------------
bool RRTmaze::isCollide(Vector2f p1, Vector2f p2)
{
	Rectf other(p1.X(), p1.Y(), p2.X(), p2.Y());
	return rect.IsIntersect(other);
}
//----------------------------------------------------------------------------
bool RRTmaze::isInside(Vector2f p)
{
	Float2 pos(p.X(), p.Y());
	return rect.IsInsize(pos);
}
//----------------------------------------------------------------------------