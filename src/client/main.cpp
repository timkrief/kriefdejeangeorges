#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML


#include "state.h"

using namespace std;
using namespace state;

void testPlayer() {
	// Card import is not yet implemented, this file path is just here for exemple purposes.
	// creation of a fake card list to test the Player class
	Cards cards("res/cards.yaml");
	
	cout << "Test of the static counter of the Player class:" << endl;
	
	Player player(cards);
	
	cout << "Player n°" << player.getId() << endl;
	
	Player player2(cards);
	
	cout << "Player n°" << player2.getId() << endl;
	cout << endl;
	
	cout << "Test of Player's money getters and setters (oil ones are similar):" << endl;
	
	cout << "Setting player's money to -5 (no negative value allowed)" << endl;
	
	player.setMoney(-5.f);
	
	cout << "Player's money: " << player.getMoney() << endl;
	cout << endl;
		
	cout << "Setting player's money to 3.6 (expecting to return only int)" << endl;
	
	player.setMoney(3.6f);
	
	cout << "Player's money: " << player.getMoney() << endl;
	
	
	cout << endl;
}

int main(int argc,char* argv[]) 
{
	testSFML();
	testPlayer();
	
    cout << "Hello world !" << endl;

    return 0;
}
