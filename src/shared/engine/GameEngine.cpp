#include "GameEngine.h"
#include "CommandType.h"
#include "CommandEndTurn.h"
#include "CommandMove.h"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include "yaml-cpp/yaml.h"
        
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
    void GameEngine::saveHistory() {

        YAML::Emitter saveData;
        saveData << YAML:: DoubleQuoted << YAML::Flow << YAML::BeginSeq;
        
        for (auto & executedCommand : executedCommands) {
            executedCommand->save(saveData);
        }
        
        saveData << YAML::EndSeq;
        
        std::remove( "./savefile.json" );
        std::ofstream saveFileOut("./savefile.json"); // replay.txt
        saveFileOut << saveData.c_str();
    }
    
    void GameEngine::loadHistory() {
		YAML::Node parsedSaveFile = YAML::LoadFile("./savefile.json"); // Parse the file

        for(unsigned int i=0; i<parsedSaveFile.size(); i++) {

            switch (parsedSaveFile[i]["commandType"].as<int>()){
                case (int)CommandType::ENDTURN:
                    addCommand(std::make_shared<CommandEndTurn>(parsedSaveFile[i]["playerTriggeringId"].as<int>()));
                    break;
                case (int)CommandType::MOVE:
                    addCommand(
                    	std::make_shared<CommandMove>(
                    		parsedSaveFile[i]["direction"].as<int>(),
                    		parsedSaveFile[i]["fieldObjectId"].as<int>(), 
                    		parsedSaveFile[i]["playerTriggeringId"].as<int>()
                    	)
                    );
                    break;
                default:
                    break;
            }
		}
		
    }
    
};

