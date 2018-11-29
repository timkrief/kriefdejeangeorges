#include <iostream>
#include <SFML/Graphics.hpp>
#include "state.h"
#include "render.h"
#include "engine.h"

using namespace std;
using namespace state;
using namespace render;

#include "tests.h"

int main(int argc,char* argv[]) 
{
	testSFML();
	
	Cards cards("./res/cards.yaml","fr");
	
	//testPlayer();
    
    std::shared_ptr<Town> town(new Town);
    town->setMoneyProduction(4);
    town->setPosition(sf::Vector2i(10,20));
    
    std::shared_ptr<Player> player1(new Player);
    player1->addOwnedFieldObject(town);
    
    
    std::shared_ptr<Unit> unit(new Unit);
    unit->setPosition(sf::Vector2i(15,25));
    
    std::shared_ptr<Player> player2(new Player);
    player2->addOwnedFieldObject(unit);
    
    std::shared_ptr<GameState> state(new GameState("./res/maps/map.json", "fr"));
    state->addPlayer(player1);
    state->addPlayer(player2);
    
    //testMapLoaded(state.getMap());
    //testRender(state);
    //testEngine(state);
    
    
    GameEngine engine(state);
    
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
        
        
        engine.update();

        window.clear();
        grender.display(gstate);
    }
    return 0;
}
