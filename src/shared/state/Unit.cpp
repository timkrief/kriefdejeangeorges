#include "Unit.h"

namespace state {
    Unit::Unit () : FieldObject(){
        setObjectType(ObjectType::UNIT);
    }
    int getHeadcount (){}
    void move (Direction direction){}
    void attack (Unit defender){}
    void defence (Unit attacker){}
    void capture (Building building){}
    Direction getDirection (){}
};
