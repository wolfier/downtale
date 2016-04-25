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

/*
    Disclaimer: When the game is unrepsonsive press space to reset
*/

#include <iostream>
#include <OgreStringConverter.h>
#include "Game.h"
#include "Physics.h"
#include "GameObject.h"
#include "Sound.h"

struct Position {
    Ogre::Real bx;
    Ogre::Real by;
    Ogre::Real bz;
    Ogre::Real px;
    Ogre::Real py;
    Ogre::Real pz;
    Ogre::Real score;
};

Game::Game(void) : serverIP(NULL) {
    isGameRunning = false;
    // isServer = false;
    isSinglePlayer = true;
    // isBallLaunched = false;
    // score = 0;
    // cscore = 0;
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

    mainMenu->getChild("singlePlayerButton")->subscribeEvent(
        CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(
            &Game::setupSinglePlayer,
            this
        )
    );
    mainMenu->getChild("multiplayerButton")->subscribeEvent(
        CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(
            &Game::setupMultiplayer,
            this
        )
    );

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
    mPlayer->setPosition(0, 0, 0);
    mPlayer->setScale(5, 5, 5);

    PhysicsObject* playerPhysics = new PhysicsObject(mPhysics);
    playerPhysics->setShape(new btSphereShape(5.0f));
    playerPhysics->updateTransform(mPlayer->getPosition(), mPlayer->getOrientation());
    playerPhysics->setRestitution(0.95f);
    playerPhysics->setMass(0);//0.2f);
    playerPhysics->addToSimulator(mPlayer->getNode());

    mPlayer->addPhysicsObject(playerPhysics);


    // ground
    // Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    // Ogre::MeshPtr planePtr = Ogre::MeshManager::getSingleton().createPlane(
    //     "ground",
    //     Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    //     plane, 
    //     2000, 2000, 20, 20, 
    //     true, 
    //     1, 5, 10, 
    //     Ogre::Vector3::UNIT_Z);

    // mGround = new GameObject(mSceneMgr, mRootNode, "Ground", &eventQueue);
    // mGround->setEntityObject(
    //         new EntityObject(mSceneMgr, "ground", "Examples/Rockwall", false));
    // mGround->setPosition(0, -85, 0);

    // PhysicsObject* groundPhysics = new PhysicsObject(mPhysics);
    // groundPhysics->setShape(new btBoxShape(btVector3(5000, 1, 5000)));
    // groundPhysics->updateTransform(mGround->getPosition(), mGround->getOrientation());
    // groundPhysics->addToSimulator(mGround->getNode());

    // mGround->addPhysicsObject(groundPhysics);

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

    // lights
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(-1, 0, 0);
    light->setDiffuseColour(Ogre::ColourValue::White);
    light->setSpecularColour(Ogre::ColourValue::White);
    light->setPosition(0, 50, -160);
    Ogre::Light* light2 = mSceneMgr->createLight("Light2");
    light2->setType(Ogre::Light::LT_POINT);
    light2->setDiffuseColour(Ogre::ColourValue::White);
    light2->setSpecularColour(Ogre::ColourValue::White);
    light2->setPosition(0, 50, 100);

    // camera
    mCamera->setPosition(0, 200, 0);
    mCamera->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);

    // skybox
    mSceneMgr->setSkyBox(true, "Examples/SceneSkyBox1");
}

bool Game::setupSinglePlayer(const CEGUI::EventArgs &e){
    isSinglePlayer = true;
    isGameRunning = true;
    mainMenu->setVisible(false);
    // HUD->setVisible(true);
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
    // if (serverIP == NULL && mNetMgr->scanForActivity()) {
    //     // is server and message received
    //     // printf("got a message, %d, %d, %d\n", mNetMgr->getClients(), mNetMgr->tcpServerData.updated, mNetMgr->tcpServerData.output[0]);
    //     // printf("%d\n", mNetMgr->tcpClientData[0]->output[0]);
    //     mNetMgr->tcpServerData.updated = false;                 /// pretty sure this is wrong
    //     if (mNetMgr->tcpClientData[0]->output[0] == 1)
    //         mBall->reset();
    // }
        
    // mKeyboard->capture();
    // mMouse->capture();

    // mPhysics->stepSimulation(evt.timeSinceLastFrame, 1, 1/60.0f);
    // // mGUI->injectTimePulse(evt.timeSinceLastFrame);

    // mPhysics->checkCollide(mGround->getPhysicsObject(), mBall->getPhysicsObject());
    // int score = getScore();
    // if (mBall->update()) {
    //     score = 0;
    //     if (mSound->getSound()){
    //         mSound->playTableCollide();

    // if (isServer) {
    //     // is server and message received
    //     // printf("got a message, %d, %d, %d\n", mNetMgr->getClients(), mNetMgr->tcpServerData.updated, mNetMgr->tcpServerData.output[0]);
    //     // printf("%d\n", mNetMgr->tcpClientData[0]->output[0]);
    //     mNetMgr->tcpServerData.updated = false;
    //     if (mNetMgr->tcpClientData[0]->output[0] == 1)
    //         mBall->reset();
    // }

    // if(!isGameRunning && !isSinglePlayer){
    //     if(isServer){
    //         if(mNetMgr->scanForActivity()){
    //             mNetMgr->tcpServerData.updated = false;
    //             //code 100 = client joined
    //             // printf("%d\n",strcmp(mNetMgr->tcpClientData[0]->output,"100"));
    //             if(strcmp(mNetMgr->tcpClientData[0]->output,"100") == 0){
    //                 isGameRunning = true;
    //                 mainMenu->setVisible(false);
    //                 HUD->setVisible(true);
    //                 CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();
    //                 mNetMgr->denyConnections();
    //             }
    //         }
    //     }
    //     else{   //client
    //         // const char data = 1;
    //         // mNetMgr->messageServer(PROTOCOL_TCP, data, 1);
    //         char data[128] = "100";
    //         mNetMgr->messageServer(PROTOCOL_TCP, data, strlen(data));

    //         isGameRunning = true;
    //         mainMenu->setVisible(false);
    //         HUD->setVisible(true);
    //         CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();
    //     }
    // }
    // if(isGameRunning){
    //     HUD->getChild("PlayerScore")->setText("Score: " + std::to_string(score));
    //     if(isSinglePlayer){
    //         simulate(evt);
    //     }
    //     else{   //multiplayer
    //         if(isServer){
    //             simulate(evt);
    //             if(mNetMgr->scanForActivity()){
    //                 mNetMgr->tcpServerData.updated = false;
                    
    //                 if( strcmp("200", mNetMgr->tcpClientData[0]->output) == 0){
    //                     printf("%s\n", "launching");
    //                     mPhysics->setGravity(-150.f);
    //                     mBall->launch();
    //                     mBall->reset();
    //                     mBall->readd();
    //                     isBallLaunched = true;
    //                     // char data[128] = "400";
    //                     // mNetMgr->messageClient(PROTOCOL_TCP, 0, data, strlen(data));
    //                 }
    //                 else{
    //                     // printf("%s\n", "ball moving");
    //                     struct Position *p = (struct Position *)mNetMgr->tcpClientData[0]->output;
    //                     mBall->setPosition(p->bx, p->by, -400);
    //                     mBall->updateTransform(mBall->getPosition(), mBall->getOrientation());
    //                 }
    //                 struct Position p;
    //                 p.px = mPaddle->getPosition().x;
    //                 p.py = mPaddle->getPosition().y;
    //                 p.pz = mPaddle->getPosition().z;

    //                 mNetMgr->messageClient(PROTOCOL_TCP, 0, (char *)&p, sizeof(Position) & INT_MAX);
    //             }
    //             if(isBallLaunched){
    //                 struct Position p;
    //                 p.bx = mBall->getPosition().x;
    //                 p.by = mBall->getPosition().y;
    //                 p.bz = mBall->getPosition().z;
    //                 p.px = mPaddle->getPosition().x;
    //                 p.py = mPaddle->getPosition().y;
    //                 p.pz = mPaddle->getPosition().z;
    //                 p.score = cscore;

    //                 mNetMgr->messageClient(PROTOCOL_TCP, 0, (char *)&p, sizeof(Position) & INT_MAX);
    //             }
    //         }
    //         else{   // client
    //             if(mNetMgr->scanForActivity()){
    //                 mNetMgr->tcpServerData.updated = false;
    //                 if( strcmp("300", mNetMgr->tcpServerData.output) == 0){
    //                     isBallLaunched = false;
    //                     printf("%s\n", "got 300");
    //                 }
    //                 if(isBallLaunched){
                       
    //                         // struct Position p;
    //                         // p.bx = mBall->getPosition().x;
    //                         // p.by = mBall->getPosition().y+10;
    //                         // p.bz = -400;
                
    //                         // mNetMgr->messageServer(PROTOCOL_TCP, (char *)&p, sizeof(Position) & INT_MAX);
                   
    //                     struct Position *p = (struct Position *)mNetMgr->tcpServerData.output;

    //                     mBall->setPosition(p->bx, p->by, p->bz);
    //                     mPaddle->setPosition(p->px, p->py, p->pz);
    //                     score = p->score;
                        
    //                 }
    //                 else{
    //                     struct Position *p = (struct Position *)mNetMgr->tcpServerData.output;
    //                         mPaddle->setPosition(p->px, p->py, p->pz);
    //                 }
    //             }
    //         }
    //     }
    // }

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

bool Game::keyPressed(const OIS::KeyEvent &arg){
    // if (arg.key == OIS::KC_S) {
    //     mSound->mute();
    // } else if (arg.key == OIS::KC_SPACE) {
    //     // if (serverIP != NULL) {
    //     //     const char data = 1;
    //     //     mNetMgr->messageServer(PROTOCOL_TCP, &data, 1);
    //     // }
    //     if(isServer){

    //     }
    //     else
    //     {
    //         isBallLaunched = false;
    //     }
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
