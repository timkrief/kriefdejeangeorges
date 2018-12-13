#include "CommandMove.h"

namespace engine {
    CommandMove::CommandMove (unsigned int dir, unsigned int playerTriggeringId) : 
        Command(playerTriggeringId), 
        direction(dir % 4){
    }
    
    void CommandMove::execute (std::shared_ptr<state::GameState> state){
        for(auto objet: state->getPlayer(playerTriggeringId)->getOwnedFieldObjects()){
            sf::Vector2i pos(objet->getPosition());
            
            sf::Vector2i newpos;
            
            switch(direction){
                case 0: 
                    newpos = pos + sf::Vector2i(0, -1);
                    break;
                case 1: 
                    newpos = pos + sf::Vector2i(1, 0);
                    break;
                case 2: 
                    newpos = pos + sf::Vector2i(0, 1);
                    break;
                case 3: 
                    newpos = pos + sf::Vector2i(-1, 0);
                    break;
                default: 
                    newpos = pos;
                    break;
            }
            
            if(state->getMap()->getTile(sf::Vector2u(newpos.x, newpos.y))->attributes["moveCost"] > 0 && direction!=4){
                objet->setPosition(newpos);
                objet->setDirection((state::Direction)direction);
            } else {
                direction = 4;
            }
        }
    }
    void CommandMove::cancel (std::shared_ptr<state::GameState> state){
        if(direction<4){
            direction = (direction + 2) % 4;
            execute(state);
        }
    }
};

