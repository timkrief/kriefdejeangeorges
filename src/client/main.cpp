#include <iostream>
#include <SFML/Graphics.hpp>
#include "state.h"
#include "render.h"
#include "engine.h"
#include "ai.h"
#include <string.h>

using namespace std;
using namespace state;
using namespace render;
using namespace ai;

#include "tests.h"

int main(int argc,char* argv[]) 
{

    bool rollback = argc>1 && !strcmp(argv[1],"rollback");
    bool deep_ai = argc>1 && !strcmp(argv[1],"deep_ai");

    
	testSFML();
	
	Cards cards("./res/cards.yaml","fr");
	
	//testPlayer();
	
    
// Creation of players -------
    std::shared_ptr<Player> player1(new Player);
    printf("ID of the first player: %d \n", player1->getId());
    std::shared_ptr<Unit> unit0(new Unit);
    unit0->setPosition(sf::Vector2u(10,20));
    player1->addOwnedFieldObject(unit0);
    //unit0->setOwner(1);
    
    std::shared_ptr<Player> player2(new Player);
    
//    std::shared_ptr<Unit> unit(new Unit);
//    unit->setPosition(sf::Vector2u(15,25));
//    player2->addOwnedFieldObject(unit);
//    
//    
//    
    std::shared_ptr<OilWell> unit2(new OilWell);
    unit2->setPosition(sf::Vector2u(35,10));
    player2->addOwnedFieldObject(unit2);

    printf("ID of the first player: %d \n", player2->getId());
    //unit2->setOwner(2);
//    
//    
//    std::shared_ptr<Factory> unit3(new Factory);
//    unit3->setPosition(sf::Vector2u(30,20));
//    player2->addOwnedFieldObject(unit3);
    // end of Creation of players -------
    
    
    std::shared_ptr<GameState> state(new GameState("./res/maps/map.json", "fr"));
    state->addPlayer(player1);
    state->addPlayer(player2);
    
    //testMapLoaded(state.getMap());
    //testRender(state);
    //testEngine(state);
    
    
    
    std::shared_ptr<GameEngine> engine(new GameEngine(state));
    if(deep_ai){
        DeepCPU cpu1(state, engine, 0);
        
        DeepCPU cpu2(state, engine, 1);
        
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
                }
            }
            
            if(state->getPlayerTurnId() == 0){
                cpu1.run();
            }
            
            if(state->getPlayerTurnId() == 1){
                cpu2.run();
            }
            
            
            engine->update();

            render->display(gstate);
        }
    } else {
        HeuristicCPU cpu1(state, engine, 0);
        
        HeuristicCPU cpu2(state, engine, 1);
        
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
    
    
    return 0;
}
