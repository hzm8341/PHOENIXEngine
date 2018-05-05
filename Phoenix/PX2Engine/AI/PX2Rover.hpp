// PX2Rover.hpp

#ifndef PX2ROVER_HPP
#define PX2ROVER_HPP

#include "PX2CorePre.hpp"
#include "WheeledRobot.hpp"
#include "Velocities.hpp"
#include "Laser.hpp"

static const int SCAN_SIZE = 360;

namespace PX2
{

	class PX2_ENGINE_ITEM Rover : public WheeledRobot
	{
	public:
		Rover();
		virtual ~Rover();

		Velocities computeVelocities(long * odometry, Velocities & velocities);
		void extractOdometry(
			double timestamp,
			double leftWheelOdometry,
			double rightWheelOdometry,
			double & timestampSeconds,
			double & leftWheelDegrees,
			double & rightWheelDegrees);

		double ticksToDegrees(double ticks);
		void descriptorString(char * str);

		static const int TICKS_PER_CYCLE = 2000;
	};

	class PX2_ENGINE_ITEM MinesURG04LX : public Laser
	{

	public:

		MinesURG04LX(void) : Laser(SCAN_SIZE, 6.2, 360, 6000, 0, 0)
		{}
	};

}

#endif