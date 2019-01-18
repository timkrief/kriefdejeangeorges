#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "state.h"
#include "render.h"
#include "engine.h"
#include "ai.h"
#include <string.h>
#include <unistd.h>
#include <thread>


using namespace std;
using namespace state;
using namespace render;
using namespace ai;

#include "tests.h"


void engineThreadFunc(std::shared_ptr<GameEngine> engine, bool* gameRunning){
    while(*gameRunning){
        engine->update();
        usleep(10000);
    }
}
void deepCPU2ThreadFunc(std::shared_ptr<DeepCPU_2> cpu, bool* gameRunning){
    while(*gameRunning){
		cpu->run();
        usleep(10000);
    }
}

int main(int argc,char* argv[]) 
{
    bool rollback = argc>1 && !strcmp(argv[1],"rollback");
    bool deep_ai = argc>1 && !strcmp(argv[1],"deep_ai");
    bool thread = argc>1 && !strcmp(argv[1],"thread");
    bool record = argc>1 && !strcmp(argv[1],"record");
    bool play = argc>1 && !strcmp(argv[1],"play");
    bool network = argc>1 && !strcmp(argv[1],"network");
    
    
    if(network){
    	std::cout << "I'm supposed to make things right now!" << std::endl;
    } else {
		/*
		testSFML();
		Cards cards("./res/cards.yaml","fr");
		*/
		
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
		
		if(play){
		    engine->loadHistory();
		}
		
		if(deep_ai){
		    DeepCPU_2 cpu1(state, engine, 0);
		    DeepCPU_2 cpu2(state, engine, 1);
		    
		    std::shared_ptr<GRender> render(new GRender);
		    
		    EventController enventController;
		    
		    GState gstate(state);
		    
		    bool displayWindow = true;
		    sf::Event event;
		    
		    render->initTextures();
		    
		    while(displayWindow){
		        enventController.handle(event, engine, render, displayWindow);
		        
		        if(state->getTurn() > 200){
		            while(state->getTurn() != 0){
		                engine->cancelTurn();
		                render->display(gstate);
		                usleep(10000);
		            }
		        }
		        
		        if(state->getPlayerTurnId() == 0){
		            cpu1.run();
		            usleep(50000);
		        }
		        
		        if(state->getPlayerTurnId() == 1){
		            cpu2.run();
		            usleep(50000);
		        }
		        
		        
		        engine->update();

		        render->display(gstate);
		    }
		} else if(thread || record || play){
		    bool displayWindow = true;
		    std::thread engineThread(engineThreadFunc, engine, &displayWindow);
		    
		    std::shared_ptr<DeepCPU_2> cpu(new DeepCPU_2(state, engine, 1));
		    std::thread DeepCPU2Thread(deepCPU2ThreadFunc, cpu, &displayWindow);
		 
		    std::shared_ptr<GRender> render(new GRender);
		    EventController enventController;
		    GState gstate(state);
		    
		    sf::Event event;
		    
		    render->initTextures();
		    
		    while(displayWindow){
		        enventController.handle(event, engine, render, displayWindow);
		        
		        render->display(gstate);
		    }
		    engineThread.join();
		} else { 
		    DeepCPU_2 cpu1(state, engine, 0);
		    DeepCPU_2 cpu2(state, engine, 1);
		    
		    std::shared_ptr<GRender> render(new GRender);
		    
		    EventController enventController;
		    
		    GState gstate(state);
		    
		    bool displayWindow = true;
		    sf::Event event;
		    
		    render->initTextures();
		    
		    while(displayWindow){
		        enventController.handle(event, engine, render, displayWindow);
		        
		        if(rollback){
		            if(state->getTurn() > 30){
		                while(state->getTurn() != 0){
		                    engine->cancelTurn();
		                    render->display(gstate);
		                }
		            }
		            if(state->getPlayerTurnId() == 0){
		                cpu1.run();
		            }
		        }
		        
		        if(state->getPlayerTurnId() == 1){
		            cpu2.run();
		        }
		        
		        engine->update();
		
		        render->display(gstate);
		    }
		}
		
		if(record){
		    engine->saveHistory();
		}
	}
	
    return 0;
}
