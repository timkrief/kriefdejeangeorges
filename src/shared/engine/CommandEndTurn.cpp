#include "CommandEndTurn.h"

namespace engine {
    CommandEndTurn::CommandEndTurn(unsigned int playerTriggeringId) :
        Command(playerTriggeringId){
        
    }
    void CommandEndTurn::execute (std::shared_ptr<state::GameState> state){
        state->endTurn();
    }
};

