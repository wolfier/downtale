#include "Physics.h"

PhysicsObject::PhysicsObject(Physics* phy) :
        physics(phy),
        motionState(NULL),
        shape(NULL),
        body(NULL),
        mass(0.f),
        restitution(0.95f),
        friction(0.5f),
        velocity(btVector3(0, 0, 0)),
        kinematic(false) {

    tr.setIdentity();   
    inertia.setZero();
}

PhysicsObject::~PhysicsObject() {
    if (motionState) delete motionState;
    if (shape) delete shape;
    if (body) delete body;
}

void PhysicsObject::addToSimulator(Ogre::SceneNode* sceneNode) {
    node = sceneNode;
    //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
    // updateTransform();
    motionState = kinematic ? new KinematicMotionState(tr, sceneNode) :
                                new MotionState(tr, sceneNode);
    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    if (mass != 0.0f)
        shape->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, inertia);
    body = new btRigidBody(rbInfo);
    body->setRestitution(restitution);
    body->setFriction(friction);

    context = new CollisionContext();
    cCallBack = new BulletContactCallback(*body, *context);

    body->setLinearVelocity(velocity);
    if (kinematic) {
        body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
        body->setActivationState(DISABLE_DEACTIVATION);
    }
    
    physics->addObject(this);
}

void PhysicsObject::updateTransform(Ogre::Vector3 pos, Ogre::Quaternion qt) {
    tr.setOrigin(btVector3(pos.x, pos.y, pos.z));
    btQuaternion bqt = btQuaternion(qt.x, qt.y, qt.z, qt.w);
    tr.setRotation(bqt);
    if (motionState) motionState->updateTransform(tr);
}

void PhysicsObject::remove() { physics->removeObject(this); }

void PhysicsObject::reinit() {
    remove();
    addToSimulator(node);
}

void PhysicsObject::setInitVelocity(btScalar x, btScalar y, btScalar z) { velocity = btVector3(x, y, z); }

void PhysicsObject::setBody(btRigidBody* newBody) { body = newBody; }

void PhysicsObject::setShape(btCollisionShape* newShape) { shape = newShape; }

void PhysicsObject::setKinematic() { kinematic = true; }

void PhysicsObject::setMass(btScalar newMass) { mass = newMass; }

void PhysicsObject::setInertia(btVector3 newInertia) { inertia = newInertia; }

void PhysicsObject::setFriction(btScalar newFriction) { friction = newFriction; }

void PhysicsObject::setRestitution(btScalar newRestitution) { restitution = newRestitution; }

MotionState* PhysicsObject::getMotionState() { return motionState; }

btCollisionShape * PhysicsObject::getShape() { return shape; }

btRigidBody* PhysicsObject::getBody() { return body; }

btTransform* PhysicsObject::getTransform() { return &tr; }

btScalar PhysicsObject::getMass() { return mass; }

btVector3 PhysicsObject::getInertia() { return inertia; }

btScalar PhysicsObject::getFriction() { return friction; }

btScalar PhysicsObject::getRestitution() { return restitution; }

BulletContactCallback* PhysicsObject::getCollisionCallback() { return cCallBack; }

CollisionContext* PhysicsObject::getCollisionContext(){ return context; }
