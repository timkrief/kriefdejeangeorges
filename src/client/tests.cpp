#include "tests.h"

#include <SFML/Graphics.hpp>
#include <iostream>


void testSFML() {
    sf::Texture texture;
}


void testPlayer(Cards cards) {
	// Card import is not yet implemented, this file path is just here for exemple purposes.
	// creation of a fake card list to test the Player class
	cout << "Test of the static counter of the Player class:" << endl;
	Player player(cards);
	cout << "Player n°" << player.getId() << endl;
	Player player2(cards);
	cout << "Player n°" << player2.getId() << endl << endl;
	cout << "Test of Player's money getters and setters (oil ones are similar):" << endl;
	cout << "Setting player's money to -5 (no negative value allowed)" << endl;
	player.setMoney(-5.f);
	cout << "Player's money: " << player.getMoney() << endl << endl;
	cout << "Setting player's money to 3.6 (expecting to return only int)" << endl;
	player.setMoney(3.6f);
	cout << "Player's money: " << player.getMoney() << endl << endl;
}


int testMapLoaded(Map map) { // rendererPrototype
    int width = 800;
    int height = 600;
    sf::RenderWindow window(sf::VideoMode(width, height), "Test of the map");
    window.setFramerateLimit(60);

    bool displayWindow = true;
    sf::Event event;

    while(displayWindow){
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                displayWindow = false;
            }
        }
        window.clear();
        
        for(unsigned int x = 0; x < map.getSize().x; x++){
            for(unsigned int y = 0; y < map.getSize().y; y++){
                if(map.getData()[x + map.getSize().x * y] != 95){
                    sf::RectangleShape rect;
                    rect.setSize(sf::Vector2f((float)width / (float)map.getSize().x, (float)height / (float)map.getSize().y));
                    rect.setPosition((float)x / (float)map.getSize().x * width , (float)y / (float)map.getSize().y * height);
                    rect.setFillColor(sf::Color::White);

                    window.draw(rect);
                }
            }
        }
        
        window.display();
    }

    window.close();
    return 0;




}
