#include "CPU.h"
#include "state/GameState.h"
#include "engine/GameEngine.h"
#include "engine/CommandEndTurn.h"
#include "engine/CommandMove.h"


#include <cstdlib>
#include <iostream>
#include <ctime>
 
namespace ai {
    CPU::CPU (
        std::shared_ptr<state::GameState> state, 
        std::shared_ptr<engine::GameEngine> engine, 
        unsigned int playerId
    ) :
    state(state),
    engine(engine),
    playerId(playerId) {
        std::srand(std::time(nullptr));
    }
    
    void CPU::run (){
        int rand = std::rand();
        if( rand % 9 == 8){
            engine->addCommand(std::make_shared<engine::CommandEndTurn>(playerId));
        } else {
            engine->addCommand(std::make_shared<engine::CommandMove>(rand/2, playerId));
        }
    }
};
