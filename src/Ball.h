#pragma once

#include "GameObject.h"

class Ball : public GameObject {

    Ogre::Vector3     spawnPos;
    Ogre::Quaternion  spawnRot;

public:
	Ball(Ogre::SceneManager* mgr, Ogre::SceneNode* node, std::queue<Event>* eventQueue);
	bool update(void);
	void reset();
	void readd();
	void launch();
	void still();
	void updateTransform(Ogre::Vector3 pos, Ogre::Quaternion qt);

};