#pragma once

#include "GameObject.h"

class Paddle : public GameObject {
public:
	Paddle(Ogre::SceneManager* mgr, Ogre::SceneNode* node, std::queue<Event>* eventQueue);

	bool update(void);

};