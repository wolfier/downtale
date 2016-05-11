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

#include <vector>

#include "BaseApplication.h"
#include "Physics.h"
#include "Sound.h"
#include "Player.h"

#include "NetManager.h"
#include "DynamicLineDrawer.hpp"

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

//---------------------------------------------------------------------------

enum DIRECTION {
    UP = 1 << 0,
    LEFT = 1 << 1,
    DOWN = 1 << 2,
    RIGHT = 1 << 3,
    BRAKE = 1 << 4,
    BOOST = 1 << 5,
};

class Game : public BaseApplication {
public:
    Game(void);
    virtual ~Game(void);

    const char*       serverIP;
    bool setupSinglePlayer(const CEGUI::EventArgs &e);
    bool setupMultiplayer(const CEGUI::EventArgs &e);

    void setupGUI();
    void simulate(const Ogre::FrameEvent& evt);
    void ring(int i, int r, float x, float y);

protected:
    virtual void createScene(void);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    virtual int getScore();
    virtual void setScore(int s);

    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual bool keyPressed(const OIS::KeyEvent &arg);
    virtual bool keyReleased(const OIS::KeyEvent &arg);
    void reset();

    Ogre::SceneNode*    mRootNode;
    Physics*            mPhysics;

    GameObject*         startingPlatform;
    GameObject*         mRecentGround;
    GameObject*         mFar;
    GameObject*         mFloor;

    // Paddle*             mPaddle;
    // Table*              mTable;
    Player*                mPlayer;
    PhysicsObject*         mPlayerPhysics;
    std::vector<GameObject*> boxes;
    std::vector<GameObject*> glass;
    std::vector<GameObject*> powers;

    Sound*              mSound;
    NetManager*         mNetMgr;

    CEGUI::OgreRenderer* renderer;
    CEGUI::Window* mRootWindow;
    CEGUI::Window* mainMenu;
    CEGUI::Window* HUD;
    CEGUI::Window* endMenu;
    float meter;
    float maxMeter;

    int movement = 0;
    float flow = -1;
    // float               dragSensitivity;
    float               turnSensitivity;
    // float               rotSensitivity;
    // float               paddleBoundX;
    // float               paddleBoundY;
    // bool                isSwinging;
    // bool                isServer;
    bool                isSinglePlayer;
    bool                isGameRunning;
    bool                restart;
    // bool                isBallLaunched;
    // bool                networkStarted;
    int                 score;
    bool                shield;
    float               time;
    // int                 cscore;

    // Ogre::Vector3       oldpos;

    // std::queue<Event> eventQueue;
    // virtual btVector3 OgreToBulletV(Ogre::Vector3);
    // virtual btQuaternion OgreToBulletQ(Ogre::Quaternion);

    std::deque<Ogre::Vector3> points;
    CDynamicLineDrawer* lines;
};

//---------------------------------------------------------------------------

#endif // #ifndef __Game_h_

//---------------------------------------------------------------------------
