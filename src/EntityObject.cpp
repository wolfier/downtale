#include "EntityObject.h"

EntityObject::EntityObject(Ogre::SceneManager* mgr, Ogre::String meshName,
		Ogre::String matName, bool castShadows) {
	
	// create entity
	entity = mgr->createEntity(meshName);
	entity->setCastShadows(castShadows);
	entity->setMaterialName(matName);
}
	
Ogre::Entity* EntityObject::getEntity() {
	return entity;
}