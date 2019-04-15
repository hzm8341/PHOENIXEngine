// PX2RRTStartParam.hpp
//https://github.com/rishabh1b/RealTimePathPlanning

#ifndef PX2RRTSTARPARAM_HPP
#define PX2RRTSTARPARAM_HPP

#include "PX2Core.hpp"

const float inf = std::numeric_limits<float>::infinity();

#define RRT_converge 0.1
#define RRT_epsilon 25
#define RRT_starradius 100

#define RRT_allowedTimeRewiring 0.1

#define RRT_sensorRadius 200
#define RRT_accur 0.1

#define RRT_mVal 4
#define RRT_mForce 1

#define RRT_maxNeighbours 50

#define RRT_alpha 0.1
#define RRT_beta 1.4

#define RRT_starradius 100

#define RRT_startx 0
#define RRT_starty 0
#define RRT_goalx 5
#define RRT_goaly 5

#endif