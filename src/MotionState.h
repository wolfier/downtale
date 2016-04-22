// Reference:
// http://www.bulletphysics.org/mediawiki-1.5.8/index.php/MotionStates

#ifndef __MotionState_h_
#define __MotionState_h_

#include <Ogre.h>
#include <btBulletDynamicsCommon.h>

class MotionState : public btMotionState {
protected:
    Ogre::SceneNode* mSceneNode;
    btTransform mInitialPosition;
public:
    MotionState(const btTransform &initialPosition, Ogre::SceneNode *node)
    {
        mSceneNode = node;
		mInitialPosition = initialPosition;
    }

    virtual ~MotionState() {}

    void setNode(Ogre::SceneNode *node) {
        mSceneNode = node;
    }

    void updateTransform(btTransform& newpos) {
		mInitialPosition = newpos;
	}

    virtual void getWorldTransform(btTransform &worldTrans) const {
        worldTrans = mInitialPosition;
    }

    virtual void setWorldTransform(const btTransform &worldTrans) {
        if(mSceneNode == NULL)
            return; // silently return before we set a node

        btQuaternion rot = worldTrans.getRotation();
        mSceneNode ->setOrientation(rot.w(), rot.x(), rot.y(), rot.z());
        btVector3 pos = worldTrans.getOrigin();
        mSceneNode ->setPosition(pos.x(), pos.y(), pos.z());
    }
};

class KinematicMotionState : public MotionState {
public:
    KinematicMotionState(const btTransform &initialPosition,
        Ogre::SceneNode *node) : MotionState(initialPosition, node) {}

    virtual void getWorldTransform(btTransform &worldTrans) const {
        Ogre::Vector3 pos = mSceneNode->getPosition();
        Ogre::Quaternion rot = mSceneNode->getOrientation();
        // cout << pos << endl;
        worldTrans.setOrigin(btVector3(pos.x, pos.y, pos.z));
        worldTrans.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));
    }

    virtual void setWorldTransform(const btTransform &worldTrans) {}
     
};

//---------------------------------------------------------------------------

#endif // #ifndef __MotionState_h_

//---------------------------------------------------------------------------