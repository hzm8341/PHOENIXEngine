// PX2AISteeringBehavior.cpp

#include "PX2AISteeringBehavior.hpp"
#include "PX2AIAgent.hpp"
#include "PX2AIAgentObject.hpp"
#include "PX2AIAgentWorld.hpp"
#include "PX2AISteeringParamLoader.hpp"
#include "PX2AIPath.hpp"
using namespace PX2;
using namespace std;

//------------------------------------------------------------------------
SteeringBehavior::SteeringBehavior(AIAgent* agent):
	mVehicle(agent),
	m_iFlags(0),
	mDBoxLength(Prm.MinDetectionBoxLength),
	m_dWeightCohesion(Prm.CohesionWeight),
	m_dWeightAlignment(Prm.AlignmentWeight),
	m_dWeightSeparation(Prm.SeparationWeight),
	m_dWeightObstacleAvoidance(Prm.ObstacleAvoidanceWeight),
	m_dWeightWander(Prm.WanderWeight),
	m_dWeightWallAvoidance(Prm.WallAvoidanceWeight),
	m_dViewDistance(Prm.ViewDistance),
	m_dWallDetectionFeelerLength(Prm.WallDetectionFeelerLength),
	m_Feelers(3),
	m_Deceleration(normal),
	m_pTargetAgent1(0),
	m_pTargetAgent2(0),
	m_dWanderDistance(WanderDist),
	m_dWanderJitter(WanderJitterPerSec),
	m_dWanderRadius(WanderRad),
	m_dWaypointSeekDistSq(WaypointSeekDist*WaypointSeekDist),
	m_dWeightSeek(Prm.SeekWeight),
	m_dWeightFlee(Prm.FleeWeight),
	m_dWeightArrive(Prm.ArriveWeight),
	m_dWeightPursuit(Prm.PursuitWeight),
	m_dWeightOffsetPursuit(Prm.OffsetPursuitWeight),
	m_dWeightInterpose(Prm.InterposeWeight),
	m_dWeightHide(Prm.HideWeight),
	m_dWeightEvade(Prm.EvadeWeight),
	m_dWeightFollowPath(Prm.FollowPathWeight),
	m_bCellSpaceOn(false),
	m_SummingMethod(prioritized)
{
	//stuff for the wander behavior
	float theta = Mathf::UnitRandom() * Mathf::TWO_PI;

	//create a vector to a target position on the wander circle
	m_vWanderTarget = Vector3f(m_dWanderRadius * Mathf::Cos(theta),
		m_dWanderRadius * Mathf::Sin(theta), 0.0f);

	//create a Path
	mPath.LoopOn();
}
//------------------------------------------------------------------------
SteeringBehavior::~SteeringBehavior()
{
}
//------------------------------------------------------------------------
Vector3f SteeringBehavior::Calculate()
{
	//reset the steering force
	m_vSteeringForce = Vector3f::ZERO;

	//use space partitioning to calculate the neighbours of this vehicle
	//if switched on. If not, use the standard tagging system
	if (!IsSpacePartitioningOn())
	{
		//tag neighbors if any of the following 3 group behaviors are switched on
		if (On(separation) || On(allignment) || On(cohesion))
		{
			mVehicle->GetAIAgentWorld()->TagVehiclesWithinViewRange(mVehicle, m_dViewDistance);
		}
	}
	else
	{
		//calculate neighbours in cell-space if any of the following 3 group
		//behaviors are switched on
		if (On(separation) || On(allignment) || On(cohesion))
		{
			mVehicle->GetAIAgentWorld()->CellSpace()->CalculateNeighbors(mVehicle->GetPosition(), m_dViewDistance);
		}
	}

	switch (m_SummingMethod)
	{
	case weighted_average:

		m_vSteeringForce = CalculateWeightedSum(); break;

	case prioritized:

		m_vSteeringForce = CalculatePrioritized(); break;

	default:m_vSteeringForce = Vector3f::ZERO;

	}//end switch

	return m_vSteeringForce;
}
//------------------------------------------------------------------------
float SteeringBehavior::ForwardComponent()
{
	return mVehicle->GetForward().Dot(m_vSteeringForce);
}
//------------------------------------------------------------------------
float SteeringBehavior::SideComponent()
{
	return mVehicle->GetRight().Dot(m_vSteeringForce);
}
//------------------------------------------------------------------------
bool SteeringBehavior::AccumulateForce(Vector3f &runningTot,
	Vector3f forceToAdd)
{
	float magnitudeSoFar = runningTot.Length();
	float magnitudeRemaining = mVehicle->GetMaxForce() - 
		magnitudeSoFar;

	if (magnitudeRemaining <= 0.0) return false;

	float magnitudeToAdd = forceToAdd.Length();

	if (magnitudeToAdd < magnitudeRemaining)
	{
		runningTot += forceToAdd;
	}
	else
	{
		forceToAdd.Normalize();
		runningTot += (forceToAdd * magnitudeRemaining);
	}

	return true;
}
//------------------------------------------------------------------------
Vector3f SteeringBehavior::CalculatePrioritized()
{
	Vector3f force;

	if (On(wall_avoidance))
	{
		force = WallAvoidance(mVehicle->GetAIAgentWorld()->GetWalls()) *
			m_dWeightWallAvoidance;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if (On(obstacle_avoidance))
	{
		force = ObstacleAvoidance(mVehicle->GetAIAgentWorld()->GetObjects()) *
			m_dWeightObstacleAvoidance;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if (On(evade))
	{
		assert(m_pTargetAgent1 && "Evade target not assigned");

		force = Evade(m_pTargetAgent1) * m_dWeightEvade;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}


	if (On(flee))
	{
		force = Flee(mVehicle->GetTarget()) * m_dWeightFlee;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if (!IsSpacePartitioningOn())
	{
		if (On(separation))
		{
			force = Separation(mVehicle->GetAIAgentWorld()->GetAgents()) * m_dWeightSeparation;

			if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
		}

		if (On(allignment))
		{
			force = Alignment(mVehicle->GetAIAgentWorld()->GetAgents()) * m_dWeightAlignment;

			if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
		}

		if (On(cohesion))
		{
			force = Cohesion(mVehicle->GetAIAgentWorld()->GetAgents()) * m_dWeightCohesion;

			if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
		}
	}
	else
	{

		if (On(separation))
		{
			force = SeparationPlus(mVehicle->GetAIAgentWorld()->GetAgents()) * m_dWeightSeparation;

			if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
		}

		if (On(allignment))
		{
			force = AlignmentPlus(mVehicle->GetAIAgentWorld()->GetAgents()) * m_dWeightAlignment;

			if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
		}

		if (On(cohesion))
		{
			force = CohesionPlus(mVehicle->GetAIAgentWorld()->GetAgents()) * m_dWeightCohesion;

			if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
		}
	}

	if (On(seek))
	{
		force = Seek(mVehicle->GetTarget()) * m_dWeightSeek;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}


	if (On(arrive))
	{
		force = Arrive(mVehicle->GetTarget(), m_Deceleration) * m_dWeightArrive;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if (On(wander))
	{
		force = Wander() * m_dWeightWander;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if (On(pursuit))
	{
		assert(m_pTargetAgent1 && "pursuit target not assigned");

		force = Pursuit(m_pTargetAgent1) * m_dWeightPursuit;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if (On(offset_pursuit))
	{
		assert(m_pTargetAgent1 && "pursuit target not assigned");
		assert(Vector3f::ZERO != m_vOffset && "No offset assigned");

		force = OffsetPursuit(m_pTargetAgent1, m_vOffset);

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if (On(interpose))
	{
		assert(m_pTargetAgent1 && m_pTargetAgent2 && "Interpose agents not assigned");

		force = Interpose(m_pTargetAgent1, m_pTargetAgent2) * m_dWeightInterpose;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	if (On(hide))
	{
		assert(m_pTargetAgent1 && "Hide target not assigned");

		force = Hide(m_pTargetAgent1, mVehicle->GetAIAgentWorld()->GetObjects()) * m_dWeightHide;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}


	if (On(follow_path))
	{
		force = FollowPath() * m_dWeightFollowPath;

		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}

	return m_vSteeringForce;
}
//----------------------------------------------------------------------------
Vector3f SteeringBehavior::CalculateWeightedSum()
{
	if (On(wall_avoidance))
	{
		m_vSteeringForce += WallAvoidance(
			mVehicle->GetAIAgentWorld()->GetWalls()) * m_dWeightWallAvoidance;
	}

	if (On(obstacle_avoidance))
	{
		m_vSteeringForce += ObstacleAvoidance(
			mVehicle->GetAIAgentWorld()->GetObjects()) * 
			m_dWeightObstacleAvoidance;
	}

	if (On(evade))
	{
		assert(m_pTargetAgent1 && "Evade target not assigned");

		m_vSteeringForce += Evade(m_pTargetAgent1) * m_dWeightEvade;
	}

	if (!IsSpacePartitioningOn())
	{
		if (On(separation))
		{
			m_vSteeringForce += Separation(mVehicle->GetAIAgentWorld()->GetAgents()) * m_dWeightSeparation;
		}

		if (On(allignment))
		{
			m_vSteeringForce += Alignment(mVehicle->GetAIAgentWorld()->GetAgents()) * m_dWeightAlignment;
		}

		if (On(cohesion))
		{
			m_vSteeringForce += Cohesion(mVehicle->GetAIAgentWorld()->GetAgents()) * m_dWeightCohesion;
		}
	}
	else
	{
		if (On(separation))
		{
			m_vSteeringForce += SeparationPlus(mVehicle->GetAIAgentWorld()->GetAgents()) * m_dWeightSeparation;
		}

		if (On(allignment))
		{
			m_vSteeringForce += AlignmentPlus(mVehicle->GetAIAgentWorld()->GetAgents()) * m_dWeightAlignment;
		}

		if (On(cohesion))
		{
			m_vSteeringForce += CohesionPlus(mVehicle->GetAIAgentWorld()->GetAgents()) * m_dWeightCohesion;
		}
	}


	if (On(wander))
	{
		m_vSteeringForce += Wander() * m_dWeightWander;
	}

	if (On(seek))
	{
		m_vSteeringForce += Seek(mVehicle->GetTarget()) * m_dWeightSeek;
	}

	if (On(flee))
	{
		m_vSteeringForce += Flee(mVehicle->GetTarget()) * m_dWeightFlee;
	}

	if (On(arrive))
	{
		m_vSteeringForce += Arrive(mVehicle->GetTarget(), m_Deceleration) * m_dWeightArrive;
	}

	if (On(pursuit))
	{
		assert(m_pTargetAgent1 && "pursuit target not assigned");

		m_vSteeringForce += Pursuit(m_pTargetAgent1) * m_dWeightPursuit;
	}

	if (On(offset_pursuit))
	{
		assert(m_pTargetAgent1 && "pursuit target not assigned");
		assert(m_vOffset!=Vector3f::ZERO && "No offset assigned");

		m_vSteeringForce += OffsetPursuit(m_pTargetAgent1, m_vOffset) * m_dWeightOffsetPursuit;
	}

	if (On(interpose))
	{
		assert(m_pTargetAgent1 && m_pTargetAgent2 && "Interpose agents not assigned");

		m_vSteeringForce += Interpose(m_pTargetAgent1, m_pTargetAgent2) * m_dWeightInterpose;
	}

	if (On(hide))
	{
		assert(m_pTargetAgent1 && "Hide target not assigned");

		m_vSteeringForce += Hide(m_pTargetAgent1, mVehicle->GetAIAgentWorld()->GetObjects()) * m_dWeightHide;
	}

	if (On(follow_path))
	{
		m_vSteeringForce += FollowPath() * m_dWeightFollowPath;
	}

	float length = m_vSteeringForce.Length();
	if (length > mVehicle->GetMaxForce())
	{
		m_vSteeringForce.Normalize();
		m_vSteeringForce = m_vSteeringForce *  mVehicle->GetMaxForce();
	}

	return m_vSteeringForce;
}
//----------------------------------------------------------------------------
Vector3f SteeringBehavior::Seek(Vector3f targetPos)
{
	Vector3f dir = targetPos - mVehicle->GetPosition();
	dir.Normalize();
	Vector3f desiredVelocity = dir * mVehicle->GetMaxSpeed();

	return desiredVelocity - mVehicle->GetVelocity();
}
//----------------------------------------------------------------------------
Vector3f SteeringBehavior::Flee(Vector3f targetPos)
{
	Vector3f dir = mVehicle->GetPosition().To3() - targetPos;
	dir.Normalize();
	Vector3f desiredVelocity = dir * mVehicle->GetMaxSpeed();

	return (desiredVelocity - mVehicle->GetVelocity());
}
//------------------------------------------------------------------------
Vector3f SteeringBehavior::Arrive(Vector3f targetPos,
	Deceleration deceleration)
{
	Vector3f toTarget = targetPos - mVehicle->GetPosition();
	float dist = toTarget.Length();

	if (dist > 0)
	{
		//because Deceleration is enumerated as an int, this value is required
		//to provide fine tweaking of the deceleration..
		const float DecelerationTweaker = 0.3;

		//calculate the speed required to reach the target given the desired
		//deceleration
		float speed = dist / ((float)deceleration * DecelerationTweaker);

		//make sure the velocity does not exceed the max
		speed = Mathf::Min(speed, mVehicle->GetMaxSpeed());

		//from here proceed just like Seek except we don't need to normalize 
		//the toTarget vector because we have already gone to the trouble
		//of calculating its length: dist. 
		Vector3f desiredVelocity = toTarget * speed / dist;

		return desiredVelocity - mVehicle->GetVelocity();
	}

	return Vector3f::ZERO;
}
//------------------------------------------------------------------------
Vector3f SteeringBehavior::Pursuit(const AIAgent* evader)
{
	Vector3f toEvader = evader->GetPosition() 
		- mVehicle->GetPosition();

	float relativeHeading = 
		mVehicle->GetForward().Dot(evader->GetForward());

	if ((toEvader.Dot(mVehicle->GetForward()) > 0) &&
		(relativeHeading < -0.95))  //acos(0.95)=18 degs
	{
		return Seek(evader->GetPosition());
	}

	float lookAheadTime = toEvader.Length() /
		(mVehicle->GetMaxSpeed() + evader->GetSpeed());

	return Seek(evader->GetPosition() +
		evader->GetVelocity() * lookAheadTime);
}
//------------------------------------------------------------------------
Vector3f SteeringBehavior::Evade(const AIAgent* pursuer)
{
	/* Not necessary to include the check for facing direction this time */

	Vector3f toPursuer = pursuer->GetPosition() -
		mVehicle->GetPosition();

	//uncomment the following two lines to have Evade only consider pursuers 
	//within a 'threat range'
	const float ThreatRange = 100.0;
	if (toPursuer.SquaredLength() > ThreatRange * ThreatRange) return Vector3f();

	//the lookahead time is propotional to the distance between the pursuer
	//and the pursuer; and is inversely proportional to the sum of the
	//agents' velocities
	float lookAheadTime = toPursuer.Length() /
		(mVehicle->GetMaxSpeed() + pursuer->GetSpeed());

	//now flee away from predicted future position of the pursuer
	return Flee(pursuer->GetPosition() +
		pursuer->GetVelocity() * lookAheadTime);
}
//------------------------------------------------------------------------
Vector3f SteeringBehavior::Wander()
{
	//and steer towards it
	return Vector3f::ZERO;
}
//------------------------------------------------------------------------
Vector3f SteeringBehavior::ObstacleAvoidance(
	const std::vector<AIAgentObject*>& obstacles)
{
	mDBoxLength = Prm.MinDetectionBoxLength +
		(mVehicle->GetSpeed() / mVehicle->GetMaxSpeed()) *
		Prm.MinDetectionBoxLength;

	mVehicle->GetAIAgentWorld()->TagObstaclesWithinViewRange(mVehicle,
		mDBoxLength);

	AIAgentObject* closestIntersectingObstacle = NULL;
	float distToClosestIP = Mathf::MAX_REAL;

	Vector3f LocalPosOfClosestObstacle;
	std::vector<AIAgentObject*>::const_iterator curOb = obstacles.begin();



	while (curOb != obstacles.end())
	{
		//if the obstacle has been tagged within range proceed
		if ((*curOb)->IsTagged())
		{
			HMatrix localMat =
				HMatrix(mVehicle->GetRight(), mVehicle->GetForward(),
					mVehicle->GetUp(), mVehicle->GetPosition(), true);

			APoint curObjPos = (*curOb)->GetPosition();
			Vector3f localPos = localMat.Inverse() * curObjPos;

			//if the local position has a negative x value then it must lay
			//behind the agent. (in which case it can be ignored)
			if (localPos.X() >= 0)
			{
				//if the distance from the x axis to the object's position is less
				//than its radius + half the width of the detection box then there
				//is a potential intersection.
				float ExpandedRadius = (*curOb)->GetRadius() + mVehicle->GetRadius();

				if (fabs(localPos.Y()) < ExpandedRadius)
				{
					//now to do a line/circle intersection test. The center of the 
					//circle is represented by (cX, cY). The intersection points are 
					//given by the formula x = cX +/-sqrt(r^2-cY^2) for y=0. 
					//We only need to look at the smallest positive value of x because
					//that will be the closest point of intersection.
					float cX = localPos.X();
					float cY = localPos.Y();

					//we only need to calculate the sqrt part of the above equation once
					float SqrtPart = sqrt(ExpandedRadius*ExpandedRadius - cY*cY);

					float ip = cX - SqrtPart;

					if (ip <= 0.0)
					{
						ip = cX + SqrtPart;
					}

					//test to see if this is the closest so far. If it is keep a
					//record of the obstacle and its local coordinates
					if (ip < distToClosestIP)
					{
						distToClosestIP = ip;

						closestIntersectingObstacle = *curOb;

						LocalPosOfClosestObstacle = localPos;
					}
				}
			}
		}

		++curOb;
	}

	AVector SteeringForce;
	if (closestIntersectingObstacle)
	{
		//the closer the agent is to an object, the stronger the 
		//steering force should be
		float multiplier = 1.0 + (mDBoxLength - LocalPosOfClosestObstacle.X()) /
			mDBoxLength;

		//calculate the lateral force
		SteeringForce.Y() = (closestIntersectingObstacle->GetRadius() -
			LocalPosOfClosestObstacle.Y())  * multiplier;

		//apply a braking force proportional to the obstacles distance from
		//the vehicle. 
		const float BrakingWeight = 0.2;

		SteeringForce.X() = (closestIntersectingObstacle->GetRadius() -
			LocalPosOfClosestObstacle.X()) *
			BrakingWeight;
	}

	//finally, convert the steering vector from local to world space
	HMatrix mat =
		HMatrix(mVehicle->GetRight(), mVehicle->GetForward(),
			mVehicle->GetUp(), APoint::ORIGIN, true);

	AVector vec = mat * SteeringForce;
	return vec;
}
//------------------------------------------------------------------------
inline bool LineIntersection2D(Vector3f A, Vector3f B, Vector3f C,
	Vector3f D, float& dist, Vector3f& point)
{

	float rTop = (A.Y() - C.Y())*(D.X() - C.X()) - (A.X()- C.X())*(D.Y() - C.Y());
	float rBot = (B.X() - A.X())*(D.Y() - C.Y()) - (B.Y() - A.Y())*(D.X() - C.X());

	float sTop = (A.Y() - C.Y())*(B.X() - A.X()) - (A.X()- C.X())*(B.Y() - A.Y());
	float sBot = (B.X() - A.X())*(D.Y() - C.Y()) - (B.Y() - A.Y())*(D.X() - C.X());

	if ((rBot == 0) || (sBot == 0))
	{
		//lines are parallel
		return false;
	}

	float r = rTop / rBot;
	float s = sTop / sBot;

	if ((r > 0) && (r < 1) && (s > 0) && (s < 1))
	{
		Vector3f distVec = A - B;
		float length = distVec.Length();

		dist = length * r;

		point = A + r * (B - A);

		return true;
	}

	else
	{
		dist = 0;

		return false;
	}
}
Vector3f _Vec2To3(Vector2f vec2)
{
	return Vector3f(vec2[0], vec2[1], vec2[2]);
}
//------------------------------------------------------------------------
Vector3f SteeringBehavior::WallAvoidance(const std::vector<Wall2D>& walls)
{
	float DistToThisIP = 0.0;
	float distToClosestIP = Mathf::MAX_REAL;

	//this will hold an index into the vector of walls
	int ClosestWall = -1;

	Vector3f SteeringForce,
		point,         //used for storing temporary info
		ClosestPoint;  //holds the closest intersection point

					   //examine each feeler in turn
	for (unsigned int flr = 0; flr<m_Feelers.size(); ++flr)
	{
		//run through each wall checking for any intersection points
		for (unsigned int w = 0; w<walls.size(); ++w)
		{
			if (LineIntersection2D(mVehicle->GetPosition(),
				m_Feelers[flr],
				_Vec2To3(walls[w].From()),
				_Vec2To3(walls[w].To()),
				DistToThisIP,
				point))
			{
				//is this the closest found so far? If so keep a record
				if (DistToThisIP < distToClosestIP)
				{
					distToClosestIP = DistToThisIP;

					ClosestWall = w;

					ClosestPoint = point;
				}
			}
		}//next wall


		 //if an intersection point has been detected, calculate a force  
		 //that will direct the agent away
		if (ClosestWall >= 0)
		{
			//calculate by what distance the projected position of the agent
			//will overshoot the wall
			Vector3f OverShoot = m_Feelers[flr] - ClosestPoint;

			//create a force in the direction of the wall normal, with a 
			//magnitude of the overshoot
			Vector2f normal2 = walls[ClosestWall].Normal();
			Vector3f normal3(normal2.X(), normal2.Y(), 0.0f);
			SteeringForce = normal3 * OverShoot.Length();
		}

	}//next feeler

	return SteeringForce;
}
//------------------------------------------------------------------------
Vector3f SteeringBehavior::Separation(const vector<AIAgent*> &neighbors)
{
	Vector3f SteeringForce;

	for (unsigned int a = 0; a<neighbors.size(); ++a)
	{
		if ((neighbors[a] != mVehicle) && neighbors[a]->IsTagged() &&
			(neighbors[a] != m_pTargetAgent1))
		{
			Vector3f ToAgent = mVehicle->GetPosition() 
				- neighbors[a]->GetPosition();

			float length = ToAgent.Normalize();
			SteeringForce += ToAgent / length;
		}
	}

	return SteeringForce;
}
//------------------------------------------------------------------------
Vector3f SteeringBehavior::Alignment(const vector<AIAgent*>& neighbors)
{
	//used to record the average heading of the neighbors
	Vector3f AverageHeading;

	//used to count the number of vehicles in the neighborhood
	int    NeighborCount = 0;

	//iterate through all the tagged vehicles and sum their heading vectors  
	for (unsigned int a = 0; a<neighbors.size(); ++a)
	{
		//make sure *this* agent isn't included in the calculations and that
		//the agent being examined  is close enough ***also make sure it doesn't
		//include any evade target ***
		if ((neighbors[a] != mVehicle) && neighbors[a]->IsTagged() &&
			(neighbors[a] != m_pTargetAgent1))
		{
			AverageHeading += neighbors[a]->GetForward();

			++NeighborCount;
		}
	}

	//if the neighborhood contained one or more vehicles, average their
	//heading vectors.
	if (NeighborCount > 0)
	{
		AverageHeading /= (float)NeighborCount;

		AverageHeading -= mVehicle->GetForward();
	}

	return AverageHeading;
}
//------------------------------------------------------------------------
Vector3f SteeringBehavior::Cohesion(const vector<AIAgent*> &neighbors)
{
	//first find the center of mass of all the agents
	Vector3f CenterOfMass, SteeringForce;

	int NeighborCount = 0;

	//iterate through the neighbors and sum up all the position vectors
	for (unsigned int a = 0; a<neighbors.size(); ++a)
	{
		//make sure *this* agent isn't included in the calculations and that
		//the agent being examined is close enough ***also make sure it doesn't
		//include the evade target ***
		if ((neighbors[a] != mVehicle) && neighbors[a]->IsTagged() &&
			(neighbors[a] != m_pTargetAgent1))
		{
			CenterOfMass += neighbors[a]->GetPosition();

			++NeighborCount;
		}
	}

	if (NeighborCount > 0)
	{
		//the center of mass is the average of the sum of positions
		CenterOfMass /= (float)NeighborCount;

		//now seek towards that position
		SteeringForce = Seek(CenterOfMass);
	}

	SteeringForce.Normalize();

	return SteeringForce;
}
//------------------------------------------------------------------------
Vector3f SteeringBehavior::SeparationPlus( 
	const vector<AIAgent*> &neighbors)
{
	Vector3f SteeringForce;

	//iterate through the neighbors and sum up all the position vectors
	for (AIAgentBase* pV = mVehicle->GetAIAgentWorld()->CellSpace()->Begin();
		!mVehicle->GetAIAgentWorld()->CellSpace()->End();
		pV = mVehicle->GetAIAgentWorld()->CellSpace()->Next())
	{
		if (pV != mVehicle)
		{
			Vector3f ToAgent = mVehicle->GetPosition() - 
				pV->GetPosition();

			float length = ToAgent.Normalize();
			
			SteeringForce += ToAgent / length;
		}

	}

	return SteeringForce;
}
//------------------------------------------------------------------------
Vector3f SteeringBehavior::AlignmentPlus(const vector<AIAgent*> &neighbors)
{
	//This will record the average heading of the neighbors
	Vector3f AverageHeading;

	//This count the number of vehicles in the neighborhood
	float    NeighborCount = 0.0;

	//iterate through the neighbors and sum up all the position vectors
	for (AIAgent* pV = mVehicle->GetAIAgentWorld()->CellSpace()->Begin();
		!mVehicle->GetAIAgentWorld()->CellSpace()->End();
		pV = mVehicle->GetAIAgentWorld()->CellSpace()->Next())
	{
		//make sure *this* agent isn't included in the calculations and that
		//the agent being examined  is close enough
		if (pV != mVehicle)
		{
			AverageHeading += pV->GetForward();

			++NeighborCount;
		}

	}

	//if the neighborhood contained one or more vehicles, average their
	//heading vectors.
	if (NeighborCount > 0.0)
	{
		AverageHeading /= NeighborCount;

		AverageHeading -= mVehicle->GetForward();
	}

	return AverageHeading;
}
//------------------------------------------------------------------------
Vector3f SteeringBehavior::CohesionPlus(const vector<AIAgent*> &neighbors)
{
	//first find the center of mass of all the agents
	Vector3f CenterOfMass, SteeringForce;

	int NeighborCount = 0;

	//iterate through the neighbors and sum up all the position vectors
	for (AIAgent* pV = mVehicle->GetAIAgentWorld()->CellSpace()->Begin();
		!mVehicle->GetAIAgentWorld()->CellSpace()->End();
		pV = mVehicle->GetAIAgentWorld()->CellSpace()->Next())
	{
		//make sure *this* agent isn't included in the calculations and that
		//the agent being examined is close enough
		if (pV != mVehicle)
		{
			CenterOfMass += pV->GetPosition();

			++NeighborCount;
		}
	}

	if (NeighborCount > 0)
	{
		//the center of mass is the average of the sum of positions
		CenterOfMass /= (float)NeighborCount;

		//now seek towards that position
		SteeringForce = Seek(CenterOfMass);
	}

	SteeringForce.Normalize();

	return SteeringForce;
}
//------------------------------------------------------------------------
Vector3f SteeringBehavior::Interpose(const AIAgent* agentA,
	const AIAgent* agentB)
{
	Vector3f midPoint = (agentA->GetPosition() +
		agentB->GetPosition()) / 2.0;

	Vector3f vecDist = mVehicle->GetPosition().To3() - midPoint;
	float length = vecDist.Length();

	float TimeToReachMidPoint = length / mVehicle->GetMaxSpeed();

	Vector3f APos = agentA->GetPosition() + agentA->GetVelocity() * TimeToReachMidPoint;
	Vector3f BPos = agentB->GetPosition() + agentB->GetVelocity() * TimeToReachMidPoint;

	midPoint = (APos + BPos) / 2.0;

	return Arrive(midPoint, fast);
}
//------------------------------------------------------------------------
Vector3f SteeringBehavior::Hide(const AIAgent* hunter,
	const vector<AIAgentObject*>& obstacles)
{
	float    DistToClosest = Mathf::MAX_REAL;
	Vector3f BestHidingSpot;

	std::vector<AIAgentObject*>::const_iterator curOb = obstacles.begin();
	std::vector<AIAgentObject*>::const_iterator closest;

	while (curOb != obstacles.end())
	{
		//calculate the position of the hiding spot for this obstacle
		Vector3f HidingSpot = GetHidingPosition((*curOb)->GetPosition(),
			(*curOb)->GetRadius(),
			hunter->GetPosition());

		//work in distance-squared space to find the closest hiding
		//spot to the agent
		Vector3f vecDist = HidingSpot - mVehicle->GetPosition();
		float dist = vecDist.Length();

		if (dist < DistToClosest)
		{
			DistToClosest = dist;

			BestHidingSpot = HidingSpot;

			closest = curOb;
		}

		++curOb;

	}//end while


	if (DistToClosest == Mathf::MAX_REAL)
	{
		return Evade(hunter);
	}

	//else use Arrive on the hiding spot
	return Arrive(BestHidingSpot, fast);
}
//------------------------------------------------------------------------
Vector3f SteeringBehavior::GetHidingPosition(const Vector3f& posOb,
	const float     radiusOb,
	const Vector3f& posHunter)
{
	//calculate how far away the agent is to be from the chosen obstacle's
	//bounding radius
	const float DistanceFromBoundary = 30.0;
	float       DistAway = radiusOb + DistanceFromBoundary;

	//calculate the heading toward the object from the hunter
	Vector3f ToOb = (posOb - posHunter);
	ToOb.Normalize();

	//scale it to size and add to the obstacles position to get
	//the hiding spot.
	return (ToOb * DistAway) + posOb;
}
//------------------------------------------------------------------------
Vector3f SteeringBehavior::FollowPath()
{
	//move to next target if close enough to current target (working in
	//distance squared space)
	Vector3f vec = mPath.CurrentWaypoint() - mVehicle->GetPosition();
	float lengthSquare = vec.SquaredLength();

	if (lengthSquare < m_dWaypointSeekDistSq)
	{
		mPath.SetNextWaypoint();
	}

	if (!mPath.Finished())
	{
		return Seek(mPath.CurrentWaypoint());
	}

	else
	{
		return Arrive(mPath.CurrentWaypoint(), normal);
	}
}

//------------------------------------------------------------------------
Vector3f SteeringBehavior::OffsetPursuit(const AIAgent* leader,
	const Vector3f offset)
{
	HMatrix localMat =
		HMatrix(leader->GetRight(), leader->GetForward(),
			leader->GetUp(), leader->GetPosition(), true);

	//calculate the offset's position in world space
	APoint worldOffsetPos = localMat * APoint(offset.X(), offset.Y(), offset.Z());

	Vector3f ToOffset = worldOffsetPos.To3() - mVehicle->GetPosition();

	float lookAheadTime = ToOffset.Length() /
		(mVehicle->GetMaxSpeed() + leader->GetSpeed());

	//now Arrive at the predicted future position of the offset
	return Arrive(worldOffsetPos + leader->GetVelocity() * lookAheadTime, fast);
}
//------------------------------------------------------------------------
void SteeringBehavior::RenderAids()
{
	//gdi->TransparentText();
	//gdi->TextColor(Cgdi::grey);

	//int NextSlot = 0; int SlotSize = 20;

	//if (KEYDOWN(VK_INSERT)) { mVehicle->SetMaxForce(mVehicle->MaxForce() + 1000.0f*mVehicle->TimeElapsed()); }
	//if (KEYDOWN(VK_DELETE)) { if (mVehicle->MaxForce() > 0.2f) mVehicle->SetMaxForce(mVehicle->MaxForce() - 1000.0f*mVehicle->TimeElapsed()); }
	//if (KEYDOWN(VK_HOME)) { mVehicle->SetMaxSpeed(mVehicle->MaxSpeed() + 50.0f*mVehicle->TimeElapsed()); }
	//if (KEYDOWN(VK_END)) { if (mVehicle->MaxSpeed() > 0.2f) mVehicle->SetMaxSpeed(mVehicle->MaxSpeed() - 50.0f*mVehicle->TimeElapsed()); }

	//if (mVehicle->MaxForce() < 0) mVehicle->SetMaxForce(0.0f);
	//if (mVehicle->MaxSpeed() < 0) mVehicle->SetMaxSpeed(0.0f);

	//if (mVehicle->ID() == 0) { gdi->TextAtPos(5, NextSlot, "MaxForce(Ins/Del):"); gdi->TextAtPos(160, NextSlot, ttos(mVehicle->MaxForce() / Prm.SteeringForceTweaker)); NextSlot += SlotSize; }
	//if (mVehicle->ID() == 0) { gdi->TextAtPos(5, NextSlot, "MaxSpeed(Home/End):"); gdi->TextAtPos(160, NextSlot, ttos(mVehicle->MaxSpeed())); NextSlot += SlotSize; }

	////render the steering force
	//if (mVehicle->World()->RenderSteeringForce())
	//{
	//	gdi->RedPen();
	//	Vector3f F = (m_vSteeringForce / Prm.SteeringForceTweaker) * Prm.VehicleScale;
	//	gdi->Line(mVehicle->Pos(), mVehicle->Pos() + F);
	//}

	////render wander stuff if relevant
	//if (On(wander) && mVehicle->World()->RenderWanderCircle())
	//{
	//	if (KEYDOWN('F')) { m_dWanderJitter += 1.0f*mVehicle->TimeElapsed(); Clamp(m_dWanderJitter, 0.0f, 100.0f); }
	//	if (KEYDOWN('V')) { m_dWanderJitter -= 1.0f*mVehicle->TimeElapsed(); Clamp(m_dWanderJitter, 0.0f, 100.0f); }
	//	if (KEYDOWN('G')) { m_dWanderDistance += 2.0f*mVehicle->TimeElapsed(); Clamp(m_dWanderDistance, 0.0f, 50.0f); }
	//	if (KEYDOWN('B')) { m_dWanderDistance -= 2.0f*mVehicle->TimeElapsed(); Clamp(m_dWanderDistance, 0.0f, 50.0f); }
	//	if (KEYDOWN('H')) { m_dWanderRadius += 2.0f*mVehicle->TimeElapsed(); Clamp(m_dWanderRadius, 0.0f, 100.0f); }
	//	if (KEYDOWN('N')) { m_dWanderRadius -= 2.0f*mVehicle->TimeElapsed(); Clamp(m_dWanderRadius, 0.0f, 100.0f); }


	//	if (mVehicle->ID() == 0) { gdi->TextAtPos(5, NextSlot, "Jitter(F/V): "); gdi->TextAtPos(160, NextSlot, ttos(m_dWanderJitter)); NextSlot += SlotSize; }
	//	if (mVehicle->ID() == 0) { gdi->TextAtPos(5, NextSlot, "Distance(G/B): "); gdi->TextAtPos(160, NextSlot, ttos(m_dWanderDistance)); NextSlot += SlotSize; }
	//	if (mVehicle->ID() == 0) { gdi->TextAtPos(5, NextSlot, "Radius(H/N): "); gdi->TextAtPos(160, NextSlot, ttos(m_dWanderRadius)); NextSlot += SlotSize; }


	//	//calculate the center of the wander circle
	//	Vector3f m_vTCC = PointToWorldSpace(Vector3f(m_dWanderDistance*mVehicle->GetRadius(), 0),
	//		mVehicle->Heading(),
	//		mVehicle->Side(),
	//		mVehicle->Pos());
	//	//draw the wander circle
	//	gdi->GreenPen();
	//	gdi->HollowBrush();
	//	gdi->Circle(m_vTCC, m_dWanderRadius*mVehicle->GetRadius());

	//	//draw the wander target
	//	gdi->RedPen();
	//	gdi->Circle(PointToWorldSpace((m_vWanderTarget + Vector3f(m_dWanderDistance, 0))*mVehicle->GetRadius(),
	//		mVehicle->Heading(),
	//		mVehicle->Side(),
	//		mVehicle->Pos()), 3);
	//}

	////render the detection box if relevant
	//if (mVehicle->World()->RenderDetectionBox())
	//{
	//	gdi->GreyPen();

	//	//a vertex buffer rqd for drawing the detection box
	//	static std::vector<Vector3f> box(4);

	//	float length = Prm.MinDetectionBoxLength +
	//		(mVehicle->Speed() / mVehicle->MaxSpeed()) *
	//		Prm.MinDetectionBoxLength;

	//	//verts for the detection box buffer
	//	box[0] = Vector3f(0, mVehicle->GetRadius());
	//	box[1] = Vector3f(length, mVehicle->GetRadius());
	//	box[2] = Vector3f(length, -mVehicle->GetRadius());
	//	box[3] = Vector3f(0, -mVehicle->GetRadius());


	//	if (!mVehicle->isSmoothingOn())
	//	{
	//		box = WorldTransform(box, mVehicle->Pos(), mVehicle->Heading(), mVehicle->Side());
	//		gdi->ClosedShape(box);
	//	}
	//	else
	//	{
	//		box = WorldTransform(box, mVehicle->Pos(), mVehicle->SmoothedHeading(), mVehicle->SmoothedHeading().Perp());
	//		gdi->ClosedShape(box);
	//	}


	//	//////////////////////////////////////////////////////////////////////////
	//	//the detection box length is proportional to the agent's velocity
	//	mDBoxLength = Prm.MinDetectionBoxLength +
	//		(mVehicle->Speed() / mVehicle->MaxSpeed()) *
	//		Prm.MinDetectionBoxLength;

	//	//tag all obstacles within range of the box for processing
	//	mVehicle->World()->TagObstaclesWithinViewRange(mVehicle, mDBoxLength);

	//	//this will keep track of the closest intersecting obstacle (CIB)
	//	BaseGameEntity* closestIntersectingObstacle = NULL;

	//	//this will be used to track the distance to the CIB
	//	float distToClosestIP = MaxDouble;

	//	//this will record the transformed local coordinates of the CIB
	//	Vector3f LocalPosOfClosestObstacle;

	//	std::vector<BaseGameEntity*>::const_iterator curOb = mVehicle->World()->Obstacles().begin();

	//	while (curOb != mVehicle->World()->Obstacles().end())
	//	{
	//		//if the obstacle has been tagged within range proceed
	//		if ((*curOb)->IsTagged())
	//		{
	//			//calculate this obstacle's position in local space
	//			Vector3f localPos = PointToLocalSpace((*curOb)->Pos(),
	//				mVehicle->Heading(),
	//				mVehicle->Side(),
	//				mVehicle->Pos());

	//			//if the local position has a negative x value then it must lay
	//			//behind the agent. (in which case it can be ignored)
	//			if (localPos.X() >= 0)
	//			{
	//				//if the distance from the x axis to the object's position is less
	//				//than its radius + half the width of the detection box then there
	//				//is a potential intersection.
	//				if (fabs(localPos.Y()) < ((*curOb)->GetRadius() + mVehicle->GetRadius()))
	//				{
	//					gdi->ThickRedPen();
	//					gdi->ClosedShape(box);
	//				}
	//			}
	//		}

	//		++curOb;
	//	}


	//	/////////////////////////////////////////////////////
	//}

	////render the wall avoidnace feelers
	//if (On(wall_avoidance) && mVehicle->World()->RenderFeelers())
	//{
	//	gdi->OrangePen();

	//	for (unsigned int flr = 0; flr<m_Feelers.size(); ++flr)
	//	{

	//		gdi->Line(mVehicle->Pos(), m_Feelers[flr]);
	//	}
	//}

	////render path info
	//if (On(follow_path) && mVehicle->World()->RenderPath())
	//{
	//	mPath.Render();
	//}


	//if (On(separation))
	//{
	//	if (mVehicle->ID() == 0) { gdi->TextAtPos(5, NextSlot, "Separation(S/X):"); gdi->TextAtPos(160, NextSlot, ttos(m_dWeightSeparation / Prm.SteeringForceTweaker)); NextSlot += SlotSize; }

	//	if (KEYDOWN('S')) { m_dWeightSeparation += 200 * mVehicle->TimeElapsed(); Clamp(m_dWeightSeparation, 0.0f, 50.0f * Prm.SteeringForceTweaker); }
	//	if (KEYDOWN('X')) { m_dWeightSeparation -= 200 * mVehicle->TimeElapsed(); Clamp(m_dWeightSeparation, 0.0f, 50.0f * Prm.SteeringForceTweaker); }
	//}

	//if (On(allignment))
	//{
	//	if (mVehicle->ID() == 0) { gdi->TextAtPos(5, NextSlot, "Alignment(A/Z):"); gdi->TextAtPos(160, NextSlot, ttos(m_dWeightAlignment / Prm.SteeringForceTweaker)); NextSlot += SlotSize; }

	//	if (KEYDOWN('A')) { m_dWeightAlignment += 200 * mVehicle->TimeElapsed(); Clamp(m_dWeightAlignment, 0.0f, 50.0f * Prm.SteeringForceTweaker); }
	//	if (KEYDOWN('Z')) { m_dWeightAlignment -= 200 * mVehicle->TimeElapsed(); Clamp(m_dWeightAlignment, 0.0f, 50.0f * Prm.SteeringForceTweaker); }
	//}

	//if (On(cohesion))
	//{
	//	if (mVehicle->ID() == 0) { gdi->TextAtPos(5, NextSlot, "Cohesion(D/C):"); gdi->TextAtPos(160, NextSlot, ttos(m_dWeightCohesion / Prm.SteeringForceTweaker)); NextSlot += SlotSize; }
	//	if (KEYDOWN('D')) { m_dWeightCohesion += 200 * mVehicle->TimeElapsed(); Clamp(m_dWeightCohesion, 0.0f, 50.0f * Prm.SteeringForceTweaker); }
	//	if (KEYDOWN('C')) { m_dWeightCohesion -= 200 * mVehicle->TimeElapsed(); Clamp(m_dWeightCohesion, 0.0f, 50.0f * Prm.SteeringForceTweaker); }
	//}

	//if (On(follow_path))
	//{
	//	float sd = sqrt(m_dWaypointSeekDistSq);
	//	if (mVehicle->ID() == 0) { gdi->TextAtPos(5, NextSlot, "SeekDistance(D/C):"); gdi->TextAtPos(160, NextSlot, ttos(sd)); NextSlot += SlotSize; }

	//	if (KEYDOWN('D')) { m_dWaypointSeekDistSq += 1.0; }
	//	if (KEYDOWN('C')) { m_dWaypointSeekDistSq -= 1.0; Clamp(m_dWaypointSeekDistSq, 0.0f, 400.0f); }
	//}
}





