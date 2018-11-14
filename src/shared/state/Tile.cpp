#include "Tile.h"

namespace state {
    Tile::Tile ( ) {}
    
    Tile::Tile (float speed) :
    speed(speed) {
    
    }
    
    float Tile::getSpeed () {
        return speed;    
    }
};

