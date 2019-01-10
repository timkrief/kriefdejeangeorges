#include "Command.h"

namespace engine {
    Command::Command(unsigned int playerTriggeringId) : playerTriggeringId(playerTriggeringId) {
    
    }
    bool Command::execute (std::shared_ptr<state::GameState> state){
        return false;
    }
    void Command::cancel (std::shared_ptr<state::GameState> state){

    }
    unsigned int Command::getPlayerTriggeringId(){
        return playerTriggeringId;
    }
    CommandType Command::getCommandType(){
        return commandType;
    }
};
