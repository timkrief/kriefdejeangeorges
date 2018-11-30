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
    std::shared_ptr<Town> town(new Town);
    town->setMoneyProduction(4);
    town->setPosition(sf::Vector2i(10,20));
    
    std::shared_ptr<Player> player1(new Player);
    player1->addOwnedFieldObject(town);
    
    
    std::shared_ptr<Unit> unit(new Unit);
    unit->setPosition(sf::Vector2i(15,25));
    
    std::shared_ptr<Player> player2(new Player);
    player2->addOwnedFieldObject(unit);
    
    
    std::shared_ptr<Unit> unit2(new Unit);
    unit2->setPosition(sf::Vector2i(35,10));
    
    std::shared_ptr<Player> player3(new Player);
    player3->addOwnedFieldObject(unit2);
    
    
    std::shared_ptr<Unit> unit3(new Unit);
    unit3->setPosition(sf::Vector2i(30,20));
    
    std::shared_ptr<Player> player4(new Player);
    player4->addOwnedFieldObject(unit3);
    // end of Creation of players -------
    
    
    std::shared_ptr<GameState> state(new GameState("./res/maps/map.json", "fr"));
    state->addPlayer(player1);
    state->addPlayer(player2);
    state->addPlayer(player3);
    state->addPlayer(player4);
    
    //testMapLoaded(state.getMap());
    //testRender(state);
    //testEngine(state);
    
    
    
    std::shared_ptr<GameEngine> engine(new GameEngine(state));
    
    CPU cpu1(state, engine, 1);
    CPU cpu2(state, engine, 2);
    CPU cpu3(state, engine, 3);
    
    GRender grender;
    EventController enventController;
    
    sf::RenderWindow& window = grender.window;
    
    GState gstate(state);
    
    bool displayWindow = true;
    sf::Event event;
    
     while(displayWindow){
     
        while (window.pollEvent(event)){
            enventController.handle(event, engine, window, displayWindow);
        }
        
        cpu1.run();
        cpu2.run();
        cpu3.run();
        
        engine->update();

        window.clear(sf::Color(44, 146, 206));
        grender.display(gstate);
    }
    return 0;
}
