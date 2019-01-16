#include <iostream>
#include <SFML/Graphics.hpp>
#include "state.h"
#include "engine.h"
#include "ai.h"
#include <string.h>
#include <unistd.h>
#include <thread>
#include <SFML/Network.hpp>
#include <microhttpd.h>

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
    bool listen = argc>1 && !strcmp(argv[1],"listen");
    
    if(listen){
    	std::cout << "I'm supposed to be listening right now!" << std::endl;
    } else if(record){
		// Create Player 1
		std::shared_ptr<Player> player1(new Player);
		std::shared_ptr<Unit> unit0(new Unit);
		unit0->setPosition(sf::Vector2u(10,20));
		player1->addOwnedFieldObject(unit0);
		
		std::shared_ptr<Unit> unit1(new Unit);
		unit1->setPosition(sf::Vector2u(12,20));
		player1->addOwnedFieldObject(unit1);
		
		std::shared_ptr<Unit> unit2(new Unit);
		unit2->setPosition(sf::Vector2u(10,22));
		player1->addOwnedFieldObject(unit2);
		
		std::shared_ptr<Unit> unit3(new Unit);
		unit3->setPosition(sf::Vector2u(12,22));
		player1->addOwnedFieldObject(unit3);
		
		
		// Create Player 2
		std::shared_ptr<Player> player2(new Player);
		std::shared_ptr<Unit> unit4(new Unit);
		unit4->setPosition(sf::Vector2u(35,10));
		player2->addOwnedFieldObject(unit4);

		std::shared_ptr<Unit> unit5(new Unit);
		unit5->setPosition(sf::Vector2u(36,10));
		player2->addOwnedFieldObject(unit5);

		std::shared_ptr<Unit> unit6(new Unit);
		unit6->setPosition(sf::Vector2u(38,13));
		player2->addOwnedFieldObject(unit6);
		
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
		
        engine->saveHistory();
    }
    return 0;
}
