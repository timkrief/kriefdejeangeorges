#include <iostream>
#include <SFML/Graphics.hpp>
#include "state.h"
#include "engine.h"
#include "ai.h"
#include <string.h>
#include <unistd.h>
#include <thread>

using namespace std;
using namespace state;
using namespace engine;
using namespace ai;

void engineThreadFunc(std::shared_ptr<GameEngine> engine, bool* gameRunning){
    while(*gameRunning){
        engine->update();
    }
}

int main(int argc,char* argv[]) 
{
    bool record = argc>1 && !strcmp(argv[1],"record");
    
	// Create Player 1
    std::shared_ptr<Player> player1(new Player);
    std::shared_ptr<Unit> unit1(new Unit);
    unit1->setPosition(sf::Vector2u(10,20));
    player1->addOwnedFieldObject(unit1);

	// Create Player 2
    std::shared_ptr<Player> player2(new Player);
    std::shared_ptr<Unit> unit2(new Unit);
    unit2->setPosition(sf::Vector2u(35,10));
    player2->addOwnedFieldObject(unit2);
    
    
    // Create State
    std::shared_ptr<GameState> state(new GameState("./res/maps/map.json", "fr"));
    
    state->addPlayer(player1);
    state->addPlayer(player2);

    // Create engine
    std::shared_ptr<GameEngine> engine(new GameEngine(state));

    bool gameRunning;
    gameRunning = true;
    std::thread engineThread(engineThreadFunc, engine, &gameRunning);
    
    DeepCPU cpu1(state, engine, 0);
    DeepCPU cpu2(state, engine, 1);
    
    while(state->getTurn() < 100){
        cpu1.run();
        cpu2.run();
    }
    gameRunning = false;
    engineThread.join();
    
    if(record){
        engine->saveHistory();
    }
    return 0;
}
