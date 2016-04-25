// Reference:
// http://oramind.com/ogre-bullet-a-beginners-basic-guide/
// http://bulletphysics.org/Bullet/BulletFull/classbtDynamicsWorld.html#a5ab26a0d6e8b2b21fbde2ed8f8dd6294

#ifndef __Physics_h_
#define __Physics_h_


#include <Ogre.h>
#include "PhysicsObject.h"
#include "GameObject.h"
#include "DebugDraw.hpp"

class Physics {
protected:
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btBroadphaseInterface* overlappingPairCache;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;
    Ogre::SceneManager* sceneMgr;

    // List of objects that the bullet is tracking
    std::list<PhysicsObject*> objList;

    CDebugDraw* mDebugDrawer;
    bool debug;
    
public:
    Physics(Ogre::SceneManager* mgr, bool _debug);
    virtual ~Physics();

    std::list<PhysicsObject*> * getObjList ();
    void addObject(PhysicsObject* o);
    void removeObject(PhysicsObject* o);
    void stepSimulation(const Ogre::Real elapsedTime, int maxSubSteps, Ogre::Real fixedTimestep);
    void checkCollide(PhysicsObject* a, PhysicsObject* b);
    btDiscreteDynamicsWorld* getDynamicsWorld();
    void setGravity(btScalar y);
    void setDebug(bool b);

};

//---------------------------------------------------------------------------

#endif // #ifndef __Physics_h_

//---------------------------------------------------------------------------