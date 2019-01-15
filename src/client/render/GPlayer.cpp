#include "GPlayer.h"
#include "state/Player.h"
#include <iostream>

namespace render {
    GPlayer::GPlayer ( std::shared_ptr<state::Player> player) : 
        player(player){
        
    }
	void GPlayer::getSelection(sf::Vector2u selectedTile, int& selectedPlayer, int& selectedFieldObject, GFieldObject& selectedUnit){
        int count = 0;
        for(auto fieldObject: player->getOwnedFieldObjects()){
        	if(fieldObject->getPosition() == selectedTile){
        		selectedPlayer = fieldObject->getOwner()-1;
        		selectedFieldObject = count;
        		selectedUnit = GFieldObject(fieldObject);
        		break;
        	}
        	count ++;
        }
    }
	sf::Vector2u GPlayer::getSelectionPosition(int selectedFieldObject){
        return player->getOwnedFieldObjects()[selectedFieldObject]->getPosition();
    }
    
    void GPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
        std::vector<GFieldObject> gfieldObjects;
        
        for(auto fieldObject: player->getOwnedFieldObjects()){
            gfieldObjects.push_back(fieldObject);
            target.draw(gfieldObjects.back());
        }
    }
};
