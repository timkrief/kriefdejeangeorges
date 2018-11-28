#include "FieldObject.h"


namespace state {

    FieldObject::FieldObject(){
        position = sf::Vector2i(0, 0);
        owner = -1;
    }

    void FieldObject::setObjectType (ObjectType selectedType){
        //sprite = ;//associated sprite

        type = selectedType;//associated type
    }

    sf::Vector2i FieldObject::getPosition(){
        return position;
    }

    void FieldObject::setPosition(sf::Vector2i pos){
        position = pos;
    }


    void FieldObject::setOwner (int playerId){
        owner = playerId;
    }

    ObjectType FieldObject::getObjectType(){
        return type;
    }

};
