#include "FieldObject.h"


namespace state {

    FieldObject::FieldObject() : 
        position(sf::Vector2u(0, 0)), 
        owner(-1), 
        normalMovePoints(10),
        movePoints(10){
        
    }
    
    void FieldObject::setObjectType (ObjectType selectedType){
        //sprite = ;//associated sprite

        type = selectedType;//associated type
    }

    sf::Vector2u FieldObject::getPosition(){
        return position;
    }

    void FieldObject::setPosition(sf::Vector2u pos){
        position = pos;
    }


    void FieldObject::setOwner (int playerId){
        owner = playerId;
    }


    ObjectType FieldObject::getObjectType(){
        return type;
    }
    Direction FieldObject::getDirection(){
        return Direction::UP;
    }
    void FieldObject::setDirection (Direction dir){}

    int FieldObject::getOwner(){
        return(owner);
    }
    int FieldObject::getMovePoints(){
        return(movePoints);
    }
    void FieldObject::setMovePoints(int newMovePoints){
        movePoints = newMovePoints;
    }
    void FieldObject::resetMovePoints(){
        movePoints = normalMovePoints;
    }
    
    int FieldObject::getNormalMovePoints(){
		return normalMovePoints;
	}
};
