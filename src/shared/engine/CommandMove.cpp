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
    CommandMove::CommandMove (unsigned int dir, unsigned int fieldObjectId, unsigned int playerTriggeringId) : 
        Command(playerTriggeringId), 
        fieldObjectId(fieldObjectId), 
        direction(dir % 4){
        
        commandType = CommandType::MOVE;
    }
    
    bool CommandMove::execute (std::shared_ptr<state::GameState> state){
    	auto objet = state->getPlayer(playerTriggeringId)->getOwnedFieldObjects()[fieldObjectId];
        sf::Vector2u pos(objet->getPosition());
        
        applyDirection(pos, direction);
        int newMovePoints = objet->getMovePoints() - state->getMap()->getTile(pos)->attributes["moveCost"];
        
        for(unsigned int playerId = 0; playerId < state->getPlayerCount(); playerId++){
		    for(auto fieldObject: state->getPlayer(playerId)->getOwnedFieldObjects()){
		    	if(fieldObject->getPosition() == pos) return false;
		    }
        }
        if(state->getMap()->getTile(pos)->attributes["moveCost"] > 0 && direction!=4 && newMovePoints>=0){
            objet->setMovePoints(newMovePoints);
            objet->setPosition(pos);
            objet->setDirection((state::Direction)direction);
            return true;
        }
        return false;
    }
    void CommandMove::cancel (std::shared_ptr<state::GameState> state){
        direction = (direction + 2) % 4;
        
    	auto objet = state->getPlayer(playerTriggeringId)->getOwnedFieldObjects()[fieldObjectId];
    	
        sf::Vector2u pos(objet->getPosition());
        
        int newMovePoints = objet->getMovePoints() + state->getMap()->getTile(pos)->attributes["moveCost"];
        applyDirection(pos, direction);
                
        if(state->getMap()->getTile(pos)->attributes["moveCost"] > 0 && direction!=4){
            objet->setMovePoints(newMovePoints);
            objet->setPosition(pos);
            objet->setDirection((state::Direction)((direction + 2) % 4));
        }
    }
    void CommandMove::save(YAML::Emitter& saveData){
        std::map <std::string, int> attributes;
        attributes["commandType"] = (int)commandType;
        attributes["playerTriggeringId"] = playerTriggeringId;
        attributes["fieldObjectId"] = fieldObjectId;
        attributes["direction"] = direction;

        saveData << attributes;
    }
};

