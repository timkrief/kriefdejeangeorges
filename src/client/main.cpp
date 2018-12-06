#include <iostream>
#include <SFML/Graphics.hpp>
#include "state.h"
#include "render.h"
#include "engine.h"
#include "ai.h"

using namespace std;
using namespace state;
using namespace render;
using namespace ai;

#include "tests.h"

int main(int argc,char* argv[]) 
{
	testSFML();
	
	Cards cards("./res/cards.yaml","fr");
	
	//testPlayer();
	
    
    // Creation of players -------
    
    std::shared_ptr<Player> player1(new Player);
    
    std::shared_ptr<Unit> unit0(new Unit);
    unit0->setPosition(sf::Vector2i(10,20));
    player1->addOwnedFieldObject(unit0);
    
    
    std::shared_ptr<Player> player2(new Player);
    
//    std::shared_ptr<Unit> unit(new Unit);
//    unit->setPosition(sf::Vector2i(15,25));
//    player2->addOwnedFieldObject(unit);
//    
//    
//    
    std::shared_ptr<OilWell> unit2(new OilWell);
    unit2->setPosition(sf::Vector2i(35,10));
    player2->addOwnedFieldObject(unit2);
//    
//    
//    std::shared_ptr<Factory> unit3(new Factory);
//    unit3->setPosition(sf::Vector2i(30,20));
//    player2->addOwnedFieldObject(unit3);
    // end of Creation of players -------
    
    
    std::shared_ptr<GameState> state(new GameState("./res/maps/map.json", "fr"));
    state->addPlayer(player1);
    state->addPlayer(player2);
    
    //testMapLoaded(state.getMap());
    //testRender(state);
    //testEngine(state);
    
    
    
    std::shared_ptr<GameEngine> engine(new GameEngine(state));
    
    HeuristicCPU cpu1(state, engine, 1);
    
    std::shared_ptr<GRender> render(new GRender);
    
    EventController enventController;
    
    GState gstate(state);
    
    bool displayWindow = true;
    sf::Event event;
    
    render->initTextures();
    
    while(displayWindow){
        enventController.handle(event, engine, render, displayWindow);
        
        if(state->getPlayerTurnId() == 1){
            cpu1.run();
        }
        
        engine->update();

        render->display(gstate);
    }
    return 0;
}
