// Reference:
// https://piazza.com/class/ijeszzgvrj46wc?cid=67

#ifndef __GameObject_h_
#define __GameObject_h_

#include <Ogre.h>
#include <queue>

#include "EntityObject.h"
#include "PhysicsObject.h"

class GameObject {
public:
    GameObject(Ogre::SceneManager* mgr, Ogre::SceneNode* parentNode, Ogre::String name);
    virtual ~GameObject(void);

    virtual bool getCollideFlag();

    Ogre::SceneNode* getNode();
    Ogre::Vector3 getPosition();
    Ogre::Vector3 getLocalPosition();
    Ogre::Quaternion getOrientation();
    Ogre::Entity* getEntity();
    void setPosition(float x, float y, float z);
    void setPosition(Ogre::Vector3 v);
    void setScale(float x, float y, float z);
    void setRotation(float pitch, float yaw, float roll);
    void translate(float x, float y, float z);
    void localtranslate(float x, float y, float z);
    void rotate(float pitch, float yaw, float roll);
    void localrotate(float pitch, float yaw, float roll);

    PhysicsObject* getPhysicsObject();
    void addPhysicsObject(PhysicsObject* phy);
    void setEntityObject(EntityObject* ent);
    bool touched;

protected:
    Ogre::String name;
    Ogre::SceneManager* sceneMgr;
    Ogre::SceneNode* sceneNode;
    PhysicsObject* physicsObj;
    EntityObject* entityObj;
};

//---------------------------------------------------------------------------

#endif // #ifndef __GameScreen_h_

//---------------------------------------------------------------------------