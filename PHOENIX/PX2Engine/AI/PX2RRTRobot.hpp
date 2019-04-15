// PX2RRTRobot.hpp

#ifndef PX2RRTROBOT_HPP
#define PX2RRTROBOT_HPP

#include "PX2CorePre.hpp"
#include "PX2Vector2.hpp"
#include "PX2RRTObstacle.hpp"
#include "PX2RRTnodeStruct.hpp"

namespace PX2
{

	class RRTRobot
	{
	public:
		//--------------------------------------------------------------Function
		// Default constructor  
		RRTRobot() { setup(); }
		RRTRobot(Vector2f loc) { setup(loc); }
		// Default destructor  
		~RRTRobot() {};
		void setup();
		void setup(Vector2f loc);
		void update();
			void render();
		void addForce(Vector2f force);
		void controller(Vector2f target);

		bool isAlive() { return alive; }
		float x() { return location.X(); }
		float y() { return location.Y(); }
		float accu() { return accuracy; }
		float getScanRadius() { return scanRadius; }
		Vector2f getLocation() { return location; }
		Float3 getColor() { return color; }
		void fillEnviroment(const std::list<RRTobstacles*> obst, std::list<Nodes> &node);
		void updateEnviroment(std::list<Nodes> &node, RRTobstacles *obst);

	private:
		bool alive;
		float scanRadius, mass, accuracy;

		Float3 color;
		Vector2f HOME, location, velocity, accelaration, maxVelocity, maxForce;
		Vector2f pt;
	};

}

#endif