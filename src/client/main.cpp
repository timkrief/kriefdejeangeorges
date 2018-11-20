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
	
	testPlayer(cards);
    
    GameState state("./res/maps/map.json", "fr");
    
    //testMapLoaded(state.getMap());
    testRender(state);
    return 0;
}
