#include <iostream>
#include <SFML/Graphics.hpp>
#include "state.h"
#include "render.h"

using namespace std;
using namespace state;
using namespace render;

#include "tests.h"

int main(int argc,char* argv[]) 
{
	/*
	testSFML();
	
	Cards cards("res/cards.yaml","fr");
	testPlayer(cards);
	
	Map map("res/maps/map.json");
		
	
    cout << "Hello world !" << endl;

    return testMapLoaded(map);
	*/

	GameState s;
	GRender r;
	//Engine eng; 
	while (1){

		////Event
		//eng.pushCommande();


		////exe
		//eng.execute.all();

		////Display
		r.display(s);


	}



	return 0;

}
