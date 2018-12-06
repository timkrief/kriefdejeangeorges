#include "HeuristicCPU.h"
#include "state/GameState.h"
#include "engine/GameEngine.h"
#include "engine/CommandEndTurn.h"
#include "engine/CommandMove.h"


namespace ai {
    HeuristicCPU::HeuristicCPU (
        std::shared_ptr<state::GameState> state, 
        std::shared_ptr<engine::GameEngine> engine, 
        unsigned int playerId
    ) : CPU (state, engine, playerId), turnSteps(2) {}
    
    void HeuristicCPU::run (){
    
        if(turnSteps == -1){
            engine->addCommand(std::make_shared<engine::CommandEndTurn>(playerId));
            turnSteps = 2;
        } else {
        
            sf::Vector2i playerPos = state->getPlayer(0)->getOwnedFieldObjects()[0]->getPosition();
            sf::Vector2i cpuPos = state->getPlayer(playerId)->getOwnedFieldObjects()[0]->getPosition();
            int direction = -1;
            if(playerPos.y < cpuPos.y){
                direction = 0;
            } else if (playerPos.x > cpuPos.x){
                direction = 1;
            } else if (playerPos.y > cpuPos.y){
                direction = 2;
            } else if (playerPos.x < cpuPos.x){
                direction = 3;
            } 
            if(direction>=0){
                engine->addCommand(std::make_shared<engine::CommandMove>(direction, playerId));
            } else{
                turnSteps = 0;
            }
            turnSteps--;
        }
    }
};
