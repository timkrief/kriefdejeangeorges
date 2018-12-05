#include "Unit.h"

namespace state {
    Unit::Unit () : FieldObject(), direction(Direction::LEFT){
        setObjectType(ObjectType::UNIT);
    }
    int Unit::getHeadcount (){}
    void Unit::move (Direction direction){}
    void Unit::attack (Unit defender){}
    void Unit::defence (Unit attacker){}
    void Unit::capture (Building building){}
    Direction Unit::getDirection (){
        return direction;
    }
    void Unit::setDirection (Direction dir){
        direction = dir;
    }
};
