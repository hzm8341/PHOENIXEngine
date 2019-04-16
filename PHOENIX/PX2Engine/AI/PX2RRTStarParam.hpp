// PX2RRTStartParam.hpp
//https://github.com/rishabh1b/RealTimePathPlanning

#ifndef PX2RRTSTARPARAM_HPP
#define PX2RRTSTARPARAM_HPP

#include "PX2Core.hpp"

const float inf = std::numeric_limits<float>::infinity();

#define RRT_converge 1
#define RRT_epsilon 2
#define RRT_sensorScanObstRadius 3.0f

#define RRT_allowedTimeRewiring 0.5f

#define RRT_starradius 2

#define RRT_maxNeighbours 50

#define RRT_alpha 0.1
#define RRT_beta 1.4

#define RRT_startx 0
#define RRT_starty 0
#define RRT_goalx -50
#define RRT_goaly 50

#endif