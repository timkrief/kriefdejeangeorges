#include "CommandEndTurn.h"
#include "CommandType.h"

namespace engine {
    CommandEndTurn::CommandEndTurn(unsigned int playerTriggeringId) :
        Command(playerTriggeringId){
        commandType = CommandType::ENDTURN;
    }
    bool CommandEndTurn::execute (std::shared_ptr<state::GameState> state){
        for(auto objet: state->getPlayer(playerTriggeringId)->getOwnedFieldObjects()){
            objet->resetMovePoints();
        }
        state->endTurn();
        return true;
    }
    void CommandEndTurn::cancel (std::shared_ptr<state::GameState> state){
        state->endTurn(true);
    }
    void CommandEndTurn::save(YAML::Emitter& saveData){
        std::map <std::string, int> attributes;
        attributes["commandType"] = (int)commandType;
        attributes["playerTriggeringId"] = playerTriggeringId;

        saveData << attributes;
    }
};

