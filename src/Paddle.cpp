#include "Paddle.h"

Paddle::Paddle(Ogre::SceneManager* mgr, Ogre::SceneNode* node,
		std::queue<Event>* eventQueue) :
		GameObject(mgr, node, "Paddle", eventQueue) {

	setEntityObject(new EntityObject(mgr, "models/Paddle.mesh",
			"PaddleMat", true));
}

bool Paddle::update(void) {
	if(physicsObj->getCollisionContext()->hit) {
		return true;
	}
	return false;
}