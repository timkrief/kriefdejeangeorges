#include "GameEngine.h"
#include <unistd.h>
        
namespace engine {
    GameEngine::GameEngine (std::shared_ptr<state::GameState> state) :
        currentState(state) {
    
    }
    GameEngine::~GameEngine () {
    
    }
    std::shared_ptr<state::GameState> GameEngine::getState () const{
        return currentState;
    }
    void GameEngine::update () {
        while (!commands.empty()){
            if(commands.front()->getPlayerTriggeringId() == currentState->getPlayerTurnId()){
                //if(commands.front()->getPlayerTriggeringId() > 0) usleep(100000);
                commands.front()->execute(currentState);
            }
            commands.pop();
        }
    }
    void GameEngine::addCommand(std::shared_ptr<Command> command){
        commands.push(command);
    }
    
};

