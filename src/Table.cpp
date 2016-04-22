#include "Table.h"

Table::Table(Ogre::SceneManager* mgr, Ogre::SceneNode* node,
		std::queue<Event>* eventQueue) :
		GameObject(mgr, node, "Table", eventQueue), score(0) {

	setEntityObject(new EntityObject(mgr, "models/Table.mesh",
			"TableMat", true));

}

bool Table::update(){
	if(physicsObj->getCollisionContext()->hit) {
		score = 1;
		return true;
	} else {
		score = 0;
		return false;
	}
}