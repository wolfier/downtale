/*
-----------------------------------------------------------------------------
Filename:    Game.cpp
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

// Reference:
// http://www.ogre3d.org/tikiwiki/DynamicLineDrawing&structure=Cookbook#Example
// http://bulletphysics.org/Bullet/BulletFull/btRigidBody_8h_source.html


#include <iostream>
#include <OgreStringConverter.h>
#include "Game.h"
#include "Physics.h"
#include "GameObject.h"
#include "Sound.h"

Game::Game(void) : serverIP(NULL) {
    isGameRunning = false;
    // isServer = false;
    isSinglePlayer = true;
    // isBallLaunched = false;
    score = 0;
    // cscore = 0;
    meter = 1000.0;
    maxMeter = 1000.0;
    shield = false;
}

Game::~Game(void) {
    // if (mPhysics) delete mPhysics;
    // if (mPaddle) delete mPaddle;
    // if (mTable) delete mTable;
    // if (mSound) delete mSound;
    // if (mGui) delete mGui;
    if(mNetMgr) delete mNetMgr;
}

void Game::setupGUI(){
    renderer = &CEGUI::OgreRenderer::bootstrapSystem();

    CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
    CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

    mRootWindow = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("uiLayout.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mRootWindow);

    mainMenu = mRootWindow->getChild("mainMenu");
    HUD = mRootWindow->getChild("HUD");
    endMenu = mRootWindow->getChild("endMenu");

    mainMenu->getChild("singlePlayerButton")->subscribeEvent(
        CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(
            &Game::setupSinglePlayer,
            this
        )
    );
    // mainMenu->getChild("multiplayerButton")->subscribeEvent(
    //     CEGUI::PushButton::EventClicked,
    //     CEGUI::Event::Subscriber(
    //         &Game::setupMultiplayer,
    //         this
    //     )
    // );

}

void Game::ring(int i, int r, float x, float y){

    // GameObject* box = new GameObject(mSceneMgr, mRootNode, "1-Ring" + std::to_string(i));
    // box->setPosition(x, i, y);

    // PhysicsObject* boxPhysics = new PhysicsObject(mPhysics);
    // boxPhysics->setShape(new btSphereShape(100));
    // boxPhysics->updateTransform(box->getPosition(), box->getOrientation());
    // boxPhysics->setMass(0);
    // boxPhysics->addToSimulator(box->getNode());

    // box->addPhysicsObject(boxPhysics);
    // boxes.push_back(box);

    if((static_cast<float>(rand()) / RAND_MAX) < 0.05){
        if((static_cast<float>(rand()) / RAND_MAX) < 0.8){
            GameObject* mPowerup = new GameObject(mSceneMgr, mRootNode, "boost"+std::to_string(i));
            mPowerup->setEntityObject(new EntityObject(mSceneMgr, "sphere.mesh", "Examples/Boost", false));
            mPowerup->setPosition(x, i, y);
            powers.push_back(mPowerup);
        }else {
            GameObject* mPowerup = new GameObject(mSceneMgr, mRootNode, "shield"+std::to_string(i));
            mPowerup->setEntityObject(new EntityObject(mSceneMgr, "sphere.mesh", "Examples/Shield", false));
            mPowerup->setPosition(x, i, y);
            powers.push_back(mPowerup);
        }
    }

    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshPtr planePtr = Ogre::MeshManager::getSingleton().createPlane(
        "ground"+std::to_string(i),
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 
        r, r, 20, 20, 
        true, 
        1, 5, 10, 
        Ogre::Vector3::UNIT_Z);

    GameObject* mGround = new GameObject(mSceneMgr, mRootNode, "Ground"+std::to_string(i));
    mGround->setEntityObject(
            new EntityObject(mSceneMgr, "ground"+std::to_string(i), "Examples/TransparentTexture", false));
    mGround->setPosition(x, i, y);
    glass.push_back(mGround);


    // GameObject* c = new GameObject(mSceneMgr, mRootNode, "center" + std::to_string(i));
    // c->setPosition(x, i, y);

    float w = 500.0;
    float l = 200.0;

    // PhysicsObject* cPhysics = new PhysicsObject(mPhysics);
    // cPhysics->setShape(new btBoxShape(btVector3(w, 30, l)));
    // cPhysics->updateTransform(c->getPosition(), box->getOrientation());
    // cPhysics->setMass(0);
    // cPhysics->addToSimulator(c->getNode());

    // box->addPhysicsObject(boxPhysics);

    GameObject* box = new GameObject(mSceneMgr, mRootNode, "1-Ring" + std::to_string(i));
    box->setPosition(x, i, y+r);

    PhysicsObject* boxPhysics = new PhysicsObject(mPhysics);
    boxPhysics->setShape(new btBoxShape(btVector3(w, 30, l)));
    boxPhysics->updateTransform(box->getPosition(), box->getOrientation());
    boxPhysics->setMass(0);
    boxPhysics->addToSimulator(box->getNode());

    box->addPhysicsObject(boxPhysics);
    boxes.push_back(box);

    GameObject* box1 = new GameObject(mSceneMgr, mRootNode, "2-Ring" + std::to_string(i));
    box1->setPosition(x, i, y-r);

    PhysicsObject* boxPhysics1 = new PhysicsObject(mPhysics);
    boxPhysics1->setShape(new btBoxShape(btVector3(w, 30, l)));
    boxPhysics1->updateTransform(box1->getPosition(), box1->getOrientation());
    boxPhysics1->setMass(0);
    boxPhysics1->addToSimulator(box1->getNode());

    box1->addPhysicsObject(boxPhysics1);
    boxes.push_back(box1);

    w = 200.0;
    l = 400.0;

    GameObject* box2 = new GameObject(mSceneMgr, mRootNode, "3-Ring" + std::to_string(i));
    box2->setPosition(x+r, i, y);

    PhysicsObject* boxPhysics2 = new PhysicsObject(mPhysics);
    boxPhysics2->setShape(new btBoxShape(btVector3(w, 30, l)));
    boxPhysics2->updateTransform(box2->getPosition(), box2->getOrientation());
    boxPhysics2->setMass(0);
    boxPhysics2->addToSimulator(box2->getNode());

    box2->addPhysicsObject(boxPhysics2);
    boxes.push_back(box2);

    GameObject* box3 = new GameObject(mSceneMgr, mRootNode, "4-Ring" + std::to_string(i));
    box3->setPosition(x-r, i, y);

    PhysicsObject* boxPhysics3 = new PhysicsObject(mPhysics);
    boxPhysics3->setShape(new btBoxShape(btVector3(w, 30, l)));
    boxPhysics3->updateTransform(box3->getPosition(), box3->getOrientation());
    boxPhysics3->setMass(0);
    boxPhysics3->addToSimulator(box3->getNode());

    box3->addPhysicsObject(boxPhysics3);
    boxes.push_back(box3);
}

// TODO: Create your scene here :)
void Game::createScene(void) {
    mSound = new Sound(true);
    setupGUI();
    // mGUI->setupSinglePlayerButton(&Game::setupSinglePlayer, this);

    Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
    Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(16);
    mRootNode = mSceneMgr->getRootSceneNode();
    mPhysics = new Physics(mSceneMgr, true);

    // Player
    mPlayer = new Player(mSceneMgr, mRootNode);
    mPlayer->setPosition(0, 500, 0);
    mPlayer->setScale(1, 1, 1);

    mPlayerPhysics = new PhysicsObject(mPhysics);
    mPlayerPhysics->setShape(new btSphereShape(10.0f));
    mPlayerPhysics->updateTransform(mPlayer->getPosition(), mPlayer->getOrientation());
    mPlayerPhysics->setRestitution(1.0f);
    mPlayerPhysics->setMass(1);
    // mPlayerPhysics->setKinematic();
    mPlayerPhysics->addToSimulator(mPlayer->getNode());

    mPlayer->addPhysicsObject(mPlayerPhysics);

    GameObject* startingPlatform = new GameObject(mSceneMgr, mRootNode, "startingPlatform");
    startingPlatform->setPosition(0, 400, 0);

    PhysicsObject* spPhysics = new PhysicsObject(mPhysics);
    spPhysics->setShape(new btBoxShape(btVector3(100, 30, 100)));
    spPhysics->updateTransform(startingPlatform->getPosition(), startingPlatform->getOrientation());
    spPhysics->setMass(0);
    spPhysics->addToSimulator(startingPlatform->getNode());

    startingPlatform->addPhysicsObject(spPhysics);

    // // ground
    // Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    // Ogre::MeshPtr planePtr = Ogre::MeshManager::getSingleton().createPlane(
    //     "ground",
    //     Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    //     plane,
    //     2000, 2000, 20, 20,
    //     true,
    //     1, 5, 10,
    //     Ogre::Vector3::UNIT_Z);

    // mGround = new GameObject(mSceneMgr, mRootNode, "Ground");
    // mGround->setEntityObject(
    //         new EntityObject(mSceneMgr, "ground", "Examples/Rockwall", false));
    // mGround->setPosition(0, -5000, 0);

    // PhysicsObject* groundPhysics = new PhysicsObject(mPhysics);
    // groundPhysics->setShape(new btBoxShape(btVector3(5000, 1, 5000)));
    // groundPhysics->updateTransform(mGround->getPosition(), mGround->getOrientation());
    // groundPhysics->addToSimulator(mGround->getNode());

    // mGround->addPhysicsObject(groundPhysics);

    // for (int i = -50000; i < 0; i += 5) {
    //     float r1, r2, w, l;
    //     if ((r1 = static_cast<float>(rand()) / RAND_MAX) < 0.1) {
    //         r1 = static_cast<float>(rand()) / RAND_MAX * 20000 - 10000;
    //         r2 = static_cast<float>(rand()) / RAND_MAX * 20000 - 10000;
    //         GameObject* box = new GameObject(mSceneMgr, mRootNode, "Box" + std::to_string(i));
    //         box->setPosition(r1, i, r2);

    //         w = static_cast<float>(rand()) / RAND_MAX * 50 + 20;
    //         l = static_cast<float>(rand()) / RAND_MAX * 50 + 20;

    //         PhysicsObject* boxPhysics = new PhysicsObject(mPhysics);
    //         boxPhysics->setShape(new btBoxShape(btVector3(w, 30, l)));
    //         boxPhysics->updateTransform(box->getPosition(), box->getOrientation());
    //         boxPhysics->setMass(0);
    //         boxPhysics->addToSimulator(box->getNode());

    //         box->addPhysicsObject(boxPhysics);
    //         boxes.push_back(box);
    //     }
    // }
    float l1 = 0, l2 = -1000;
    for (int i = -50000; i < -5000; i += 3000) {
        l1 = l1 + static_cast<float>(rand()) / RAND_MAX * 300 - 150;
        l2 = l2 + static_cast<float>(rand()) / RAND_MAX * 300 - 150;
        ring(i, 750, l1, l2);
        // printf("a %f %f\n", l1, l2);
    }
    for (int i = -75000; i < -50000; i += 1000) {
        ring(i, 750, l1, l2);
        // printf("k %f %f\n", l1, l2);
    }
    for (int i = -150000; i < -75000; i += 2500) {
        l1 = l1 + static_cast<float>(rand()) / RAND_MAX * 300 - 150;
        l2 = l2 + static_cast<float>(rand()) / RAND_MAX * 300 - 150;
        ring(i, 750, l1, l2);
        // printf("b %f %f\n", l1, l2);
    }

    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshPtr planePtr = Ogre::MeshManager::getSingleton().createPlane(
        "floor",
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 
        20000, 20000, 20, 20, 
        true, 
        1, 5, 10, 
        Ogre::Vector3::UNIT_Z);

    mFloor = new GameObject(mSceneMgr, mRootNode, "Floor");
    mFloor->setEntityObject(
            new EntityObject(mSceneMgr, "floor", "Examples/Rockwall", false));
    mFloor->setPosition(0, -175000, 0);

    PhysicsObject* floorPhysics = new PhysicsObject(mPhysics);
    floorPhysics->setShape(new btBoxShape(btVector3(10000, 30, 10000)));
    floorPhysics->updateTransform(mFloor->getPosition(), mFloor->getOrientation());
    floorPhysics->setMass(0);
    floorPhysics->addToSimulator(mFloor->getNode());

    mFloor->addPhysicsObject(floorPhysics);

    // // paddle
    // mPaddle = new Paddle(mSceneMgr, mRootNode, &eventQueue);
    // mPaddle->setPosition(0, 0, -25);
    // mPaddle->setScale(3, 3, 3);
    // mPaddle->setRotation(90, 0, 0);

    // PhysicsObject* paddlePhysics = new PhysicsObject(mPhysics);
    // paddlePhysics->setShape(new btBoxShape(btVector3(8.0, 3.0, 15.0)));
    // paddlePhysics->updateTransform(mPaddle->getPosition(), mPaddle->getOrientation());
    // paddlePhysics->setKinematic();
    // paddlePhysics->addToSimulator(mPaddle->getNode());

    // mPaddle->addPhysicsObject(paddlePhysics);

    // // paddle input variables
    // dragSensitivity = .2;
    // swingSensitivity = .12;
    // rotSensitivity = .6;
    // paddleBoundX = 130;
    // paddleBoundY = 80;
    // isSwinging = false;

    // // table
    // mTable = new Table(mSceneMgr, mRootNode, &eventQueue);
    // mTable->setPosition(-65, -50, -320);
    // mTable->setScale(5, 5, 5);

    // PhysicsObject* tablePhysics = new PhysicsObject(mPhysics);
    // tablePhysics->setShape(new btBoxShape(btVector3(76, 4.0, 136.0)));
    // tablePhysics->updateTransform(Ogre::Vector3(2.5, -47.8, -190), mTable->getOrientation());
    // tablePhysics->addToSimulator(mTable->getNode());

    // mTable->addPhysicsObject(tablePhysics);

    points.push_back(Ogre::Vector3(1000.0f, -100000.0f, 0.0f ));
    points.push_back(Ogre::Vector3(1000.0f, 500.0f, 0.0f ));
    points.push_back(Ogre::Vector3(0.0f, 500.0f, 0.0f ));
    points.push_back(Ogre::Vector3(0.0f, -50000.0f, 0.0f ));

    lines = new CDynamicLineDrawer();
    for (int i=0; i<points.size(); i++) {
      lines->AddPoint(points[i], Ogre::ColourValue(1, 1, 1));
    }
    lines->Update();
    Ogre::SceneNode *linesNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("lines");
    linesNode->attachObject(lines);

    // lights
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(0, -1, 0);
    light->setDiffuseColour(Ogre::ColourValue::White);
    light->setSpecularColour(Ogre::ColourValue::White);
    light->setPosition(0, 200, 0);

    // camera
    mCamera->setPosition(Ogre::Vector3(0, 1000, 0));
    // mCamera->lookAt(Ogre::Vector3(0,0,-1));

    // mCamera->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);

    // skybox
    // mSceneMgr->setSkyBox(true, "Examples/SceneSkyBox1");
}

bool Game::setupSinglePlayer(const CEGUI::EventArgs &e){
    isSinglePlayer = true;
    isGameRunning = true;
    mainMenu->setVisible(false);
    HUD->setVisible(true);
    endMenu->setVisible(false);
    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();
    // mBall->launch();
    // mBall->reset();
    // mBall->readd();
    mPlayer-> reinit();

    return true;
}

bool Game::setupMultiplayer(const CEGUI::EventArgs &e){
    // isSinglePlayer = false;

    // mNetMgr = new NetManager();
    // mNetMgr->initNetManager();
    // mNetMgr->addNetworkInfo(PROTOCOL_TCP, serverIP);

    // if (serverIP == NULL) {
    //     isServer = true;
    //     mNetMgr->startServer();
    //     mNetMgr->acceptConnections();
    // } else {
    //     mCamera->setPosition(0, 25, -700);
    //     mCamera->setDirection(0, 0, 1);
    //     mNetMgr->startClient();
    // }

    // mRootWindow->getChild("mainMenu/singlePlayerButton")->setVisible(false);
    // mRootWindow->getChild("mainMenu/multiplayerButton")->setVisible(false);
    // mRootWindow->getChild("mainMenu/infoBox")->setText("Host IP is " + mNetMgr->getIPstring() + "\nWaiting for client... " );

    // mPhysics->setGravity(0.f);

    // mBall->reset();

    return true;
}

int Game::getScore() {
    return 0; //Ogre::StringConverter::parseInt(mScoreTextBox->getText());
}

void Game::setScore(int s) {
    // mScoreTextBox->setText(Ogre::StringConverter::toString(s));
}

bool Game::frameRenderingQueued(const Ogre::FrameEvent& evt) {
    time = time + 1;
    // if (serverIP == NULL && mNetMgr->scanForActivity()) {
    //     // is server and message received
    //     // printf("got a message, %d, %d, %d\n", mNetMgr->getClients(), mNetMgr->tcpServerData.updated, mNetMgr->tcpServerData.output[0]);
    //     // printf("%d\n", mNetMgr->tcpClientData[0]->output[0]);
    //     mNetMgr->tcpServerData.updated = false;                 /// pretty sure this is wrong
    //     if (mNetMgr->tcpClientData[0]->output[0] == 1)
    //         mBall->reset();
    // }

    points.push_back(mPlayer->getPosition());

    Ogre::SceneNode *lnode = dynamic_cast<Ogre::SceneNode*>(mSceneMgr->getRootSceneNode()->getChild("lines"));
    CDynamicLineDrawer *lines = dynamic_cast<CDynamicLineDrawer*>(lnode->getAttachedObject(0));

    // add points if you wish (maybe elsewhere, this is just an example)
    //somePoints.push_back(Ogre::Vector3(4543.0f, 45.0f, 134.0f));

    if (lines->GetNumPoints()!= points.size()) {
      // Oh no!  Size changed, just recreate the list from scratch
      lines->Clear();
      for (int i=0; i<points.size(); ++i) {
        lines->AddPoint(points[i], Ogre::ColourValue(1, 1, 1));
      }
    }
    else {
      // Just values have changed, use 'setPoint' instead of 'addPoint'
      for (int i=0; i<points.size(); ++i) {
        lines->SetPoint(i, points[i], Ogre::ColourValue(1, 1, 1));
      }
    }
    lines->Update();

    // if ((static_cast<float>(rand()) / RAND_MAX) < 0.2) {
    //     mPhysics->setDebug(0);
    // }else{
    //     mPhysics->setDebug(1);
    // }
    if(mSceneMgr->getAmbientLight().g <= 0 || mSceneMgr->getAmbientLight().g > 1){
        flow = -flow;
    }
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1, mSceneMgr->getAmbientLight().g-flow*0.001, 1));

    mKeyboard->capture();
    mMouse->capture();

    mPhysics->stepSimulation(evt.timeSinceLastFrame, 1, 1/60.0f);

    mPhysics->checkCollide(mFloor->getPhysicsObject(), mPlayer->getPhysicsObject());
    if (mPlayer->update()) {
        mPlayer->setPosition(Ogre::Vector3(mPlayer->getPosition().x,-174000,mPlayer->getPosition().z));
        mPlayer->getPhysicsObject()->updateTransform(mPlayer->getPosition(), mPlayer->getOrientation());
        mPlayer->reinit();
        mPhysics->setGravity(0.f);
        endMenu->setVisible(true);
        endMenu->getChild("Stats")->setText(
            "  You Finished in:       " + std::to_string(time/60.0) + " seconds\n" +
            "                 Score:       " + std::to_string(score) + "\n" + 
            "     Shield Bonus:       " + ((shield) ? "1000" : "0") + "\n" +
            "         Fuel Bonus:       " + std::to_string(meter) + "\n\n"+
            "          Total:       " + std::to_string((time/60.0) + score + ((shield) ? 1000 : 0) + meter)
        );
        printf("b\n");
    }

    for(GameObject* a : boxes){
        mPhysics->checkCollide(a->getPhysicsObject(), mPlayer->getPhysicsObject());
        if (mPlayer->update()) {
            // mPlayer->setPosition(Ogre::Vector3(0,500,0));
            if(!shield){
                mPlayer->setPosition(Ogre::Vector3(0,500,0));
                mPlayer->getPhysicsObject()->updateTransform(mPlayer->getPosition(), mPlayer->getOrientation());
                mPlayer->reinit();
                printf("a\n");
            }else{
                shield = !shield;
                mPlayer->setPosition(mRecentGround->getPosition());
                mPlayer->getPhysicsObject()->updateTransform(mPlayer->getPosition(), mPlayer->getOrientation());
                mPlayer->reinit();
                printf("s\n");
            }
            break;
        }
    }

    for(GameObject* a : glass){
        mRecentGround = a;
        // printf("checkig %s\n", a->getEntity()->getName().c_str());
        Ogre::Vector3 c = a->getPosition()-mPlayer->getPosition();
        if(!a->touched && abs(c.y) < 50 && abs(c.x) < 750 && abs(c.z) < 750){
            printf("%s contain\n", a->getEntity()->getName().c_str());
            a->touched = true;
            a->getEntity()->setMaterialName("Examples/TransparentTexture2");
            score = score + 500;
            mSound->playShatter(rand() % 4);
            break;
        }
    }

    for(GameObject* a : powers){
        Ogre::Vector3 c = a->getPosition()-mPlayer->getPosition();
        if(!a->touched && abs(c.y) < 50 && abs(c.x) < 100 && abs(c.z) < 100){
            printf("%s contain\n", a->getEntity()->getName().c_str());
            a->touched = true;
            a->getEntity()->setMaterialName("Examples/TransparentTexture2");
            if(a->getEntity()->getName().find("boost")){
                meter = meter + 300;
            }
            if(a->getEntity()->getName().find("shield")){
                shield = true;
            }
            break;
        }
    }

    btVector3 relpos=mPlayerPhysics->getBody()->getCenterOfMassPosition();
    btVector3 wvel=mPlayerPhysics->getBody()->getVelocityInLocalPoint(relpos);

    HUD->getChild("PlayerScore")->setText("Score: " + std::to_string(score) +
        "\nFuel: " + std::to_string(meter) + "/" + std::to_string(maxMeter) +
        "\nSpeed: " + std::to_string(sqrt(abs(wvel.y()))) + " m/s" +
        "\nPower: " + ((shield) ? "shield" : "none")
        );

    btRigidBody* playerBody = mPlayerPhysics->getBody();

    Ogre::Vector3 dir = mCamera->getDirection().normalisedCopy();
    dir.y = 0;
    dir.normalise();

    // std::cout << dir << std::endl;

    btVector3 vel = playerBody->getLinearVelocity();
    btScalar y = vel.y();

    if (movement & UP) {
        // mPlayer->setPosition(mPlayer->getPosition()+Ogre::Vector3(0,0,-2));
        playerBody->applyCentralImpulse(btVector3(dir.x, 0, dir.z));
    }
    if (movement & LEFT) {
        // mPlayer->setPosition(mPlayer->getPosition()+Ogre::Vector3(-2,0,0));
        playerBody->applyCentralImpulse(btVector3(dir.z, 0, -dir.x));
    }
    if (movement & DOWN) {
        // mPlayer->setPosition(mPlayer->getPosition()+Ogre::Vector3(0,0,2));
        playerBody->applyCentralImpulse(btVector3(-dir.x, 0, -dir.z));
    }
    if (movement & RIGHT) {
        // mPlayer->setPosition(mPlayer->getPosition()+Ogre::Vector3(2,0,0));
        playerBody->applyCentralImpulse(btVector3(-dir.z, 0, dir.x));
    }
    if (movement & BRAKE && wvel.y() < 0) {
        // mPlayer->setPosition(mPlayer->getPosition()+Ogre::Vector3(2,0,0));
        mPlayerPhysics->getBody()->applyCentralImpulse(btVector3(0, abs(wvel.y())*0.00045, 0));
    }
    if (movement & BOOST && meter > 0) {

        // printf("a %f %f %f | %f\n", wvel.x(), wvel.y(), wvel.z(), meter);

        mPlayerPhysics->getBody()->applyCentralImpulse(btVector3(0, -2.0, 0));
        meter = meter-(100/meter);
        if(meter < 0) meter = 0;
    }
    if (sqrt(abs(wvel.y())) > 80){
        mPlayerPhysics->getBody()->applyCentralImpulse(btVector3(0, abs(wvel.y())*0.00045, 0));
    }

    mCamera->setPosition(mPlayer->getPosition() + Ogre::Vector3(0,-12,0));


    simulate(evt);
    CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);
    return BaseApplication::frameRenderingQueued(evt);
}

void Game::simulate(const Ogre::FrameEvent& evt){
        mPhysics->stepSimulation(evt.timeSinceLastFrame, 1, 1/60.0f);

        // if the ball touches the ground
        // ball collide flag triggers
        // mPhysics->checkCollide(mGround->getPhysicsObject(), mBall->getPhysicsObject());
        // if (mBall->update()) {
        //     //send to client that ball fell so they can set is ball launched to false
        //     if(isSinglePlayer){
        //         mBall->reset();
        //         mBall->readd();
        //     }
        //     if(isServer && isBallLaunched){
        //         mPhysics->setGravity(0);
        //         mBall->still();
        //         mBall->reset();
        //         isBallLaunched = false;
        //         char data[128] = "300";
        //         mNetMgr->messageClient(PROTOCOL_TCP, 0, data, strlen(data));
        //         printf("%s\n", "sending 300");
        //     }
        // }

        // int score = getScore();
        // if (mBall->update()) {
        //     // score = 0;
        //     if (mSound->getSound()){
        //         mSound->playTableCollide();
        //     }
        // }

        // mPhysics->checkCollide(mBall->getPhysicsObject(), mTable->getPhysicsObject());
        // if (mTable->update() && mSound->getSound()) {
        //    cscore++;
        // }

        // if (mTable->score > 0 && mSound->getSound()) {
        //     mSound->playTableCollide();
        // }

        // mPhysics->checkCollide(mBall->getPhysicsObject(), mPaddle->getPhysicsObject());
        // if (mPaddle->update() && mSound->getSound()) {
        //     score++;
        //     mSound->playPaddleSwing();
        // }
        // // setScore(score + mTable->score);
        // if(mPaddle->getPosition().x > paddleBoundX) {
        //     mPaddle->setPosition(paddleBoundX, mPaddle->getPosition().y, mPaddle->getPosition().z);
        // }
        // if(mPaddle->getPosition().x < -paddleBoundX) {
        //     mPaddle->setPosition(-paddleBoundX, mPaddle->getPosition().y, mPaddle->getPosition().z);
        // }
        // if(mPaddle->getPosition().y > paddleBoundY+20) {
        //     mPaddle->setPosition(mPaddle->getPosition().x, paddleBoundY+20, mPaddle->getPosition().z);
        // }
        // if(mPaddle->getPosition().y < -paddleBoundY+20) {
        //     mPaddle->setPosition(mPaddle->getPosition().x, -paddleBoundY+20, mPaddle->getPosition().z);
        // }

        // Ogre::Vector3 camPos = mCamera->getPosition();
        // Ogre::Vector3 padPos = mPaddle->getPosition();
        // if(!isSwinging)
        //     mCamera->setPosition(padPos.x, padPos.y + 12, camPos.z);
}
//---------------------------------------------------------------------------
CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;

    case OIS::MB_Right:
        return CEGUI::RightButton;

    case OIS::MB_Middle:
        return CEGUI::MiddleButton;

    default:
        return CEGUI::LeftButton;
    }
}

bool Game::mouseMoved(const OIS::MouseEvent &arg)
{
    // if(isGameRunning) {
    //     if(isServer | isSinglePlayer){
    //         if (arg.state.buttonDown(OIS::MB_Left)) {
    //             isSwinging = true;
    //             mPaddle->localtranslate(0, swingSensitivity*arg.state.Y.rel, 0);
    //         }
    //         else if (arg.state.buttonDown(OIS::MB_Right)) {
    //             mPaddle->rotate(0, 0, rotSensitivity*-arg.state.X.rel);
    //             mPaddle->localrotate(rotSensitivity*arg.state.Y.rel, 0, 0);
    //         }
    //         else {
    //             mPaddle->translate(dragSensitivity*arg.state.X.rel, dragSensitivity*-arg.state.Y.rel, 0);
    //         }
    //     }
    //     else{
    //         // printf("%d\n", isBallLaunched);
    //         if(!isBallLaunched){
    //             mBall->translate(-dragSensitivity*arg.state.X.rel, dragSensitivity*-arg.state.Y.rel, 0);
    //             mBall->setPosition(mBall->getPosition().x, mBall->getPosition().y, -400);
    //             struct Position p;
    //             p.bx = mBall->getPosition().x;
    //             p.by = mBall->getPosition().y;
    //             p.bz = mBall->getPosition().z;

    //             mNetMgr->messageServer(PROTOCOL_TCP, (char *)&p, sizeof(Position) & INT_MAX);
    //         }
    //     }

    // }

    if (isGameRunning) {
        float sensitivity = 0.001;
        mCamera->pitch(Ogre::Radian(arg.state.Y.rel * -sensitivity));
        if (mCamera->getDirection().y < -0.999) {
            // printf ("hoi\n");
            mCamera->pitch(Ogre::Radian(arg.state.Y.rel * sensitivity));
        }

        mCamera->yaw(Ogre::Radian(arg.state.X.rel * -sensitivity));
    }

    CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();

    context.injectMouseMove(arg.state.X.rel, arg.state.Y.rel);

    return BaseApplication::mouseMoved(arg);
}

bool Game::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
    // if(isGameRunning) {
    //     // NEED TO IMPLEMENT
    //     // send message to client to play the sound
    //     if(isServer | isSinglePlayer){
    //         if(id == OIS::MB_Left && mSound->getSound()) {
    //             mSound->playPaddleSwing();
    //         }
    //     }
    //     else
    //     {
    //         if(id == OIS::MB_Left && !isBallLaunched) {
    //             printf("%s\n", "pressed to launch");
    //             isBallLaunched = true;
    //             printf("%d\n", isBallLaunched);

    //             //send launch code
    //             // while(!isBallLaunched){
    //             char data[128] = "200";
    //             mNetMgr->messageServer(PROTOCOL_TCP, data, strlen(data));
    //             // }
    //         }

    //     }
    // }

    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertButton(id));
    return BaseApplication::mousePressed(arg, id);
}

bool Game::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
    // if(isGameRunning) {
    //     if(isServer | isSinglePlayer){
    //         if(id == OIS::MB_Right) {
    //             mPaddle->setRotation(90, 0, 0);
    //         }
    //         else if(id == OIS::MB_Left) {
    //             isSwinging = false;
    //             mPaddle->setPosition(mPaddle->getPosition().x, mPaddle->getPosition().y, -25);
    //         }
    //     }
    //     else
    //     {

    //     }
    // }
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertButton(id));

    return BaseApplication::mouseReleased(arg, id);
}

bool Game::keyReleased(const OIS::KeyEvent &arg){
    switch (arg.key) {
        case OIS::KC_M:
            mSound->mute();
            break;
        case OIS::KC_W:
            movement ^= UP;
            break;
        case OIS::KC_A:
            movement ^= LEFT;
            break;
        case OIS::KC_S:
            movement ^= DOWN;
            break;
        case OIS::KC_D:
            movement ^= RIGHT;
            break;
        case OIS::KC_LSHIFT:
            movement ^= BRAKE;
            break;
        case OIS::KC_SPACE:
            movement ^= BOOST;
            break;
        default: break;
    }
    // if (arg.key == OIS::KC_S) {
    //     mSound->mute();
    // } else if (arg.key == OIS::KC_W) {
    //     mPlayer->setPosition(mPlayer->getPosition()+Ogre::Vector3(0,0,10));
    // } else if (arg.key == OIS::KC_A) {
    //     mPlayer->setPosition(mPlayer->getPosition()+Ogre::Vector3(-10,0,0));
    // } else if (arg.key == OIS::KC_S) {
    //     mPlayer->setPosition(mPlayer->getPosition()+Ogre::Vector3(0,0,-10));
    // } else if (arg.key == OIS::KC_D) {
    //     mPlayer->setPosition(mPlayer->getPosition()+Ogre::Vector3(10,0,0));
    // }

    return BaseApplication::keyPressed(arg);
}

bool Game::keyPressed(const OIS::KeyEvent &arg){
    switch (arg.key) {
        case OIS::KC_M:
            mSound->mute();
            break;
        case OIS::KC_W:
            movement ^= UP;
            break;
        case OIS::KC_A:
            movement ^= LEFT;
            break;
        case OIS::KC_S:
            movement ^= DOWN;
            break;
        case OIS::KC_D:
            movement ^= RIGHT;
            break;
        case OIS::KC_LSHIFT:
            movement ^= BRAKE;
            break;
        case OIS::KC_SPACE:
            movement ^= BOOST;
            break;
        case OIS::KC_K:
            mPlayer->setPosition(Ogre::Vector3(0,500,0));
            mPlayer->getPhysicsObject()->updateTransform(mPlayer->getPosition(), mPlayer->getOrientation());
            mPhysics->setGravity(-25.0);
            mPlayer->reinit();
            endMenu->setVisible(false);
            score = 0;
            shield = false;
            meter = 1000;
            time = 0;
            break;
        default: break;
    }

    // if (arg.key == OIS::KC_S) {
    //     mSound->mute();
    // } else if (arg.key == OIS::KC_W) {
    //     mPlayer->setPosition(mPlayer->getPosition()+Ogre::Vector3(0,0,10));
    // } else if (arg.key == OIS::KC_A) {
    //     mPlayer->setPosition(mPlayer->getPosition()+Ogre::Vector3(-10,0,0));
    // } else if (arg.key == OIS::KC_S) {
    //     mPlayer->setPosition(mPlayer->getPosition()+Ogre::Vector3(0,0,-10));
    // } else if (arg.key == OIS::KC_D) {
    //     mPlayer->setPosition(mPlayer->getPosition()+Ogre::Vector3(10,0,0));
    // }

    return BaseApplication::keyPressed(arg);
}

//---------------------------------------------------------------------------
// Boilerplate stuff below
//---------------------------------------------------------------------------

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        Game app;

        if (argc == 2) {
            app.serverIP = argv[1];
        }

        try {
            app.go();
        } catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
