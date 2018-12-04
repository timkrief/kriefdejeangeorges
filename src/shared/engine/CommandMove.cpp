#include "CommandMove.h"

namespace engine {
    CommandMove::CommandMove (unsigned int dir, unsigned int playerTriggeringId) : 
        Command(playerTriggeringId), 
        direction(dir % 4){
    }
    
    void CommandMove::execute (std::shared_ptr<state::GameState> state){
        for(auto objet: state->getPlayer(playerTriggeringId)->getOwnedFieldObjects()){
            sf::Vector2i pos(objet->getPosition());
            sf::Vector2i newpos(
                abs(
                    pos.x +
                    (direction == 1 ? 
                        1 : 
                        (direction == 3 ? -1 : 0)
                    )
                ),
                abs(
                    pos.y + 
                    (direction == 0 ? 
                        -1 : 
                        (direction == 2 ? 1 : 0)
                    )
                )
            );
            if(state->getMap()->getTile(sf::Vector2u(newpos.x, newpos.y))->attributes["speed"] > 0){
                objet->setPosition(newpos);
            }
        }
    }
};

