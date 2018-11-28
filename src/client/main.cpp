#include <iostream>
#include <SFML/Graphics.hpp>
#include "state.h"

using namespace std;
using namespace state;

#include "tests.h"

int main(int argc,char* argv[]) 
{
	testSFML();
	
	Cards cards("./res/cards.yaml","fr");
	
	testPlayer();
    
    std::shared_ptr<Town> town(new Town);
    town->setMoneyProduction(4);
    town->setPosition(sf::Vector2i(10,20));
    
    std::shared_ptr<Player> player1(new Player);
    player1->addOwnedFieldObject(town);
    
    GameState state("./res/maps/map.json", "fr");
    state.addPlayer(player1);
    
    //testMapLoaded(state.getMap());
    testRender(state);
    //testEngine(state);
    return 0;
}
