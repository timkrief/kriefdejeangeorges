#include "Command.h"

namespace engine {
    Command::Command(unsigned int playerTriggeringId) : playerTriggeringId(playerTriggeringId) {
    
    }
    void Command::execute (std::shared_ptr<state::GameState> state){

    }
    void Command::cancel (std::shared_ptr<state::GameState> state){

    }
    unsigned int Command::getPlayerTriggeringId(){
        return playerTriggeringId;
    }
};
