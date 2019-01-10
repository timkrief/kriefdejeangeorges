#include "CommandMove.h"
#include "CommandType.h"


void applyDirection(sf::Vector2u &pos, int direction){
    switch(direction){
        case 0: 
            pos.y --;
            break;
        case 1: 
            pos.x ++;
            break;
        case 2: 
            pos.y ++;
            break;
        case 3: 
            pos.x --;
            break;
        default: 
            break;
    }
}

namespace engine {
    CommandMove::CommandMove (unsigned int dir, unsigned int playerTriggeringId) : 
        Command(playerTriggeringId), 
        direction(dir % 4){
        
        commandType = CommandType::MOVE;
    }
    
    bool CommandMove::execute (std::shared_ptr<state::GameState> state){
        for(auto objet: state->getPlayer(playerTriggeringId)->getOwnedFieldObjects()){
            sf::Vector2u pos(objet->getPosition());
            
            applyDirection(pos, direction);
            int newMovePoints = objet->getMovePoints() - state->getMap()->getTile(pos)->attributes["moveCost"];
                    
            if(state->getMap()->getTile(pos)->attributes["moveCost"] > 0 && direction!=4 && newMovePoints>=0){
                objet->setMovePoints(newMovePoints);
                objet->setPosition(pos);
                objet->setDirection((state::Direction)direction);
                return true;
            }
        }
        return false;
    }
    void CommandMove::cancel (std::shared_ptr<state::GameState> state){
        direction = (direction + 2) % 4;
        
        for(auto objet: state->getPlayer(playerTriggeringId)->getOwnedFieldObjects()){
            sf::Vector2u pos(objet->getPosition());
            
            applyDirection(pos, direction);
            int newMovePoints = objet->getMovePoints() + state->getMap()->getTile(pos)->attributes["moveCost"];
                    
            if(state->getMap()->getTile(pos)->attributes["moveCost"] > 0 && direction!=4){
                objet->setMovePoints(newMovePoints);
                objet->setPosition(pos);
                objet->setDirection((state::Direction)((direction + 2) % 4));
            }
        }
    }
    void CommandMove::save(YAML::Emitter& saveData){
        std::map <std::string, int> attributes;
        attributes["commandType"] = (int)commandType;
        attributes["playerTriggeringId"] = playerTriggeringId;
        attributes["direction"] = direction;

        saveData << attributes;
    }
};

