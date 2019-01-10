#include "DeepCPU.h"
#include "state/GameState.h"
#include "engine/GameEngine.h"
#include "engine/CommandEndTurn.h"
#include "engine/CommandMove.h"


#include <cstdlib>
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <set>
#include <sstream> 
#include <string> 

std::string vec2str(sf::Vector2u vec){
    std::stringstream str;
    str << vec.x << ';' << vec.y;
    return str.str();
}

sf::Vector2u str2vec(std::string str){
    std::stringstream bufferX;
    std::stringstream bufferY;
	sf::Vector2u vec;
	int cursor = 0;
	bool writingX = true;
	char character;
	while(character = str[cursor++]){
	    if(character == ';') writingX = false;
	    else {
	        if(writingX) bufferX << character;
	        else bufferY << character;
	    }
	}
	return sf::Vector2u( std::stoi( bufferX.str() ), std::stoi( bufferY.str() ) );
}

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
        int lastdist;
        
        int deepness = dist*4;
        int authorizedCost = state->getPlayer(playerId)->getOwnedFieldObjects()[0]->getMovePoints();
        int samples = dist*dist*10<20000 ? dist*dist*10 : 20000;
        std::map<std::string, std::vector<int>> paths;
        std::map<std::string, std::vector<int>> pathsLimited;
        std::map<std::string, int> pathsMoveCost;
        std::map<std::string, int> pathsDistance;
        
        paths[vec2str(cpuPos)] = std::vector<int>();
        pathsLimited[vec2str(cpuPos)] = std::vector<int>();
        pathsMoveCost[vec2str(cpuPos)] = 0;
        pathsDistance[vec2str(cpuPos)] = dist;
        
        std::set<std::string> pathsToCheck;
        pathsToCheck.insert(vec2str(cpuPos));
        
        std::string bestPath = vec2str(cpuPos);
        int bestDist = dist;
        bool targetFound = false;
        
        if(dist != 0){
            while(!pathsToCheck.empty()){
            
                std::string coord = *pathsToCheck.begin();
                sf::Vector2u vecCoord = str2vec(coord);
                pathsToCheck.erase(pathsToCheck.begin());
                
                std::vector<int> path = paths[coord];
                
                for(int dir=0; dir < 4; dir++){
                    sf::Vector2u vecNewCoord = vecCoord;
                    switch(dir){
                        case 0:
                            vecNewCoord.y --;
                            break;
                        case 1:
                            vecNewCoord.x ++;
                            break;
                        case 2:
                            vecNewCoord.y ++;
                            break;
                        case 3:
                            vecNewCoord.x --;
                            break;
                    }
                    std::string newCoord = vec2str(vecNewCoord);
                    int costToMove = state->getMap()->getTile(vecNewCoord)->attributes["moveCost"];
                    if(costToMove >= 0){
                    
                        int newPathMoveCost = pathsMoveCost[coord] + costToMove;
                        int newPathDistance = state->getDistance(vecNewCoord, playerPos);
                        
                        if(newPathMoveCost <= deepness && (paths.find(newCoord) == paths.end() || newPathMoveCost < pathsMoveCost[newCoord])){
                        
                            pathsToCheck.insert(newCoord);
                            
                            paths[newCoord] = paths[coord];
                            paths[newCoord].push_back(dir);
                            pathsLimited[newCoord] = pathsLimited[coord];
                            if(newPathMoveCost <= authorizedCost){
                                pathsLimited[newCoord].push_back(dir);
                            }
                            pathsMoveCost[newCoord] = newPathMoveCost;
                            pathsDistance[newCoord] = newPathDistance;
                            
                            if(newPathDistance < bestDist){
                                bestDist = newPathDistance;
                                bestPath = newCoord;
                            }
                        }
                    }
                }
            }
            
            for(int j=0; j<pathsLimited[bestPath].size(); j++){
                engine->addCommand(std::make_shared<engine::CommandMove>(pathsLimited[bestPath][j], playerId));
            }
        }
        engine->addCommand(std::make_shared<engine::CommandEndTurn>(playerId));
    }
};
