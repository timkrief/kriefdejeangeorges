#include "HeuristicCPU.h"
#include "state/GameState.h"
#include "engine/GameEngine.h"
#include "engine/CommandEndTurn.h"
#include "engine/CommandMove.h"


#include <cstdlib>
#include <iostream>
#include <ctime>

namespace ai {
    HeuristicCPU::HeuristicCPU (
        std::shared_ptr<state::GameState> state, 
        std::shared_ptr<engine::GameEngine> engine, 
        unsigned int playerId
    ) : CPU (state, engine, playerId), turnSteps(3) {
        
        int rand = std::rand();
        
        targetedPlayerId = rand % (state->getPlayerCount() - 1); 
        if(targetedPlayerId >= playerId){
            targetedPlayerId++;
        }
    }
    
    void HeuristicCPU::run (){
        if(turnSteps == -1){
            engine->addCommand(std::make_shared<engine::CommandEndTurn>(playerId));
            turnSteps = 3;
        } else {
            
            int rand = std::rand();
        
            sf::Vector2u playerPos = state->getPlayer(targetedPlayerId)->getOwnedFieldObjects()[0]->getPosition();
            sf::Vector2u cpuPos = state->getPlayer(playerId)->getOwnedFieldObjects()[0]->getPosition();
            int direction = -1;
            
            if(rand%2){
                if(playerPos.y < cpuPos.y){
                    direction = 0;
                }  else if (playerPos.y > cpuPos.y){
                    direction = 2;
                } else {
                    if (playerPos.x > cpuPos.x){
                        direction = 1;
                    } else if (playerPos.x < cpuPos.x){
                        direction = 3;
                    } 
                }
            } else {
                if (playerPos.x > cpuPos.x){
                    direction = 1;
                } else if (playerPos.x < cpuPos.x){
                    direction = 3;
                } else {
                    if(playerPos.y < cpuPos.y){
                        direction = 0;
                    }  else if (playerPos.y > cpuPos.y){
                        direction = 2;
                    } 
                }
            }
            
            ////std::cout<<"player"<<playerId<<" is going to player"<<targetedPlayerId<<" with direction"<<direction<<"."<<std::endl;
            if(direction>=0){
                engine->addCommand(std::make_shared<engine::CommandMove>(direction, 0, playerId));
            } else{
                turnSteps = 0;
            }
            turnSteps--;
        }
    }
};
