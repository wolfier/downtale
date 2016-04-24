#pragma once

#include <Ogre.h>
#include <btBulletDynamicsCommon.h>

#include "BulletContactCallback.h"
#include "MotionState.h"

class Physics;

class PhysicsObject {
public:
	PhysicsObject(Physics* phy);
    virtual ~PhysicsObject();

    virtual void addToSimulator(Ogre::SceneNode* sceneNode);

    MotionState* getMotionState();
    btCollisionShape * getShape();
    btRigidBody* getBody();
    btTransform* getTransform();
    btScalar getMass();
    btVector3 getInertia();
    btScalar getFriction();
    btScalar getRestitution();
    BulletContactCallback* getCollisionCallback();
    CollisionContext* getCollisionContext();
    
    void setInitVelocity(btScalar x, btScalar y, btScalar z);
    void setShape(btCollisionShape* newShape);
    void setBody(btRigidBody* newBody);
    void updateTransform(Ogre::Vector3 pos, Ogre::Quaternion qt);
    void setKinematic();
    void setMass(btScalar newMass);
    void setInertia(btVector3 newInertia);
    void setFriction(btScalar newFriction);
    void setRestitution(btScalar newRestitution);

    void remove();
    void reinit();

protected:
    Ogre::SceneNode* node;

	Physics* physics;
	MotionState* motionState;
	btCollisionShape* shape;
    btRigidBody* body;
    btTransform tr;
    btVector3 inertia;
    btScalar mass;
    btScalar restitution;
    btScalar friction;

    CollisionContext* context;
    BulletContactCallback* cCallBack;

    btVector3 velocity;

    bool kinematic;
};