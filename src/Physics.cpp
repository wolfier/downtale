#include "Physics.h"

#include <iostream>
using namespace std;

Physics::Physics(Ogre::SceneManager* mgr, bool _debug) {
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    overlappingPairCache = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver();
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0.0f, -25.0f, 0.0f));
   
    debug = _debug;
    sceneMgr = mgr;
    mDebugDrawer = new CDebugDraw(mgr, dynamicsWorld);
    dynamicsWorld->setDebugDrawer(mDebugDrawer);
}

Physics::~Physics() { }

void Physics::addObject (PhysicsObject* o)
{
    objList.push_back(o);
    dynamicsWorld->addRigidBody(o->getBody());
}

void Physics::removeObject(PhysicsObject* o) {
    objList.remove(o);
    dynamicsWorld->removeRigidBody(o->getBody());
}

void Physics::checkCollide(PhysicsObject* a, PhysicsObject* b){
    dynamicsWorld->contactPairTest(a->getBody(), b->getBody(), *(a->getCollisionCallback()));
    dynamicsWorld->contactPairTest(b->getBody(), a->getBody(), *(b->getCollisionCallback()));
}

btDiscreteDynamicsWorld* Physics::getDynamicsWorld() { return dynamicsWorld; }

std::list<PhysicsObject*>* Physics::getObjList () { return &objList; }

void Physics::setGravity(btScalar y){ dynamicsWorld->setGravity(btVector3(0.0f, y, 0.0f)); }

void Physics::stepSimulation(const Ogre::Real elapsedTime, int maxSubSteps, const Ogre::Real fixedTimestep)
{
    dynamicsWorld->stepSimulation(elapsedTime, maxSubSteps, fixedTimestep);

    typedef std::list<PhysicsObject*>::iterator iter;
    for (iter i = objList.begin(); i != objList.end(); i++)
        (*i)->getCollisionCallback()->ctxt.hit = false;

    if( debug ) mDebugDrawer->Update();
}

void Physics::setDebug(bool b) { debug = b; }
