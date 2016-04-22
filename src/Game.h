/*
-----------------------------------------------------------------------------
Filename:    Game.h
-----------------------------------------------------------------------------

This source file is modified from part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
Tutorial Framework (for Ogre 1.9)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/
// Reference :
// https://github.com/cloudbreath9/PONG-PING/tree/physics
// https://github.com/mbelyaeva/PaddleShip/tree/master
// http://classes.cs.kent.edu/gpg/trac/wiki/jadamek
// http://bulletphysics.org/Bullet/BulletFull/classbtCollisionObject.html#a041fb60b524f5008b08bc9400e49a2de
// http://bulletphysics.org/mediawiki-1.5.8/index.php/MotionStates
// https://www.packtpub.com/sites/default/files/downloads/Integrating_with_Bullet_Physics.pdf

#ifndef __Game_h_
#define __Game_h_

#include "BaseApplication.h"
#include "Physics.h"
#include "Sound.h"

#include "NetManager.h"

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

//---------------------------------------------------------------------------

class Game : public BaseApplication {
public:
    Game(void);
    virtual ~Game(void);

    const char*       serverIP;
    bool setupSinglePlayer(const CEGUI::EventArgs &e);
    bool setupMultiplayer(const CEGUI::EventArgs &e);

    void setupGUI();
    void simulate(const Ogre::FrameEvent& evt);

protected:
    virtual void createScene(void);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    virtual int getScore();
    virtual void setScore(int s);

    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual bool keyPressed(const OIS::KeyEvent &arg);

    Ogre::SceneNode*    mRootNode;
    Physics*            mPhysics;

    // GameObject*         mGround;
    // Paddle*             mPaddle;
    // Table*              mTable;
    // Ball*               mBall;

    Sound*              mSound;
    NetManager*         mNetMgr;

    CEGUI::OgreRenderer* renderer;
    CEGUI::Window* mRootWindow;
    CEGUI::Window* mainMenu;
    CEGUI::Window* HUD;

    // float               dragSensitivity;
    // float               swingSensitivity;
    // float               rotSensitivity;
    // float               paddleBoundX;
    // float               paddleBoundY;
    // bool                isSwinging;
    // bool                isServer;
    // bool                isSinglePlayer;
    // bool                isGameRunning;
    // bool                isBallLaunched;
    // bool                networkStarted;
    // int                 score;
    // int                 cscore;

    // Ogre::Vector3       oldpos;

    // std::queue<Event> eventQueue;
    // virtual btVector3 OgreToBulletV(Ogre::Vector3);
    // virtual btQuaternion OgreToBulletQ(Ogre::Quaternion);
};

//---------------------------------------------------------------------------

#endif // #ifndef __Game_h_

//---------------------------------------------------------------------------
