// PX2Rover.hpp

#include "PX2Rover.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
Rover::Rover() : WheeledRobot(
	77,     // wheelRadiusMillimeters
	165)
{
}
//----------------------------------------------------------------------------
Rover::~Rover()
{
}
//----------------------------------------------------------------------------
Velocities Rover::computeVelocities(long * odometry, Velocities & velocities)
{
	return WheeledRobot::computeVelocities(
		odometry[0],
		odometry[1],
		odometry[2]);
}
//----------------------------------------------------------------------------
double Rover::ticksToDegrees(double ticks)
{
	return ticks * (180. / this->TICKS_PER_CYCLE);
}
//----------------------------------------------------------------------------
void Rover::extractOdometry(
	double timestamp,
	double leftWheelOdometry,
	double rightWheelOdometry,
	double & timestampSeconds,
	double & leftWheelDegrees,
	double & rightWheelDegrees)
{
	timestampSeconds = timestamp / 1e6;
	leftWheelDegrees = ticksToDegrees(leftWheelOdometry);
	rightWheelDegrees = ticksToDegrees(rightWheelOdometry);
}
//----------------------------------------------------------------------------
void Rover::descriptorString(char * str)
{
	sprintf(str, "ticks_per_cycle=%d", this->TICKS_PER_CYCLE);
}
//----------------------------------------------------------------------------