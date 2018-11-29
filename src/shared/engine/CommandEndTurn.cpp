#include "CommandEndTurn.h"

namespace engine {
    void CommandEndTurn::execute (std::shared_ptr<state::GameState> state){
        state->endTurn();
    }
};

