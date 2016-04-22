#pragma once

#include <Ogre.h>

class EntityObject {
public:
	EntityObject(Ogre::SceneManager* mgr, Ogre::String meshName,
			Ogre::String matName, bool castShadows);
	virtual Ogre::Entity* getEntity();
protected:
	Ogre::Entity* entity;
};