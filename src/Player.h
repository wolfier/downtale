#pragma once

#include "GameObject.h"

class Player : public GameObject {
public:
	Player(Ogre::SceneManager* mgr, Ogre::SceneNode* node);

	bool update(void);

};