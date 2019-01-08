#include "DeepCPU.h"
#include "state/GameState.h"
#include "engine/GameEngine.h"
#include "engine/CommandEndTurn.h"
#include "engine/CommandMove.h"


#include <cstdlib>
#include <iostream>
#include <ctime>

namespace ai {
    DeepCPU::DeepCPU (
        std::shared_ptr<state::GameState> state, 
        std::shared_ptr<engine::GameEngine> engine, 
        unsigned int playerId
    ) : CPU (state, engine, playerId) {
        
        int rand = std::rand();
        
        targetedPlayerId = rand % (state->getPlayerCount() - 1); 
        if(targetedPlayerId >= playerId){
            targetedPlayerId++;
        }
    }
    
    void DeepCPU::run (){
    
        sf::Vector2u playerPos = state->getPlayer(targetedPlayerId)->getOwnedFieldObjects()[0]->getPosition();
        sf::Vector2u cpuPos = state->getPlayer(playerId)->getOwnedFieldObjects()[0]->getPosition();
        int dist = state->getDistance(playerPos, cpuPos);
        
        int playedSteps = 5;
        int steps = dist * 2;
        int samples = dist*dist*4<5000 ? dist*dist*4 : 5000;
        std::vector<std::vector<int>> paths(samples, std::vector<int>(steps));
        std::vector<std::vector<sf::Vector2u>> coord(samples, std::vector<sf::Vector2u>(steps));
        int bestPath = 0;
        int bestDist = 10000;
        bool targetFound = false;
        
        if(dist != 0){
            for(int i=0; i<samples; i++){
                for(int j=0; j<steps; j++){
                    int rand = std::rand();
                    // Choose a random direction, but don't go back'
                    if(j==0){
                        paths[i][j] = rand % 4;
                    } else {
                        paths[i][j] = (rand % 3 >= (paths[i][j-1] + 2) % 4) ? rand % 3 + 1 : rand % 3 ;
                    }
                    engine->addCommand(std::make_shared<engine::CommandMove>(paths[i][j], playerId));
                    engine->update();
                    cpuPos = state->getPlayer(playerId)->getOwnedFieldObjects()[0]->getPosition();
                    coord[i][j] = sf::Vector2u(cpuPos);
                }
                
                dist = state->getDistance(playerPos, cpuPos);
                if(dist == 0 && i<playedSteps){
                    break;
                    targetFound = true;
                }
                if(dist<bestDist){
                    bestDist = dist;
                    bestPath = i;
                }
                for(int j=0; j<steps; j++){
                    engine->cancel();
                }
            }
            
            if(!targetFound){
                for(int j=0; j<playedSteps; j++){
                    engine->addCommand(std::make_shared<engine::CommandMove>(paths[bestPath][j], playerId));
                }
            }
        }
        engine->addCommand(std::make_shared<engine::CommandEndTurn>(playerId));
    }
};
