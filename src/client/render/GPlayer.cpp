#include "GPlayer.h"
#include "state/Player.h"
#include <iostream>

namespace render {
    GPlayer::GPlayer ( std::shared_ptr<state::Player> player) : 
        player(player){
        
    }

    void GPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
        std::vector<GFieldObject> gfieldObjects;
        
        for(auto fieldObject: player->getOwnedFieldObjects()){
            gfieldObjects.push_back(fieldObject);
        }
        for(auto gfieldObject: gfieldObjects){
            target.draw(gfieldObject);
        }
    }
};
