#include "CommandEndTurn.h"

namespace engine {
    void CommandEndTurn::execute (state::GameState& state){
        state.endTurn();
    }
};

