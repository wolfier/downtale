#include "Ball.h"

Ball::Ball(Ogre::SceneManager* mgr, Ogre::SceneNode* node,
		std::queue<Event>* eventQueue) :
		GameObject(mgr, node, "Ball", eventQueue) {

	setEntityObject(new EntityObject(mgr, "models/Ball.mesh",
			"BallMat", true));

    spawnPos = node->getPosition();
    spawnRot = node->getOrientation();
}

bool Ball::update(){
	if(physicsObj->getCollisionContext()->hit) {
		return true;
	}
	return false;
}

void Ball::reset() {
	physicsObj->reset();
}

void Ball::readd() {
	physicsObj->readd();
}

void Ball::launch() {
	physicsObj->setInitVelocity(0,0,200);
}

void Ball::still() {
	physicsObj->setInitVelocity(0,0,0);
}

void Ball::updateTransform(Ogre::Vector3 pos, Ogre::Quaternion qt) {
	physicsObj->updateTransform(pos, qt);
}