// PX2RRTObstacle.hpp

#ifndef PX2RRTOBSTACLE_HPP
#define PX2RRTOBSTACLE_HPP

#include "PX2Vector2.hpp"
#include "PX2Float3.hpp"
#include "PX2Rect.hpp"

namespace PX2
{

	class PX2_ENGINE_ITEM RRTobstacles
	{
	public:
		RRTobstacles();
		RRTobstacles(Vector2f loc);
		~RRTobstacles();

		virtual void render();
		virtual Vector2f loc() { return location; }
		virtual float rad() { return radius; }
		float getX() { return location.X(); }
		float getY() { return location.Y(); }
		virtual  bool isCircle() { return true; }
		virtual bool isCollide(Vector2f, Vector2f);
		virtual bool isInside(Vector2f);

		float mass;
	
	private:
		Vector2f location, velocity, accelaration;
		float radius;
		Float3 color;
	};

	class PX2_ENGINE_ITEM RRTmovingObst : public RRTobstacles
	{
	public:
		RRTmovingObst();
		~RRTmovingObst();
		void render();

		Vector2f loc() { return this->location; }
		float rad() { return this->radius; }
		bool isCircle() { return true; }
		bool isCollide(Vector2f, Vector2f);
		bool isInside(Vector2f);

	private:
		Vector2f location, accelaration;
		float radius;
		Float3 color;
	};

	class PX2_ENGINE_ITEM RRTmaze :public RRTobstacles
	{
	public:
		RRTmaze(Vector2f loc);
		RRTmaze(Vector2f loc, float width, float height);
		~RRTmaze();
		void render();

		Vector2f loc();
		bool isCircle() { return false; }
		bool isCollide(Vector2f p1, Vector2f p2);
		bool isInside(Vector2f p);

	private:
		Float3 color;
		Vector2f location;
		float width, height;
		Rectf rect;
	};

}

#endif