#include "GameEngine.h"

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
            commands.front()->execute(currentState);
            commands.pop();
        }
    }
    void GameEngine::addCommand(std::shared_ptr<Command> command){
        commands.push(command);
    }
    
};

