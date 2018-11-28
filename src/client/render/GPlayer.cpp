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
        
        // text test
        int height = 24;
        
        sf::Text playerName;
        
        sf::Font font;
        
        if (!font.loadFromFile("src/army1.ttf")){
            std::cout << "Font not found" << std::endl;
        }
        
        playerName.setFont(font);
        playerName.setString(player->getName());
        playerName.setCharacterSize(height); 
        playerName.setFillColor(sf::Color::White);
        playerName.setStyle(sf::Text::Bold);
        playerName.setPosition(10, height + player->getId() * height * 2);
        target.draw(playerName);
    }
};
