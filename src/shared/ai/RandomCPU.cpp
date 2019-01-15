#include "RandomCPU.h"
#include "state/GameState.h"
#include "engine/GameEngine.h"
#include "engine/CommandEndTurn.h"
#include "engine/CommandMove.h"


#include <cstdlib>
#include <iostream>
#include <ctime>
 
namespace ai {

    RandomCPU::RandomCPU (
        std::shared_ptr<state::GameState> state, 
        std::shared_ptr<engine::GameEngine> engine, 
        unsigned int playerId
    ) : CPU (state, engine, playerId){}
    
    void RandomCPU::run (){
        int rand = std::rand();
        if( rand % 9 == 8){
            engine->addCommand(std::make_shared<engine::CommandEndTurn>(playerId));
        } else {
            engine->addCommand(std::make_shared<engine::CommandMove>(rand/2, 0, playerId));
        }
    }
};
