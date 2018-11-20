#include "FieldObject.h"


namespace state {

    FieldObject::FieldObject(){
        position = sf::Vector2f(0.f, 0.f);
        owner = -1;
    }

    void FieldObject::setObjectType (ObjectType selectedType){
        //sprite = ;//associated sprite

        type = selectedType;//associated type
    }

    sf::Vector2f FieldObject::getPosition(){
        return position;
    }


    void FieldObject::setOwner (int playerId){
        owner = playerId;
    }

    ObjectType FieldObject::getObjectType(){
        return type;
    }

};
