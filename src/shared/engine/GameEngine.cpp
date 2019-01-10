#include "GameEngine.h"
#include "CommandType.h"
#include <unistd.h>
#include <iostream>
        
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
                if(commands.front()->execute(currentState)){
                    executedCommands.push_back(commands.front());
                }
            }
            
            commands.pop();
        }
    }
    void GameEngine::cancel () {
        if (!executedCommands.empty()){
            executedCommands.back()->cancel(currentState);
            executedCommands.pop_back();
        }
    }
    void GameEngine::cancelFromPlayer(int playerId) {
        if (!executedCommands.empty()){
            if (executedCommands.back()->getPlayerTriggeringId() == playerId && executedCommands.back()->getCommandType()!=CommandType::ENDTURN){
                executedCommands.back()->cancel(currentState);
                executedCommands.pop_back();
            }
        }
    }
    void GameEngine::cancelTurn () {
        int currentTurn = currentState->getTurn();
        while ((int)currentState->getTurn() > currentTurn -2 && !executedCommands.empty()){
            cancel();
        }
    }
    void GameEngine::addCommand(std::shared_ptr<Command> command){
        commands.push(command);
    }
    
};

