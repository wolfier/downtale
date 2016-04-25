#include "GameObject.h"

GameObject::GameObject(Ogre::SceneManager* mgr, Ogre::SceneNode* parentnode, Ogre::String name) :
        name(name),
        physicsObj(NULL),
        entityObj(NULL) {
    sceneMgr = mgr;
    sceneNode = parentnode->createChildSceneNode(name);
    setPosition(0, 0, 0);
}

GameObject::~GameObject() {
    if (physicsObj) delete physicsObj;
    if (entityObj) delete entityObj;
}

void GameObject::addPhysicsObject(PhysicsObject* phy) {
    if (physicsObj) delete physicsObj;
    physicsObj = phy;
}

void GameObject::setEntityObject(EntityObject* ent) {
    if (entityObj) delete entityObj;
    entityObj = ent;
    sceneNode->attachObject(entityObj->getEntity());
}

bool GameObject::getCollideFlag(){ return false; }

PhysicsObject* GameObject::getPhysicsObject() { return physicsObj; }

Ogre::SceneNode* GameObject::getNode() { return sceneNode; }

Ogre::Vector3 GameObject::getPosition() { return sceneNode->getPosition(); }

Ogre::Vector3 GameObject::getLocalPosition() { return sceneNode->convertWorldToLocalPosition(sceneNode->getPosition()); }

Ogre::Quaternion GameObject::getOrientation() { return sceneNode->getOrientation(); }

void GameObject::setPosition(float x, float y, float z) { sceneNode->setPosition(Ogre::Vector3(x,y,z)); }
void GameObject::setPosition(Ogre::Vector3 v) { sceneNode->setPosition(v); }

void GameObject::setScale(float x, float y, float z) { sceneNode->setScale(Ogre::Vector3(x,y,z)); }

void GameObject::setRotation(float pitch, float yaw, float roll) {
    sceneNode->resetOrientation();
    sceneNode->pitch(Ogre::Degree(pitch));
    sceneNode->yaw(Ogre::Degree(yaw));
    sceneNode->roll(Ogre::Degree(roll));
}

void GameObject::translate(float x, float y, float z) { sceneNode->translate(Ogre::Vector3(x,y,z)); }

void GameObject::localtranslate(float x, float y, float z) { sceneNode->translate(Ogre::Vector3(x,y,z), Ogre::Node::TS_LOCAL); }

void GameObject::rotate(float pitch, float yaw, float roll) {
    sceneNode->pitch(Ogre::Degree(pitch));
    sceneNode->yaw(Ogre::Degree(yaw));
    sceneNode->roll(Ogre::Degree(roll));
}

void GameObject::localrotate(float pitch, float yaw, float roll) {
    sceneNode->pitch(Ogre::Degree(pitch), Ogre::Node::TS_LOCAL);
    sceneNode->yaw(Ogre::Degree(yaw), Ogre::Node::TS_LOCAL);
    sceneNode->roll(Ogre::Degree(roll), Ogre::Node::TS_LOCAL);
}


