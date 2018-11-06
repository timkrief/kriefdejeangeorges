#include <iostream>
#include <SFML/Graphics.hpp>
#include "state.h"

using namespace std;
using namespace state;

#include "tests.h"

int main(int argc,char* argv[]) 
{
	testSFML();
	
	Cards cards("res/cards.yaml","fr");
	testPlayer(cards);
	
	Map map("res/maps/map.json");
	
	
    cout << "Hello world !" << endl;

    return testMapLoaded(map);
}
