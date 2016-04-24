#include "Player.h"

Player::Player(Ogre::SceneManager* mgr, Ogre::SceneNode* node) :
		GameObject(mgr, node, "Player") {

	setEntityObject(new EntityObject(mgr, "models/Player.mesh",
			"PlayerMat", true));

//     spawnPos = node->getPosition();
//     spawnRot = node->getOrientation();
}

bool Player::update(){
	if(physicsObj->getCollisionContext()->hit) {
		return true;
	}
	return false;
}

// void Player::reset() {
// 	physicsObj->reset();
// }

// void Player::readd() {
// 	physicsObj->readd();
// }

// void Player::launch() {
// 	physicsObj->setInitVelocity(0,0,200);
// }

// void Player::still() {
// 	physicsObj->setInitVelocity(0,0,0);
// }

// void Player::updateTransform(Ogre::Vector3 pos, Ogre::Quaternion qt) {
// 	physicsObj->updateTransform(pos, qt);
// }