#include "FieldObject.h"


namespace state {

	FieldObject::FieldObject (){
		position = sf::Vector2f(0.f, 0.f);
		owner = -1;
	}
	void FieldObject::setOwner (int playerId){
		owner = playerId;
	}

};
