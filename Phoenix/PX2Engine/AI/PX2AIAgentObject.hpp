// PX2AIAgentObject.hpp

#ifndef PX2AIAGENTOBJECT_HPP
#define PX2AIAGENTOBJECT_HPP

#include "PX2CorePre.hpp"
#include "PX2Object.hpp"
#include "PX2HQuaternion.hpp"
#include "OpenSteer/Obstacle.h"

class btRigidBody;

namespace PX2
{

	class Node;

	class AIAgentObject : public Object, private OpenSteer::SphereObstacle
	{
		friend class AIAgent;

	public:
		AIAgentObject(int objectID, Node *sceneNode, btRigidBody* rigidBody);
		virtual ~AIAgentObject();

		virtual void Initialize();
		virtual void Cleanup();
		virtual void Update(float elapsedSeconds);

		void SetMass(const float mass);
		float GetMass() const;

		void SetOrientation(const HQuaternion& quaternion);
		HQuaternion GetOrientation() const;

		void SetPosition(const Vector3f& position);
		Vector3f GetPosition() const;

		float GetRadius() const;

		Node* GetSceneNode();
		const Node* GetSceneNode() const;

		btRigidBody* GetRigidBody();
		const btRigidBody* GetRigidBody() const;

	private:
		Node* sceneNode_;
		btRigidBody* rigidBody_;

		AIAgentObject(const AIAgentObject& gameObject);
		AIAgentObject& operator=(const AIAgentObject& gameObject);

		OpenSteer::Vec3 getPosition() const;

		// Overloading the SphereObstacle's radius implementation.
		virtual float getRadius() const;

		virtual OpenSteer::Vec3 steerToAvoid(
			const OpenSteer::AbstractVehicle& vehicle,
			const float minTimeToCollision) const;
	};

}

#endif