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
        int playedSteps = 4;
        int steps = 20;
        int samples = 5000;
        std::vector<std::vector<int>> paths(samples, std::vector<int>(steps));
        int bestPath = 0;
        int bestDist = 10000;
        int dist;
        bool targetFound = false;
        
        sf::Vector2i playerPos = state->getPlayer(targetedPlayerId)->getOwnedFieldObjects()[0]->getPosition();
        sf::Vector2i cpuPos = state->getPlayer(playerId)->getOwnedFieldObjects()[0]->getPosition();
        dist = abs(playerPos.x - cpuPos.x)+abs(playerPos.y - cpuPos.y);
        if(dist != 0){
            for(int i=0; i<samples; i++){
                for(int j=0; j<steps; j++){
                    int rand = std::rand();
                    paths[i][j] = rand%4;
                    engine->addCommand(std::make_shared<engine::CommandMove>(paths[i][j], playerId));
                }
                engine->update();
                
                playerPos = state->getPlayer(targetedPlayerId)->getOwnedFieldObjects()[0]->getPosition();
                cpuPos = state->getPlayer(playerId)->getOwnedFieldObjects()[0]->getPosition();
                dist = abs(playerPos.x - cpuPos.x)+abs(playerPos.y - cpuPos.y);
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
