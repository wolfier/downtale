#pragma once

#include "GameObject.h"

class Table : public GameObject {
public:
	Table(Ogre::SceneManager* mgr, Ogre::SceneNode* node, std::queue<Event>* eventQueue);
	bool update(void);
	int score;
};